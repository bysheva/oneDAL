/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#include <fstream>

#include "oneapi/dal/data/detail/graph_container.hpp"
#include "oneapi/dal/data/detail/undirected_adjacency_array_graph_impl.hpp"
#include "oneapi/dal/data/graph_common.hpp"
#include "oneapi/dal/data/undirected_adjacency_array_graph.hpp"
#include "oneapi/dal/exceptions.hpp"
#include "oneapi/dal/util/csv_data_source.hpp"
#include "oneapi/dal/util/load_graph_descriptor.hpp"
#include "services/daal_atomic_int.h"
#include "services/daal_memory.h"

namespace oneapi::dal::preview::load_graph::detail {

typedef void (*functype)(int i, const void *a);

extern "C" {
DAAL_EXPORT void _daal_threader_for(int n, int threads_request, const void *a, functype func);
}

template <typename F>
inline void threader_func(int i, const void *a) {
    const F &lambda = *static_cast<const F *>(a);
    lambda(i);
}

template <typename F>
inline void threader_for(int n, int threads_request, const F &lambda) {
    const void *a = static_cast<const void *>(&lambda);

    _daal_threader_for(n, threads_request, a, threader_func<F>);
}

edge_list<std::int32_t> load_edge_list(const std::string &name) {
    using int_t = std::int32_t;

    std::ifstream file(name);
    edge_list<int_t> elist;

    char source_vertex[32], destination_vertex[32];
    while (file >> source_vertex >> destination_vertex) {
        auto edge = std::make_pair(daal::services::daal_string_to_int(&source_vertex[0], 0),
                                   daal::services::daal_string_to_int(&destination_vertex[0], 0));
        elist.push_back(edge);
    }

    file.close();
    return elist;
}

template <typename Graph>
void convert_to_csr_impl(const edge_list<vertex_type<Graph>> &edges, Graph &g) {
    auto layout           = oneapi::dal::preview::detail::get_impl(g);
    using int_t           = typename Graph::vertex_size_type;
    using vertex_t        = typename Graph::vertex_type;
    using vector_vertex_t = typename Graph::vertex_set;
    using vector_edge_t   = typename Graph::edge_set;
    using allocator_t     = typename Graph::allocator_type;
    using vertex_size_t   = typename Graph::vertex_size_type;

    if (edges.size() == 0) {
        layout->_vertex_count = 0;
        layout->_edge_count   = 0;
        throw invalid_argument("Empty edge list");
    }

    Graph g_unfiltred;
    auto layout_unfilt = oneapi::dal::preview::detail::get_impl(g_unfiltred);

    vertex_t max_node_id = edges[0].first;
    for (auto u : edges) {
        vertex_t max_id_in_edge = std::max(u.first, u.second);
        max_node_id             = std::max(max_node_id, max_id_in_edge);
    }

    layout_unfilt->_vertex_count = max_node_id + 1;

    using atomic_t = typename daal::services::Atomic<int_t>;
    using allocator_atomic_t =
        typename std::allocator_traits<allocator_t>::template rebind_alloc<atomic_t>;

    auto *degrees_vec = new (std::nothrow)
        oneapi::dal::preview::detail::graph_container<atomic_t, allocator_atomic_t>(
            layout_unfilt->_vertex_count);
    if (degrees_vec == nullptr) {
        throw bad_alloc();
    }
    daal::services::Atomic<int_t> *degrees_cv = degrees_vec->data();
    if (degrees_cv == nullptr) {
        throw bad_alloc();
    }

    threader_for(layout_unfilt->_vertex_count, layout_unfilt->_vertex_count, [&](int u) {
        degrees_cv[u].set(0);
    });

    threader_for(edges.size(), edges.size(), [&](int u) {
        degrees_cv[edges[u].first].inc();
        degrees_cv[edges[u].second].inc();
    });

    auto *rows_vec = new (std::nothrow)
        oneapi::dal::preview::detail::graph_container<atomic_t, allocator_atomic_t>(
            layout_unfilt->_vertex_count + 1);
    if (rows_vec == nullptr) {
        throw bad_alloc();
    }
    daal::services::Atomic<int_t> *rows_cv = rows_vec->data();
    if (rows_cv == nullptr) {
        throw bad_alloc();
    }

    int_t total_sum_degrees = 0;
    rows_cv[0].set(total_sum_degrees);

    for (vertex_size_t i = 0; i < layout_unfilt->_vertex_count; ++i) {
        total_sum_degrees += degrees_cv[i].get();
        rows_cv[i + 1].set(total_sum_degrees);
    }
    delete degrees_vec;

    layout_unfilt->_vertex_neighbors =
        std::move(vector_vertex_t(rows_cv[layout_unfilt->_vertex_count].get()));
    layout_unfilt->_edge_offsets = std::move(vector_edge_t(layout_unfilt->_vertex_count + 1));
    auto _rows_un                = layout_unfilt->_edge_offsets.data();
    auto _cols_un                = layout_unfilt->_vertex_neighbors.data();

    threader_for(layout_unfilt->_vertex_count + 1, layout_unfilt->_vertex_count + 1, [&](int n) {
        _rows_un[n] = rows_cv[n].get();
    });

    threader_for(edges.size(), edges.size(), [&](int u) {
        _cols_un[rows_cv[edges[u].first].inc() - 1]  = edges[u].second;
        _cols_un[rows_cv[edges[u].second].inc() - 1] = edges[u].first;
    });
    delete rows_vec;

    //removing self-loops,  multiple edges from graph, and make neighbors in CSR sorted

    layout->_vertex_count = layout_unfilt->_vertex_count;

    layout->_degrees = std::move(vector_vertex_t(layout->_vertex_count));

    threader_for(layout_unfilt->_vertex_count, layout_unfilt->_vertex_count, [&](int u) {
        std::sort(layout_unfilt->_vertex_neighbors.begin() + layout_unfilt->_edge_offsets[u],
                  layout_unfilt->_vertex_neighbors.begin() + layout_unfilt->_edge_offsets[u + 1]);
        auto neighs_u_new_end = std::unique(
            layout_unfilt->_vertex_neighbors.begin() + layout_unfilt->_edge_offsets[u],
            layout_unfilt->_vertex_neighbors.begin() + layout_unfilt->_edge_offsets[u + 1]);
        neighs_u_new_end =
            std::remove(layout_unfilt->_vertex_neighbors.begin() + layout_unfilt->_edge_offsets[u],
                        neighs_u_new_end,
                        u);
        layout->_degrees[u] = neighs_u_new_end - (layout_unfilt->_vertex_neighbors.begin() +
                                                  layout_unfilt->_edge_offsets[u]);
    });

    layout->_edge_offsets.clear();
    layout->_edge_offsets.reserve(layout->_vertex_count + 1);

    total_sum_degrees = 0;
    layout->_edge_offsets.push_back(total_sum_degrees);

    for (vertex_size_t i = 0; i < layout->_vertex_count; ++i) {
        total_sum_degrees += layout->_degrees[i];
        layout->_edge_offsets.push_back(total_sum_degrees);
    }
    layout->_edge_count = layout->_edge_offsets[layout->_vertex_count] / 2;

    layout->_vertex_neighbors =
        std::move(vector_vertex_t(layout->_edge_offsets[layout->_vertex_count]));

    threader_for(layout->_vertex_count, layout->_vertex_count, [&](int u) {
        for (vertex_size_t i = 0; i < layout->_degrees[u]; i++) {
            *(layout->_vertex_neighbors.begin() + layout->_edge_offsets[u] + i) =
                *(layout_unfilt->_vertex_neighbors.begin() + layout_unfilt->_edge_offsets[u] + i);
        }
    });

    return;
} // namespace oneapi::dal::preview::load_graph::detail

template <typename Descriptor, typename DataSource>
output_type<Descriptor> load_impl(const Descriptor &desc, const DataSource &data_source) {
    output_type<Descriptor> graph;
    convert_to_csr_impl(load_edge_list(data_source.get_filename()), graph);
    return graph;
}
} // namespace oneapi::dal::preview::load_graph::detail
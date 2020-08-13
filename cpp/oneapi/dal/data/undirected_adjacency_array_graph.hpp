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

#include "oneapi/dal/data/detail/graph_container.hpp"
#include "oneapi/dal/data/detail/undirected_adjacency_array_graph_impl.hpp"
#include "oneapi/dal/data/graph_common.hpp"
#include "services/daal_atomic_int.h"
#include "services/daal_memory.h"
// #include "src/threading/threading.h"

namespace oneapi::dal::preview {

namespace detail {

template <typename G>
typename G::pimpl &get_impl(G &g) {
    return g.impl_;
}

template <typename G>
const typename G::pimpl &get_impl(const G &g) {
    return g.impl_;
}
} // namespace detail

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

template <typename VertexValue = empty_value,
          typename EdgeValue   = empty_value,
          typename GraphValue  = empty_value,
          typename IndexType   = std::int32_t,
          typename Allocator   = std::allocator<empty_value>>
class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph {
public:
    using graph_type =
        undirected_adjacency_array_graph<VertexValue, EdgeValue, GraphValue, IndexType, Allocator>;
    using allocator_type               = Allocator;
    using graph_user_value_type        = GraphValue;
    using const_graph_user_value_type  = const graph_user_value_type;
    using vertex_type                  = IndexType;
    using vertex_user_value_type       = VertexValue;
    using const_vertex_user_value_type = vertex_user_value_type;
    using vertex_key_type              = vertex_type;
    using const_vertex_key_type        = const vertex_key_type;
    using const_vertex_type            = const vertex_type;
    using vertex_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<vertex_type>;
    using vertex_set            = detail::graph_container<vertex_type, vertex_allocator_type>;
    using vertex_iterator       = typename vertex_set::iterator;
    using const_vertex_iterator = typename vertex_set::const_iterator;
    using vertex_size_type      = typename vertex_set::size_type;
    using vertex_user_value_set = detail::graph_container<vertex_user_value_type, allocator_type>;
    using edge_user_value_type  = EdgeValue;
    using edge_type             = IndexType;
    using edge_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<edge_type>;
    using edge_set                   = detail::graph_container<edge_type, edge_allocator_type>;
    using edge_index                 = IndexType;
    using edge_size_type             = typename edge_set::size_type;
    using vertex_edge_size_type      = edge_size_type;
    using edge_iterator              = typename edge_set::iterator;
    using const_edge_iterator        = typename edge_set::const_iterator;
    using vertex_edge_iterator       = typename edge_set::iterator;
    using const_vertex_edge_iterator = typename edge_set::const_iterator;
    using edge_range                 = range<edge_iterator>;
    using const_edge_range           = range<const_edge_iterator>;
    using vertex_edge_range          = range<vertex_edge_iterator>;
    using const_vertex_edge_range    = range<const_vertex_edge_iterator>;
    using edge_key_type              = std::pair<vertex_key_type, vertex_key_type>;
    using edge_value_type            = std::pair<edge_key_type, edge_user_value_type>;
    using edge_value_set = detail::graph_container<edge_user_value_type, allocator_type>;

    undirected_adjacency_array_graph()
            : impl_(new detail::undirected_adjacency_array_graph_impl<VertexValue,
                                                                      EdgeValue,
                                                                      GraphValue,
                                                                      IndexType,
                                                                      Allocator>) {}
    undirected_adjacency_array_graph(undirected_adjacency_array_graph &&graph)      = default;
    undirected_adjacency_array_graph(undirected_adjacency_array_graph const &graph) = default;

    undirected_adjacency_array_graph(allocator_type alloc)
            : impl_(new detail::undirected_adjacency_array_graph_impl<VertexValue,
                                                                      EdgeValue,
                                                                      GraphValue,
                                                                      IndexType,
                                                                      Allocator>(alloc)) {}
    undirected_adjacency_array_graph(graph_user_value_type const &,
                                     allocator_type allocator = allocator_type()){};
    undirected_adjacency_array_graph(graph_user_value_type &&,
                                     allocator_type allocator = allocator_type()){};

    undirected_adjacency_array_graph &operator=(undirected_adjacency_array_graph const &) = default;
    undirected_adjacency_array_graph &operator=(undirected_adjacency_array_graph &&) = default;

    using pimpl =
        oneapi::dal::detail::pimpl<detail::undirected_adjacency_array_graph_impl<VertexValue,
                                                                                 EdgeValue,
                                                                                 GraphValue,
                                                                                 IndexType,
                                                                                 Allocator>>;

private:
    pimpl impl_;

    friend pimpl &detail::get_impl<>(graph_type &g);

    friend const pimpl &detail::get_impl<>(const graph_type &g);
};

template <typename G>
ONEAPI_DAL_EXPORT auto get_vertex_count_impl(const G &g) noexcept -> vertex_size_type<G>;

template <typename G>
ONEAPI_DAL_EXPORT auto get_edge_count_impl(const G &g) noexcept -> edge_size_type<G>;

template <typename G>
ONEAPI_DAL_EXPORT auto get_vertex_degree_impl(const G &g, const vertex_type<G> &vertex) noexcept
    -> vertex_edge_size_type<G>;

template <typename G>
ONEAPI_DAL_EXPORT auto get_vertex_neighbors_impl(const G &g, const vertex_type<G> &vertex) noexcept
    -> const_vertex_edge_range_type<G>;

template <typename G>
ONEAPI_DAL_EXPORT auto get_vertex_count_impl(const G &g) noexcept -> vertex_size_type<G> {
    const auto &layout = detail::get_impl(g);
    return layout->_vertex_count;
}

template <typename G>
ONEAPI_DAL_EXPORT auto get_edge_count_impl(const G &g) noexcept -> edge_size_type<G> {
    const auto &layout = detail::get_impl(g);
    return layout->_edge_count;
}

template <typename G>
ONEAPI_DAL_EXPORT auto get_vertex_degree_impl(const G &g, const vertex_type<G> &vertex) noexcept
    -> vertex_edge_size_type<G> {
    const auto &layout = detail::get_impl(g);
    return layout->_degrees[vertex];
}

template <typename G>
ONEAPI_DAL_EXPORT auto get_vertex_neighbors_impl(const G &g, const vertex_type<G> &vertex) noexcept
    -> const_vertex_edge_range_type<G> {
    const auto &layout = detail::get_impl(g);
    const_vertex_edge_iterator_type<G> vertex_neighbors_begin =
        layout->_vertex_neighbors.begin() + layout->_edge_offsets[vertex];
    const_vertex_edge_iterator_type<G> vertex_neighbors_end =
        layout->_vertex_neighbors.begin() + layout->_edge_offsets[vertex + 1];
    return std::make_pair(vertex_neighbors_begin, vertex_neighbors_end);
}

template <typename G>
void convert_to_csr_impl(const edge_list<vertex_type<G>> &edges, G &g) {
    auto layout           = detail::get_impl(g);
    using int_t           = typename G::vertex_size_type;
    using vertex_t        = typename G::vertex_type;
    using vector_vertex_t = typename G::vertex_set;
    using vector_edge_t   = typename G::edge_set;
    using allocator_t     = typename G::allocator_type;

    if (edges.size() == 0) {
        layout->_vertex_count = 0;
        layout->_edge_count   = 0;
        return;
    }

    G g_unfiltred;
    auto layout_unfilt = detail::get_impl(g_unfiltred);

    vertex_t max_node_id = edges[0].first;
    for (auto u : edges) {
        vertex_t max_id_in_edge = std::max(u.first, u.second);
        max_node_id             = std::max(max_node_id, max_id_in_edge);
    }

    layout_unfilt->_vertex_count = max_node_id + 1;

    using atomic_t = typename daal::services::Atomic<int_t>;
    using allocator_atomic_t =
        typename std::allocator_traits<allocator_t>::template rebind_alloc<atomic_t>;

    auto *degrees_vec =
        new detail::graph_container<atomic_t, allocator_atomic_t>(layout_unfilt->_vertex_count);
    daal::services::Atomic<int_t> *degrees_cv = degrees_vec->data();

    threader_for(layout_unfilt->_vertex_count, layout_unfilt->_vertex_count, [&](int u) {
        degrees_cv[u].set(0);
    });

    threader_for(edges.size(), edges.size(), [&](int u) {
        degrees_cv[edges[u].first].inc();
        degrees_cv[edges[u].second].inc();
    });

    auto *rows_vec =
        new detail::graph_container<atomic_t, allocator_atomic_t>(layout_unfilt->_vertex_count + 1);
    daal::services::Atomic<int_t> *rows_cv = rows_vec->data();

    int_t total_sum_degrees = 0;
    rows_cv[0].set(total_sum_degrees);

    for (size_t i = 0; i < layout_unfilt->_vertex_count; ++i) {
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

    for (size_t i = 0; i < layout->_vertex_count; ++i) {
        total_sum_degrees += layout->_degrees[i];
        layout->_edge_offsets.push_back(total_sum_degrees);
    }
    layout->_edge_count = layout->_edge_offsets[layout->_vertex_count] / 2;

    layout->_vertex_neighbors =
        std::move(vector_vertex_t(layout->_edge_offsets[layout->_vertex_count]));

    threader_for(layout->_vertex_count, layout->_vertex_count, [&](int u) {
        auto neighs = get_vertex_neighbors_impl(g_unfiltred, u);
        for (int_t i = 0; i < get_vertex_degree_impl(g, u); i++) {
            *(layout->_vertex_neighbors.begin() + layout->_edge_offsets[u] + i) =
                *(neighs.first + i);
        }
    });

    return /*ok*/;
}
template <typename VertexValue = empty_value,
          typename EdgeValue   = empty_value,
          typename GraphValue  = empty_value,
          typename IndexType   = std::int32_t,
          typename Allocator   = std::allocator<empty_value>>
using undirected_adjacency_array =
    undirected_adjacency_array_graph<VertexValue, EdgeValue, GraphValue, IndexType, Allocator>;

using graph = undirected_adjacency_array<>;

} // namespace oneapi::dal::preview

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
#include "oneapi/dal/data/detail/graph_service_functions_impl.hpp"
#include "oneapi/dal/data/detail/undirected_adjacency_array_graph_impl.hpp"
#include "oneapi/dal/data/graph_common.hpp"

namespace oneapi::dal::preview {

template <typename VertexValue = empty_value,
          typename EdgeValue   = empty_value,
          typename GraphValue  = empty_value,
          typename IndexType   = std::int32_t,
          typename Allocator   = std::allocator<char>>
class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph {
public:
    using graph_type =
        undirected_adjacency_array_graph<VertexValue, EdgeValue, GraphValue, IndexType, Allocator>;
    using allocator_type = Allocator;

    // graph weight types
    using graph_user_value_type       = GraphValue;
    using const_graph_user_value_type = const graph_user_value_type;

    // vertex types
    using vertex_type       = IndexType;
    using const_vertex_type = const vertex_type;
    using vertex_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<vertex_type>;
    using vertex_set            = detail::graph_container<vertex_type, vertex_allocator_type>;
    using vertex_iterator       = typename vertex_set::iterator;
    using const_vertex_iterator = typename vertex_set::const_iterator;
    using vertex_size_type      = typename vertex_set::size_type;

    using vertex_key_type       = vertex_type;
    using const_vertex_key_type = const vertex_key_type;

    // vertex weight types
    using vertex_user_value_type       = VertexValue;
    using const_vertex_user_value_type = const vertex_user_value_type;
    using vertex_user_value_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<vertex_user_value_type>;
    using vertex_user_value_set =
        detail::graph_container<vertex_user_value_type, vertex_user_value_allocator_type>;

    // edge types
    using edge_type = IndexType;
    using edge_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<edge_type>;
    using edge_set            = detail::graph_container<edge_type, edge_allocator_type>;
    using edge_iterator       = typename edge_set::iterator;
    using const_edge_iterator = typename edge_set::const_iterator;
    using edge_size_type      = typename edge_set::size_type;

    // edge weight types
    using edge_user_value_type = EdgeValue;
    using edge_user_value_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<edge_user_value_type>;
    using edge_user_value_set =
        detail::graph_container<edge_user_value_type, edge_user_value_allocator_type>;

    using edge_key_type   = std::pair<vertex_key_type, vertex_key_type>;
    using edge_value_type = std::pair<edge_key_type, edge_user_value_type>;
    using edge_index      = IndexType;

    // vertex edge types
    using vertex_edge_size_type      = edge_size_type;
    using vertex_edge_iterator       = typename edge_set::iterator;
    using const_vertex_edge_iterator = typename edge_set::const_iterator;

    // ranges
    using edge_range              = range<edge_iterator>;
    using const_edge_range        = range<const_edge_iterator>;
    using vertex_edge_range       = range<vertex_edge_iterator>;
    using const_vertex_edge_range = range<const_vertex_edge_iterator>;

    undirected_adjacency_array_graph()
            : impl_(new detail::undirected_adjacency_array_graph_impl<VertexValue,
                                                                      EdgeValue,
                                                                      GraphValue,
                                                                      IndexType,
                                                                      Allocator>) {}
    undirected_adjacency_array_graph(undirected_adjacency_array_graph &&graph)      = default;
    undirected_adjacency_array_graph(const undirected_adjacency_array_graph &graph) = default;

    undirected_adjacency_array_graph(allocator_type alloc)
            : impl_(new detail::undirected_adjacency_array_graph_impl<VertexValue,
                                                                      EdgeValue,
                                                                      GraphValue,
                                                                      IndexType,
                                                                      Allocator>(alloc)) {}
    undirected_adjacency_array_graph(const graph_user_value_type &graph_user_value,
                                     allocator_type allocator = allocator_type()){};
    undirected_adjacency_array_graph(graph_user_value_type &&graph_user_value,
                                     allocator_type allocator = allocator_type()){};

    undirected_adjacency_array_graph &operator=(const undirected_adjacency_array_graph &graph) =
        default;
    undirected_adjacency_array_graph &operator=(undirected_adjacency_array_graph &&graph) = default;

    using pimpl =
        oneapi::dal::detail::pimpl<detail::undirected_adjacency_array_graph_impl<VertexValue,
                                                                                 EdgeValue,
                                                                                 GraphValue,
                                                                                 IndexType,
                                                                                 Allocator>>;

private:
    pimpl impl_;

    friend pimpl &detail::get_impl<graph_type>(graph_type &graph);

    friend const pimpl &detail::get_impl<graph_type>(const graph_type &graph);
};
namespace detail {
template <typename Graph>
ONEAPI_DAL_EXPORT auto get_vertex_count_impl(const Graph &g) noexcept -> vertex_size_type<Graph>;

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_edge_count_impl(const Graph &g) noexcept -> edge_size_type<Graph>;

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_vertex_degree_impl(const Graph &g,
                                              const vertex_type<Graph> &vertex) noexcept
    -> vertex_edge_size_type<Graph>;

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_vertex_neighbors_impl(const Graph &g,
                                                 const vertex_type<Graph> &vertex) noexcept
    -> const_vertex_edge_range_type<Graph>;

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_vertex_count_impl(const Graph &g) noexcept -> vertex_size_type<Graph> {
    const auto &layout = detail::get_impl(g);
    return layout->_vertex_count;
}

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_edge_count_impl(const Graph &g) noexcept -> edge_size_type<Graph> {
    const auto &layout = detail::get_impl(g);
    return layout->_edge_count;
}

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_vertex_degree_impl(const Graph &g,
                                              const vertex_type<Graph> &vertex) noexcept
    -> vertex_edge_size_type<Graph> {
    const auto &layout = detail::get_impl(g);
    return layout->_degrees[vertex];
}

template <typename Graph>
ONEAPI_DAL_EXPORT auto get_vertex_neighbors_impl(const Graph &g,
                                                 const vertex_type<Graph> &vertex) noexcept
    -> const_vertex_edge_range_type<Graph> {
    const auto &layout = detail::get_impl(g);
    const_vertex_edge_iterator_type<Graph> vertex_neighbors_begin =
        layout->_vertex_neighbors.begin() + layout->_edge_offsets[vertex];
    const_vertex_edge_iterator_type<Graph> vertex_neighbors_end =
        layout->_vertex_neighbors.begin() + layout->_edge_offsets[vertex + 1];
    return std::make_pair(vertex_neighbors_begin, vertex_neighbors_end);
}
} // namespace detail
template <typename VertexValue = empty_value,
          typename EdgeValue   = empty_value,
          typename GraphValue  = empty_value,
          typename IndexType   = std::int32_t,
          typename Allocator   = std::allocator<empty_value>>
using undirected_adjacency_array =
    undirected_adjacency_array_graph<VertexValue, EdgeValue, GraphValue, IndexType, Allocator>;

using graph = undirected_adjacency_array<>;

} // namespace oneapi::dal::preview

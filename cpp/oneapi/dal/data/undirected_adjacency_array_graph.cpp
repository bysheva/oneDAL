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

#include "oneapi/dal/data/undirected_adjacency_array_graph.hpp"

namespace oneapi::dal::preview {

// template <typename VertexValue,
//           typename EdgeValue,
//           typename GraphValue,
//           typename IndexType,
//           typename Allocator>
// undirected_adjacency_array_graph<VertexValue, EdgeValue, GraphValue, IndexType, Allocator>::
//     undirected_adjacency_array_graph()
//         : impl_(new detail::undirected_adjacency_array_graph_impl<VertexValue,
//                                                                   EdgeValue,
//                                                                   GraphValue,
//                                                                   IndexType,
//                                                                   Allocator>) {}

// template <typename VertexValue,
//           typename EdgeValue,
//           typename GraphValue,
//           typename IndexType,
//           typename Allocator>
// undirected_adjacency_array_graph<VertexValue, EdgeValue, GraphValue, IndexType, Allocator>::
//     undirected_adjacency_array_graph(allocator_type alloc)
//         : impl_(new detail::undirected_adjacency_array_graph_impl<VertexValue,
//                                                                   EdgeValue,
//                                                                   GraphValue,
//                                                                   IndexType,
//                                                                   Allocator>(alloc)) {}

template class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph<empty_value,
                                                                  empty_value,
                                                                  empty_value,
                                                                  std::int32_t,
                                                                  std::allocator<empty_value>>;

using graph32 = undirected_adjacency_array_graph<empty_value,
                                                 empty_value,
                                                 empty_value,
                                                 std::int32_t,
                                                 std::allocator<empty_value>>;

// template ONEAPI_DAL_EXPORT void convert_to_csr_impl(const edge_list<vertex_type<graph32>> &edges,
//                                                     graph32 &g);

} // namespace oneapi::dal::preview

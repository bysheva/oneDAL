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
#include <immintrin.h>
#include <iostream>

#include "oneapi/dal/algo/jaccard/backend/cpu/vertex_similarity_default_kernel.hpp"
#include "oneapi/dal/algo/jaccard/common.hpp"
#include "oneapi/dal/algo/jaccard/vertex_similarity_types.hpp"
#include "oneapi/dal/backend/dispatcher.hpp"
#include "oneapi/dal/backend/interop/common.hpp"
#include "oneapi/dal/backend/interop/table_conversion.hpp"
#include "oneapi/dal/data/graph_service_functions.hpp"
#include "oneapi/dal/policy.hpp"

namespace oneapi::dal::preview {
namespace jaccard {
namespace detail {

template <>
similarity_result call_jaccard_block_kernel<undirected_adjacency_array_graph<>,
                                            oneapi::dal::backend::cpu_dispatch_avx512>(
    const descriptor_base &desc,
    similarity_input<undirected_adjacency_array_graph<>> &input) {
    std::cout << "Hi! I am avx512 specialization!" << std::endl;

    const auto my_graph = input.get_graph();

    std::cout << oneapi::dal::preview::detail::get_vertex_count_impl(my_graph) << std::endl;
    std::cout << oneapi::dal::preview::detail::get_edge_count_impl(my_graph) << std::endl;
    auto node_id = 0;
    std::cout << "degree of " << node_id << ": "
              << oneapi::dal::preview::detail::get_vertex_degree_impl(my_graph, node_id)
              << std::endl;
    for (unsigned int j = 0; j < oneapi::dal::preview::detail::get_vertex_count_impl(my_graph);
         ++j) {
        std::cout << "neighbors of " << j << ": ";
        auto neigh = oneapi::dal::preview::detail::get_vertex_neighbors_impl(my_graph, j);
        for (auto i = neigh.first; i != neigh.second; ++i)
            std::cout << *i << " ";
        std::cout << std::endl;
    }
    const auto row_begin                = desc.get_row_range_begin();
    const auto row_end                  = desc.get_row_range_end();
    const auto column_begin             = desc.get_column_range_begin();
    const auto column_end               = desc.get_column_range_end();
    const auto number_elements_in_block = (row_end - row_begin) * (column_end - column_begin);

    int *vertex1                        = reinterpret_cast<int *>(input.get_result_ptr());
    int *vertex2                        = vertex1 + number_elements_in_block;
    float *jaccard = reinterpret_cast<float *>(vertex1 + 2 * number_elements_in_block);
    int64_t nnz    = 0;
    for (auto i = row_begin; i < row_end; ++i) {
        const auto i_neighbor_size =
            oneapi::dal::preview::detail::get_vertex_degree_impl(my_graph, i);
        const auto i_neigbhors =
            oneapi::dal::preview::detail::get_vertex_neighbors_impl(my_graph, i).first;
        for (auto j = column_begin; j < column_end; ++j) {
            if (j == i)
                continue;
            const auto j_neighbor_size =
                oneapi::dal::preview::detail::get_vertex_degree_impl(my_graph, j);
            const auto j_neigbhors =
                oneapi::dal::preview::detail::get_vertex_neighbors_impl(my_graph, j).first;
            size_t intersection_value = 0;
            size_t i_u = 0, i_v = 0;
            //__m512i v_u   = _mm512_loadu_si512((void *)(i_neigbhors + i_u)); // load 16 neighbors of u
            while (i_u < i_neighbor_size && i_v < j_neighbor_size) {
                if (i_neigbhors[i_u] == j_neigbhors[i_v])
                    intersection_value++, i_u++, i_v++;
                else if (i_neigbhors[i_u] < j_neigbhors[i_v])
                    i_u++;
                else if (i_neigbhors[i_u] > j_neigbhors[i_v])
                    i_v++;
            }
            if (intersection_value == 0)
                continue;
            const auto union_size = i_neighbor_size + j_neighbor_size - intersection_value;
            if (union_size == 0)
                continue;
            jaccard[nnz] = float(intersection_value) / float(union_size);
            vertex1[nnz] = i;
            vertex2[nnz] = j;
            nnz++;
        }
    }
    //similarity_result res;

    similarity_result res(
        homogen_table_builder{}
            .reset(array(vertex1, 2 * number_elements_in_block, empty_delete<const int>()),
                   2,
                   number_elements_in_block)
            .build(),
        homogen_table_builder{}
            .reset(array(jaccard, number_elements_in_block, empty_delete<const float>()),
                   1,
                   number_elements_in_block)
            .build(),
        nnz);

    /*
    similarity_result res(homogen_table(2, number_elements_in_block, vertex1),
                          homogen_table(1, number_elements_in_block, jaccard), nnz);*/
    std::cout << "Jaccard block kernel ended" << std::endl;
    return res;
}

#define INSTANTIATE(cpu)                                                                           \
    template similarity_result call_jaccard_block_kernel<undirected_adjacency_array_graph<>, cpu>( \
        const descriptor_base &desc,                                                               \
        similarity_input<undirected_adjacency_array_graph<>> &input);

INSTANTIATE(oneapi::dal::backend::cpu_dispatch_avx512)
} // namespace detail
} // namespace jaccard
} // namespace oneapi::dal::preview

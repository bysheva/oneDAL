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

#include <vector>
#include "oneapi/dal/data/graph.hpp"
#include "oneapi/dal/util/load_graph.hpp"

using namespace oneapi::dal;
using namespace oneapi::dal::preview;

int main(int argc, char ** argv)
{
    std::vector<int32_t> columns { 0, 1, 3, 0, 1, 2, 3, 4, 0, 2, 3, 1, 4 };
    std::vector<int32_t> row_index { 0, 3, 5, 8, 11, 13 };

    csr_arrays_to_csr_descriptor d;
    auto vertices_neighbors = array<int32_t>::wrap(columns.data(), columns.size());
    auto edges_offsets      = array<int32_t>::wrap(row_index.data(), row_index.size());

    auto my_graph = create_graph<graph>(d, vertices_neighbors, edges_offsets);
    return 0;
}

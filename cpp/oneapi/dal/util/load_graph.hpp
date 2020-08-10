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

#include "oneapi/dal/data/graph.hpp"
#include "oneapi/dal/util/csv_data_source.hpp"

#include <chrono>
#include <iostream>

namespace oneapi::dal::preview {

struct edge_list_to_csr_descriptor {};

namespace detail {
template <typename IndexT>
edge_list<IndexT> load(const std::string &name);
}

template <typename G, typename Descriptor, typename DataSource>
G load_graph(const Descriptor &d, const DataSource &ds) {
    G graph_data;

    std::chrono::steady_clock::time_point begin_read = std::chrono::steady_clock::now();
    const auto &edges = detail::load<typename G::vertex_type>(ds.get_filename());
    std::chrono::steady_clock::time_point end_read = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point begin_construct = std::chrono::steady_clock::now();
    convert_to_csr(edges, graph_data);
    std::chrono::steady_clock::time_point end_construct = std::chrono::steady_clock::now();

    std::cout << "Time difference read = "
              << std::chrono::duration_cast<std::chrono::seconds>(end_read - begin_read).count()
              << "[s]" << std::endl;
    std::cout
        << "Time difference construct = "
        << std::chrono::duration_cast<std::chrono::seconds>(end_construct - begin_construct).count()
        << "[s]" << std::endl;

    return graph_data;
}
} // namespace oneapi::dal::preview

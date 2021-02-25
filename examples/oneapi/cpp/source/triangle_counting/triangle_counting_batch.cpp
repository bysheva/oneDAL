/*******************************************************************************
* Copyright 2020-2021 Intel Corporation
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

#include <memory>
#include <chrono>

#include "example_util/utils.hpp"
#include "oneapi/dal/algo/triangle_counting.hpp"
#include "oneapi/dal/graph/undirected_adjacency_vector_graph.hpp"
#include "oneapi/dal/io/graph_csv_data_source.hpp"
#include "oneapi/dal/io/load_graph.hpp"

namespace dal = oneapi::dal;
using namespace dal::preview::triangle_counting;
using namespace std::chrono;

int main(int argc, char** argv) {
    const auto filename = get_data_path("graph.csv");

    // read the graph
    const dal::preview::graph_csv_data_source ds(filename);
    int num_trials = 1;
    const dal::preview::load_graph::descriptor<> d;
    const auto my_graph = dal::preview::load_graph::load(d, ds);
    std::allocator<char> alloc;
    // set algorithm parameters
    std::cout << "Global TC relabel: " << std::endl;

    for (int i = 0; i < num_trials; i++) {
    auto start = high_resolution_clock::now();
    const auto tc_desc =
        descriptor<float, method::ordered_count, task::global, std::allocator<char>>(alloc)
            .set_relabel(relabel::yes);

    // compute local and global triangles
    const auto result_vertex_ranking = dal::preview::vertex_ranking(tc_desc, my_graph);
    auto stop = high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() << std::endl;
    // extract the result
    std::cout << "Global triangles: " << result_vertex_ranking.get_global_rank() << std::endl;
    }

    std::cout << "Global TC no relabel: " << std::endl;

    for (int i = 0; i < num_trials; i++) {

    auto start = high_resolution_clock::now();
    const auto tc_desc =
        descriptor<float, method::ordered_count, task::global, std::allocator<char>>(alloc)
            .set_relabel(relabel::no);

    const auto result_vertex_ranking = dal::preview::vertex_ranking(tc_desc, my_graph);
    auto stop = high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() << std::endl;

    std::cout << "Global triangles: " << result_vertex_ranking.get_global_rank() << std::endl;
    }
    
    std::cout << "Local TC relabel: " << std::endl;

    for (int i = 0; i < num_trials; i++) {

    auto start = high_resolution_clock::now();
    const auto tc_desc =
        descriptor<float, method::ordered_count, task::local, std::allocator<char>>(alloc)
            .set_relabel(relabel::yes);

    const auto result_vertex_ranking = dal::preview::vertex_ranking(tc_desc, my_graph);
    auto stop = high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() << std::endl;

    std::int64_t checksum = 0;

    auto local_triangles_table = result_vertex_ranking.get_ranks();
    const auto& local_triangles = static_cast<const dal::homogen_table&>(local_triangles_table);
    const auto local_triangles_data = local_triangles.get_data<std::int64_t>();
    for (auto i = 0; i < local_triangles_table.get_row_count(); i++) {
        checksum += local_triangles_data[i];
    }

    std::cout << "Local triangle schecksum: " << checksum << std::endl;
    }

    for (int i = 0; i < num_trials; i++) {

    auto start = high_resolution_clock::now();
    const auto tc_desc =
        descriptor<float, method::ordered_count, task::local_and_global, std::allocator<char>>(alloc)
            .set_relabel(relabel::yes);

    const auto result_vertex_ranking = dal::preview::vertex_ranking(tc_desc, my_graph);
    auto stop = high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() << std::endl;

    std::int64_t checksum = 0;

    auto local_triangles_table = result_vertex_ranking.get_ranks();
    const auto& local_triangles = static_cast<const dal::homogen_table&>(local_triangles_table);
    const auto local_triangles_data = local_triangles.get_data<std::int64_t>();
    for (auto i = 0; i < local_triangles_table.get_row_count(); i++) {
        checksum += local_triangles_data[i];
    }

    std::cout << "Local triangle schecksum (local and global): " << checksum << std::endl;
    }

    return 0;
}

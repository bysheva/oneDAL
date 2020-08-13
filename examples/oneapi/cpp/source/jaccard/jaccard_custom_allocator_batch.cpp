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

#include <iostream>

#include "oneapi/dal/algo/jaccard.hpp"
#include "oneapi/dal/data/table.hpp"
#include "oneapi/dal/data/undirected_adjacency_array_graph.hpp"
#include "oneapi/dal/util/csv_data_source.hpp"
#include "oneapi/dal/util/load_graph.hpp"

using namespace oneapi::dal;
using namespace oneapi::dal::preview;

template <class T>
struct Mallocator {
    typedef T value_type;

    Mallocator() = default;
    template <class U>
    constexpr Mallocator(const Mallocator<U>&) noexcept {}

    [[nodiscard]] T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_alloc();

        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            report(p, n);
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n) noexcept {
        report(p, n, 0);
        std::free(p);
    }

private:
    void report(T* p, std::size_t n, bool alloc = true) const {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n << " bytes at " << std::hex
                  << std::showbase << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

using my_own_graph_t = undirected_adjacency_array_graph<empty_value,
                                                        empty_value,
                                                        empty_value,
                                                        std::int32_t,
                                                        Mallocator<int>>;

int main(int argc, char** argv) {
    if (argc < 2)
        return 0;
    std::string filename = argv[1];
    csv_data_source ds(filename);

    using my_desc_t = load_graph::descriptor<edge_list<int32_t>, my_own_graph_t>;

    my_desc_t d;
    auto my_graph = load_graph::load<my_desc_t, csv_data_source>(d, ds);

    const auto jaccard_desc_default = jaccard::descriptor<>().set_block({ 0, 2 }, { 0, 3 });

    auto result_default = vertex_similarity(jaccard_desc_default, my_graph);

    auto jaccard      = result_default.get_coeffs();
    auto vertex_pairs = result_default.get_vertex_pairs();

    std::cout << "Number of non-zero coefficients in block =" << jaccard.get_size() << std::endl;
    std::cout << "Jaccard indices:" << std::endl;
    for (auto i = 0; i < jaccard.get_size(); ++i) {
        std::cout << "Pair: (" << vertex_pairs[i].first << "," << vertex_pairs[i].second
                  << ")\tcoefficient: " << jaccard[i] << std::endl;
    }
}

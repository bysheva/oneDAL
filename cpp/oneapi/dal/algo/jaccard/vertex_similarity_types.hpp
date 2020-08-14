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

#include "oneapi/dal/algo/jaccard/common.hpp"
#include "oneapi/dal/data/table.hpp"
#include "oneapi/dal/data/undirected_adjacency_array_graph.hpp"

namespace oneapi::dal::preview {
namespace jaccard {

namespace detail {
template <typename Graph>
class similarity_input_impl;
class similarity_result_impl;
} // namespace detail

template <typename Graph>
class ONEAPI_DAL_EXPORT similarity_input {
public:
    similarity_input(const Graph &g, void *result_ptr);
    const Graph &get_graph() const;
    void *get_result_ptr();

private:
    dal::detail::pimpl<detail::similarity_input_impl<Graph>> impl_;
};

class ONEAPI_DAL_EXPORT similarity_result {
public:
    similarity_result(){};
    similarity_result(const table &vertex_pairs, const table &coeffs, int64_t &nonzero_coeff_count);
    table get_coeffs() const;
    table get_vertex_pairs() const;
    int64_t get_nonzero_coeff_count() const;

private:
    dal::detail::pimpl<detail::similarity_result_impl> impl_;
};
} // namespace jaccard
} // namespace oneapi::dal::preview

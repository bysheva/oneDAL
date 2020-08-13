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

#include "oneapi/dal/algo/jaccard/common.hpp"
#include "oneapi/dal/algo/jaccard/vertex_similarity_types.hpp"

namespace oneapi::dal::preview {
namespace jaccard {
namespace detail {
template <typename Graph>
class similarity_input_impl : public base {
public:
    similarity_input_impl(const Graph &graph_data_input) : graph_data(graph_data_input) {}

    const Graph &graph_data;
};

} // namespace detail
} // namespace jaccard
} // namespace oneapi::dal::preview

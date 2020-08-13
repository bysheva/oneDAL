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

#include "oneapi/dal/algo/jaccard/backend/cpu/select_kernel.hpp"
#include "oneapi/dal/backend/dispatcher.hpp"

namespace oneapi::dal::preview {
namespace jaccard {
namespace detail {

template <typename Graph, typename Cpu>
extern similarity_result call_jaccard_block_kernel(const descriptor_base &desc,
                                                   const similarity_input<Graph> &input);

template <typename Float, typename Method, typename Graph>
similarity_result backend_default<Float, Method, Graph>::operator()(
    const dal::backend::context_cpu &ctx,
    const descriptor_base &desc,
    const similarity_input<Graph> &input) {
    return dal::backend::dispatch_by_cpu(ctx, [&](auto cpu) {
        return call_jaccard_block_kernel<Graph, decltype(cpu)>(desc, input);
    });
}

} // namespace detail
} // namespace jaccard
} // namespace oneapi::dal::preview

// Student Practice C++: Prefix tree
// Copyright 2025 AlexBurnes@gmail.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <benchmark/benchmark.h>

#include <malloc.h>

#include <cstring>
#include <prefix.hpp>
#include <vector>

#include "prefixes.hpp"

benchmark::IterationCount g_num_new = 0;
benchmark::IterationCount g_sum_size_new = 0;
benchmark::IterationCount g_max_size_new = 0;
benchmark::IterationCount g_min_size_new = -1;
auto                      new_hook = [](const void*, size_t size) {
    ++g_num_new;
    g_sum_size_new += size;
    g_max_size_new = std::max((long int)g_max_size_new, (long int)size);
    g_min_size_new = std::min((long int)g_min_size_new, (long int)size);
};

#define BENCH_MEM_BEFORE_TEST                                \
    benchmark::IterationCount num_new = g_num_new;           \
    benchmark::IterationCount sum_size_new = g_sum_size_new; \
    g_max_size_new = 0;                                      \
    g_min_size_new = -1;                                     \
    MallocHook::AddNewHook(new_hook);

#define BENCH_MEM_AFTER_TEST                                                                      \
    MallocHook::RemoveNewHook(new_hook);                                                          \
    auto iter = state.iterations();                                                               \
    state.counters["#new"] = (g_num_new - num_new) / iter;                                        \
    state.counters["sum_new_B"] = (g_sum_size_new - sum_size_new) / iter;                         \
    state.counters["avg_new_B"] =                                                                 \
        (g_num_new - num_new) == 0 ? 0 : (g_sum_size_new - sum_size_new) / (g_num_new - num_new); \
    state.counters["max_new_B"] = g_max_size_new;                                                 \
    if (((benchmark::IterationCount) - 1) != g_min_size_new) {                                    \
        state.counters["min_new_B"] = g_min_size_new;                                             \
    }

namespace bm = benchmark;

unsigned int seed = time(nullptr);

static void prefix_search(bm::State& state) {

    auto count = static_cast<size_t>(state.range(0));
    std::srand(seed);

    prefix::Prefix<int> prefixes;
    init_prefixes(prefixes);

    for (auto _ : state) {
        auto value = prefixes.Search("250019120223473");
        // bm::DoNotOptimize(keys.size());
    }
    state.SetComplexityN(count);
    state.SetItemsProcessed(count * state.iterations());
    state.SetBytesProcessed(count * state.iterations() * sizeof(int32_t) * 2);

}

BENCHMARK(prefix_search)->Args({size_t(1e6)});

# Student Practice C++: Prefix tree
# Copyright 2025 AlexBurnes@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_executable(
    test_prefix_tree
        test.cpp
        prefixes.cpp
)

target_compile_options(
    test_prefix_tree
    PRIVATE
        -coverage
        -O0
)

target_link_libraries(
    test_prefix_tree
    PRIVATE
            fmt::fmt
            GTest::gtest_main
)

target_link_options(
    test_prefix_tree
    PRIVATE
        -coverage
)

add_test(
    NAME test_prefix_tree
    COMMAND $<TARGET_FILE:test_prefix_tree>
)

add_executable(
    test_bench
        bench.cpp
        prefixes.cpp
)

target_link_libraries(
    test_bench
        PRIVATE
            fmt::fmt
            benchmark::benchmark_main
            #gperftools::gperftools
)


install(
    TARGETS
        test_prefix_tree
        test_bench
    RUNTIME DESTINATION bin
)

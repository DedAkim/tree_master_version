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

cmake_minimum_required(VERSION 3.20)
project(prefix_tree CXX)

include(CTest)

include(cmake/modules.cmake)

include(pedantic)

find_package(fmt REQUIRED)
find_package(GTest)
find_package(gperftools)
find_package(benchmark)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto -ffat-lto-objects -fuse-linker-plugin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -ffat-lto-objects -fuse-linker-plugin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-lto")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-lto")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-lto")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fno-lto")

include(sparsepp.cmake)

enable_testing()

add_subdirectory(src)



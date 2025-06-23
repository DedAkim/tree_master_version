# Collection of cmake modules and macroses used to build C++ projects
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

macro(define_parallel_degree)
    if(WIN32)
        execute_process(
            COMMAND
                wmic "cpu" "get" "NumberOfCores"
            OUTPUT_VARIABLE
                _number_of_cpu
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if (NOT ${_number_of_cpu})
            set(_number_of_cpu 1)
        endif()
    else()
        execute_process(
            COMMAND
                bash "-c" "cat /proc/cpuinfo | grep processor | wc | awk '{print \$1}'"
            OUTPUT_VARIABLE
                _number_of_cpu
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if (NOT ${_number_of_cpu})
            set(_number_of_cpu 1)
        endif()
    endif()

    set(_core_ratio 4)
    if (${_number_of_cpu} GREATER 1 AND ${_number_of_cpu} LESS ${_core_ratio})
        MATH(EXPR _number_of_cpu "${_number_of_cpu} - 1")
    endif()

    if (${_number_of_cpu} GREATER_EQUAL 4)
        MATH(EXPR _number_of_cpu "${_number_of_cpu} - ${_number_of_cpu} / ${_core_ratio}")
    endif()

    lr("Number of cpu ${_number_of_cpu}, set CMAKE_BUIL_PARALLEL_LEVEL")

    set(CMAKE_BUILD_PARALLEL_LEVEL ${_number_of_cpu})

    # Define Ninja job pool
    set_property(GLOBAL PROPERTY JOB_POOLS single_job=1 parallel_jobs=${CMAKE_BUILD_PARALLEL_LEVEL})
    set(CMAKE_JOB_POOL_COMPILE parallel_jobs)
    set(CMAKE_JOB_POOL_LINK parallel_jobs)

endmacro()

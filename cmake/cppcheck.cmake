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

# run cppcheck while compile source code cppeck could be assing 
# in CMAKE_CXX_CPPCHECK for example /usr/local/bin/cppcheck 

if ("${CMAKE_CXX_CPPCHECK}" STREQUAL "")
    find_program(CPPCHECK NAMES cppcheck)
    if (NOT (CPPCHECK MATCHES "NOTFOUND"))
        set(CMAKE_CXX_CPPCHECK "${CPPCHECK}")
    endif()
endif()
message("CMAKE_CXX_CPPCHECK=${CMAKE_CXX_CPPCHECK}")
if (NOT ("${CMAKE_CXX_CPPCHECK}" STREQUAL ""))
    message("run static code analisys tool ${CMAKE_CXX_CPPCHECK}")
    set(
        CMAKE_CXX_CPPCHECK 
            "${CMAKE_CXX_CPPCHECK}"
            "--enable=all"
            "--suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck_suppress.txt"
            "--include=${PROJECT_SOURCE_DIR}/cppcheck_include.txt"
            "--error-exitcode=1"
            "--check-level=exhaustive"
            "-rp=${PROJECT_SOURCE_DIR}"
    )
endif()
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

option(CMAKE_DEBUG "log debug mode" OFF)

macro(lg _text)
    message("${_text}")
endmacro()

macro(lr _text)
    message(STATUS "${Bold}${_text}${Reset}")
endmacro()

macro(ld _text)
    if(CMAKE_DEBUG)
        string(REPLACE "${PROJECT_SOURCE_DIR}" "." _LIST_FILE "${CMAKE_CURRENT_LIST_FILE}")
        message("${Yellow}DEBUG: ${_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ${_text}${Reset}")
    endif()
endmacro()

macro(le _text)
    message(SEND_ERROR "${Red}${_text}${Reset}")
endmacro()

macro(lf _text)
    message(FATAL_ERROR "${Red}${Bold}${_text}${Reset}")
endmacro()

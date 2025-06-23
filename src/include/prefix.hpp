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

#pragma once

#include <fmt/core.h>

#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "sparsepp/spp.h"

//!@namespace prefix
namespace prefix {

    //!@class Prefix<T>
    //!@note Imlements prefix search tree algorigthm, search values belonging to numeric range or numeric prefix.
    //!| The algorithm expands the range of numbers into a prefix tree.
    //!| Number ranges must have the following properties:
    //!|   - A small range can clarify a larger range if overlapping is permitted, but intersection of ranges is not
    //!|     permitted.
    //!|   - Search returns the value belonging to the smallest range.
    //!|   - Ranges must be added in sorted order, largest range first, then smaller range, or the order must be
    //!|     ensured in the implementation of the addition ranges into the search structure.
    //!|   - Number ranges must be the same length.

    template <typename Value>
    class Prefix {
        public:
            //!@typedef value_t, value type
            typedef Value value_t;
            //!@typedef value_ptr, value pointer
            typedef std::shared_ptr<value_t> value_ptr;

        
            //!@typedef hash_t, map<key, values> prefixes map, key is a prefix part of a range, values is list of
            //!| values defined by range
            typedef spp::sparse_hash_map<std::string, std::vector<value_ptr>> hash_t;
            //!@typedef hash_ptr, shared pointer to prefixes map
            // FIXME replace by unique ptr
            typedef std::shared_ptr<hash_t> hash_ptr;
            //!@typedef length_keys_pair_t pair<prefix length, prefixes map> prefixes pairs
            typedef std::pair<size_t, hash_ptr> length_keys_pair_t;

            //!@class length_key_cmp, comparer for ordering search structure of prefixes lengthes
            struct length_key_cmp {
                    bool operator()(const size_t& lhs, const size_t& rhs) const { return lhs > rhs; }
            };

            //!@typedef length_keys_t, map<prefixes length, prefixes map, length comparer>
            typedef std::map<size_t, hash_ptr, length_key_cmp> length_keys_t;
            //!@typedef search_t, vector of prefixes pairs
            typedef std::vector<length_keys_pair_t> search_t;

            //!@member keys, prefixes map
            hash_ptr keys;

            //!@member search unique_ptr, prefixes tree search structure - array of key lengthes in descent order
            //!| referenced to prefixes map
            std::unique_ptr<search_t> search;

            //!@member builede bool, flags shows that search structure is builded after added ranges, require to build
            //!| before call check and search
            bool builded;

            //!@fn add, add prefix to keys referenced to value pointer
            //!@param prefix string
            //!@param value shared_ptr, pointer to value
            //!@param overlap bool, overlapping ranges permition:
            //!| true allow
            //!| false forbidden
            //!@param check bool, check search structure after insert a prefix
            //!@return int, 0 ok| 1 error
            int add(const std::string& prefix, value_ptr value, bool overlap, bool check);

            //!@fn build, build search structure for added ranges
            //!@return noting
            int build();

            //!@fn clear search structure
            //!@return noting
            void erase() {
                search = nullptr;
                builded = false;
            }

        
            //!@fn ctor
            Prefix() : keys{std::make_shared<hash_t>()}, search{nullptr}, builded{false} {}

            //!@fn dtor
            ~Prefix() {}

            //!@fn PrefixAdd, add prefix for value into search structure
            //!@param prefix string
            //!@param value Value, reference to a value
            //!@param overlap bool, overlapping ranges permition, default is forbidden:
            //!| true allow
            //!| false forbidden
            //!@param check bool, default is not check, check search structure after insert a prefix
            //!@return int, 0 ok| 1 error
            int PrefixAdd(const std::string& prefix, value_t&& value, bool overlap = false, bool check = false);

            //!@fn RangeAdd, add number range for value into search structure
            //!@param from string, number range start
            //!@param till string, number range end
            //!@param value Value, reference to a value
            //!@param overlap bool, overlapping ranges permition, default is forbidden:
            //!| true allow
            //!| false forbidden
            //!@param check bool, default is not check, check search structure after insert a prefix
            //!@return int, 0 ok| 1 error
            int RangeAdd(std::string from, std::string till, value_t&& value, bool overlap = false, bool check = false);

            //!@fn Search, searching number in prefix tree structure
            //!@param number string, number to search
            //!@param overlap_prefix, share pointer to prefix string by which number is found, default is nullptr
            //!@return shared_ptr, shared pointer to value
            //!| nullptr if not found a value
            //!| reference to value if value is found
            value_ptr Search(const std::string& number, std::shared_ptr<std::string> overlap_prefix = nullptr);

            //!@fn SearchAll, searching number in prefix tree structure
            //!@param number string, number to search
            //!@return vector<shared_ptr>, list of founded values belonging to number ranges, sorted in order of the
            //!| length of the number range
            typename std::vector<value_ptr> SearchAll(const std::string& number);

            //!@fn Check, check number range in prefix tree returns the same value for each number in the range
            //!@param from string, number range start
            //!@param till string, number range end
            //!@param value Value, reference to a value
            //!@param overlap bool, range may overlapped in prefix tree
            //!| true is overlapped
            //!| false is not
            //!@return int, 0 ok| 1 error
            int Check(const std::string& from, const std::string& till, value_t&& value, bool overlap);
    };

#include "prefix_impl.hpp"

}  // namespace prefix

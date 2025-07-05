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
#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cerrno>
#include <cstdlib>
#include <algorithm>

namespace prefix {

    static size_t len = 15;

template <typename Value>
class Prefix {
public:
    typedef Value value_t;
    typedef std::shared_ptr<value_t> value_ptr;
    std::unordered_map<std::string, std::vector<value_ptr>> keys;

private:

    static long long pow10(int exp);

    std::string NormalizePrefix(const std::string& prefix, size_t length = len, char pad_char = '0');

    std::string ToFixedLengthString(long long number, size_t length = len);

    struct Node
    {
        std::string key_part;
        std::string range_start;
        std::string range_end;
        std::vector<value_ptr> values;
        std::unordered_map<char, std::unique_ptr<Node>> children;

        Node(const std::string& key = "", const std::string& start = "", const std::string& end = "") : key_part(key), range_start(start), range_end(end) {}
    };

    std::unique_ptr<Node> root;

    void SplitRangeToPrefixesRecursive(long long start, long long end, size_t length, std::vector<std::string>& out);
    
    std::vector<std::string> SplitRangeToPrefixes(long long start, long long end);

    void InsertRange(Node* node, const std::string& prefix, const std::string& range_start, const std::string& range_end, value_ptr value);

    value_ptr SearchInternal(Node* node, const std::string& key, size_t pos = 0, value_ptr last_found = nullptr);

public:
    Prefix() : root(std::make_unique<Node>("")) {}

    ~Prefix() = default;

    void Clear();

    int RangeAdd(const std::string& from, const std::string& till, value_t&& value, bool overlap = false, bool check = false);

    value_ptr Search(const std::string& key);
};

} // namespace prefix

#include "prefix_impl.hpp"

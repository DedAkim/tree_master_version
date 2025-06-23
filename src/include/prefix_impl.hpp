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

//!@note implementation Prefix<T>

#include "prefix.hpp"

#define unless(x) if (not(x))
#define ctoi(x) (int)*x - (int)'0'
#define itoc(x) (char)(x + (int)'0')

template <typename Value>
int prefix::Prefix<Value>::PrefixAdd(const std::string &prefix, value_t &&value, bool overlap, bool check) {
    if (check) {
        if (builded == false) build();
    }
    if (add(prefix, std::make_shared<Prefix::value_t>(value), overlap, check) == 0) {
        return 0;
    }
    builded = false;
    return 1;
}

template <typename Value>
int prefix::Prefix<Value>::add(const std::string &prefix, value_ptr value, bool overlap, bool check) {
    if (keys->count(prefix) and not overlap) {
        fmt::print("ERROR: prefix '{}' already exists", prefix);
        return 0;
    }
    if (not overlap and check) {
        std::shared_ptr<std::string> overlap_prefix;
        if (Search(prefix, overlap_prefix)) {
            fmt::print("ERROR: prefix '{}' is overlaped by prefix '{}'", prefix, *overlap_prefix);
            return 0;
        }
    }

    (*keys)[prefix].insert((*keys)[prefix].begin(), value);
    return 1;
}

template <typename Value>
int prefix::Prefix<Value>::RangeAdd(std::string from, std::string till, value_t &&value_, bool overlap, bool check) {
    auto value = std::make_shared<Prefix::value_t>(value_);

    if (check) {
        unless(builded) build();
    }

    errno = 0;
    auto from_n = strtoll(from.c_str(), nullptr, 10);
    if (errno == ERANGE) {
        fmt::print("ERROR: failed convert start range '{}' into number", from);
        return 0;
    }

    auto till_n = strtoll(till.c_str(), nullptr, 10);
    if (errno == ERANGE) {
        fmt::print("ERROR: failed convert end range '{}' into number", till);
        return 0;
    }

    if (from_n > till_n) {
        fmt::print("ERROR: wrong range from '{}' greater than till '{}'", from, till);
        return 0;
    }

    for (auto num = from_n; num <= till_n; ++num) {
        std::string prefix = fmt::format("{}", num);

        if (add(prefix, value, overlap, check) == 0) {
            return 0;
        }
    }

    builded = false;

    return 1;
}

template <typename Value> 
typename prefix::Prefix<Value>::value_ptr prefix::Prefix<Value>::Search(const std::string &number, std::shared_ptr<std::string> overlap_prefix) {
    unless(builded) build();
    std::string prefix;
    size_t len = number.length();
    // fmt::print("search '{}' length {}\n", number, len);
    for (auto &[length, hash] : *search) {
        if (length > len) continue;
        prefix = number.substr(0, length);
        // fmt::print("prefix '{}' length {}\n", prefix, length);
        if (hash->count(prefix)) {
            return (*hash)[prefix][0];
        }
    }
    return nullptr;
}

template <typename Value>
std::vector<std::shared_ptr<Value>> prefix::Prefix<Value>::SearchAll(const std::string &number) {
    unless(builded) build();
    std::string prefix;
    size_t len = number.length();
    std::vector<Prefix::value_ptr> values;
    for (auto &[length, hash] : *search) {
        if (length > len) continue;
        prefix = number.substr(0, length);
        if (hash->count(prefix)) {
            std::copy_backward((*hash)[prefix].begin(), (*hash)[prefix].end(), values.end());
        }
    }
    return values;
}

template <typename Value>
int prefix::Prefix<Value>::build() {
    if (builded) return 1;
    unless(search == nullptr) erase();
    search = std::make_unique<search_t>();

    // typedef std::map<size_t, hash_ptr, length_key_cmp> length_keys_t;
    length_keys_t length_keys;

    // typedef spp::sparse_hash_map<std::string, std::vector<value_ptr>> hash_t;

    // key size_t, key_values  std::vector<value_ptr>
    for (auto &[key, key_values] : *keys) {
        unless(length_keys.count(key.length())) length_keys[key.length()] = std::make_shared<hash_t>();

        auto length_hash = length_keys[key.length()];

        (*length_hash)[key] = key_values;
    }
    // ok now sort keys by length in descend order and push into search_t
    for (auto &[key, values] : length_keys) {
        search->push_back({key, std::move(values)});
    }
    builded = true;
    return 1;
}

template <typename Value>
int prefix::Prefix<Value>::Check(const std::string &from, const std::string &till, value_t &&value, bool overlap) {
    unless(builded) build();
    errno = 0;
    auto from_n = strtoll(from.c_str(), nullptr, 10);

    if (errno == ERANGE) {
        fmt::print("ERROR: failed convert start range '{}' into number", from);
        return 0;
    }

    auto till_n = strtoll(till.c_str(), nullptr, 10);

    if (errno == ERANGE) {
        fmt::print("ERROR: failed convert end range '{}' into number", from);
        return 0;
    }

    if (from_n > till_n) {
        fmt::print("ERROR: wrog range from '{}' greatest then till '{}'", from, till);
        return 0;
    }

    std::shared_ptr<std::string> prefix;
    fmt::print("check range from '{}' till '{}', numbers {}", from, till, till_n - from_n);
    {
        for (auto num = from_n; num <= till_n; ++num) {
            std::string number = fmt::format("{}", num);

            if (overlap) {
                auto values = SearchAll(number);
                if (values.empty()) {
                    fmt::print("ERROR: number '{}' not found", number);
                    return 0;
                }

                bool found_value = false;
                for (const auto &val_ptr : values) {
                    if (*val_ptr == value) {
                        found_value = true;
                        break;
                    }
                }
                if (!found_value) {
                    fmt::print("ERROR: number '{}' found but value not equal", number);
                    return 0;
                }
            }
            else {
                value_ptr found = Search(number, prefix);
                unless(found) {
                    fmt::print("ERROR: number '{}' not found", number);
                    return 0;
                }
                unless(*found == value) {
                    fmt::print("ERROR: number '{}' found by prefix '{}', but value not equal", number, *prefix);
                    return 0;
                }
            }
        }
    }

    fmt::print("check range from '{}' till '{}' success", from, till);

    return 1;

}

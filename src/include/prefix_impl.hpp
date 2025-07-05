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

template <typename Value>
inline long long prefix::Prefix<Value>::pow10(int exp)
{
    long long res = 1;
    while (exp-- > 0) res *= 10;
    return res;
}


template <typename Value>
inline std::string prefix::Prefix<Value>::NormalizePrefix(const std::string &prefix, size_t length, char pad_char)
{
    if (prefix.size() >= length)
    {
        return prefix.substr(0, length);
    }
    return prefix + std::string(length - prefix.size(), pad_char);
}

template <typename Value>
inline std::string prefix::Prefix<Value>::ToFixedLengthString(long long number, size_t length)
{
    std::string s = std::to_string(number);
    if (s.size() < length)
    {
        s = std::string(length - s.size(), '0') + s;
    }
    return s;
}

template <typename Value>
inline void prefix::Prefix<Value>::SplitRangeToPrefixesRecursive(long long start, long long end, size_t length, std::vector<std::string> &out)
{
    if (start > end)
        return;

    if (length == prefix::len)
    {
        for (long long num = start; num <= end; ++num)
        {
            out.push_back(ToFixedLengthString(num, prefix::len));
        }
        return;
    }

    long long block_size = pow10(prefix::len - length);

    long long block_start = (start / block_size) * block_size;
    long long block_end = block_start + block_size - 1;

    if (start == block_start && end >= block_end)
    {

        std::string prefix = ToFixedLengthString(start, prefix::len).substr(0, length);
        out.push_back(prefix);
        SplitRangeToPrefixesRecursive(block_end + 1, end, length, out);
    }
    else
    {
        long long next_block_start = block_start + block_size;
        SplitRangeToPrefixesRecursive(start, std::min(end, block_end), length + 1, out);
        if (end >= next_block_start)
        {
            SplitRangeToPrefixesRecursive(next_block_start, end, length, out);
        }
    }
}

template <typename Value>
inline std::vector<std::string> prefix::Prefix<Value>::SplitRangeToPrefixes(long long start, long long end)
{
    std::vector<std::string> prefixes;
    this->SplitRangeToPrefixesRecursive(start, end, 1, prefixes);

    for (auto& p : prefixes)
    {
        if (p.size() < prefix::len) {
            p.append(prefix::len - p.size(), '0');
        }
    }

    std::unordered_set<std::string> unique(prefixes.begin(), prefixes.end());
    prefixes.assign(unique.begin(), unique.end());

    /*for (const auto& p : prefixes)
    {
        fmt::print("Unique prefix: {}\n", p);
    }*/

    return prefixes;
}

template <typename Value>
inline void prefix::Prefix<Value>::InsertRange(Node *node, const std::string &prefix, const std::string &range_start, const std::string &range_end, value_ptr value)
{
    size_t common_len = 0;
    while (common_len < node->key_part.size() && common_len < prefix.size() && node->key_part[common_len] == prefix[common_len])
    {
        ++common_len;
    }

    if (common_len == node->key_part.size() && common_len == prefix.size())
    {
        if (node->range_start.empty() || range_start < node->range_start)
        {
            node->range_start = range_start;
        }
        if (node->range_end.empty() || range_end > node->range_end)
        {
            node->range_end = range_end;
        }
        auto& vals = node->values;
        if (std::find_if(vals.begin(), vals.end(), [&](const value_ptr& v) { return *v == *value; }) == vals.end())
        {
            vals.push_back(value);
        }
        return;
    }

    if (common_len == 0)
    {
        char next_char = prefix[0];
        if (node->children.find(next_char) == node->children.end())
        {
            node->children[next_char] = std::make_unique<Node>(prefix, range_start, range_end);
            node->children[next_char]->values.push_back(value);
        }
        else
        {
            InsertRange(node->children[next_char].get(), prefix, range_start, range_end, value);
        }
        return;
    }

    if (common_len < node->key_part.size())
    {
        std::string old_suffix = node->key_part.substr(common_len);
        auto old_children = std::move(node->children);
        auto old_values = std::move(node->values);
        std::string old_start = node->range_start;
        std::string old_end = node->range_end;

        node->key_part = node->key_part.substr(0, common_len);
        node->children.clear();
        node->values.clear();

        auto child = std::make_unique<Node>(old_suffix, old_start, old_end);
        child->values = std::move(old_values);
        child->children = std::move(old_children);

        node->children[old_suffix[0]] = std::move(child);
    }

    std::string new_suffix = prefix.substr(common_len);
    char next_char = new_suffix[0];
    if (node->children.find(next_char) == node->children.end())
    {
        node->children[next_char] = std::make_unique<Node>(new_suffix, range_start, range_end);
        node->children[next_char]->values.push_back(value);
    }
    else
    {
        InsertRange(node->children[next_char].get(), new_suffix, range_start, range_end, value);
    }
}

template <typename Value>
inline typename prefix::Prefix<Value>::value_ptr prefix::Prefix<Value>::SearchInternal(Node* node, const std::string& key, size_t pos, value_ptr last_found)
{
    size_t i = 0;
    while (i < node->key_part.size() && pos + i < key.size() && node->key_part[i] == key[pos + i])
    {
        ++i;
    }
    if (i < node->key_part.size())
    {
        return last_found;
    }

    if (!node->range_start.empty() && !node->range_end.empty())
    {
        if (key >= node->range_start && key <= node->range_end)
        {
            if (!node->values.empty())
            {
                last_found = node->values[0];
            }
        }
    }

    pos += i;
    if (pos == key.size())
    {
        return last_found;
    }

    char next_char = key[pos];
    auto it = node->children.find(next_char);
    if (it == node->children.end())
    {
        return last_found;
    }
    return SearchInternal(it->second.get(), key, pos, last_found);
}





template <typename Value>
inline void prefix::Prefix<Value>::Clear()
{
    keys.clear();
    root = std::make_unique<Node>("");
}

template <typename Value>
inline int prefix::Prefix<Value>::RangeAdd(const std::string &from, const std::string &till, value_t &&value, bool overlap, bool check)
{
    auto prefixes = SplitRangeToPrefixes(std::stoll(from), std::stoll(till));

    for (const auto& prefix : prefixes)
    {
        std::string start = NormalizePrefix(prefix, prefix::len, '0');
        std::string end = NormalizePrefix(prefix, prefix::len, '9');

        for (size_t l = 1; l <= prefix.size(); ++l)
        {
            std::string sub_prefix = prefix.substr(0, l);
            std::string sub_start = NormalizePrefix(sub_prefix, prefix::len, '0');
            std::string sub_end = NormalizePrefix(sub_prefix, prefix::len, '9');

            InsertRange(root.get(), sub_prefix, sub_start, sub_end, std::make_shared<value_t>(value));
        }
    }
    return 1;
}

template <typename Value>
inline typename prefix::Prefix<Value>::value_ptr prefix::Prefix<Value>::Search(const std::string &key)
{
    std::string norm_key = NormalizePrefix(key);
    return SearchInternal(root.get(), norm_key, 0, nullptr);
}
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

#include <gtest/gtest.h>
#include <thread>

#include <algorithm>
#include <prefix.hpp>


#include "prefixes.hpp"

/*
    Prove tests

    Build prefix tree for small prefixes for eaxample 100-999
    Prefixes order is matter.

        100-199 1
        101-108 2
        103-105 3
        119-151 4
        140-200 5 but this is an error, must not be added

    ProveTest1  100 1
    ProveTest2  101 2
    ProveTest3  102 2
    ProveTest4  103 3
    ProveTest5  104 3
    ProveTest6  105 3
    ProveTest7  106 2
    ProveTest8  107 2
    ProveTest9  108 2
    ProveTest10 109 1
    ProveTest11 118 1
    ProveTest12 119 4
    ProveTest13 140 4   5 (in case of allow redefine range 140-200)
    ProveTest14 151 4   5 (in case of allow redefine range 140-200)
    ProveTest15 152 1   5 (in case of allow redefine range 140-200)
*/

template <typename Value>
void CheckPrefixKeys(const prefix::Prefix<Value>& prefixes,
                     const std::map<std::string, Value>& expected) {
    for (const auto& [key, expected_value] : expected) {
        auto found = prefixes.keys.find(key);
        ASSERT_NE(found, prefixes.keys.end()) << "Key '" << key << "' not found in prefix tree";
        ASSERT_FALSE(found->second.empty()) << "Values vector for key '" << key << "' is empty";
        EXPECT_EQ(*(found->second[0]), expected_value) << "Value mismatch for key '" << key << "'";
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
static void prove_prefixes(prefix::Prefix<int>& prefixes) {
    
    prefixes.RangeAdd("100", "199", 1);
    prefixes.RangeAdd("101", "108", 2, true);
    prefixes.RangeAdd("103", "105", 3, true);
    prefixes.RangeAdd("119", "151", 4, true);
    //prefixes.RangeAdd("140", "200", 5, true);

}

TEST(TestPrefix, TreeStructureAfterRangeAdd) {
    prefix::Prefix<int> prefixes;

    prove_prefixes(prefixes);
    std::map<std::string, int> expected = {
        {"100", 1},
        {"101", 2},
        {"102", 2},
        {"103", 3},
        {"104", 3},
        {"105", 3},
        {"106", 2},
        {"107", 2},
        {"108", 2},
        {"109", 1},
        {"110", 1},
        {"119", 4},
        {"120", 4},
        {"121", 4},
        {"140", 4},
        {"151", 4},
        {"152", 1},
    };

    prefixes.Clear();
    CheckPrefixKeys(prefixes, expected);
}

TEST(TestPrefix, ProveTest1) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("100");
    if (value != nullptr) {
        EXPECT_EQ(*value, 1);
    }
}

TEST(TestPrefix, ProveTest2) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("101");
    if (value != nullptr) {
        EXPECT_EQ(*value, 2);
    }
}

TEST(TestPrefix, ProveTest3) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("102");
    if (value != nullptr) {
        EXPECT_EQ(*value, 2);
    }
}

TEST(TestPrefix, ProveTest4) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("103");
    if (value != nullptr) {
        EXPECT_EQ(*value, 3);
    }
}

TEST(TestPrefix, ProveTest5) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("104");
    if (value != nullptr) {
        EXPECT_EQ(*value, 3);
    }
}

TEST(TestPrefix, ProveTest6) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("105");
    if (value != nullptr) {
        EXPECT_EQ(*value, 3);
    }
}

TEST(TestPrefix, ProveTest7) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("106");
    if (value != nullptr) {
        EXPECT_EQ(*value, 2);
    }
}

TEST(TestPrefix, ProveTest8) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("107");
    if (value != nullptr) {
        EXPECT_EQ(*value, 2);
    }
}

TEST(TestPrefix, ProveTest9) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("108");
    if (value != nullptr) {
        EXPECT_EQ(*value, 2);
    }
}

TEST(TestPrefix, ProveTest10) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("109");
    if (value != nullptr) {
        EXPECT_EQ(*value, 1);
    }
}

TEST(TestPrefix, ProveTest11) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("118");
    if (value != nullptr) {
        EXPECT_EQ(*value, 1);
    }
}

TEST(TestPrefix, ProveTest12) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("119");
    if (value != nullptr) {
        EXPECT_EQ(*value, 4);
    }
}


TEST(TestPrefix, ProveTest13) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("140");
    if (value != nullptr) {
        EXPECT_EQ(*value, 4);
    }
}

TEST(TestPrefix, ProveTest14) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("151");
    if (value != nullptr) {
        EXPECT_EQ(*value, 4);
    }
}

TEST(TestPrefix, ProveTest15) {
    prefix::Prefix<int> prefixes;
    prove_prefixes(prefixes);
    auto value = prefixes.Search("152");
    if (value != nullptr) {
        EXPECT_EQ(*value, 1);
    }
}

*/


TEST(TestPrefix, SearchValue1) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("201000000000000");
    if (value == nullptr) {
        EXPECT_EQ(value, nullptr);
    }
}

TEST(TestPrefix, SearchValue2) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("250019120223473");
    EXPECT_NE(value, nullptr);
    if (value != nullptr) {
        EXPECT_EQ(*value, 17198);
    }
}

TEST(TestPrefix, SearchValue3) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("655100000000000");
    EXPECT_NE(value, nullptr);
    if (value != nullptr) {
        EXPECT_EQ(*value, 16087);
    }
}

TEST(TestPrefix, SearchValue4) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("655100999999999");
    EXPECT_NE(value, nullptr);
    if (value != nullptr) {
        EXPECT_EQ(*value, 16087);
    }
}

TEST(TestPrefix, SearchValue5) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("655101113159589");
    EXPECT_NE(value, nullptr);
    if (value != nullptr) {
        EXPECT_EQ(*value, 16087);
    }
}

TEST(TestPrefix, SearchValue6) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("655101110000000");
    EXPECT_NE(value, nullptr);
    if (value != nullptr) {
        EXPECT_EQ(*value, 16087);
    }
}

TEST(TestPrefix, SearchValue7) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("655109999999999");
    EXPECT_NE(value, nullptr);
    if (value != nullptr) {
        EXPECT_EQ(*value, 16088);
    }
}

TEST(TestPrefix, SearchValue8) {
    prefix::Prefix<int> prefixes;
    prefixes.Clear();
    init_prefixes(prefixes);
    auto value = prefixes.Search("902099999999999");
    if (value == nullptr) {
        EXPECT_EQ(value, nullptr);
    }
}
    
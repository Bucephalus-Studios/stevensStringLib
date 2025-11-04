/**
 * @file property_based_test.cpp
 * @brief Property-based tests for stevensStringLib
 *
 * These tests verify mathematical properties that should hold for all inputs,
 * using randomized testing to find edge cases.
 */

#include <gtest/gtest.h>
#include <random>
#include <algorithm>
#include "../../stevensStringLib.h"

using namespace stevensStringLib;

// ============================================================================
// TEST FIXTURE WITH RANDOM GENERATION
// ============================================================================

class PropertyTest : public ::testing::Test {
protected:
    std::mt19937 rng{std::random_device{}()};

    // Generate random string of given length
    std::string randomString(size_t length, const std::string& charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") {
        std::uniform_int_distribution<> dist(0, charset.size() - 1);

        std::string result;
        result.reserve(length);
        for(size_t i = 0; i < length; ++i) {
            result += charset[dist(rng)];
        }
        return result;
    }

    // Generate random integer in range [min, max]
    int randomInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(rng);
    }

    // Generate random character
    char randomChar(const std::string& charset = "abcdefghijklmnopqrstuvwxyz") {
        std::uniform_int_distribution<> dist(0, charset.size() - 1);
        return charset[dist(rng)];
    }
};

// ============================================================================
// PROPERTY: separate() then join() should return original (inverse operations)
// ============================================================================

TEST_F(PropertyTest, SeparateJoin_AreInverses) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        // Generate random delimited string
        std::vector<std::string> parts;
        int num_parts = randomInt(1, 10);

        for(int i = 0; i < num_parts; ++i) {
            // Generate parts without commas
            parts.push_back(randomString(randomInt(1, 20), "abcdefghijklmnopqrstuvwxyz"));
        }

        std::string original = join(parts, ",");
        auto separated = separate(original, ',');
        std::string rejoined = join(separated, ",");

        EXPECT_EQ(original, rejoined)
            << "Trial " << trial << " failed\n"
            << "Original: " << original << "\n"
            << "Rejoined: " << rejoined;
    }
}

// ============================================================================
// PROPERTY: toUpper() then toLower() preserves original lowercase
// ============================================================================

TEST_F(PropertyTest, CaseConversion_Reversible) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string original = randomString(randomInt(1, 100));

        // Convert to lower, then upper, then lower again
        std::string roundtrip = toLower(toUpper(toLower(original)));

        EXPECT_EQ(toLower(original), roundtrip)
            << "Trial " << trial << " failed for: " << original;
    }
}

// ============================================================================
// PROPERTY: multiply(s, n) should have length == s.length() * n
// ============================================================================

TEST_F(PropertyTest, Multiply_LengthProperty) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string s = randomString(randomInt(1, 10));
        int n = randomInt(0, 20);

        std::string result = multiply(s, n);

        EXPECT_EQ(result.length(), s.length() * n)
            << "Trial " << trial << " failed\n"
            << "String: " << s << "\n"
            << "Multiplier: " << n << "\n"
            << "Expected length: " << (s.length() * n) << "\n"
            << "Actual length: " << result.length();
    }
}

// ============================================================================
// PROPERTY: multiply(s, n) contains exactly n copies of s
// ============================================================================

TEST_F(PropertyTest, Multiply_ContainsNCopies) {
    const int NUM_TRIALS = 50;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string s = randomString(randomInt(2, 10));
        int n = randomInt(1, 10);

        std::string result = multiply(s, n);

        // Count occurrences of s in result
        size_t count = 0;
        size_t pos = 0;
        while((pos = result.find(s, pos)) != std::string::npos) {
            ++count;
            pos += s.length();
        }

        EXPECT_EQ(count, static_cast<size_t>(n))
            << "Trial " << trial << " failed\n"
            << "String: " << s << "\n"
            << "Expected " << n << " copies, found " << count;
    }
}

// ============================================================================
// PROPERTY: reverse(reverse(s)) == s (involution)
// ============================================================================

TEST_F(PropertyTest, Reverse_IsInvolution) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string original = randomString(randomInt(0, 100));
        std::string roundtrip = reverse(reverse(original));

        EXPECT_EQ(original, roundtrip)
            << "Trial " << trial << " failed for: " << original;
    }
}

// ============================================================================
// PROPERTY: isPalindrome(s) == isPalindrome(reverse(s))
// ============================================================================

TEST_F(PropertyTest, Palindrome_ReversedSame) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string s = randomString(randomInt(0, 50));

        EXPECT_EQ(isPalindrome(s), isPalindrome(reverse(s)))
            << "Trial " << trial << " failed for: " << s;
    }
}

// ============================================================================
// PROPERTY: scramble() preserves string length
// ============================================================================

TEST_F(PropertyTest, Scramble_PreservesLength) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string original = randomString(randomInt(0, 100));
        std::string scrambled = scramble(original);

        EXPECT_EQ(original.length(), scrambled.length())
            << "Trial " << trial << " failed\n"
            << "Original length: " << original.length() << "\n"
            << "Scrambled length: " << scrambled.length();
    }
}

// ============================================================================
// PROPERTY: scramble() preserves character counts
// ============================================================================

TEST_F(PropertyTest, Scramble_PreservesCharacters) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string original = randomString(randomInt(1, 50));
        std::string scrambled = scramble(original);

        // Sort both strings and compare
        std::string sorted_original = original;
        std::string sorted_scrambled = scrambled;
        std::sort(sorted_original.begin(), sorted_original.end());
        std::sort(sorted_scrambled.begin(), sorted_scrambled.end());

        EXPECT_EQ(sorted_original, sorted_scrambled)
            << "Trial " << trial << " failed\n"
            << "Original: " << original << "\n"
            << "Scrambled: " << scrambled;
    }
}

// ============================================================================
// PROPERTY: removeWhitespace() never increases length
// ============================================================================

TEST_F(PropertyTest, RemoveWhitespace_NeverIncreases) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        // Generate string with random whitespace
        std::string original = randomString(randomInt(0, 100), "abc \t\n\r");
        std::string cleaned = removeWhitespace(original);

        EXPECT_LE(cleaned.length(), original.length())
            << "Trial " << trial << " failed\n"
            << "Original length: " << original.length() << "\n"
            << "Cleaned length: " << cleaned.length();
    }
}

// ============================================================================
// PROPERTY: contains(s, substr) implies findAll(s, substr).size() > 0
// ============================================================================

TEST_F(PropertyTest, Contains_ImpliesFindAll) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string str = randomString(randomInt(10, 50));
        std::string substr = randomString(randomInt(1, 5));

        bool contains_result = contains(str, substr);
        auto findall_result = findAll(str, substr);

        if(contains_result) {
            EXPECT_GT(findall_result.size(), 0)
                << "Trial " << trial << " failed\n"
                << "String: " << str << "\n"
                << "Substring: " << substr;
        } else {
            EXPECT_EQ(findall_result.size(), 0)
                << "Trial " << trial << " failed\n"
                << "String: " << str << "\n"
                << "Substring: " << substr;
        }
    }
}

// ============================================================================
// PROPERTY: startsWith(s, prefix) implies contains(s, prefix)
// ============================================================================

TEST_F(PropertyTest, StartsWith_ImpliesContains) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string str = randomString(randomInt(10, 50));
        size_t prefix_len = randomInt(0, std::min<size_t>(10, str.length()));
        std::string prefix = str.substr(0, prefix_len);

        if(startsWith(str, prefix)) {
            EXPECT_TRUE(contains(str, prefix))
                << "Trial " << trial << " failed\n"
                << "String: " << str << "\n"
                << "Prefix: " << prefix;
        }
    }
}

// ============================================================================
// PROPERTY: eraseCharsFromEnd then eraseCharsFromStart preserves order
// ============================================================================

TEST_F(PropertyTest, EraseOperations_PreserveOrder) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string original = randomString(randomInt(10, 50));
        size_t erase_end = randomInt(0, original.length() / 2);
        size_t erase_start = randomInt(0, original.length() / 2);

        std::string result = eraseCharsFromStart(
            eraseCharsFromEnd(original, erase_end),
            erase_start
        );

        // Result should be a substring of original with same character order
        if(!result.empty()) {
            size_t pos = original.find(result);
            EXPECT_NE(pos, std::string::npos)
                << "Trial " << trial << " failed\n"
                << "Original: " << original << "\n"
                << "Result: " << result;
        }
    }
}

// ============================================================================
// PROPERTY: replaceSubstr with empty replacement is like deletion
// ============================================================================

TEST_F(PropertyTest, Replace_EmptyIsDelete) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string original = randomString(randomInt(20, 50));
        char target = randomChar();
        std::string target_str(1, target);

        std::string replaced = replaceSubstr(original, target_str, "");

        // Result should not contain target character
        EXPECT_EQ(replaced.find(target), std::string::npos)
            << "Trial " << trial << " failed\n"
            << "Original: " << original << "\n"
            << "Target: " << target << "\n"
            << "Result: " << replaced;
    }
}

// ============================================================================
// PROPERTY: circularIndex wraps correctly
// ============================================================================

TEST_F(PropertyTest, CircularIndex_WrapsCorrectly) {
    const int NUM_TRIALS = 100;

    for(int trial = 0; trial < NUM_TRIALS; ++trial) {
        std::string str = randomString(randomInt(1, 20));
        size_t index = randomInt(0, 1000);

        char result = circularIndex(str, index);
        char expected = str[index % str.length()];

        EXPECT_EQ(result, expected)
            << "Trial " << trial << " failed\n"
            << "String: " << str << "\n"
            << "Index: " << index;
    }
}

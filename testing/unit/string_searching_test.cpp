/**
 * @file string_searching_test.cpp
 * @brief Unit tests for string searching and matching functions
 *
 * Tests for: contains, containsOnly, startsWith, endsWith, findAll
 */

#include <gtest/gtest.h>
#include "../../stevensStringLib.h"
#include "../fixtures/test_data.h"

using namespace stevensStringLib;

// ============================================================================
// TESTS - contains() string variant
// ============================================================================

TEST(Contains_String, SubstringExists_ReturnsTrue) {
    EXPECT_TRUE(contains("hello world", "world"));
    EXPECT_TRUE(contains("hello world", "hello"));
    EXPECT_TRUE(contains("hello world", "o w"));
}

TEST(Contains_String, SubstringNotFound_ReturnsFalse) {
    EXPECT_FALSE(contains("hello world", "foo"));
    EXPECT_FALSE(contains("hello world", "HELLO"));  // Case sensitive
}

TEST(Contains_String, SubstringIsWholeString_ReturnsTrue) {
    EXPECT_TRUE(contains("hello", "hello"));
}

TEST(Contains_String, EmptyStringEmptySubstring_ReturnsTrue) {
    EXPECT_TRUE(contains("", ""));
}

TEST(Contains_String, NonEmptyStringEmptySubstring_ReturnsTrue) {
    // Empty string is substring of any string
    EXPECT_TRUE(contains("hello", ""));
}

TEST(Contains_String, EmptyStringNonEmptySubstring_ReturnsFalse) {
    EXPECT_FALSE(contains("", "hello"));
}

TEST(Contains_String, LargeString_WorksCorrectly) {
    class LocalFixture : public TestData::LargeTextFixture {};
    LocalFixture::SetUpTestSuite();

    EXPECT_TRUE(contains(LocalFixture::getFrankenstein(), "conflagration"));
    EXPECT_FALSE(contains(LocalFixture::getFrankenstein(), "zzzzzznonexistent"));
}

// ============================================================================
// TESTS - contains() char variant
// ============================================================================

TEST(Contains_Char, CharExists_ReturnsTrue) {
    EXPECT_TRUE(contains("hello", 'h'));
    EXPECT_TRUE(contains("hello", 'e'));
    EXPECT_TRUE(contains("hello", 'o'));
}

TEST(Contains_Char, CharNotFound_ReturnsFalse) {
    EXPECT_FALSE(contains("hello", 'x'));
    EXPECT_FALSE(contains("hello", 'H'));  // Case sensitive
}

TEST(Contains_Char, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(contains("", 'a'));
}

TEST(Contains_Char, SpecialCharacters) {
    EXPECT_TRUE(contains("Hello, World!", ','));
    EXPECT_TRUE(contains("Hello, World!", '!'));
}

// ============================================================================
// TESTS - containsOnly()
// ============================================================================

TEST(ContainsOnly, StringContainsOnlySpecifiedChars_ReturnsTrue) {
    EXPECT_TRUE(containsOnly("111222333", "123"));
    EXPECT_TRUE(containsOnly("aabbccaabbcc", "abc"));
}

TEST(ContainsOnly, StringContainsOtherChars_ReturnsFalse) {
    EXPECT_FALSE(containsOnly("111022233", "123"));  // Contains '0'
    EXPECT_FALSE(containsOnly("abcx", "abc"));       // Contains 'x'
}

TEST(ContainsOnly, EmptyStringEmptyChars_ReturnsTrue) {
    EXPECT_TRUE(containsOnly("", ""));
}

TEST(ContainsOnly, NonEmptyStringEmptyChars_ReturnsFalse) {
    EXPECT_FALSE(containsOnly("hello", ""));
}

TEST(ContainsOnly, EmptyStringNonEmptyChars_ReturnsTrue) {
    // Empty string contains only nothing
    EXPECT_TRUE(containsOnly("", "abc"));
}

TEST(ContainsOnly, SingleChar) {
    EXPECT_TRUE(containsOnly("aaaaa", "a"));
    EXPECT_FALSE(containsOnly("aaaba", "a"));
}

TEST(ContainsOnly, NumericString) {
    EXPECT_TRUE(containsOnly("000000000000000000000000000000000000001", "01"));
    EXPECT_FALSE(containsOnly("11101112222", "12"));  // Contains '0'
}

// ============================================================================
// TESTS - startsWith()
// ============================================================================

TEST(StartsWith, StringStartsWithPrefix_ReturnsTrue) {
    EXPECT_TRUE(startsWith("hello world", "hello"));
    EXPECT_TRUE(startsWith("hello world", "h"));
}

TEST(StartsWith, StringDoesNotStartWithPrefix_ReturnsFalse) {
    EXPECT_FALSE(startsWith("hello world", "world"));
    EXPECT_FALSE(startsWith("hello world", "Hello"));  // Case sensitive
}

TEST(StartsWith, PrefixLongerThanString_ReturnsFalse) {
    EXPECT_FALSE(startsWith("hi", "hello"));
}

TEST(StartsWith, EmptyPrefix_ReturnsTrue) {
    EXPECT_TRUE(startsWith("hello", ""));
}

TEST(StartsWith, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(startsWith("", "hello"));
}

TEST(StartsWith, EmptyStringEmptyPrefix_ReturnsTrue) {
    EXPECT_TRUE(startsWith("", ""));
}

TEST(StartsWith, WholeStringAsPrefix_ReturnsTrue) {
    EXPECT_TRUE(startsWith("test", "test"));
}

TEST(StartsWith, LongSentence) {
    std::string sentence = "By the authority vested in me by the state of Ohio";
    EXPECT_TRUE(startsWith(sentence, "By the authority"));
    EXPECT_FALSE(startsWith(sentence, "by the authority"));  // Case sensitive
}

// ============================================================================
// TESTS - endsWith()
// ============================================================================

TEST(EndsWith, StringEndsWithSuffix_ReturnsTrue) {
    EXPECT_TRUE(endsWith("hello world", "world"));
    EXPECT_TRUE(endsWith("hello world", "d"));
}

TEST(EndsWith, StringDoesNotEndWithSuffix_ReturnsFalse) {
    EXPECT_FALSE(endsWith("hello world", "hello"));
    EXPECT_FALSE(endsWith("hello world", "World"));  // Case sensitive
}

TEST(EndsWith, SuffixLongerThanString_ReturnsFalse) {
    EXPECT_FALSE(endsWith("hi", "hello"));
}

TEST(EndsWith, EmptySuffix_ReturnsTrue) {
    EXPECT_TRUE(endsWith("hello", ""));
}

TEST(EndsWith, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(endsWith("", "hello"));
}

TEST(EndsWith, EmptyStringEmptySuffix_ReturnsTrue) {
    EXPECT_TRUE(endsWith("", ""));
}

TEST(EndsWith, WholeStringAsSuffix_ReturnsTrue) {
    EXPECT_TRUE(endsWith("test", "test"));
}

TEST(EndsWith, LongSentence) {
    std::string sentence = "The quick brown fox jumps over the lazy dog";
    EXPECT_TRUE(endsWith(sentence, "lazy dog"));
    EXPECT_FALSE(endsWith(sentence, "lazy cat"));
}

// ============================================================================
// TESTS - findAll() string variant
// ============================================================================

TEST(FindAll_String, FindMultipleOccurrences) {
    std::string mine = "rock,iron,rock,clay,gold,rock,rock,rock,clay,topaz,rock,gold,gold,rock";
    std::string gold = "gold";
    std::vector<size_t> expected = {20, 56, 61};

    auto result = findAll(mine, gold);
    EXPECT_EQ(result, expected);
}

TEST(FindAll_String, NoOccurrences_ReturnsEmpty) {
    std::string str = "You're never awake, but don't seem to sleep at all";
    auto result = findAll(str, "mtns.");
    EXPECT_EQ(result.size(), 0);
}

TEST(FindAll_String, FindEmptyString_ReturnsAllPositions) {
    std::string str = "You tried to disappear. So long, I followed you.";
    auto result = findAll(str, "");
    // Empty string matches at every position
    EXPECT_EQ(result.size(), 49);
}

TEST(FindAll_String, SingleOccurrence) {
    auto result = findAll("hello world", "world");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 6);
}

TEST(FindAll_String, OverlappingPatterns) {
    auto result = findAll("aaaa", "aa");
    // Should find at positions 0, 1, 2
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
}

// ============================================================================
// TESTS - findAll() char variant
// ============================================================================

TEST(FindAll_Char, FindMultipleOccurrences) {
    std::string str = "xxxxxxxxxx";
    auto result = findAll(str, 'x');
    EXPECT_EQ(result.size(), 10);
}

TEST(FindAll_Char, NoOccurrences_ReturnsEmpty) {
    auto result = findAll("hello", 'x');
    EXPECT_TRUE(result.empty());
}

TEST(FindAll_Char, SingleOccurrence) {
    auto result = findAll("hello", 'h');
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

TEST(FindAll_Char, BinaryString) {
    std::string binary = "00010000000000000101011100000000000000000000000100000000000000000000000000000000000000011";
    auto result = findAll(binary, '1');
    EXPECT_GT(result.size(), 0);
    // Verify all found positions actually contain '1'
    for(auto pos : result) {
        EXPECT_EQ(binary[pos], '1');
    }
}

// ============================================================================
// PROPERTY-BASED TESTS
// ============================================================================

// Property: If contains() returns true, findAll() should return non-empty vector
TEST(SearchingProperties, ContainsImpliesFindAll) {
    std::string str = "hello world";
    std::string substr = "world";

    bool contains_result = contains(str, substr);
    auto findall_result = findAll(str, substr);

    if(contains_result) {
        EXPECT_FALSE(findall_result.empty());
    } else {
        EXPECT_TRUE(findall_result.empty());
    }
}

// Property: startsWith(s, prefix) implies contains(s, prefix)
TEST(SearchingProperties, StartsWithImpliesContains) {
    std::string str = "hello world";
    std::string prefix = "hello";

    if(startsWith(str, prefix)) {
        EXPECT_TRUE(contains(str, prefix));
    }
}

// Property: endsWith(s, suffix) implies contains(s, suffix)
TEST(SearchingProperties, EndsWithImpliesContains) {
    std::string str = "hello world";
    std::string suffix = "world";

    if(endsWith(str, suffix)) {
        EXPECT_TRUE(contains(str, suffix));
    }
}

/**
 * @file string_manipulation_test.cpp
 * @brief Unit tests for string manipulation functions
 *
 * Tests for: separate, join, trim, removeWhitespace, trimWhitespace,
 *            toUpper, toLower, cap1stChar, reverse, scramble, multiply
 */

#include <gtest/gtest.h>
#include <algorithm>
#include "../../stevensStringLib.h"
#include "../fixtures/test_data.h"

using namespace stevensStringLib;

// ============================================================================
// PARAMETERIZED TESTS - separate()
// ============================================================================

struct SeparateTestCase {
    std::string input;
    char separator;
    std::vector<std::string> expected;
    bool omit_empty;

    friend std::ostream& operator<<(std::ostream& os, const SeparateTestCase& tc) {
        return os << "input='" << tc.input << "', sep='" << tc.separator << "'";
    }
};

class SeparateTest : public ::testing::TestWithParam<SeparateTestCase> {};

TEST_P(SeparateTest, SeparatesCorrectly) {
    const auto& tc = GetParam();
    auto result = separate(tc.input, tc.separator, tc.omit_empty);
    EXPECT_EQ(result, tc.expected);
}

INSTANTIATE_TEST_SUITE_P(
    VariousInputs,
    SeparateTest,
    ::testing::Values(
        SeparateTestCase{"a,b,c", ',', {"a", "b", "c"}, true},
        SeparateTestCase{"a,,c", ',', {"a", "c"}, true},
        SeparateTestCase{"a,,c", ',', {"a", "", "c"}, false},
        SeparateTestCase{"", ',', {}, true},
        SeparateTestCase{"no-separator", ',', {"no-separator"}, true},
        SeparateTestCase{",,,", ',', {}, true},
        SeparateTestCase{",,,", ',', {"", "", "", ""}, false}
    )
);

// ============================================================================
// INDIVIDUAL TESTS - separate()
// ============================================================================

TEST(Separate, BasicCommaDelimited) {
    auto result = separate("Charmander,Squirtle,Bulbasaur");
    std::vector<std::string> expected = {"Charmander", "Squirtle", "Bulbasaur"};
    EXPECT_EQ(result, expected);
}

TEST(Separate, StringSeparator) {
    auto result = separate("bacon strips and bacon strips and bacon strips", " and ");
    std::vector<std::string> expected = {"bacon strips", "bacon strips", "bacon strips"};
    EXPECT_EQ(result, expected);
}

TEST(Separate, EmptySeparator_SplitsIntoChars) {
    auto result = separate("Hello", "");
    std::vector<std::string> expected = {"H", "e", "l", "l", "o"};
    EXPECT_EQ(result, expected);
}

TEST(Separate, NoSeparatorFound_ReturnsWholeString) {
    auto result = separate("no separators here", "@");
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "no separators here");
}

TEST(Separate, LargeString_WorksCorrectly) {
    // Use the fixture for large text
    class LocalFixture : public TestData::LargeTextFixture {};
    LocalFixture::SetUpTestSuite();

    auto result = separate(LocalFixture::getFrankenstein(), "\n");
    EXPECT_EQ(result.size(), 7742);
}

// ============================================================================
// TESTS - join()
// ============================================================================

TEST(Join, BasicJoin) {
    std::vector<std::string> vec = {"apple", "banana", "cherry"};
    auto result = join(vec, ", ");
    EXPECT_EQ(result, "apple, banana, cherry");
}

TEST(Join, EmptyVector_ReturnsEmpty) {
    std::vector<std::string> vec = {};
    auto result = join(vec, ", ");
    EXPECT_EQ(result, "");
}

TEST(Join, SingleElement_NoSeparator) {
    std::vector<std::string> vec = {"apple"};
    auto result = join(vec, ", ");
    EXPECT_EQ(result, "apple");
}

TEST(Join, WithEmptyStrings_OmitTrue) {
    std::vector<std::string> vec = {"apple", "", "cherry", ""};
    auto result = join(vec, ", ", true);
    EXPECT_EQ(result, "apple, cherry");
}

TEST(Join, WithEmptyStrings_OmitFalse) {
    std::vector<std::string> vec = {"apple", "", "cherry"};
    auto result = join(vec, ", ", false);
    EXPECT_EQ(result, "apple, , cherry");
}

// Property: separate then join should give back original (roundtrip)
TEST(JoinSeparate, RoundtripProperty) {
    std::string original = "apple,banana,cherry,date";
    auto separated = separate(original, ',');
    auto rejoined = join(separated, ",");
    EXPECT_EQ(original, rejoined);
}

// ============================================================================
// TESTS - Case Conversion
// ============================================================================

TEST(ToUpper, BasicConversion) {
    EXPECT_EQ(toUpper("Hello, world!"), "HELLO, WORLD!");
}

TEST(ToUpper, AlreadyUppercase_Unchanged) {
    EXPECT_EQ(toUpper("ALREADY UPPER"), "ALREADY UPPER");
}

TEST(ToUpper, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(toUpper(""), "");
}

TEST(ToUpper, NumbersAndSymbols_Unchanged) {
    EXPECT_EQ(toUpper("123!@#"), "123!@#");
}

TEST(ToLower, BasicConversion) {
    EXPECT_EQ(toLower("HELLO, WORLD!"), "hello, world!");
}

TEST(ToLower, AlreadyLowercase_Unchanged) {
    EXPECT_EQ(toLower("already lower"), "already lower");
}

TEST(ToLower, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(toLower(""), "");
}

TEST(ToLower, MixedWithNumbers) {
    EXPECT_EQ(toLower("Hello123World!"), "hello123world!");
}

TEST(Cap1stChar, BasicCapitalization) {
    EXPECT_EQ(cap1stChar("john"), "John");
}

TEST(Cap1stChar, AlreadyCapitalized_Unchanged) {
    EXPECT_EQ(cap1stChar("Jeff"), "Jeff");
}

TEST(Cap1stChar, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(cap1stChar(""), "");
}

TEST(Cap1stChar, SingleChar) {
    EXPECT_EQ(cap1stChar("a"), "A");
}

// Property: Case conversion roundtrip
TEST(CaseConversion, RoundtripProperty) {
    std::string original = "The Quick Brown Fox";
    std::string roundtrip = toUpper(toLower(original));
    EXPECT_EQ(toUpper(original), roundtrip);
}

// ============================================================================
// TESTS - Whitespace Handling
// ============================================================================

TEST(RemoveWhitespace, BasicRemoval) {
    EXPECT_EQ(removeWhitespace("Hello, world!"), "Hello,world!");
}

TEST(RemoveWhitespace, MultilineString) {
    std::string input = "All\tof\tyour\tfears\n"
                        "All of my hands\r\n"
                        "All\vof\fmy arrows";
    std::string expected = "Allofyourfears"
                          "Allofmyhands"
                          "Allofmyarrows";
    EXPECT_EQ(removeWhitespace(input), expected);
}

TEST(RemoveWhitespace, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(removeWhitespace(""), "");
}

TEST(RemoveWhitespace, OnlyWhitespace_ReturnsEmpty) {
    EXPECT_EQ(removeWhitespace(" \t\n\r\v\f"), "");
}

TEST(TrimWhitespace, BasicTrim) {
    EXPECT_EQ(trimWhitespace(" Hello, world! "), "Hello, world!");
}

TEST(TrimWhitespace, AllTypesOfWhitespace) {
    EXPECT_EQ(trimWhitespace(" \n\t\r\v\f Hello, world! \n\t\r\v\f"), "Hello, world!");
}

TEST(TrimWhitespace, OneSidedTrim) {
    EXPECT_EQ(trimWhitespace("  \rdata"), "data");
}

TEST(TrimWhitespace, NothingToTrim_Unchanged) {
    EXPECT_EQ(trimWhitespace("SmittyWerbenjaegermanjensen"), "SmittyWerbenjaegermanjensen");
}

TEST(TrimWhitespace, OnlyWhitespace_ReturnsEmpty) {
    EXPECT_EQ(trimWhitespace("   \t\n\r   "), "");
}

TEST(Trim, BasicTrimFromBothEnds) {
    EXPECT_EQ(trim("Hello, world!", 1), "ello, world");
}

TEST(Trim, TrimNothing) {
    std::string input = "unchanged";
    EXPECT_EQ(trim(input, 0), input);
}

TEST(Trim, TrimMoreThanHalfLength_ReturnsEmpty) {
    EXPECT_EQ(trim("short", 10), "");
    EXPECT_EQ(trim("test", 2), "");
}

// ============================================================================
// TESTS - String Reversal and Palindromes
// ============================================================================

TEST(Reverse, BasicReversal) {
    EXPECT_EQ(reverse("Hello, world!"), "!dlrow ,olleH");
}

TEST(Reverse, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(reverse(""), "");
}

TEST(Reverse, Palindrome_Unchanged) {
    EXPECT_EQ(reverse("racecar"), "racecar");
}

TEST(IsPalindrome, ValidPalindrome) {
    EXPECT_TRUE(isPalindrome("racecar"));
    EXPECT_TRUE(isPalindrome("noon"));
}

TEST(IsPalindrome, LongPalindrome) {
    EXPECT_TRUE(isPalindrome("gohangasalamiimalasagnahog"));
}

TEST(IsPalindrome, NotPalindrome) {
    EXPECT_FALSE(isPalindrome("hello"));
    EXPECT_FALSE(isPalindrome("There was an anchor"));
}

TEST(IsPalindrome, CaseSensitive_NotPalindrome) {
    // Case and punctuation matter
    EXPECT_FALSE(isPalindrome("A man, a plan, a canal, panama"));
}

TEST(IsPalindrome, EmptyString_IsPalindrome) {
    EXPECT_TRUE(isPalindrome(""));
}

TEST(IsPalindrome, SingleChar_IsPalindrome) {
    EXPECT_TRUE(isPalindrome("a"));
}

// ============================================================================
// TESTS - String Multiplication
// ============================================================================

TEST(Multiply, BasicMultiplication) {
    EXPECT_EQ(multiply("x", 5), "xxxxx");
}

TEST(Multiply, MultiCharString) {
    EXPECT_EQ(multiply("abc", 3), "abcabcabc");
}

TEST(Multiply, TimesZero_ReturnsEmpty) {
    EXPECT_EQ(multiply("test", 0), "");
}

TEST(Multiply, TimesOne_ReturnsSame) {
    EXPECT_EQ(multiply("hello", 1), "hello");
}

TEST(Multiply, EmptyString) {
    EXPECT_EQ(multiply("", 10), "");
}

// Property: Length should equal original length * multiplier
TEST(Multiply, LengthProperty) {
    std::string str = "test";
    int n = 10;
    auto result = multiply(str, n);
    EXPECT_EQ(result.length(), str.length() * n);
}

// ============================================================================
// TESTS - Scramble
// ============================================================================

TEST(Scramble, LengthUnchanged) {
    std::string input = "Hello, World!";
    auto result = scramble(input);
    EXPECT_EQ(result.length(), input.length());
}

TEST(Scramble, ContainsSameCharacters) {
    std::string input = "abcdef";
    auto result = scramble(input);

    // Sort both strings and compare
    std::string sorted_input = input;
    std::string sorted_result = result;
    std::sort(sorted_input.begin(), sorted_input.end());
    std::sort(sorted_result.begin(), sorted_result.end());

    EXPECT_EQ(sorted_input, sorted_result);
}

TEST(Scramble, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(scramble(""), "");
}

TEST(Scramble, SingleChar_Unchanged) {
    EXPECT_EQ(scramble("a"), "a");
}

// ============================================================================
// TESTS - Character Manipulation
// ============================================================================

TEST(EraseCharsFromEnd, EraseOneChar) {
    std::string input = "She pushed her feet across the board walk.";
    std::string expected = "She pushed her feet across the board walk";
    EXPECT_EQ(eraseCharsFromEnd(input, 1), expected);
}

TEST(EraseCharsFromEnd, EraseWholeString) {
    std::string input = "test";
    EXPECT_EQ(eraseCharsFromEnd(input, input.length()), "");
}

TEST(EraseCharsFromEnd, EraseNothing) {
    std::string input = "unchanged";
    EXPECT_EQ(eraseCharsFromEnd(input, 0), input);
}

TEST(EraseCharsFromEnd, EraseMoreThanLength_ReturnsEmpty) {
    EXPECT_EQ(eraseCharsFromEnd("short", 100), "");
}

TEST(EraseCharsFromStart, EraseOneChar) {
    std::string input = "She pushed her feet.";
    std::string expected = "he pushed her feet.";
    EXPECT_EQ(eraseCharsFromStart(input, 1), expected);
}

TEST(EraseCharsFromStart, EraseWholeString) {
    std::string input = "test";
    EXPECT_EQ(eraseCharsFromStart(input, input.length()), "");
}

TEST(EraseCharsFromStart, EraseNothing) {
    std::string input = "unchanged";
    EXPECT_EQ(eraseCharsFromStart(input, 0), input);
}

TEST(EraseNonNumericChars, AllNumeric_Unchanged) {
    EXPECT_EQ(eraseNonNumericChars("0123456789"), "0123456789");
}

TEST(EraseNonNumericChars, NoNumeric_ReturnsEmpty) {
    EXPECT_EQ(eraseNonNumericChars("abcdefg"), "");
}

TEST(EraseNonNumericChars, MixedContent) {
    EXPECT_EQ(eraseNonNumericChars("1 pumpkin, 5 eggplant, 3 squash"), "153");
}

TEST(EraseNonNumericChars, EmptyString_ReturnsEmpty) {
    EXPECT_EQ(eraseNonNumericChars(""), "");
}

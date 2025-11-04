/**
 * @file string_conversion_test.cpp
 * @brief Unit tests for string conversion and formatting functions
 *
 * Tests for: stringToBool, boolToString, charToString, format,
 *            replaceSubstr, mapifyString, stringifyMap
 */

#include <gtest/gtest.h>
#include "../../stevensStringLib.h"
#include "../fixtures/test_data.h"

using namespace stevensStringLib;

// ============================================================================
// TESTS - stringToBool()
// ============================================================================

TEST(StringToBool, TrueVariants_ReturnsTrue) {
    EXPECT_TRUE(stringToBool("true"));
    EXPECT_TRUE(stringToBool("TRUE"));
    EXPECT_TRUE(stringToBool("True"));
    EXPECT_TRUE(stringToBool("tRuE"));
}

TEST(StringToBool, FalseString_ReturnsFalse) {
    EXPECT_FALSE(stringToBool("false"));
    EXPECT_FALSE(stringToBool("FALSE"));
    EXPECT_FALSE(stringToBool("False"));
}

TEST(StringToBool, NumericZero_ReturnsFalse) {
    EXPECT_FALSE(stringToBool("0"));
    EXPECT_FALSE(stringToBool("0.0"));
}

TEST(StringToBool, NumericNonZero_ReturnsTrue) {
    EXPECT_TRUE(stringToBool("1"));
    EXPECT_TRUE(stringToBool("9001"));
    EXPECT_TRUE(stringToBool("-5"));
    EXPECT_TRUE(stringToBool("3.14"));
}

TEST(StringToBool, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(stringToBool(""));
}

TEST(StringToBool, NonBooleanNonNumeric_ReturnsFalse) {
    EXPECT_FALSE(stringToBool("hello"));
    EXPECT_FALSE(stringToBool("yes"));
    EXPECT_FALSE(stringToBool("no"));
}

// ============================================================================
// TESTS - boolToString()
// ============================================================================

TEST(BoolToString, True_ReturnsTrue) {
    EXPECT_EQ(boolToString(true), "true");
}

TEST(BoolToString, False_ReturnsFalse) {
    EXPECT_EQ(boolToString(false), "false");
}

TEST(BoolToString, NumericTruthy_ReturnsTrue) {
    EXPECT_EQ(boolToString(9001), "true");
    EXPECT_EQ(boolToString(-1), "true");
}

TEST(BoolToString, NumericZero_ReturnsFalse) {
    EXPECT_EQ(boolToString(0), "false");
}

// ============================================================================
// TESTS - charToString()
// ============================================================================

TEST(CharToString, BasicChar) {
    EXPECT_EQ(charToString('a'), "a");
    EXPECT_EQ(charToString('Z'), "Z");
}

TEST(CharToString, Digit) {
    EXPECT_EQ(charToString('5'), "5");
}

TEST(CharToString, SpecialChar) {
    EXPECT_EQ(charToString('@'), "@");
}

TEST(CharToString, Newline) {
    EXPECT_EQ(charToString('\n'), "\n");
}

TEST(CharToString, NumericValue) {
    // ASCII 90 is 'Z'
    EXPECT_EQ(charToString(90), "Z");
}

// ============================================================================
// TESTS - format() vector variant
// ============================================================================

TEST(Format_Vector, SingleReplacement) {
    std::string str = "Man, it sure is {0} around here!";
    auto result = format(str, {"boring"});
    EXPECT_EQ(result, "Man, it sure is boring around here!");
}

TEST(Format_Vector, MultipleReplacements) {
    std::string str = "{2}{1}{3}{4}{0}";
    auto result = format(str, {"emerald?", "DAMN ", "Where's that ", "fourth ", "chaos "});
    EXPECT_EQ(result, "Where's that DAMN fourth chaos emerald?");
}

TEST(Format_Vector, NoMatchingIndices_Unchanged) {
    std::string str = "{Bacon} {Lettuce} {Tomato}";
    auto result = format(str, {"pb", "and", "j"});
    EXPECT_EQ(result, "{Bacon} {Lettuce} {Tomato}");
}

TEST(Format_Vector, OutOfBoundsIndex_Unchanged) {
    std::string str = "{0} {1} {5}";
    auto result = format(str, {"first", "second"});
    EXPECT_EQ(result, "first second {5}");
}

TEST(Format_Vector, NestedBraces) {
    std::string str = "{1{2}}{feelin{0}nesty}{{yo}}";
    auto result = format(str, {"zero", "one", "two"});
    EXPECT_EQ(result, "{1two}{feelinzeronesty}{{yo}}");
}

TEST(Format_Vector, EmptyString) {
    auto result = format("", {"test"});
    EXPECT_EQ(result, "");
}

TEST(Format_Vector, EmptyVector) {
    auto result = format("{0} {1}", {});
    EXPECT_EQ(result, "{0} {1}");
}

// ============================================================================
// TESTS - format() map variant
// ============================================================================

TEST(Format_Map, SingleReplacement) {
    std::string str = "You are known as jimmy the {title}!";
    std::unordered_map<std::string, std::string> map = {{"title", "bandit"}};
    auto result = format(str, map);
    EXPECT_EQ(result, "You are known as jimmy the bandit!");
}

TEST(Format_Map, MultipleReplacements) {
    std::string str = "Abandon {noun1}, all ye who {verb1} here!";
    std::unordered_map<std::string, std::string> map = {
        {"noun1", "smelliness"},
        {"verb1", "shower"}
    };
    auto result = format(str, map);
    EXPECT_EQ(result, "Abandon smelliness, all ye who shower here!");
}

TEST(Format_Map, NestedBraces) {
    std::string str = "You enter the {dungeon of {dungeonOwner}}$[textColor=red]!";
    std::unordered_map<std::string, std::string> map = {{"dungeonOwner", "jimmy"}};
    auto result = format(str, map);
    EXPECT_EQ(result, "You enter the {dungeon of jimmy}$[textColor=red]!");
}

TEST(Format_Map, EmptyString) {
    std::unordered_map<std::string, std::string> map = {{"key", "value"}};
    auto result = format("", map);
    EXPECT_EQ(result, "");
}

TEST(Format_Map, EmptyMap) {
    std::unordered_map<std::string, std::string> map = {};
    auto result = format("{key}", map);
    EXPECT_EQ(result, "{key}");
}

TEST(Format_Map, KeyNotInMap_Unchanged) {
    std::string str = "{exists} {missing}";
    std::unordered_map<std::string, std::string> map = {{"exists", "found"}};
    auto result = format(str, map);
    EXPECT_EQ(result, "found {missing}");
}

// ============================================================================
// TESTS - replaceSubstr()
// ============================================================================

TEST(ReplaceSubstr, ReplaceAllOccurrences) {
    std::string str = "The fox is quick. The fox is clever.";
    auto result = replaceSubstr(str, "fox", "wolf");
    EXPECT_EQ(result, "The wolf is quick. The wolf is clever.");
}

TEST(ReplaceSubstr, ReplaceLimitedQuantity) {
    std::string str = "The fox is quick. The fox is clever.";
    auto result = replaceSubstr(str, "fox", "wolf", 1);
    EXPECT_EQ(result, "The wolf is quick. The fox is clever.");
}

TEST(ReplaceSubstr, ReplaceFromRight) {
    std::string str = "The fox is quick. The fox is clever.";
    auto result = replaceSubstr(str, "fox", "wolf", 1, "right");
    EXPECT_EQ(result, "The fox is quick. The wolf is clever.");
}

TEST(ReplaceSubstr, TargetNotFound_Unchanged) {
    std::string str = "The cat is quick.";
    auto result = replaceSubstr(str, "fox", "wolf");
    EXPECT_EQ(result, "The cat is quick.");
}

TEST(ReplaceSubstr, EmptyTarget_Unchanged) {
    std::string str = "hello";
    auto result = replaceSubstr(str, "", "X");
    EXPECT_EQ(result, "hello");
}

TEST(ReplaceSubstr, ReplaceWithEmpty) {
    std::string str = "hello world";
    auto result = replaceSubstr(str, " ", "");
    EXPECT_EQ(result, "helloworld");
}

TEST(ReplaceSubstr, ReplacementLongerThanTarget) {
    std::string str = "a b c";
    auto result = replaceSubstr(str, " ", " and ");
    EXPECT_EQ(result, "a and b and c");
}

// ============================================================================
// TESTS - mapifyString() and stringifyMap()
// ============================================================================

TEST(MapifyString, BasicParsing) {
    std::string str = "textColor=red,bgColor=green,bold=true";
    auto result = mapifyString(str, "=", ",");

    EXPECT_EQ(result["textColor"], "red");
    EXPECT_EQ(result["bgColor"], "green");
    EXPECT_EQ(result["bold"], "true");
}

TEST(MapifyString, CustomSeparators) {
    std::string str = "name:John;age:30;city:NYC";
    auto result = mapifyString(str, ":", ";");

    EXPECT_EQ(result["name"], "John");
    EXPECT_EQ(result["age"], "30");
    EXPECT_EQ(result["city"], "NYC");
}

TEST(MapifyString, EmptyString) {
    auto result = mapifyString("", "=", ",");
    EXPECT_TRUE(result.empty());
}

TEST(MapifyString, KeyWithoutValue) {
    std::string str = "key1=value1,key2,key3=value3";
    auto result = mapifyString(str, "=", ",");

    EXPECT_EQ(result["key1"], "value1");
    EXPECT_EQ(result["key2"], "");  // Empty value
    EXPECT_EQ(result["key3"], "value3");
}

TEST(StringifyMap, BasicConversion) {
    std::map<std::string, std::string> map = {
        {"CultGame", "Jeff Stevens"},
        {"Kindred Fates", "Rob Cravens"},
        {"Warsim", "Huw Milward"}
    };

    auto result = stringifyMap(map);

    // Map is ordered, so output is predictable
    EXPECT_TRUE(contains(result, "Warsim:Huw Milward"));
    EXPECT_TRUE(contains(result, "CultGame:Jeff Stevens"));
    EXPECT_TRUE(contains(result, "Kindred Fates:Rob Cravens"));
}

TEST(StringifyMap, CustomSeparators) {
    std::map<std::string, std::string> map = {
        {"key1", "value1"},
        {"key2", "value2"}
    };

    auto result = stringifyMap(map, "=", ";");
    EXPECT_TRUE(contains(result, "key1=value1"));
    EXPECT_TRUE(contains(result, "key2=value2"));
    EXPECT_TRUE(contains(result, ";"));
}

TEST(StringifyMap, EmptyMap) {
    std::map<std::string, std::string> map = {};
    auto result = stringifyMap(map);
    EXPECT_EQ(result, "");
}

// Property: mapifyString and stringifyMap are inverses
TEST(MapConversion, RoundtripProperty) {
    std::map<std::string, std::string> original = {
        {"a", "1"},
        {"b", "2"},
        {"c", "3"}
    };

    auto stringified = stringifyMap(original);
    auto roundtrip = mapifyString(stringified);

    EXPECT_EQ(original, roundtrip);
}

// ============================================================================
// TESTS - Other Conversion Functions
// ============================================================================

TEST(EraseTrailingZeroes, RemovesTrailingZeros) {
    EXPECT_EQ(eraseTrailingZeroes(123.5f), "123.5");
}

TEST(EraseTrailingZeroes, RemovesDecimalPoint) {
    EXPECT_EQ(eraseTrailingZeroes(123.0f), "123");
}

TEST(EraseTrailingZeroes, NoTrailingZeros) {
    std::string result = eraseTrailingZeroes(123.456f);
    EXPECT_TRUE(result.find("123.456") == 0);
}

TEST(CsvAppend, AppendToExisting) {
    std::string csvs = "apple,banana,cherry";
    csvAppend(csvs, "date");
    EXPECT_EQ(csvs, "apple,banana,cherry,date");
}

TEST(CsvAppend, AppendToEmpty) {
    std::string csvs = "";
    csvAppend(csvs, "apple");
    EXPECT_EQ(csvs, "apple");
}

TEST(CsvAppend, CustomDelimiter) {
    std::string csvs = "apple;banana";
    csvAppend(csvs, "cherry", ';');
    EXPECT_EQ(csvs, "apple;banana;cherry");
}

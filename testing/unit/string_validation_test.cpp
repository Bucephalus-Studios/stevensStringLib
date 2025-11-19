/**
 * @file string_validation_test.cpp
 * @brief Unit tests for string validation functions
 *
 * Tests for: isInteger, isFloat, isNumber, isStandardNumber, isScientificNumber
 */

#include <gtest/gtest.h>
#include "../../stevensStringLib.h"
#include "../fixtures/test_data.h"

using namespace stevensStringLib;

// ============================================================================
// PARAMETERIZED NUMBER VALIDATION TESTS
// ============================================================================

/**
 * @brief Test case structure for comprehensive number validation
 */
struct NumberTestCase {
    std::string input;
    bool is_integer;
    bool is_float;
    bool is_standard;
    bool is_scientific;
    bool is_number;

    friend std::ostream& operator<<(std::ostream& os, const NumberTestCase& tc) {
        return os << "input='" << tc.input << "'";
    }
};

class NumberValidationTest : public ::testing::TestWithParam<NumberTestCase> {};

TEST_P(NumberValidationTest, ValidatesCorrectly) {
    const auto& tc = GetParam();

    EXPECT_EQ(isInteger(tc.input), tc.is_integer)
        << "isInteger failed for: " << tc.input;
    EXPECT_EQ(isFloat(tc.input), tc.is_float)
        << "isFloat failed for: " << tc.input;
    EXPECT_EQ(isStandardNumber(tc.input), tc.is_standard)
        << "isStandardNumber failed for: " << tc.input;
    EXPECT_EQ(isScientificNumber(tc.input), tc.is_scientific)
        << "isScientificNumber failed for: " << tc.input;
    EXPECT_EQ(isNumber(tc.input), tc.is_number)
        << "isNumber failed for: " << tc.input;
}

INSTANTIATE_TEST_SUITE_P(
    ComprehensiveNumberTests,
    NumberValidationTest,
    ::testing::Values(
        // {input, is_int, is_float, is_std, is_sci, is_num}
        NumberTestCase{"0", true, true, true, false, true},
        NumberTestCase{"123", true, true, true, false, true},
        NumberTestCase{"-456", true, true, true, false, true},
        NumberTestCase{"+789", true, true, true, false, true},
        NumberTestCase{"123.0", true, true, true, false, true},
        NumberTestCase{"123.5", false, true, true, false, true},
        NumberTestCase{"-987.654", false, true, true, false, true},
        NumberTestCase{".5", false, true, true, false, true},
        NumberTestCase{"5.", false, true, true, false, true},
        NumberTestCase{"1.23e10", false, true, false, true, true},
        NumberTestCase{"2.5e-3", false, true, false, true, true},
        NumberTestCase{"3.14E2", false, true, false, true, true},
        NumberTestCase{"1.5x10^3", false, false, false, true, true},
        NumberTestCase{"2.0X10^-2", false, false, false, true, true},
        NumberTestCase{"3.5*10^5", false, false, false, true, true},
        NumberTestCase{"", false, false, false, false, false},
        NumberTestCase{"abc", false, false, false, false, false},
        NumberTestCase{"12.34.56", false, false, false, false, false},
        NumberTestCase{"1a2b3c", false, false, false, false, false}
    )
);

// ============================================================================
// INDIVIDUAL FUNCTION TESTS - isInteger
// ============================================================================

TEST(IsInteger, ValidPositiveInteger) {
    EXPECT_TRUE(isInteger("100"));
    EXPECT_TRUE(isInteger("0"));
    EXPECT_TRUE(isInteger("999999"));
}

TEST(IsInteger, ValidNegativeInteger) {
    EXPECT_TRUE(isInteger("-100"));
    EXPECT_TRUE(isInteger("-1"));
}

TEST(IsInteger, IntegerWithTrailingZeros) {
    EXPECT_TRUE(isInteger("123.0"));
    EXPECT_TRUE(isInteger("100.00"));
}

TEST(IsInteger, FloatWithDecimals_ReturnsFalse) {
    EXPECT_FALSE(isInteger("3.14159"));
    EXPECT_FALSE(isInteger("123.5"));
}

TEST(IsInteger, OverflowNumber_ReturnsFalse) {
    EXPECT_FALSE(isInteger("9999999999999999999999999999999"));
}

TEST(IsInteger, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(isInteger(""));
}

TEST(IsInteger, NonNumericString_ReturnsFalse) {
    EXPECT_FALSE(isInteger("beebop"));
    EXPECT_FALSE(isInteger("abc123"));
}

TEST(IsInteger, Expression_ReturnsFalse) {
    EXPECT_FALSE(isInteger("(3/2)+4"));
}

// ============================================================================
// INDIVIDUAL FUNCTION TESTS - isFloat
// ============================================================================

TEST(IsFloat, ValidFloatWithDecimals) {
    EXPECT_TRUE(isFloat("1.5"));
    EXPECT_TRUE(isFloat("3.14159"));
}

TEST(IsFloat, ValidNegativeFloat) {
    EXPECT_TRUE(isFloat("-1.5"));
    EXPECT_TRUE(isFloat("-999.999"));
}

TEST(IsFloat, IntegerIsValidFloat) {
    EXPECT_TRUE(isFloat("42"));
    EXPECT_TRUE(isFloat("-100"));
}

TEST(IsFloat, NothingLeftOfDecimal_IsValid) {
    EXPECT_TRUE(isFloat(".2"));
    EXPECT_TRUE(isFloat(".999"));
}

TEST(IsFloat, ScientificNotation_IsValid) {
    EXPECT_TRUE(isFloat("2.05e3"));
    EXPECT_TRUE(isFloat("1.23E-10"));
}

TEST(IsFloat, VeryPreciseNumber_IsValid) {
    EXPECT_TRUE(isFloat(".123412312312312312312312312312312331231231231"));
}

TEST(IsFloat, MultipleDecimalPoints_ReturnsFalse) {
    EXPECT_FALSE(isFloat("7.0.0"));
    EXPECT_FALSE(isFloat("1.2.3.4"));
}

TEST(IsFloat, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(isFloat(""));
}

// ============================================================================
// INDIVIDUAL FUNCTION TESTS - isStandardNumber
// ============================================================================

TEST(IsStandardNumber, Zero_IsValid) {
    EXPECT_TRUE(isStandardNumber("0"));
    EXPECT_TRUE(isStandardNumber("0.0"));
}

TEST(IsStandardNumber, LargeNumberThatWouldOverflow_IsValid) {
    EXPECT_TRUE(isStandardNumber("-214748364721474836472147483647.123123123123123"));
}

TEST(IsStandardNumber, ScientificNumber_ReturnsFalse) {
    EXPECT_FALSE(isStandardNumber("2.5e2"));
    EXPECT_FALSE(isStandardNumber("1.0E10"));
}

TEST(IsStandardNumber, SignedZero_ReturnsFalse) {
    // Standard notation should not have signed zeros
    EXPECT_FALSE(isStandardNumber("+0"));
    EXPECT_FALSE(isStandardNumber("-0"));
    EXPECT_FALSE(isStandardNumber("+0.0"));
    EXPECT_FALSE(isStandardNumber("-0.00"));
}

TEST(IsStandardNumber, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(isStandardNumber(""));
}

TEST(IsStandardNumber, SingleDigit_IsValid) {
    EXPECT_TRUE(isStandardNumber("5"));
    EXPECT_TRUE(isStandardNumber("9"));
}

// ============================================================================
// INDIVIDUAL FUNCTION TESTS - isScientificNumber
// ============================================================================

TEST(IsScientificNumber, ValidWithLowercaseE) {
    EXPECT_TRUE(isScientificNumber("2.5e2"));
    EXPECT_TRUE(isScientificNumber("1.0e-10"));
}

TEST(IsScientificNumber, ValidWithUppercaseE) {
    EXPECT_TRUE(isScientificNumber("5.22E32"));
    EXPECT_TRUE(isScientificNumber("3.14E-5"));
}

TEST(IsScientificNumber, ValidWithX) {
    EXPECT_TRUE(isScientificNumber("+1.17x10^532"));
    EXPECT_TRUE(isScientificNumber("2.5x10^-3"));
}

TEST(IsScientificNumber, ValidWithUppercaseX) {
    EXPECT_TRUE(isScientificNumber("6232.006X10^11"));
}

TEST(IsScientificNumber, ValidWithAsterisk) {
    EXPECT_TRUE(isScientificNumber("0.023*10^5"));
}

TEST(IsScientificNumber, StandardNumber_ReturnsFalse) {
    EXPECT_FALSE(isScientificNumber("-23456"));
    EXPECT_FALSE(isScientificNumber("123.456"));
}

TEST(IsScientificNumber, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(isScientificNumber(""));
}

TEST(IsScientificNumber, NoExponent_ReturnsFalse) {
    EXPECT_FALSE(isScientificNumber("123.456"));
}

// ============================================================================
// INDIVIDUAL FUNCTION TESTS - isNumber
// ============================================================================

TEST(IsNumber, ValidStandardNumber) {
    EXPECT_TRUE(isNumber("-123456789101112131415"));
    EXPECT_TRUE(isNumber("3.14159"));
}

TEST(IsNumber, ValidScientificNumber) {
    EXPECT_TRUE(isNumber("7.92850238e28"));
    EXPECT_TRUE(isNumber("1.5x10^10"));
}

TEST(IsNumber, NonNumericString_ReturnsFalse) {
    EXPECT_FALSE(isNumber("A blood moon is rising to honor the old ancient skies!"));
}

TEST(IsNumber, MixedAlphanumeric_ReturnsFalse) {
    EXPECT_FALSE(isNumber("f4h6c3k0f6k2la05jfm49gn3o320tjniew"));
}

TEST(IsNumber, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(isNumber(""));
}

// ============================================================================
// TESTS - getWhitespaceString()
// ============================================================================

TEST(GetWhitespaceString, ContainsTab) {
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    EXPECT_TRUE(contains(whitespaceString, "\t"));
}

TEST(GetWhitespaceString, ContainsNewline) {
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    EXPECT_TRUE(contains(whitespaceString, "\n"));
}

TEST(GetWhitespaceString, ContainsVerticalTab) {
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    EXPECT_TRUE(contains(whitespaceString, "\v"));
}

TEST(GetWhitespaceString, ContainsFormFeed) {
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    EXPECT_TRUE(contains(whitespaceString, "\f"));
}

TEST(GetWhitespaceString, ContainsCarriageReturn) {
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    EXPECT_TRUE(contains(whitespaceString, "\r"));
}

TEST(GetWhitespaceString, ContainsSpace) {
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    EXPECT_TRUE(contains(whitespaceString, " "));
}

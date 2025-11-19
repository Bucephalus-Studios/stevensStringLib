/**
 * @file test_data.h
 * @brief Centralized test data management for stevensStringLib tests
 *
 * This file provides reusable test fixtures and common test data
 * to ensure consistency across all test suites.
 */

#pragma once

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace TestData {

/**
 * @brief Fixture for large text file testing
 *
 * Lazy-loads the Frankenstein text file only once per test run
 * for efficiency in tests that need large text data.
 */
class LargeTextFixture : public ::testing::Test {
protected:
    inline static std::string frankenstein_text;
    inline static bool loaded = false;

public:
    static void SetUpTestSuite() {
        if (!loaded) {
            std::filesystem::path test_file =
                std::filesystem::path(__FILE__).parent_path().parent_path() /
                "test_string_files" / "frankenstein.txt";

            std::ifstream file(test_file);
            if (!file.is_open()) {
                throw std::runtime_error(
                    "Cannot load test file: " + test_file.string() +
                    "\nMake sure test_string_files/frankenstein.txt exists"
                );
            }

            frankenstein_text = std::string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
            );
            loaded = true;
        }
    }

    static const std::string& getFrankenstein() {
        return frankenstein_text;
    }
};

/**
 * @brief Common test strings used across multiple test suites
 */
namespace Strings {
    constexpr auto EMPTY = "";
    constexpr auto SINGLE_CHAR = "a";
    constexpr auto SIMPLE = "Hello, World!";
    constexpr auto UNICODE_BASIC = "Hello 世界";
    constexpr auto UNICODE_EMOJI = "Hello 🌍🎉";
    constexpr auto WHITESPACE_ALL = " \t\n\r\v\f ";
    constexpr auto WHITESPACE_MIXED = "  \tHello\n\rWorld  \v\f";
    constexpr auto NUMERIC_INTEGER = "12345";
    constexpr auto NUMERIC_FLOAT = "123.456";
    constexpr auto NUMERIC_SCIENTIFIC = "1.23e-4";
    constexpr auto NUMERIC_NEGATIVE = "-987.65";
    constexpr auto ALPHANUMERIC = "abc123XYZ";
    constexpr auto SPECIAL_CHARS = "!@#$%^&*()_+-=[]{}|;:',.<>?/";
    constexpr auto PALINDROME = "racecar";
    constexpr auto CSV_SAMPLE = "apple,banana,cherry,date,elderberry";
    constexpr auto REPEATED_SEPARATORS = "a,,b,,,c,,,,d";
}

/**
 * @brief Test data for number validation tests
 */
namespace Numbers {
    // Valid integers
    inline const std::vector<std::string> VALID_INTEGERS = {
        "0", "1", "123", "-456", "9999", "+42"
    };

    // Valid floats
    inline const std::vector<std::string> VALID_FLOATS = {
        "0.0", "1.5", "123.456", "-987.654", ".5", "5.", "1.0e10", "2.5e-3"
    };

    // Invalid numbers
    inline const std::vector<std::string> INVALID_NUMBERS = {
        "", "abc", "12.34.56", "1.2.3e4", "inf", "NaN", "12a34"
    };
}

} // namespace TestData

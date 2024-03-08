/**
 * This is the code for testing stevensStringLib. All testing is carried out with GoogleTest.
 * 
 * To run these tests on your machine, you should use the cmake tool in the "testing" folder by running the command "cmake -S . -B build".
 * This will generate an makefile to create an executable in the "build_of_test" folder. Then, go to the "build_of_test" folder and run the command "make".
 * Once you have done this, you should have an executable named "test" in the "build_of_test" folder which you can run.
*/

#include "../stevensStringLib.h"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>


using namespace stevensStringLib;


std::string frankenstein_fulltext;


/*** Contains ***/
TEST( contains, substring_is_string )
{
    //Arrange
    std::string string = "hello";
    std::string substring = "hello";
    //Act and assert
    ASSERT_TRUE(contains(string, substring));
}

TEST( contains, empty_string_and_empty_substring)
{
    //Arrange
    std::string string = "";
    std::string substring = "";
    //Act and assert
    ASSERT_TRUE(contains(string, substring));
}

TEST( contains, string_contains_empty_string)
{
    //Arrange
    std::string string = "hello";
    std::string substring = "";
    //Act and assert
    ASSERT_TRUE(contains(string, substring));
}

TEST( contains, empty_string_does_not_contain_string)
{
    //Arrange
    std::string string = "";
    std::string substring = "hello";
    //Act and assert
    ASSERT_FALSE(contains(string, substring));
}

TEST( contains, test_on_large_string)
{
    //Arrange
    std::string substring = "conflagration";
    //Act and assert
    ASSERT_TRUE(contains(frankenstein_fulltext, substring));
}


/*** containsOnly ***/
TEST( containsOnly, check_string_of_zeroes_and_one)
{
    //Arrange
    std::string string = "000000000000000000000000000000000000001";
    std::string chars = "01";
    //Act and assert
    ASSERT_TRUE(containsOnly(string, chars)) << "string=" << string << "\nchars=" << chars;
}

TEST( containsOnly, check_string_of_ones_and_twos)
{
    //Arrange
    std::string string = "11101112222";
    std::string chars = "12";
    //Act and assert
    ASSERT_FALSE(containsOnly(string,chars)) << "string" << string << "\nchars=" << chars;
}   

TEST( containsOnly, check_empty_string_with_empty_chars)
{
    //Arrange
    std::string string = "";
    std::string chars = "";
    //Act and assert
    ASSERT_TRUE(containsOnly(string,chars)) << "string" << string << "\nchars=" << chars;
}

TEST( containsOnly, check_string_with_empty_chars)
{
    //Arrange
    std::string string = "This is my vision!";
    std::string chars = "";
    //Act and assert
    ASSERT_FALSE(containsOnly(string,chars)) << "string" << string << "\nchars=" << chars;
}


/***  Separate  ***/
TEST( separate, separate_3_comma_delmited_words)
{
    //Arrange
    std::string string = "Charmander,Squirtle,Bulbasaur";
    std::vector<std::string> modelResult = {"Charmander","Squirtle","Bulbasaur"};
    //Act
    std::vector<std::string> result = separate(string);
    //Assert
    if(result == modelResult)
    {
        SUCCEED();
    }
    else
    {
        std::cout << "Expected result: " << std::endl;
        for(int i = 0; i < modelResult.size(); i++)
        {
            std::cout << modelResult[i] << std::endl;
        }
        std::cout << "Actual result: " << std::endl;
        for(int i = 0; i < result.size(); i++)
        {
            std::cout << result[i] << std::endl;
        }
        FAIL();
    }
}

TEST( separate, separate_a_large_string_with_no_separator_character_found )
{
    //Arrange
        //Using frankenstein as string to separate
        //Using '@' to separate, where none exist in the fulltext of frankenstein
    //Act
    std::vector<std::string> result = separate(frankenstein_fulltext, "@");
    //Assert
        //Separating a string with a character that doesn't exist within it will not result in a split string. 
        //The result should be the entire non-separated string as the first element of the vector.
    EXPECT_EQ(result.size(),1);
    ASSERT_TRUE(result[0] == frankenstein_fulltext);
}

//Note: This works but does not count the get the last line, so it creates a vector of size equal the number of lines minus 1.
TEST( separate, separate_a_large_string_by_newline)
{
    //Arrange
        //Using frankenstein as a string to separate
    std::string separator = "\n";
    //Act
    std::vector<std::string> result = separate(frankenstein_fulltext, separator);
    //Assert
    ASSERT_EQ(result.size(), 7742);
}


TEST( separate, separate_by_empty_string)
{
    //Arrange
    std::string string = "Hello, world!";
    std::string separator = "";
    std::vector<std::string> modelResult = {"H","e","l","l","o",","," ","w","o","r","l","d","!"};
    //Act
    std::vector<std::string> result = separate(string, separator);
    //Assert
    if(result == modelResult)
    {
        SUCCEED();
    }
    else
    {
        FAIL();
    }
}


TEST( separate, separate_by_a_separator_of_length_5)
{
    //Arrange
    std::string string = "bacon strips and bacon strips and bacon strips and bacon strips";
    std::string separator = " and ";
    std::vector<std::string> modelResult = {"bacon strips", "bacon strips", "bacon strips", "bacon strips"};
    //Act
    std::vector<std::string> result = separate(string, separator);
    //Assert
    if(result == modelResult)
    {
        SUCCEED();
    }
    else
    {
        FAIL();
    }
}


/*** cap1stChar ***/
TEST(cap1stChar, capitalize_a_name)
{
    //Arrange
    std::string name = "john";
    //Act
    std::string result = cap1stChar(name);
    //Assert
    ASSERT_STREQ(result.c_str(),"John");
}

TEST(cap1stChar, already_capitalized)
{
    //Arrange
    std::string name = "Jeff";
    //Act
    std::string result = cap1stChar(name);
    //Assert
    ASSERT_STREQ(result.c_str(),"Jeff");
}

TEST(cap1stChar, empty_string)
{
    //Arrange
    std::string emptyString = "";
    //Act
    std::string result = cap1stChar(emptyString);
    //Assert
    ASSERT_STREQ(result.c_str(),"");
}


/*** toUpper ***/
TEST(toUpper, hello_world_to_upper_case)
{
    //Arrange
    std::string string = "Hello, world!";
    std::string modelResult = "HELLO, WORLD!";
    //Act
    std::string result = toUpper(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(toUpper, empty_string)
{
    //Arrange
    std::string emptyString = "";
    //Act
    std::string result = toUpper(emptyString);
    //Assert
    ASSERT_STREQ(emptyString.c_str(), result.c_str());
}

TEST(toUpper, already_all_upper_case)
{
    //Arrange
    std::string string = "IM BIG ANGRY";
    //Act
    std::string result = toUpper(string);
    //Assert
    ASSERT_STREQ(string.c_str(), result.c_str());
}

TEST(toUpper, all_numbers_and_symbols)
{
    //Arrange
    std::string string = "123456789!@#$%^&*()";
    //Act
    std::string result = toUpper(string);
    //Assert
    ASSERT_STREQ(string.c_str(), result.c_str());
}


/*** isInteger ***/
TEST(isInteger, check_100)
{
    //Arrange
    std::string string = "100";
    //Act and assert
    ASSERT_TRUE(isInteger(string)) << "string=" << string;
}

TEST(isInteger, check_negative_100)
{
    //Arrange
    std::string string = "-100";
    //Act and assert
    ASSERT_TRUE(isInteger(string)) << "string=" << string;
}

TEST(isInteger, check_non_integer)
{
    //Arrange
    std::string string = "beebop";
    //Act and assert
    ASSERT_FALSE(isInteger(string)) << "string=" << string;
}

TEST(isInteger, check_overflowed_number)
{
    //Arrange
    std::string string = "9999999999999999999999999999999";
    //Act and assert
    ASSERT_FALSE(isInteger(string)) << "string=" << string;
}

TEST(isInteger, check_float)
{
    //Arrange
    std::string string = "3.14159";
    //Act and assert
    ASSERT_FALSE(isInteger(string)) << "string=" << string;
}

TEST(isInteger, check_expression)
{
    //Arrange
    std::string string = "(3/2)+4";
    //Act and assert
    ASSERT_FALSE(isInteger(string)) << "string=" << string;
}

TEST(isInteger, check_empty_string)
{
    //Arrange
    std::string string = "";
    //Act and assert
    ASSERT_FALSE(isInteger(string)) << "string=" << string;
}


/*** isFloat ***/
TEST(isFloat, check_1point5)
{
    //Arrange
    std::string string = "1.5";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, check_negative_1point5)
{
    //Arrange
    std::string string = "-1.5";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, check_for_only_one_decimal_point)
{
    //Arrange
    std::string string = "7.0.0";
    //Act and assert
    ASSERT_FALSE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, nothing_to_left_of_point)
{
    //Arrange
    std::string string = ".2";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, check_scientific_notation)
{
    //Arrange
    std::string string = "2.05e3";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, very_precise_number)
{
    //Arrange
    std::string string = ".123412312312312312312312312312312331231231231231231231234123123123123123123123123123123312312312312312312312341231231231231231231231231231233123123123123123123";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}


TEST(isFLoat, lots_of_insignificant_figures)
{
    //Arrange
    std::string string = "1.23000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //ACt and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string; 
}


TEST(isFloat, check_empty_string)
{
    //Arrange
    std::string string = "";
    //Act and assert
    ASSERT_FALSE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, check_42)
{
    //Arrange
    std::string string = "42";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}

TEST(isFloat, check_precise_scientfic_number)
{
    //Arrange
    std::string string = "8.025000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e2";
    //Act and assert
    ASSERT_TRUE(isFloat(string)) << "string=" << string;
}


/*** isStandardNumber ***/
TEST(isStandardNumber, check_zero)
{
    //Arrange
    std::string string = "0";
    //Act and assert
    ASSERT_TRUE(isStandardNumber(string)) << "string=" << string;
}

TEST(isStandardNumber, check_big_number_that_will_overflow)
{
    //Arrange
    std::string string = "-214748364721474836472147483647.123123123123123";
    //Act and assert
    ASSERT_TRUE(isStandardNumber(string)) << "string=" << string;
}

TEST(isStandardNumber, check_scientific_number)
{
    //Arrange
    std::string string = "2.5e2";
    //Act and assert
    ASSERT_FALSE(isStandardNumber(string)) << "string=" << string;
}


/*** isScientificNumber ***/
TEST(isScientificNumber, check_scientific_number_with_e)
{
    //Arrange
    std::string string = "2.5e2";
    //Act and assert
    ASSERT_TRUE(isScientificNumber(string)) << "string=" << string;
}

TEST(isScientificNumber, check_scientific_number_with_uppercase_e)
{
    //Arrange
    std::string string = "5.22E32";
    //Act and assert
    ASSERT_TRUE(isScientificNumber(string)) << "string=" << string;
}

TEST(isScientificNumber, check_scientific_number_with_x)
{
    //Arrange
    std::string string = "+1.17x10^532";
    //Act and assert
    ASSERT_TRUE(isScientificNumber(string)) << "string=" << string;
}

TEST(isScientificNumber, check_scientific_number_with_uppercase_x)
{
    //Arrange
    std::string string = "6232.006X10^11";
    //Act and assert
    ASSERT_TRUE(isScientificNumber(string)) << "string=" << string;
}

TEST(isScientificNumber, check_scientific_number_with_asterisk)
{
    //Arrange
    std::string string = "0.023*10^5";
    //Act and assert
    ASSERT_TRUE(isScientificNumber(string)) << "string=" << string;
}

TEST(isScientificNumber, check_standard_number)
{
    //Arrange
    std::string string = "-23456";
    //Act and assert
    ASSERT_FALSE(isScientificNumber(string)) << "string=" << string;
}


/*** isNumber ***/
TEST(isNumber, check_non_number)
{
    //Arrange
    std::string string = "A blood moon is rising to honor the old ancient skies!";
    //Act and assert
    ASSERT_FALSE(isNumber(string)) << "string=" << string;
}

TEST(isNumber, check_number_and_letter_mix)
{
    //Arrange
    std::string string = "f4h6c3k0f6k2la05jfm49gn3o320tjniew";
    //Act and assert
    ASSERT_FALSE(isNumber(string)) << "string=" << string;
}

TEST(isNumber, check_scientific_number)
{
    //Arrange
    std::string string = "7.92850238e28";
    //Act and assert
    ASSERT_TRUE(isNumber(string)) << "string=" << string;
}

TEST(isNumber, check_real_number)
{
    //Arrange
    std::string string = "-123456789101112131415";
    //Act and assert
    ASSERT_TRUE(isNumber(string)) << "string=" << string;
}


/*** stringToBool ***/
TEST(stringToBoolTest, check_true)
{
    //Arrange
    std::string string = "true";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(stringToBoolTest, check_false)
{
    //Arrange
    std::string string = "false";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(stringToBoolTest, check_TRUE)
{
    //Arrange
    std::string string = "TRUE";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(stringToBoolTest, check_FALSE)
{
    //Arrange
    std::string string = "FALSE";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(stringToBoolTest, check_true_alternating_caps)
{
    //Arrange
    std::string string = "tRuE";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(stringToBoolTest, check_0)
{
    //Arrange
    std::string string = "0";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(stringToBoolTest, check_9001)
{
    //Arrange
    std::string string = "9001";
    //Act
    bool result = stringToBool(string);
    //Assert
    ASSERT_TRUE(result);
}


/*** boolToString ***/
TEST(boolToStringTest, check_true)
{
    //Arrange
    bool myBool = true;
    //Act
    std::string result = boolToString(myBool);
    //Assert
    ASSERT_STREQ(result.c_str(), "true");
}

TEST(boolToStringTest, check_false)
{
    //Arrange
    bool myBool = false;
    //Act
    std::string result = boolToString(myBool);
    //Assert
    ASSERT_STREQ(result.c_str(), "false");
}

TEST(boolToStringTest, check_9001)
{
    //Arrange
    int myInt = 9001;
    //Act
    std::string result = boolToString(myInt);
    //Assert
    ASSERT_STREQ(result.c_str(), "true");
}

TEST(boolToStringTest, check_0)
{
    //Arrange
    int myInt = 0;
    //Act
    std::string result = boolToString(myInt);
    //Assert
    ASSERT_STREQ(result.c_str(), "false");
}


/*** trim ***/
TEST(trim, trim_1_from_hello_world)
{
    //Arrange
    std::string string = "Hello, world!";
    //Act
    std::string result = trim(string, 1);
    //Assert
    ASSERT_STREQ(result.c_str(), "ello, world");
}

TEST(trim, trim_both_halves_of_string)
{
    //Arrange
    std::string string = "[1st half][2nd half]";
    //Act
    std::string result = trim(string, 10);
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}

TEST(trim, trim_nothing)
{
    //Arrange
    std::string string = "Heavy weight, one more stone. Leaving flaming arrow.";
    //Act
    std::string result = trim(string, 0);
    //Assert
    ASSERT_STREQ(result.c_str(), string.c_str());
}

TEST(trim, trim_whole_length_of_string)
{
    //Arrange
    std::string string = "How could we wake up with what we know?";
    //Act
    std::string result = trim(string, string.length());
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}


/*** removeWhitespace ***/
TEST(removeWhitespace, hello_world)
{
    //Arrange
    std::string string = "Hello, world!";
    //Act
    std::string result = removeWhitespace(string);
    //Assert
    ASSERT_STREQ(result.c_str(), "Hello,world!");
}

TEST(removeWhitespace, remove_whitespace_from_multiline_string)
{
    //Arrange
    std::string string = "All\tof\tyour\tfears\tare\twell-founded\tand\ttrue\n"
                         "All of my hands are callous and cruel\n"
                         "All\rof\rmy\rarrows\rthat\rriddle\ryou\rthrough\n"
                         "Are\vbullets\vthat\ffire\fme\fback into you";
    std::string modelResult = "Allofyourfearsarewell-foundedandtrue"
                              "Allofmyhandsarecallousandcruel"
                              "Allofmyarrowsthatriddleyouthrough"
                              "Arebulletsthatfiremebackintoyou";
    //Act
    std::string result = removeWhitespace(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(removeWhitespace, empty_string)
{
    //Arrange
    std::string string = "";
    //Act
    std::string result = removeWhitespace(string);
    //Assert
    ASSERT_STREQ(result.c_str(),"");
}


/*** mapifyString ***/
TEST(mapifyString, mapify_cg_style)
{
    //Arrange
    std::string string = "textColor=red,bgColor=green,bold=true";
    std::map<std::string,std::string> result;
    std::map<std::string,std::string> modelResult = {   {"textColor","red"},
                                                        {"bgColor","green"},
                                                        {"bold","true"}     };
    //Act 
    result = mapifyString(string, "=",",");
    //std::cout << "result:" << result << "\nmodeltResult:" << modelResult << std::endl;
    //Assert
    if(result == modelResult)
    {

        SUCCEED();
    }
    else
    {
        FAIL();
    }
}


/*** unorderedMapifyString ***/
TEST(unorderedMapifyString, unorderedMapify_cg_style)
{
    //Arrange
    std::string string = "textColor=red,bgColor=green,bold=true";
    std::unordered_map<std::string,std::string> result;
    std::unordered_map<std::string,std::string> modelResult = { {"textColor","red"},
                                                                {"bgColor","green"},
                                                                {"bold","true"}     };
    //Act 
    result = unorderedMapifyString(string, "=",",");
    //std::cout << "result:" << result << "\nmodeltResult:" << modelResult << std::endl;
    //Assert
    if(result == modelResult)
    {
        SUCCEED();
    }
    else
    {
        FAIL();
    }
}

/*** stringifyMap ***/
TEST(stringifyMap, stringify_3_pair_map)
{
    //Arrange
    std::map<std::string,std::string> map = {   {"Warsim","Huw Milward"},
                                                {"CultGame","Jeff Stevens"},
                                                {"Kindred Fates","Rob Cravens"}   };
    //Act
    std::string stringifiedMap = stringifyMap(map);
    std::cout << "stringifeidMap:" << stringifiedMap << std::endl;
    //Assert
    if( contains(stringifiedMap, "Warsim:Huw Milward") &&
        contains(stringifiedMap, "CultGame:Jeff Stevens") &&
        contains(stringifiedMap, "Kindred Fates:Rob Cravens") )
    {
        SUCCEED();
    }
    else
    {
        FAIL();
    }
}


/*** countLines ***/
TEST(countLines, 3_line_string)
{
    //Arrange
    std::string string = "firstline\nsecondline\nthirdline\n";
    //Act
    int lineCount =  countLines(string);
    //Assert
    ASSERT_EQ(lineCount, 3);
}

TEST(countLines, emptyString)
{
    //Arrange
    std::string string = "";
    //Act
    int lineCount =  countLines(string);
    //Assert
    ASSERT_EQ(lineCount, 0);
}

TEST(countLines, frankenstein)
{
    //Arrange
        //Using the frankenstein_fulltext string from the global scope
    //Act
    int lineCount = countLines(frankenstein_fulltext);
    //Assert
    ASSERT_EQ(lineCount, 7742);
}


/*** countFileLines ***/
TEST(countFileLines, load_frankenstein_and_count_lines)
{
    //Arrange
    std::string filePath = "../test_string_files/frankenstein.txt";
    //Act
    int lineCount = countFileLines(filePath);
    //Assert
    ASSERT_EQ(lineCount, 7742);
}

// TEST(countFileLines, load_non_existent_file)
// {
//     //Arrange
//     std::string filePath = "test_string_files/loonymcfloonyloo.txt";
//     //Act

//     //Assert
    
// }

TEST(countFileLines, load_empty_file)
{
    //Arrange
    std::string filePath = "../test_string_files/emptyFile.txt";
    //Act
    int lineCount = countFileLines(filePath);
    //Assert
    ASSERT_EQ(lineCount, 0);
}


/*** wrapToWidth ***/
TEST(wrapToWidth, wrap_to_width_3)
{
    //Arrange
    std::string string = "111222333";
    int width = 3;
    std::string modelResult = "111\n222\n333\n";
    //Act
    std::string result = wrapToWidth(string, width);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(wrapToWidth, wrap_to_width_0)
{
    //Arrange
    std::string string = "111222333";
    int width = 0;
    std::string modelResult = "";
    //Act
    std::string result = wrapToWidth(string, width);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(wrapToWidth, wrap_to_width_5)
{
    //Arrange
    std::string string = "111112";
    int width = 5;
    std::string modelResult = "11111\n2\n";
    //Act
    std::string result = wrapToWidth(string, width);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(wrapToWidth, wrap_empty_string)
{
    //Arrange
    std::string string = "";
    int width = 10;
    std::string modelResult = "";
    //Act
    std::string result = wrapToWidth(string, width);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}


/*** circularIndex ***/
TEST(circularIndex, normal_indexing)
{
    //Arrange
    std::string string = "resonance!";
    //Act
    char result = circularIndex(string, 0);
    //Assert
    ASSERT_EQ(result, 'r');
}

TEST(circularIndex, last_index)
{
    //Arrange
    std::string string = "resonance!";
    //Act
    char result = circularIndex(string, 9);
    //Assert
    ASSERT_EQ(result, '!');
}

TEST(circularIndex, loop_around_once)
{
    //Arrange
    std::string string = "resonance!";
    //Act
    char result = circularIndex(string, 15);
    //Assert
    ASSERT_EQ(result, 'a');
}

TEST(circularIndex, loop_around_100_times)
{
    //Arrange
    std::string string = "resonance!";
    //Act
    char result = circularIndex(string, 105);
    //Assert
    ASSERT_EQ(result, 'a');
}


/*** eraseCharsFromEnd ***/
TEST(eraseCharsFromEnd, erase_1_from_end)
{
    //Arrange
    std::string string = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    std::string modelResult = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes";
    //Act
    std::string result = eraseCharsFromEnd(string, 1);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(eraseCharsFromEnd, erase_whole_string)
{
    //Arrange
    std::string string = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    //Act
    std::string result = eraseCharsFromEnd(string, string.length());
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}

TEST(eraseCharsFromEnd, erase_nothing)
{
    //Arrange
    std::string string = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    //Act
    std::string result = eraseCharsFromEnd(string, 0);
    //Assert
    ASSERT_STREQ(string.c_str(), result.c_str());
}

TEST(eraseCharsFromEnd, erase_from_empty_string)
{
    //Arrange
    std::string string = "";
    //Act
    std::string result = eraseCharsFromEnd(string, 3);
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}


/*** eraseCharsFromStart ***/
TEST(eraseCharsFromStart, erase_1_from_start)
{
    //Arrange
    std::string string = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    std::string modelResult = "he pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    //Act
    std::string result = eraseCharsFromStart(string, 1);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(eraseCharsFromStart, erase_whole_string)
{
    //Arrange
    std::string string = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    //Act
    std::string result = eraseCharsFromStart(string, string.length());
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}

TEST(eraseCharsFromStart, erase_nothing)
{
    //Arrange
    std::string string = "She pushed her feet across the board walk She keeps the sunset right with movement in her eyes.";
    //Act
    std::string result = eraseCharsFromStart(string, 0);
    //Assert
    ASSERT_STREQ(string.c_str(), result.c_str());
}

TEST(eraseCharsFromStart, erase_from_empty_string)
{
    //Arrange
    std::string string = "";
    //Act
    std::string result = eraseCharsFromStart(string, 3);
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}


/*** startsWith ***/
TEST(startsWith, check_basic_sentence_true)
{
    //Arrange
    std::string string = "By the authority vested in me by the state of Ohio, I now pronounce you husband and wife!";
    //Act and assert
    ASSERT_TRUE(startsWith(string, "By the authority vested in me by the state of Ohio,"));
}


TEST(startsWith, check_basic_sentence_false)
{
    //Arrange
    std::string string = "By the authority vested in me by the state of Ohio, I now pronounce you husband and wife!";
    //Act and assert
    ASSERT_FALSE(startsWith(string, "By the authority vested in me, Skiddiddle skadoodle you and him are now ready to canoodle!"));
}


/*** findAll ***/
TEST(findAll, prospect_for_gold)
{
    //Arrange
    std::string mine = "rock,iron,rock,clay,gold,rock,rock,rock,clay,topaz,rock,gold,gold,rock";
    std::string gold = "gold";
    std::vector<size_t> modelGoldLocations = {20, 56, 61};
    //Act
    std::vector<size_t> foundGoldLocations = findAll(mine, gold);
    //Assert
    EXPECT_EQ(foundGoldLocations.size(), 3);
    ASSERT_EQ( foundGoldLocations, modelGoldLocations);
}

TEST(findAll, find_all_chars)
{
    //Arrange
    std::string string = "xxxxxxxxxx";
    char x = 'x';
    //Act
    std::vector<size_t> result = findAll(string, x);
    //Assert
    ASSERT_EQ(result.size(), 10);
}

TEST(findAll, substr_not_in_string)
{
    //Arrange
    std::string string = "You're never awake, but don't seem to sleep at all";
    std::string substr = "mtns.";
    //Act
    std::vector<size_t> result = findAll(string, substr);
    //Assert
    ASSERT_EQ( result.size(), 0 );
}

TEST(findAll, find_empty_string)
{
    //Arrange
    std::string string = "You tried to disappear. So long, I followed you.";
    std::string substr = "";
    //Act
    std::vector<size_t> result = findAll(string, substr);
    //Assert
    //The empty string is a subset of every string, so we get a match for each character.
    ASSERT_EQ( result.size(), 49 );
}


/*** getWhitespaceString ***/
//These are all of the whitespace characters in the test environment locale: "\t\n\v\f\r "
TEST(getWhitespaceString, has_tab)
{
    //Arrange
    std::string targetChar = "\t";
    //Act
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    //Assert
    ASSERT_TRUE( contains(whitespaceString, targetChar) );
}

TEST(getWhitespaceString, has_newline)
{
    //Arrange
    std::string targetChar = "\n";
    //Act
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    //Assert
    ASSERT_TRUE( contains(whitespaceString, targetChar) );
}

TEST(getWhitespaceString, has_vert_tab)
{
    //Arrange
    std::string targetChar = "\v";
    //Act
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    //Assert
    ASSERT_TRUE( contains(whitespaceString, targetChar) );
}

TEST(getWhitespaceString, has_form_feed)
{
    //Arrange
    std::string targetChar = "\f";
    //Act
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    //Assert
    ASSERT_TRUE( contains(whitespaceString, targetChar) );
}

TEST(getWhitespaceString, has_carriage_return)
{
    //Arrange
    std::string targetChar = "\r";
    //Act
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    //Assert
    ASSERT_TRUE( contains(whitespaceString, targetChar) );
}

TEST(getWhitespaceString, has_space)
{
    //Arrange
    std::string targetChar = " ";
    //Act
    std::string whitespaceString = getWhitespaceString(std::locale(""));
    //Assert
    ASSERT_TRUE( contains(whitespaceString, targetChar) );
}


/*** trimWhitespace ***/
TEST(trimWhitespace, trim_extra_space)
{
    //Arrange
    std::string string = " The click of the lock, the chime of the bell. ";
    std::string modelResult = "The click of the lock, the chime of the bell.";
    //Act
    std::string result = trimWhitespace(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(trimWhitespace, trim_a_lot_of_whitespace)
{
    //Arrange
    std::string string = " \n\t\r\v\f Hello, world! \n\t\r\v\f";
    std::string modelResult = "Hello, world!";
    //Act
    std::string result = trimWhitespace(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(trimWhitespace, trim_one_side)
{
    //Arrange
    std::string string = "  \rdata";
    std::string modelResult = "data";
    //Act
    std::string result = trimWhitespace(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(trimWhitespace, nothing_to_trim)
{
    //Arrange
    std::string string = "Smitty Werbenjaegermanjensen";
    //Act
    std::string result = trimWhitespace(string);
    //Assert
    ASSERT_STREQ(string.c_str(), result.c_str());
}


/*** charToString ***/
TEST(charToStringTest, check_a)
{
    //Arrange
    char myChar = 'a';
    //Act
    std::string string = charToString(myChar);
    //Assert
    ASSERT_STREQ(string.c_str(), "a");
}

TEST(charToStringTest, check_newline)
{
    //Arrange
    char myChar = '\n';
    //Act
    std::string string = charToString(myChar);
    //Assert
    ASSERT_STREQ(string.c_str(), "\n");
}

TEST(charToStringTest, check_number)
{
    //Arrange
    char myChar = 90;
    //Act
    std::string string = charToString(myChar);
    //Assert
    ASSERT_STREQ(string.c_str(), "Z");
}


/*** eraseNonNumericChars ***/
TEST(eraseNonNumericChars, all_numeric_chars)
{
    //Arrange
    std::string string = "0123456789";
    //Act
    std::string result = eraseNonNumericChars(string);
    //Assert
    ASSERT_STREQ(result.c_str(), string.c_str());
}

TEST(eraseNonNumericChars, no_numeric_chars)
{
    //Arrange
    std::string string = "Savior, forever threadbare and faded. Drunken and arcane. Curse the day.";
    //Act
    std::string result = eraseNonNumericChars(string);
    //Assert
    ASSERT_STREQ(result.c_str(), "");
}

TEST(eraseNonNumericChars, mix_of_numeric_and_non_numeric)
{
    //Arrange
    std::string string = "1 pumpkin, 5 eggplant, 3 squash, 9001 nappa cabbage";
    std::string modelResult = "1539001";
    //Act
    std::string result = eraseNonNumericChars(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(eraseNonNumericChars, empty_string)
{
    //Arrange
    std::string string = "";
    std::string modelResult = "";
    //Act
    std::string result = eraseNonNumericChars(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}


/*** reverse ***/
TEST(reverse, check_hello_world)
{
    //Arrange
    std::string string = "Hello, world!";
    std::string modelResult = "!dlrow ,olleH";
    //Act
    std::string result = reverse(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}

TEST(reverse, check_empty_string)
{
    //Arrange
    std::string string = "";
    std::string modelResult = "";
    //Act
    std::string result = reverse(string);
    //Assert
    ASSERT_STREQ(result.c_str(), modelResult.c_str());
}


/*** isPalindrome ***/
TEST(isPalindrome, check_racecar)
{
    //Arrange
    std::string string = "racecar";
    //Act
    bool result = isPalindrome(string);
    //Assert
    ASSERT_TRUE(result);   
}

TEST(isPalindrome, check_go_hang_a_salami)
{
    //Arrange
    std::string string = "gohangasalamiimalasagnahog";
    //Act
    bool result = isPalindrome(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isPalindrome, check_punctuated_english_palindrome)
{
    //Arrange
    std::string string = "A man, a plan, a canal, panama";
    //Act
    bool result = isPalindrome(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(isPalindrome, check_empty_string)
{
    //Arrange
    std::string string = "";
    //Act
    bool result = isPalindrome(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isPalindrome, check_non_palindrome)
{
    //Arrange
    std::string string = "There was an anchor, there was a silver, sweet refrain";
    //Act
    bool result = isPalindrome(string);
    //Assert
    ASSERT_FALSE(result);
}


/*** multiply ***/
TEST(multiply, single_char)
{
    //Arrange
    std::string str = "x";
    //Act
    std::string result = multiply( "x", 5);
    //Assert
    ASSERT_STREQ( result.c_str(), "xxxxx" );
}

TEST(multiply, multi_char)
{
    //Arrange
    std::string str = "(multiplyThis)";
    //Act
    std::string result = multiply( str, 2);
    //Assert
    ASSERT_STREQ( result.c_str(), "(multiplyThis)(multiplyThis)" );
}

TEST(multiply, times_zero)
{
    //Arrange
    std::string str = "poof! gone";
    //Act
    std::string result = multiply( str, 0);
    //Assert
    ASSERT_STREQ( result.c_str(), "");
}


/*** format (vector variant) ***/
TEST(format_vectorVariant, single_replace)
{
    //Arrange
    std::string str = "Man, it sure is {0} around here!";
    //Act
    std::string result = format(str, {"boring"});
    //Assert
    ASSERT_STREQ( result.c_str(), "Man, it sure is boring around here!");
}

TEST(format_vectorVariant, multi_replace)
{
    //Arrange
    std::string str = "{2}{1}{3}{4}{0}";
    //Act
    std::string result = format(str, {"emerald?","DAMN ","Where's that ","fourth ","chaos "});
    //Assert
    ASSERT_STREQ( result.c_str(), "Where's that DAMN fourth chaos emerald?");
}

TEST(format_vectorVariant, no_replace)
{
    //Arrange
    std::string str = "{Bacon} {Lettuce} {Tomato}";
    //Act
    std::string result = format(str, {"pb","and","j"});
    //Assert
    ASSERT_STREQ( result.c_str(), "{Bacon} {Lettuce} {Tomato}");
}

TEST(format_vectorVariant, nested_braces)
{
    //Arrange
    std::string str = "{1{2}}{feelin{0}nesty}{{yo}}";
    //Act
    std::string result = format(str, {"zero", "one", "two"});
    //Assert
    ASSERT_STREQ( result.c_str(), "{1two}{feelinzeronesty}{{yo}}");
}


/*** format (map variant) ***/
TEST(format_mapVariant, single_replace)
{
    //Arrange
    std::string str = "You are known as jimmy the {title}!";
    std::unordered_map<std::string,std::string> formatMap = {   {"title","bandit"}    };
    //Act
    std::string result = stevensStringLib::format(str, formatMap);
    //Assert
    ASSERT_STREQ( result.c_str(), "You are known as jimmy the bandit!");
}

TEST(format_mapVariant, multi_replace)
{
    //Arrange
    std::string str = "Abandon {noun1}, all ye who {verb1} here!";
    std::unordered_map<std::string,std::string> formatMap = {   {"noun1",   "smelliness"},
                                                                {"verb1",   "shower"}  };
    //Act
    std::string result = format(str, formatMap);
    //Assert
    ASSERT_STREQ( result.c_str(), "Abandon smelliness, all ye who shower here!");
}

TEST(format_mapVariant, allow_for_style_tokens)
{
    //Arrange
    std::string str = "You enter the {dungeon of {dungeonOwner}}$[textColor=red]!";
    std::unordered_map<std::string,std::string> formatMap = {  {"dungeonOwner", "jimmy"}  };
    //Act
    std::string result = format(str, formatMap);
    //Assert
    ASSERT_STREQ( result.c_str(), "You enter the {dungeon of jimmy}$[textColor=red]!");
}



int main(   int argc,
            char * argv[]   )
{
    //We'll use the text of Frankenstein as a large string to run our functions on
    std::ifstream input_file("../test_string_files/frankenstein.txt");
    if (!input_file.is_open())
    {
        //Error if we cannot successfully print the file
        throw std::invalid_argument("Error, could not file testing_string_frankenstein.txt");
    }
    //Store the text content of the file in a string
    frankenstein_fulltext = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
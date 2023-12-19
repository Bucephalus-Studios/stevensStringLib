/**
 * This is the code for testing stevensStringLib. All testing is carried out with GoogleTest.
 * Must have GoogleTest installed to compile this program!
 * GoogleTest installation tutorial stuff:
 * https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
 *
 * Compiles with: g++ -std=c++23 test.cpp -lgtest -o test
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
    //Act
    bool result = contains(string, substring);
    //Assert
    ASSERT_TRUE(result);
}

TEST( contains, empty_string_and_empty_substring)
{
    //Arrange
    std::string string = "";
    std::string substring = "";
    //Act
    bool result = contains(string, substring);
    //Assert
    ASSERT_TRUE(result);
}

TEST( contains, string_contains_empty_string)
{
    //Arrange
    std::string string = "hello";
    std::string substring = "";
    //Act
    bool result = contains(string, substring);
    //Assert
    ASSERT_TRUE(result);
}

TEST( contains, empty_string_does_not_contain_string)
{
    //Arrange
    std::string string = "";
    std::string substring = "hello";
    //Act
    bool result = contains(string, substring);
    //Assert
    ASSERT_FALSE(result);
}

TEST( contains, test_on_large_string)
{
    //Arrange
    std::string substring = "conflagration";
    //Act
    bool result = contains(frankenstein_fulltext, substring);
    //Assert
    ASSERT_TRUE(result);
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
    std::string name = "jeff";
    //Act
    std::string result = cap1stChar(name);
    //Assert
    ASSERT_STREQ(result.c_str(),"Jeff");
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
    //Act
    bool result = isInteger(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isInteger, check_negative_100)
{
    //Arrange
    std::string string = "-100";
    //Act
    bool result = isInteger(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isInteger, check_non_integer)
{
    //Arrange
    std::string string = "beebop";
    //Act
    bool result = isInteger(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(isInteger, check_overflowed_number)
{
    //Arrange
    std::string string = "999999999999999999999";
    //Act
    bool result = isInteger(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(isInteger, check_float)
{
    //Arrange
    std::string string = "3.14159";
    //Act
    bool result = isInteger(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(isInteger, check_expression)
{
    //Arrange
    std::string string = "(3/2)+4";
    //Act
    bool result = isInteger(string);
    //Assert
    ASSERT_FALSE(result);
}


/*** isFloat ***/
TEST(isFloat, check_1point5)
{
    //Arrange
    std::string string = "1.5";
    //Act
    bool result = isFloat(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isFloat, check_negative_1point5)
{
    //Arrange
    std::string string = "-1.5";
    //Act
    bool result = isFloat(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isFloat, check_for_one_decimal_point)
{
    //Arrange
    std::string string = "7.0.0";
    //Act
    bool result = isFloat(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(isFloat, nothing_to_left_of_point)
{
    //Arrange
    std::string string = ".2";
    //Act
    bool result = isFloat(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(isFloat, too_precise_of_number)
{
    //Arrange
    std::string string = ".12341231231231231231231231231231233123123123123123123";
    //Act
    bool result = isFloat(string);
    //Assert
    ASSERT_FALSE(result);
}


/*** isNumber ***/


/*** string_to_bool ***/


/*** bool_to_string ***/


/*** trim ***/


/*** removeWhitespace ***/


/*** mapifyString ***/


/*** stringifyMap ***/


/*** countLines ***/


/*** countFileLines ***/


/*** wrapToWidth ***/


/*** circularIndex ***/


/*** eraseCharsFromEnd ***/


/*** findAll ***/


/*** trimWhitespace ***/


/*** char_to_string ***/


/*** isNotDigit ***/


/*** eraseNonNumericChars ***/


/*** reverse ***/


/*** isPalindrome ***/


int main(   int argc,
            char * argv[]   )
{
    //We'll use the text of Frankenstein as a large string to run our functions on
    std::ifstream input_file("testing_string_frankenstein.txt");
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
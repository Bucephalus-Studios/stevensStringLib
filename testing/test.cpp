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

TEST(isFloat, check_for_only_one_decimal_point)
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
TEST(stringToBool, check_true)
{
    //Arrange
    std::string string = "true";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(stringToBool, check_false)
{
    //Arrange
    std::string string = "false";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(stringToBool, check_TRUE)
{
    //Arrange
    std::string string = "TRUE";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(stringToBool, check_FALSE)
{
    //Arrange
    std::string string = "FALSE";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(stringToBool, check_true_alternating_caps)
{
    //Arrange
    std::string string = "tRuE";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_TRUE(result);
}

TEST(stringToBool, check_0)
{
    //Arrange
    std::string string = "0";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_FALSE(result);
}

TEST(stringToBool, check_9001)
{
    //Arrange
    std::string string = "9001";
    //Act
    bool result = string_to_bool(string);
    //Assert
    ASSERT_TRUE(result);
}


/*** bool_to_string ***/
TEST(boolToString, check_true)
{
    //Arrange
    bool myBool = true;
    //Act
    std::string result = bool_to_string(myBool);
    //Assert
    ASSERT_STREQ(result.c_str(), "true");
}

TEST(boolToString, check_false)
{
    //Arrange
    bool myBool = false;
    //Act
    std::string result = bool_to_string(myBool);
    //Assert
    ASSERT_STREQ(result.c_str(), "false");
}

TEST(boolToString, check_9001)
{
    //Arrange
    int myInt = 9001;
    //Act
    std::string result = bool_to_string(myInt);
    //Assert
    ASSERT_STREQ(result.c_str(), "true");
}

TEST(boolToString, check_0)
{
    //Arrange
    int myInt = 0;
    //Act
    std::string result = bool_to_string(myInt);
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


/*** stringifyMap ***/


/*** countLines ***/


/*** countFileLines ***/


/*** wrapToWidth ***/


/*** circularIndex ***/


/*** eraseCharsFromEnd ***/


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
    std::string x = "x";
    //Act
    std::vector<size_t> result = findAll(string, x);
    //Assert
    ASSERT_EQ(result.size(), 10);
}


/*** trimWhitespace ***/


/*** char_to_string ***/


/*** isNotDigit ***/


/*** eraseNonNumericChars ***/


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
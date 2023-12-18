/**
 * This is the code for testing stevensStringLib. All testing is carried out with GoogleTest.
 * Must have GoogleTest installed to compile this program!
 * GoogleTest installation tutorial stuff:
 * https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
 *
 * Compiles with: g++ -std=c++23 test.cpp -lgtest -o test
*/
#include "stevensStringLib.h"
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

TEST( separate, separate_a_large_string_with_no_separator_character_Found_within)
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
    ASSERT_STREQ( result[0], frankenstein_fulltext);
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
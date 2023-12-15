/**
 * stevensStringLib.h
 *
 * Defines the stevensStringLib namespace, a library meant to provide useful functions to expand interactions with the standard string type.
 */

//Include guard
#ifndef _STEVENSSTRINGLIB_

#define _STEVENSSTRINGLIB_

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>
#include<istream>
#include<cctype>
#include<locale>
#include<charconv>
#include<map>
#include<unordered_map>


namespace stevensStringLib
{
    /**
     * Given a string, tell whether it has an occurrence of the substring somewhere 
     * within it.
     * 
     * Parameters:
     *  const std::string & input - The string we are examining to see if it contains the substring.
     *  const std::string & substring - The substring we are trying to see if it is contained in the input string.
     * 
     *  Returns:
     *  bool - Boolean indicating that input string contains the substring (true) or not (false).
     */
    bool contains(  const std::string & input,
                    const std::string & substring)
    {
        int result = input.find(substring);
        if((result >= 0) && (result <= input.length()))
        {
            return true;
        }
        else if(result == std::string::npos)
        {
            return false;
        }
        else
        {
            std::cout << "stevensStringLibrary notification: Use of contains(" + input + "," + substring + ") has returned an unexpected value: " + std::to_string(result);
            return false;
        }
    }


    /**
     * Separates a string by a separator substring. Returns a vector of strings that 
     * were separated by the separator substring.
     * 
     * Parameters:
     *  const std::string & input - The string we intend to separate with this function.
     *  const std::string & separator - The substring of the input string we intend to separate it by.
     *  const bool omitEmptyStrings - If true, do not include empty strings in the returned vector. TODO!!!!
     * 
     * Returns:
     *  vector<std::string> - A vector of substrings of the original string that have been split up by all occurrences of the separator parameter
     */
    std::vector<std::string> separate(  const std::string & input,
                                        const std::string & separator = "," )
    {
        std::vector<std::string> separatedStrings = {};
        std::string word = "";

        //If we have a single character separator, we can use a more efficient method
        if(separator.length() == 1)
        {
            //Taken from https://stackoverflow.com/a/5757851
            std::istringstream split(input);
            for (std::string each; std::getline(split, each, separator[0]); separatedStrings.push_back(each));
            //Check to see if the last element needs a separator character trimmed off (if there exists a trailing separator character)
            if(!separatedStrings.empty())
            {
                if(separatedStrings.back().back() == separator[0])
                {
                    separatedStrings.back().pop_back();
                }
            }
        }
        else
        {
            //Iterate through the input string and piece together the strings we want to separate
            for(int i = 0; i < input.length(); i++)
            {
                word += input[i];
                //Every time we add a character to the word, we check to see if it contains the separator
                if(contains(word, separator))
                {
                    //Extract the separator from the word
                    word.erase(word.find(separator), separator.length());
                    //Push the word into the vector
                    separatedStrings.push_back(word);
                    //Clear the word
                    word.clear();
                }
            }
            //If we had no separators at all, or if the string doesn't end in a separator, we push the remaining
            //word to the vector.
            separatedStrings.push_back(word);
        }
        

        return separatedStrings;
    }


    /**
     * Returns a string with the first letter capitalized. If the string is empty, then we just return the empty string.
     * 
     * Parameter:
     *  std::string input - The string we want to capitalize the first letter of.
     * 
     * Returns:
     *  std::string - The input string with the first letter capitalized.
     */
    std::string cap1stChar(std::string input)
    {
        if(input.length() > 0)
        {
            input[0] = std::toupper(input[0]);
        }
        return input;
    }


    /**
     *  Returns a string with all characters in uppercase if possible.
     *  Gleaned from this article:
     *  https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
     * 
     * 
     * Parameters:
     *  std::string & input - The string we would like to make all uppercase.
     * 
     * Returns:
     *  std::string - The input, but all in uppercase!
     *  
    `*/
    std::string toUpper(std::string & input)
    {
        std::transform(input.begin(), input.end(), input.begin(), [](unsigned char x) { return std::toupper(x); });
        return input;
    }


    /**
     *  Detects whether or not the user input is in the form of an integer or floating point number. 
     *  Does not work for mathematical expressions!
     *
     *  Parameter:
     *       const std::string & str - The string we are checking to see if it represents a number.
     *  Returns:
     *      bool - True if the string represents a number. False if otherwise.
     *    
     */
    bool isNumber(  const std::string & str   )
    {
        return ( isInteger(str) || isFloat(str) );
    }


    /**
     * Detects if a string is in the form of an integer.
     * 
     * Parameter:
     *  const std::string & str - A string we are checking to see if it represents an integer.
     * 
     * Returns:
     *  bool - true if the string str represents an integer, false otherwise.
    */
    bool isInteger( const std::string & str )
    {
        for (int charIndex = 0; charIndex < str.length(); charIndex++)
        {
            //The first index has the possibility of having a negative sign
            if(charIndex == 0)
            {
                if(str[charIndex] == '-')
                {
                    continue;
                }
            }
            //Check to see if the character is a numerical digit
            if (!isdigit(str[charIndex]))
            {
                return false;
            }
        }
        
        //Now that we're sure we have a string that contains only digits and possibly a negative sign, we check
        //to see if converting the string to an integer will cause errors 
        int value = 0;
        const auto res = std::from_chars(   str.data(), 
                                            str.data() + str.size(), 
                                            value );
        if (res.ec == std::errc::invalid_argument)
        {
            //Invalid argument for std::from_chars()
            return false;
        }
        else if (res.ec == std::errc::result_out_of_range)
        {
            //Overflow/underflow has occurred
            return false;
        }

        //Otherwise, return true
        return true;
    }


    /**
     * Detects if a string is in the form of a floating point number.
     * 
     * Parameter:
     *  const std::string & str - A string we are checking to see if it represents a floating point number.
     * 
     * Returns:
     *  bool - true if the string str represents a floating point number. False otherwise.
    */
    bool isFloat( const std::string & str )
    {
        //Let's keep track of if we've seen the decimal point or not
        bool seenDecimalPoint = false;
        char point = std::use_facet< std::numpunct<char> >(std::cout.getloc()).decimal_point();
        for (int charIndex = 0; charIndex < str.length(); charIndex++)
        {
            //The first index has the possibility of having a negative sign
            if(charIndex == 0)
            {
                if(str[charIndex] == '-')
                {
                    continue;
                }
            }
            if(!seenDecimalPoint)
            {
                if(str[charIndex] == point)
                {
                    seenDecimalPoint = true;
                    continue;
                }
            }
            //Check to see if the character is a numerical digit
            if(!isdigit(str[charIndex]))
            {
                return false;
            }
        }

        //If we've looked at the whole string and not found a decimal point, then we couldn't be looking at a floating point number.
        if(!seenDecimalPoint)
        {
            return false;
        }

        //Now that we're sure we have digits with a decimal point, and possibly a negative sign in front, we convert the string to
        //a floating point number using std::from_chars to see if we run into any problems.
        double value = 0;
        const auto format = std::chars_format::general;
        const auto res = std::from_chars(   str.data(), 
                                            str.data() + str.size(), 
                                            value, 
                                            format  );
        if (res.ec == std::errc::invalid_argument)
        {
            //Invalid argument
            return false;
        }
        else if (res.ec == std::errc::result_out_of_range)
        {
            //Overflow/unverflow has occurred
            return false;
        }

        //Otherwise, return true
        return true;
    }


    /**
     * Takes in a string and checks to see if it is a representation of the word "true" or "0".
     * In those cases, return a true bool. In all other cases, return false. 
     * 
     * Parameter:
     *  std::string input - A string we are converting to a bool.
     * 
     * Returns:
     *  bool - True if the input is a form of the word true or 0, and false otherwise.
    */
    bool string_to_bool( std::string & input )
    {
        if( toUpper(input) == "TRUE")
        {
            return true;
        }
        else if( isNumber(input) )
        {
            if(std::stoi(input) == 0)
            {
                return true;
            }
        }
        return false;
    }


    /**
     * Converts a boolean value to a string value. 
     * 
     * Taken from OJ's answer here: https://stackoverflow.com/questions/29383/converting-bool-to-text-in-c
     * 
     * Parameter:
     *  bool input - The boolean value we wish to convert to a string.
     * 
     * Returns
     *  std::string - The boolean value represented as a string.
     */
    std::string bool_to_string( const bool & input  )
    {
        return input ? "true" : "false";
    }


    /**
     * Given a string and integer X, erase (trim) X characters from both the beginning and end of the string.
     * 
     * Parameters:
     *  std::string input - A string we would like to trim the characters from.
     *  const int & charsToTrim - The number of characters to trim from the beginning and end of the string.
     * 
     * Returns:
     *  std::string -   A modified version of the input string, with X characters from both the beginning and end of the 
     *                  string trimmed off.
     */
    std::string trim(   const std::string & input,
                        const int & charsToTrim   )
    {
        //We don't accept negative numbers of characters to trim
        if(charsToTrim < 0)
        {
            //TODO: Work out how to do error handling
            return input;
        }
        //If we have a charsToTrim value greater than the length of the input, we return an empty string
        if(charsToTrim > input.length())
        {
            return "";
        }
        
        return input.substr(charsToTrim, (input.length() - (charsToTrim * 2)));
    }


    /**
     * Removes all tabs, spaces, and carriage returns from an input string.
     * 
     * From Michael Steller: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
     * 
     * Paraemter:
     *  std::string str - The string from which we wish to remove all the whitespace from.
     * 
     * Returns:
     *  std::string - The input string but with all of the tabs and spaces removed
     */
    std::string removeWhitespace( std::string str )
    {
        str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end());
        return str;
    }


    /**
     * TODO: Make one mapify function for std::map and std::unordered_map. This can be done with templates, somehow. Need to do research.
     * 
     * Given an input string str that can represent a map, take two separator strings and 
     * separate the pairs from eachother, and they keys and values from each other. Then
     * insert each key value pair into a std::map<std::string,std::string> object.
     * 
     * 
     * 
    */
    std::map<std::string,std::string> mapifyString( std::string str,
                                                    std::string keyValueSeparator,
                                                    std::string pairSeparator,
                                                    bool ignoreWhitespace = true    )
    {
        //Create the map that we'll be returning later
        std::map<std::string,std::string> mappedString = {};

        //Get rid of any whitespace if necessary (TODO: see if we can just remove whitespace between words-equals signs, and words-commas)
        if(ignoreWhitespace)
        {
            str = removeWhitespace(str);
        }

        //Separate the pairs
        std::vector<std::string> keysAndValues = separate(str,pairSeparator);

        //Separate the keys and values
        std::vector<std::string> keyAndValue; 
        for(int i = 0; i < keysAndValues.size(); i++)
        {
            keyAndValue = separate(keysAndValues[i], keyValueSeparator);
            if(keyAndValue.size() == 0)
            {
                //No keys or values found, skip
                continue;
            }
            else if(keyAndValue.size() == 1)
            {
                //Insert a key with an empty value
                mappedString[keyAndValue[0]] = "";
            }
            else if(keyAndValue.size() >= 2)
            {
                //Insert the key value pair into the map (only the first two elements)
                mappedString[keyAndValue[0]] = keyAndValue[1];
            }
        }

        return mappedString;
    }


    /**
     * Given an input string str that can represent a map, take two separator strings and 
     * separate the pairs from eachother, and they keys and values from each other. Then
     * insert each key value pair into a std::map<std::string,std::string> object.
     * 
     * 
     * 
    */
    std::unordered_map<std::string,std::string> unordered_mapifyString( std::string str,
                                                                        std::string keyValueSeparator = ":",
                                                                        std::string pairSeparator  = ",",
                                                                        bool ignoreWhitespace = true    )
    {
        //Create the map that we'll be returning later
        std::unordered_map<std::string,std::string> unordered_mappedString = {};

        //Get rid of any whitespace if necessary (TODO: see if we can just remove whitespace between words-equals signs, and words-commas)
        if(ignoreWhitespace)
        {
            str = removeWhitespace(str);
        }

        //Separate the pairs
        std::vector<std::string> keysAndValues = separate(str,pairSeparator);

        //Separate the keys and values
        std::vector<std::string> keyAndValue; 
        for(int i = 0; i < keysAndValues.size(); i++)
        {
            keyAndValue = separate(keysAndValues[i], keyValueSeparator);
            if(keyAndValue.size() == 0)
            {
                //No keys or values found, skip
                continue;
            }
            else if(keyAndValue.size() == 1)
            {
                //Insert a key with an empty value
                unordered_mappedString[keyAndValue[0]] = "";
            }
            else if(keyAndValue.size() >= 2)
            {
                //Insert the key value pair into the map (only the first two elements)
                unordered_mappedString[keyAndValue[0]] = keyAndValue[1];
            }
        }

        return unordered_mappedString;
    }


    /**
     * Given an unordered_map of strings, turn it into a string of keys and values paired together separated by delimiting characters.
     * 
     * Parameters:
     *  unordered_map<std::string,std::string> umap - The unordered map with string keys and values which we intend to turn into a string.
     *  std::string keyValueSeparator - The string that separates keys from their values in the returned string.
     *  std::string pairSeparator - The string that separates key-value pairs in the returned string.
     * 
     * Returns:
     *  std::string - The all contents of the unordered map turned into a string list of separated key-value pairs.
    */
    std::string stringifyUnordered_map( std::unordered_map<std::string,std::string> umap,
                                        std::string keyValueSeparator = ":",
                                        std::string pairSeparator =     "," )
    {
        std::string stringifiedUmap = "";
        //Iterate through the unordered map, appending each pair to the string
        for(auto & [key,value] : umap )
        {
            if(!stringifiedUmap.empty())
            {
                stringifiedUmap += pairSeparator;
            }
            stringifiedUmap += key + keyValueSeparator + value;
        }
        return stringifiedUmap;
    }


    /**
     * Given a string, count how many lines are in that string and return the integer count.
     * Solution from: https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
     * 
     * Parameter:
     *  std::string str - The string which we wish to count the number of lines of.
     * 
     * Returns:
     *  int - The integer count of the number of lines that the string str has.
    */
    int countLines(std::string str)
    {
        int number_of_lines = 0;
        std::string line;
        std::istringstream ss(str);

        while (std::getline(ss, line))
        {
            ++number_of_lines;
        }
        return number_of_lines;
    }


    /**
     * Given the path to a file, count how many lines are in the file and return the integer count.
     * 
     * Parameter:
     *  std::string filePath - The path to the file we want to count the number of lines of.
     * 
     * Returns:
     *  int - The integer number of lines that the file contains.
    */
    int countFileLines(std::string filePath)
    {
        //Create an input stream from the file we are trying to print
        std::ifstream input_file(filePath);
        if (!input_file.is_open())
        {
            //Error if we cannot successfully print the file
            throw std::invalid_argument("Error, could not find file: " + filePath);
        }
        //Store the text content of the file in a string
        std::string fileContent = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

        return countLines(fileContent);
    }


    /**
     * Given a string and integer describing the total number of characters that can exist in a line of text,
     * wrap the text by adding newlines between words so it may fit within a certain width.
     * 
     * Parameters:
     *  std::string str - The string which we wish to wrap to a certain width.
     *  int wrapWidth - The width in number of characters we wish to wrap.
     * 
     * Returns:
     *  
    */
    std::string wrapAround( std::string str,
                            int wrapWidth   )
    {
        std::istringstream in(str);
        std::string line;
        std::string word;
        std::string output = "";
        int lineCutOffIndex = 0;
        int numberOfLines = countLines(str);
        int currLineNum = 0;

        while(getline(in,line))
        {
            lineCutOffIndex = 0;
            while(true)
            {
                //Check to see if we need to wrap this line around
                if(line.length() > wrapWidth)
                {
                    //Find the last space in the string that fits on the line
                    lineCutOffIndex = line.rfind(" ", wrapWidth);
                    //If we can't find a space in the string and the string is too long, we just cut the line and wrap to the next line
                    if(lineCutOffIndex == std::string::npos)
                    {
                        //Add as much of the line as we can to the output and then add a newline
                        output += line.substr(0, wrapWidth) + "\n";
                        //Continue looping until the rest of the line is added to the output
                        line = line.substr(wrapWidth+1);
                    }
                    //If we find a space...
                    else
                    {
                        //Add the part of the string before the cut off point to the output
                        output += line.substr(0, lineCutOffIndex) + "\n";
                        //Set the line equal to the cut off portion of the string and continue looping until the rest of the line is added to the output
                        line = line.substr(lineCutOffIndex+1);
                    }
                }
                else
                {
                    output += line;
                    break;
                }
            }
            currLineNum++;
            //Add a new line when printing the next line from the string, or print a newline if we only have a newline character
            if((currLineNum < numberOfLines) || ((line.length()) == 0 && (numberOfLines == 1)))
            {
                output += "\n";
            }
        }

        return output;
    }


    /**
     * Given a string an an integer representing an index, return a single character from the string by the process of circular 
     * indexing.
     *  
     * Circular indexing is performed by indexing over the string from left to right. Once the index exceeds the length of the string, we begin
     * indexing again from the lefthand side of the string and repeat the process until we stop at the final index. We return the character at 
     * that final index.
     * 
     * Example: circularIndex("Hello world!", 13) returns 'e', as we loop around to 'H' at 12 and index one space further to reach 'e'.
     * 
     * Parameters:
     *  std::string str
     *  int circ_i
     * 
     * Returns:
     *  char - A character found in str that has been circularly indexed to at position circ_i
     * 
    */
    char circularIndex( std::string str,
                        int circ_i )
    {
        //If we have an empty string, we can't index to anything
        // if(str.empty())
        // {
        //     throw std::invalid_argument("str cannot be empty for circularIndex()");
        // }

        return str[circ_i % str.length()];
    }


    /**
     * Given a string str, erase the last n characters of the string.
     * 
     * Taken from: https://thispointer.com/remove-last-n-characters-from-a-string-in-c/
     * 
     * Parameters:
     *  std::string str - The string we want to erase characters from the end of.
     *  int n - The number of characters we want to erase
     * 
     * Returns:
     *  std::string - The string str which we erased characters from 
    */
    std::string eraseCharsFromEnd(  std::string str,
                                    int n   )
    {
        str.erase(str.size() - n);
        return str;
    }


    /**
     * Given a string str, find all occurrences of a substring within it. Returns a vector of all of the indices that the substring
     * occurs at within the string str.
     * 
     * Based off of: https://stackoverflow.com/a/4034809
     * 
     * Parameters:
     *  std::string str - The string we are searching for the substring in.
     *  std::string substr - The substring we are looking for within string str.
     * 
     * Returns:
     *  std::vector<size_t> - A vector containing all indices in increasing order that the substr occurs at.
    */
    std::vector<size_t> findAll(    std::string str,
                                    std::string substr  )
    {
        std::vector<size_t> positions;

        size_t pos = str.find(substr, 0);
        while(pos != std::string::npos)
        {
            positions.push_back(pos);
            pos = str.find(substr,pos+1);
        }

        return positions;
    }


    /**
     * Remove all leading and trailing whitespace from a string (spaces and tabs), then return it.
     * 
     * Based on: https://stackoverflow.com/a/1798170
     * 
     * Parameter:
     *  std::string str - The string to remove all of the leading and trailing whitespaces from.
     *  std::string whiteSpace - A string containing all of the whitespace characters to trim from the string
     * 
     * Returns:
     *  std::string - str modified by removing all of its leading and trailing whitespaces
    */
    std::string trimWhitespace( std::string str,
                                std::string whitespace = " \t"  )
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
        {
            return ""; // no content
        }
            
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }


    /**
     * Given a character c, convert it to a std::string.
     * 
     * Parameter:
     *  char c - The character we'd like to convert to a string.
     * 
     * Returns:
     *  std::string - A string representing the character c.
    */
    std::string char_to_string( const char & c )
    {
        std::string s(1, c);
        return s;
    }


    /**
     * Erases all non-numeric characters from a string and returns it.
     * 
     * Parameter:
     *  std::string str - The string to release all non-numeric chars from.
     * 
     * Returns:
     *  The string parameter we passed in, but all of its non-numeric characters removed from it.
    */
    std::string eraseNonNumericChars( std::string str )
    {
        str.erase(std::remove_if(str.begin(), str.end(), !isdigit), str.end());
        return str;
    }


    /**
     * Reverses the order of a string's characters using std::reverse().
     * 
     * Parameter:
     *  std::string & str - The string we would like to reverse.
     * 
     * Returns:
     *  std::string - The reversed string.
    */
    std::string reverse( std::string str )
    {
        std::reverse(str.begin(),str.end());
        return str;
    }


    /**
     * Checks to see if a std::string is a palindrime or not (the reversed order of characters equals the order of characters).
     * 
     * Credit: https://stackoverflow.com/a/8362657/16511184
     * 
     * Parameter:
     *  std::string str - The string we would like to check.
     * 
     * Returns:
     *  bool - true if str is a palindrome, false otherwise.
    */
    bool isPalindrome( const std::string & str )
    {
        return std::equal(str.begin(), str.begin() + str.size()/2, str.rbegin());
    }
}
#endif
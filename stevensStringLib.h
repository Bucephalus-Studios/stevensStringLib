/**
 * @file stevensStringLib.h
 * @author Jeff Stevens (jeff@bucephalusstudios.com)
 * @brief An easy-to-use C++ library with convenient functions for working with strings.
 * @version 0.1
 * @date 2023-12-21
 * @copyright Copyright (c) Bucephalus Studios 2023
 * 
 * Created and released under the MIT license. See the LICENSE file in the repository folder.
 * 
 * If you'd like to buy me a coffee or send me a tip for my work on this library, you can do that here: https://ko-fi.com/bucephalus_studios
 * 
 * Thank you very, very much for being interested in my code! Hope it serves you well <3
 */


#ifndef _STEVENSSTRINGLIB_
#define _STEVENSSTRINGLIB_

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<string_view>
#include<limits>
#include<sstream>
#include<fstream>
#include<cctype>
#include<locale>
#include<charconv>
#include<map>
#include<unordered_map>


namespace stevensStringLib
{
    /**
     * @deprecated
     * In C++23 and onward, please use the std::string::contains() method instead of this function.
     * 
     * Given a string, determine whether it has an occurrence of the substring somewhere 
     * within it.
     * 
     *  @param str - The string we are examining to see if it contains the substring.
     *  @param substring - The substring we are checking to if it is contained in str.
     * 
     *  @retval Boolean indicating that input string contains the substring (true) or not (false).
     */
    inline bool contains(   const std::string_view & str,
                            const std::string_view & substring   )
    {
        return (str.find(substring) != std::string::npos);
    }


    /**
     * @deprecated
     * In C++23 and onward, please use the std::string::contains() method instead of this function.
     * 
     * Given a string, determine whether it has an occurrence of a character somewhere 
     * within it.
     * 
     *  @param str - The string we are examining to see if it contains the substring.
     *  @param ch - The char we are checking to see if it is contained in str.
     * 
     *  @retval Boolean indicating that input string contains the substring (true) or not (false).
     */
    inline bool contains(   const std::string_view & str,
                            const char ch  )
    {
        return (str.find(ch) != std::string::npos);
    }


    /**
     * @brief 
     * Given a string, determine if it contains only the characters in the given string.
     * 
     * Example:
     * str = "11101112222"
     * substrs = {"111","2"};
     * 
     * Result: false, str contains the character '0', which is not equal to "111", or "2";
     * 
     * @param str - The string we are checking to see if it only contains characters present in the chars string.
     * @param chars - A string of characters we are checking to see if str contains any characters that are not in chars.
     * @return true if str contains only instances of keys in substrs.
     * @return false if str contains at least one substring that is not present as a key in substrs.
     */
    inline bool containsOnly(   const std::string_view & str,
                                const std::string_view & chars )
    {
        //For each character in chars, check to see if it is contained within str
        for(int i = 0; i < chars.length(); i++)
        {
            if(!stevensStringLib::contains(str, chars[i]))
            {
                return false;
            }
        }
        return true;
    }


        /**
     * Given a string str, find all occurrences of a substring within it. Returns a vector of all of the indices that the substring
     * occurs at within the string str.
     * 
     * Credit to Benjamin Lindley: https://stackoverflow.com/a/4034809
     * 
     * @param str - The string we are searching for the substring in.
     * @param substr - The substring we are looking for within string str.
     * 
     * @retval std::vector<size_t> - A vector containing all indices in increasing order that the substr occurs at.
    */
    inline std::vector<size_t> findAll(     const std::string & str,
                                            const std::string & substr  )
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
     * Given a string str, find all occurrences of a character within it. Returns a vector of all of the indices that the character
     * occurs at within the string str.
     * 
     * Credit to Benjamin Lindley: https://stackoverflow.com/a/4034809
     * 
     * @param str - The string we are searching for the substring in.
     * @param ch - The character we are looking for within string str.
     * 
     * @retval std::vector<size_t> - A vector containing all indices in increasing order that ch occurs at.
    */
    inline std::vector<size_t> findAll(     const std::string & str,
                                            const char ch  )
    {
        std::vector<size_t> positions;

        size_t pos = str.find(ch, 0);
        while(pos != std::string::npos)
        {
            positions.push_back(pos);
            pos = str.find(ch,pos+1);
        }

        return positions;
    }


    /**
     * 
     * 
     * Separates a string by a separator character. Returns a vector of strings that were separated.
     * 
     * Example:
     * 
     * std::vector<std::string> result = separate("John,Gina,Sebastian,Nick");
     * 
     * //Value of result is: {"John","Gina","Sebastian","Nick"}
     * 
     * @param str - The string we intend to separate with this function.
     * @param separator - The char we intend to separate str by.
     * @param omitEmptyStrings - If true, do not include empty strings in the returned vector.
     *
     * @retval A vector of substrings of the original string that have been split up by all occurrences of the separator parameter
     */
    inline std::vector<std::string> separate(   const std::string_view & str,
                                                const char separator = ',',
                                                const bool omitEmptyStrings = true  )
    {
        //If we are given an empty string, just return an empty vector
        if(str.empty())
        {
            return {};
        }

        //Initialize all the variables we'll be using in our loop
        std::vector<std::string> separatedStringsVec;
        std::string separatedString;
        size_t currSeparatorIndex;
        size_t prevSeparatorIndex = 0;

        //Loop until we've found all of the separator chars in the string_view
        while(true)
        {
            //Look for a separator char in the string_view
            currSeparatorIndex = str.find(separator, prevSeparatorIndex);
            //If the separator is not found, just get everything up until the end 
            if(currSeparatorIndex == std::string_view::npos)
            {
                separatedString = str.substr(prevSeparatorIndex, str.length());
                separatedStringsVec.push_back(separatedString);
                break;
            }
            //Once we've found the index, of the separator char, get all of the string that we jumped over since the last separator character
            separatedString = str.substr(prevSeparatorIndex, currSeparatorIndex-prevSeparatorIndex);
            //Push it bank into our vector
            separatedStringsVec.push_back(separatedString);
            //Set the prevSeparatorIndex to currSeparatorIndex now
            prevSeparatorIndex = currSeparatorIndex + 1;
        }

        //If we are omitting empty strings in our result, erase all of that we found
        if(omitEmptyStrings)
        {
            separatedStringsVec.erase(std::remove(separatedStringsVec.begin(), separatedStringsVec.end(), ""), separatedStringsVec.end());
        }

        return separatedStringsVec;
    }


    /**
     * 
     * 
     * Variant of separate that lets you separate by strings instead of chars.
     * 
     * Separates a string by a separator substring. Returns a vector of strings that 
     * were separated by the separator substring.
     * 
     * Example:
     * 
     * std::vector<std::string> result = separate("Wakko and Yakko and Dot", " and ");
     * 
     * //Value of result is: {"Wakko","Yakko","Dot"}
     *
     * @param str - The string we intend to separate with this function.
     * @param separator - The substring of str we intend to separate it by.
     * @param omitEmptyStrings - If true, do not include empty strings in the returned vector.
     *
     * @retval A vector of substrings of the original string that have been split up by all occurrences of the separator parameter
     */
    inline std::vector<std::string> separate(   const std::string & str,
                                                const std::string_view & separator,
                                                const bool omitEmptyStrings = true  )
    {
        //If we have a single character separator, we can use a more efficient method
        if(separator.length() == 1)
        {
            return stevensStringLib::separate( str, separator[0], omitEmptyStrings );
        }

        std::vector<std::string> separatedStrings;
        std::string word;
        //Iterate through the input string and piece together the strings we want to separate
        for(int i = 0; i < str.length(); i++)
        {
            word += str[i];
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
        
        //If we are omitting empty strings in our result, erase all of that we found
        if(omitEmptyStrings)
        {
            separatedStrings.erase(std::remove(separatedStrings.begin(), separatedStrings.end(), ""), separatedStrings.end());
        }

        return separatedStrings;
    }


    /**
     *  Returns a string with the first letter capitalized. If the string is empty, then we just return the empty string.
     * 
     *  @param str - The string we want to capitalize the first letter of.
     * 
     *  @retval std::string - The string str with the first letter capitalized.
     */
    inline std::string cap1stChar(std::string str)
    {
        if(str.length() > 0)
        {
            str[0] = std::toupper(str[0]);
        }
        return str;
    }


    /**
     * Returns a string with all characters in uppercase if possible.
     * 
     * Credit to this article: https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
     * 
     * @param  str - The string we would like to make all uppercase.
     * 
     * @retval string - The parameter str, but all in uppercase!
     *  
    `*/
    inline std::string toUpper(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char x) { return std::toupper(x); });
        return str;
    }


    /**
     * Detects if a string is in the form of a valid C++ integer/integral type (bool, char, short, int, long int, long long int).
     * 
     * @param str - A string we are checking to see if it represents an integer/integral type.
     * 
     * @retval bool - true if the string str represents an integer, false otherwise.
    */
    inline bool isInteger( const std::string_view & str )
    {
        //Test to see if the string can be parsed into a long long int
        long long int value;
        const auto res = std::from_chars(   str.data(), 
                                            str.data() + str.size(), 
                                            value );

        //Return false if we have relevant errors
        if (res.ec == std::errc::invalid_argument)
        {
            return false;
        }
        else if (res.ec == std::errc::result_out_of_range)
        {
            return false;
        }

        //If we have a decimal point in the string, check to see if there are any nonzero digits to the right of the point
        char point = std::use_facet< std::numpunct<char> >(std::cout.getloc()).decimal_point();
        if(contains(str, point))
        {
            std::vector<std::string> wholeAndDecimalParts = stevensStringLib::separate(str, point, false);
            //Take the decimal part, and check to see if it contains anything other than zeroes
            if(!containsOnly(wholeAndDecimalParts[1], "0"))
            {
                return false;
            }
        }

        //Otherwise, return true
        return true;
    }


    /**
     * Detects if a string is in the form of a valid c++ floating point type (float, double, long double).
     * 
     * @param str - A string we are checking to see if it represents a floating point type.
     * 
     * @retval bool - true if the string str represents a floating point type. False otherwise.
    */
    inline bool isFloat( const std::string & str )
    {
        //Test to see if the string can be parsed into a long double
        long double value;
        const auto format = std::chars_format::general;
        const auto res = std::from_chars(   str.data(), 
                                            str.data() + str.size(), 
                                            value, 
                                            format  );

        //Return false if we have relevant errors
        if (res.ec == std::errc::invalid_argument)
        {
            return false;
        }
        else if (res.ec == std::errc::result_out_of_range)
        {
            return false;
        }
        
        //Check to see if we have more than one decimal point (Only can have one decimal point)
        char point = std::use_facet< std::numpunct<char> >(std::cout.getloc()).decimal_point();
        if(stevensStringLib::findAll(str, point).size() > 1)
        {
            return false;
        }

        //Check to see if the double we are converting is too precise to be a long double (Cannot have numbers that are too precise)
        std::vector<std::string> wholeAndDecimalParts = stevensStringLib::separate(str, point, false);
        if( wholeAndDecimalParts[1].length() > std::numeric_limits<long double>::digits10 )
        {
            return false;
        }

        //Otherwise, return true
        return true;
    }


    /**
     * @brief 
     * 
     * Given a string, check to see if it represents a number in standard notation. Useful to check numbers that may cause overflow or underflow
     * to be check with isInteger or may be too precise to be checked with isFloat.
     * 
     * Example: 
     * isStandardNumber("-214748364721474836472147483647.123123123123123") == true
     * isStandardNumber("2.5e2") == false
     * 
     * @param str The string we are checking to see if it represents a number in standard notation.
     * @return true if str represents a number in standard notation
     * @return false if str does not represent a number in standard notation
     */
    inline bool isStandardNumber(   const std::string_view & str  )
    {
        //If our string is empty, return false
        if(str.empty())
        {
            return false;
        }
        //If we have a string of length 1, just check to see if the single character is a digit
        else if(str.length() == 1)
        {
            return std::isdigit(str[0]);
        }
        //Get the decimal point for our locale
        char point = std::use_facet< std::numpunct<char> >(std::cout.getloc()).decimal_point();
        bool seenDecimalPoint = false;
        //Otherwise, iterate through all of the characters in the string and examine each one
        for(int i = 0; i < str.length(); i++)
        {
            switch(i)
            {
                //Check to see if the first character in the string is a sign. We allow this!
                case 0:
                    if(str[i] == '-' || str[i] == '+')
                    {
                        continue;
                    }
                default:
                    //Check to see if the character is a decimal point
                    if(str[i] == point)
                    {
                        if(!seenDecimalPoint)
                        {
                            seenDecimalPoint = true;
                        }
                        //Numbers in standard notation only contain a single decimal point, so we return false.
                        else
                        {
                            return false;
                        }
                    }
                    //Check to see if the character is a numerical digit
                    else if(!isdigit(str[i]))
                    {
                        //If we have a character that's not a numerical digit which is not a decimal point or negative sign, it's not in standard notation. Return false.
                        return false;
                    }
                    break;
            }
        }

        //We've made it past all of the checks by this point, so we must have a string representing a number in standard notation.
        return true;
    }


    /**
     *  Detects if a string consists of only numeric characters, and potentially a 
     *  decimal point and leading negative sign.
     *
     *  @param str - The string we are checking to see if it represents a number.
     *  
     *  @retval bool - True if the string represents a number. False if otherwise.
     *    
     */
    inline bool isNumber(  const std::string_view & str   )
    {
        //Method 1: Check for standard integer/floating point notation
        bool standardResult = stevensStringLib::isStandardNumber(str);
        //Method 2: Check for a scientific notation
        //TODO isScientificNumber()

        return standardResult; // || scientificResult;
    }


    /**
     * Takes in a string and checks to see if it is a representation of the word "true" or a string
     * representing a non-zero number. In those cases, return a true bool. In all other cases, return false. 
     * 
     * @param str - A string we are converting to a bool.
     * 
     * @retval True if str is a form of the word true or 0, and false otherwise.
    */
    inline bool stringToBool( const std::string & str )
    {
        if( toUpper(str) == "TRUE")
        {
            return true;
        }
        else if( isNumber(str) )
        {
            //TODO: Eventually address this for optimization:
            // JJO: The call to isNumber as already scanned the string, **and**
            // has converted it into an integer or float via
            // std::from_chars. Here we are doing a third scan of the string.
            // It's a lot!
            return std::stold(str);
        }
        return false;
    }


    /**
     * Converts a boolean value to a string value. 
     * 
     * Credit to OJ and Igor Ganapolsky: https://stackoverflow.com/a/29798/16511184
     * 
     * @param input - The boolean value we wish to convert to a string.
     * 
     * @retval The boolean value represented as a string.
     */
    inline std::string boolToString( const bool input  )
    {
        return input ? "true" : "false";
    }


    /**
     * Given a string and integer X, erase (trim) X characters from both the beginning and end of the string.
     * 
     * @param str - A string we would like to trim the characters from.
     * @param charsToTrim - The number of characters to trim from the beginning and end of the string.
     * 
     * @retval A modified version of the string str, with a number characters from both the beginning and end of the 
     *         string trimmed off equal to charsToTrim.
     */
    inline std::string trim(    const std::string & str,
                                const unsigned int charsToTrim   )
    {
        //If we have a charsToTrim value greater than half the the length of the input string, we return an empty string
        if(charsToTrim >= (str.length()/2))
        {
            return "";
        }
        
        return str.substr(charsToTrim, (str.length() - (charsToTrim * 2)));
    }


    /**
     * Removes all tabs, spaces, newlines, and anything else from a string that is defined as whitespace in the current locale.
     * 
     * Learn what is defined as whitespace: https://en.cppreference.com/w/cpp/string/byte/isspace
     * Credit to Michael Steller: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
     * 
     * @param str - The string from which we wish to remove all the whitespace from.
     * 
     * @retval The input string but with all of the whitespace removed
     */
    inline std::string removeWhitespace( std::string str )
    {
        str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end());
        return str;
    }


    /**
     * @brief Does the work step for mapifyString and unordered_mapifyString.
     * 
     * This function does not need to be directly called, instead, please use
     * mapifyString() and unorderedMapifyString()
     */
    template<typename T>
    inline T mapifyStringHelper(    T map,
                                    std::string str,
                                    std::string keyValueSeparator,
                                    std::string pairSeparator   )
    {

        //Separate the pairs
        std::vector<std::string> keysAndValues = stevensStringLib::separate(str,pairSeparator);

        //Separate the keys and values
        std::vector<std::string> keyAndValue; 
        for(int i = 0; i < keysAndValues.size(); i++)
        {
            keyAndValue = stevensStringLib::separate(keysAndValues[i], keyValueSeparator);
            /*if(keyAndValue.size() == 0)
            {
                //No keys or values found, skip
                continue;
            }
            else */if(keyAndValue.size() == 1)
            {
                //Insert a key with an empty value
                map[keyAndValue[0]] = "";
            }
            else if(keyAndValue.size() >= 2)
            {
                //Insert the key value pair into the map (only the first two elements)
                map[keyAndValue[0]] = keyAndValue[1];
            }
        }

        return map;
    }


    /**
     * TODO: Problem!!! Data could potentially contain separator strings. We need to prevent this, possibly by requiring JSON formatting?
     * 
     * Given an input string str that can represent a map<std::string,std::string, take two separator strings and 
     * separate the pairs from eachother, and the keys and values from each other. Then
     * insert each key value pair into a std::map<std::string,std::string> object.
     * 
     * @param str - The string we would like to convert into a map<std::string,std::string>.
     * @param keyValueSeparator - The string in str using to separate keys from values.
     * @param pairSeparator - The string in str we are using separate pairs.

     * @retval A map object of string-string key-value pairs.
    */
    inline std::map<std::string,std::string> mapifyString(  const std::string & str,
                                                            const std::string & keyValueSeparator,
                                                            const std::string & pairSeparator   )
    {
        std::map<std::string,std::string> map;
        return mapifyStringHelper( map, str, keyValueSeparator, pairSeparator);
    }


    /**
     * Variant of mapifyString that works for std::unordered_maps 
    */
    inline std::unordered_map<std::string,std::string> unorderedMapifyString(  std::string str,
                                                                                std::string keyValueSeparator = ":",
                                                                                std::string pairSeparator  = ","    )
    {
        std::unordered_map<std::string,std::string> unordered_map;
        return mapifyStringHelper( unordered_map, str, keyValueSeparator, pairSeparator);
    }


    /**
     * Given an map or unordered_map of strings, turn it into a string of keys and values paired together, separated by delimiting characters.
     * 
     *  @param map - Th map or unordered_map with string keys and values which we intend to turn into a string.
     *  @param keyValueSeparator - The string that separates keys from their values in the returned string.
     *  @param pairSeparator - The string that separates key-value pairs in the returned string.
     * 
     *  @retval The all contents of the unordered map turned into a string list of separated key-value pairs.
    */
    template<typename T>
    inline std::string stringifyMap(    const T & map,
                                        const std::string & keyValueSeparator = ":",
                                        const std::string & pairSeparator =     "," )
    {
        std::string stringifiedMap = "";
        //Iterate through the unordered map, appending each pair to the string
        for(const auto & [key,value] : map )
        {
            if(!stringifiedMap.empty())
            {
                stringifiedMap += pairSeparator;
            }
            stringifiedMap += key + keyValueSeparator + value;
        }
        return stringifiedMap;
    }


    /**
     * Given a string, count how many lines are in that string and return the integer count.
     * 
     * Solution from: https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
     * 
     * TODO: Concerned with line counting problems presented here: https://stackoverflow.com/a/843484/16511184
     * 
     * @param str - The string which we wish to count the number of lines of.
     * 
     * @retval int - The integer count of the number of lines that the string str has.
    */
    inline int countLines(std::string str)
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
     * @param filePath - The path to the file we want to count the number of lines of.
     * 
     * @retval int - The integer number of lines that the file contains.
    */
    inline int countFileLines(const std::string & filePath)
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
     * @param str - The string which we wish to wrap to a certain width.
     * @param wrapWidth - The width in number of characters we wish to wrap.
     * 
     * @retval std::string - A modified version of the parameter str, with newlines added to it so that it fits within
     *                a certain character width.
     *  
    */
    inline std::string wrapToWidth(     std::string str,
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
     * Given a string and an integer representing an index, return a single character from the string by the process of circular 
     * indexing.
     *  
     * Circular indexing is performed by indexing over the string from left to right. Once the index exceeds the length of the string, we begin
     * indexing again from the lefthand side of the string and repeat the process until we stop at the final index. We return the character at 
     * that final index.
     * 
     * Example: circularIndex("Hello world!", 13) returns 'e', as we loop around to 'H' at 12 and index one space further to reach 'e'.
     * 
     * @param str - The string we are circularly indexing through.
     * @param i - The index of the string to circularly index to.
     * 
     * @retval A character found in str that has been circularly indexed to at position i
    */
    inline char circularIndex(  const std::string & str,
                                unsigned int i )
    {
        if(str.empty())
        {
            throw std::invalid_argument("str cannot be empty for circularIndex()");
        }
        return str[i % str.length()];
    }


    /**
     * Given a string str, erase the last n characters of the string.
     * 
     * Credit to Varun: https://thispointer.com/remove-last-n-characters-from-a-string-in-c/
     * 
     * @param str - The string we want to erase characters from the end of.
     * @param n - The number of characters we want to erase
     * 
     * @retval std::string - The string str having n characters erased from the end of it.
    */
    inline std::string eraseCharsFromEnd(   std::string str,
                                            int n   )
    {
        //Can't erase from empty strings, and we can't erase more characters from the string than what we have
        if(str.size() >= n)
        {
            return "";
        }

        str.erase(str.size() - n);
        return str;
    }


    /**
     * Given a locale, return all of the whitespace characters for that locale in a string.
     * 
     * Credit to Nathan Oliver: https://stackoverflow.com/a/36311304/16511184
     * 
     * @param loc - The locale which we want to obtain a string of all whitespace characters for.
     * 
     * @retval A string of all whitespace characters defined in the given locale.
    */
    inline std::string getWhitespaceString(const std::locale & loc)
    {
        std::string whitespace;
        for (char ch = std::numeric_limits<char>::min(); ch < std::numeric_limits<char>::max(); ch++)
            if (std::isspace(ch, loc))
                whitespace += ch;
        // to avoid infinte loop check char max outside the for loop.
        if (std::isspace(std::numeric_limits<char>::max(), std::locale(loc)))
            whitespace += std::numeric_limits<char>::max();
        return whitespace;
    }


    /**
     * Remove all leading and trailing whitespace from a string (spaces, tabs, newlines, etc.), then return it.
     * 
     * Credit to GManNickG and Kef Schecter: https://stackoverflow.com/a/1798170
     * 
     * @param str - The string to remove all of the leading and trailing whitespaces from.
     * 
     * @retval str modified by removing all of its leading and trailing whitespaces.
    */
    inline std::string trimWhitespace( const std::string & str )
    {
        //Get a string of all of the whitespace characters in the current locale
        std::string whitespace = getWhitespaceString(std::locale(""));
        
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
        {
            return ""; // no content
        }
            
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }


    //trimAllOf


    /**
     * Given a character c, convert it to a std::string.
     * 
     * @param c - The character we'd like to convert to a string.
     * 
     * @retval A string representing the character c.
    */
    inline std::string charToString( const char & c )
    {
        std::string s(1, c);
        return s;
    }


    /**
     * Erases all non-numeric characters from a string and returns it.
     * 
     * @param str - The string to release all non-numeric chars from.
     * 
     * @retval The string parameter we passed in, but all of its non-numeric characters removed from it.
    */
    inline std::string eraseNonNumericChars( std::string str )
    {
        str.erase(std::remove_if(str.begin(), str.end(), [](char c){ return !isdigit(c); }), str.end());
        return str;
    }


    /**
     * Reverses the order of a string's characters using std::reverse().
     * 
     * @param str - The string we would like to reverse.
     * 
     * @retval std::string - The reversed string.
    */
    inline std::string reverse( std::string str )
    {
        std::reverse(str.begin(),str.end());
        return str;
    }


    /**
     * Checks to see if a std::string is a palindrime or not (the reversed order of characters equals the original order of characters).
     * Note well that character case, spacing, and punctuation present in classic English palindromes like "A man, a plan, a canal, panama"
     * prevent them from being valid C++ palindromes with this function, as the reverse order of this exact string is "amanap ,lanac a ,nalp a ,nam A" is
     * not equivalent to the original order of characters.
     * 
     * Credit to Cubbi: https://stackoverflow.com/a/8362657/16511184
     * 
     * @param str - The string we would like to check.
     * 
     * @retval true if str is a palindrome, false otherwise.
    */
    inline bool isPalindrome( const std::string & str )
    {
        return std::equal(str.begin(), str.begin() + str.size()/2, str.rbegin());
    }


    //replace


    //eraseAll


    //scramble


    //negativeIndex


    /**
     * @deprecated
     * In C++20 and onward, please use std::string.starts_with instead.
     * 
     * @brief Check a string to see if it begins with a substring.
     * 
     * @param str - The string we are checking to see if it begins with another substring.
     * @param substr - The substring we are checking the beginning of str against to see if they are equal.
     * @return true if the string str begins with substr
     * @return false  if the string str does NOT begin with substr
     */
    inline bool startsWith(     const std::string_view & str, 
                                const std::string_view & substr )
    {
        //If the substring is longer than the string, then it's not possible for the string to start with the substring
        if(str.length() < substr.length())
        {
            return false;
        }
        //Check the beginning of str to see if it is equivalent to substr
        if(str.substr(0,substr.length()) == substr)
        {
            return true;
        }
        return false;
    }

}
#endif
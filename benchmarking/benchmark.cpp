#include <benchmark/benchmark.h>
#include<chrono>
#include<string>
#include "../stevensStringLib.h"

/*** contains (string variant) ***/
static void contains_str_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "Live and learn! Hanging on the edge of tomorrow! Live and learn! From the works of yesterday! "
                         "Live and learn! If you beg or borrow! Live and learn! You may never find your way!";
    std::string substr = "way";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::contains(string, substr);
    }
}
//Register function as a benchmark
BENCHMARK(contains_str_basic);


/*** contains (char variant) ***/
static void contains_char_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "Live and learn! Hanging on the edge of tomorrow! Live and learn! From the works of yesterday! "
                         "Live and learn! If you beg or borrow! Live and learn! You may never find your way!";
    char c = 'w';
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::contains(string, c);
    }
}
//Register function as a benchmark
BENCHMARK(contains_char_basic);


/*** containsOnly ***/
static void containsOnly_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "111122222222222222!333333333333333";
    std::string chars = "123";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::containsOnly(string, chars);
    }
}
//Register function as a benchmark
BENCHMARK(containsOnly_basic);


/*** eraseCharsFromEnd ***/
static void eraseCharsFromEnd_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "I am the eggman, I have the masterplan!";
    size_t n = 24;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::eraseCharsFromEnd(string, n);
    }
}
//Register function as a benchmark
BENCHMARK(eraseCharsFromEnd_basic);


/*** eraseCharsFromEnd ***/
static void eraseCharsFromStart_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "I am the eggman, I have the masterplan!";
    size_t n = 24;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::eraseCharsFromStart(string, n);
    }
}
//Register function as a benchmark
BENCHMARK(eraseCharsFromStart_basic);


/*** eraseCharsFromEnd ***/
static void startsWith_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "Can you feel the sunshine!";
    std::string startsWithStr = "Can you feel the sun";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::startsWith(string, startsWithStr);
    }
}
//Register function as a benchmark
BENCHMARK(startsWith_basic);


/*** findAll (string variant) ***/
static void findAll_str_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "The quick brown fox jumps over the lazy dog. The fox is quick and the dog is lazy. Quick foxes and lazy dogs are common in stories about quick animals.";
    std::string strToFind = "quick";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::findAll(string,strToFind);
    }
}
//Register function as a benchmark
BENCHMARK(findAll_str_basic);


/*** findAll (char variant) ***/
static void findAll_char_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "00010000000000000101011100000000000000000000000100000000000000000000000000000000000000011";
    char charToFind = '1';
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::findAll(string,charToFind);
    }
}
//Register function as a benchmark
BENCHMARK(findAll_char_basic);


/*** separate (char variant) ***/
static void separate_char_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "apple,banana,cherry,date,elderberry,fig,grape,honeydew,kiwi,lemon,mango,nectarine,orange,papaya,quince,raspberry,strawberry,tangerine,watermelon";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::separate(string);
    }
}
//Register function as a benchmark
BENCHMARK(separate_char_basic);


/*** separate (char variant) ***/
static void separate_str_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "67$%$14$%$633$%$99$%$$%$$%$124$%$6$%$aquatic$%$no$%$no$%$yes$%$23$%$23$%$standard";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::separate(string,"$%$");
    }
}
//Register function as a benchmark
BENCHMARK(separate_str_basic);


/*** cap1stChar ***/
static void cap1stChar_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "smitty werbenjaegermanjensen";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::cap1stChar(string);
    }
}
//Register function as a benchmark
BENCHMARK(cap1stChar_basic);


/*** toUpper ***/
static void toUpper_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "smitty werbenjaegermanjensen";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::toUpper(string);
    }
}
//Register function as a benchmark
BENCHMARK(toUpper_basic);


/*** isInteger ***/
static void isInteger_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "9001.0";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::isInteger(string);
    }
}
//Register function as a benchmark
BENCHMARK(isInteger_basic);


/*** isFloat ***/
static void isFloat_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "9001.0";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::isFloat(string);
    }
}
//Register function as a benchmark
BENCHMARK(isFloat_basic);


/*** isStandardNumber ***/
static void isStandardNumber_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "9001.0";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::isStandardNumber(string);
    }
}
//Register function as a benchmark
BENCHMARK(isStandardNumber_basic);


/*** isScientificNumber ***/
static void isScientificNumber_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "9.001e3";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::isScientificNumber(string);
    }
}
//Register function as a benchmark
BENCHMARK(isScientificNumber_basic);


/*** isNumber ***/
static void isNumber_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "9.001e3";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::isNumber(string);
    }
}
//Register function as a benchmark
BENCHMARK(isNumber_basic);


/*** stringToBool ***/
static void stringToBool_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "FALSE";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::stringToBool(string);
    }
}
//Register function as a benchmark
BENCHMARK(stringToBool_basic);


/*** boolToString ***/
static void boolToString_basic(benchmark::State & state)
{
    //Perform setup here
    bool b = false;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::boolToString(b);
    }
}
//Register function as a benchmark
BENCHMARK(boolToString_basic);


/*** trim ***/
static void trim_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "xXxEpic-GamerxXx";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::trim(string, 3);
    }
}
//Register function as a benchmark
BENCHMARK(trim_basic);


/*** removeWhiteSpace ***/
static void removeWhitespace_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "All\tof\tyour\tfears\tare\twell-founded\tand\ttrue\n"
                         "All of my hands are callous and cruel\n"
                         "All\rof\rmy\rarrows\rthat\rriddle\ryou\rthrough\n"
                         "Are\vbullets\vthat\ffire\fme\fback into you";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::removeWhitespace(string);
    }
}
//Register function as a benchmark
BENCHMARK(removeWhitespace_basic);


/*** mapifyString ***/
static void mapifyString_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "Warsim:Huw Milward,CultGame:Jeff Stevens,Kindred Fates:Rob Cravens,Photo Fighter:John Fernow";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::mapifyString(string);
    }
}
//Register function as a benchmark
BENCHMARK(mapifyString_basic);


/*** unorderedMapifyString ***/
static void unorderedMapifyString_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "Warsim:Huw Milward,CultGame:Jeff Stevens,Kindred Fates:Rob Cravens,Photo Fighter:John Fernow";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::unorderedMapifyString(string);
    }
}
//Register function as a benchmark
BENCHMARK(unorderedMapifyString_basic);


/*** stringifyMap ***/
static void stringifyMap_basic(benchmark::State & state)
{
    //Perform setup here
    std::map<std::string,std::string> map = {   {"Warsim","Huw Milward"},
                                                {"CultGame","Jeff Stevens"},
                                                {"Kindred Fates","Rob Cravens"},
                                                {"Photo Fighter","John Fernow"} };
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::stringifyMap(map);
    }
}
//Register function as a benchmark
BENCHMARK(stringifyMap_basic);


/*** countLines ***/
static void countLines_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "firstline\nsecondline\nthirdline\n";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::countLines(string);
    }
}
//Register function as a benchmark
BENCHMARK(countLines_basic);


/*** wrapToWidth ***/
static void wrapToWidth_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "111222333";
    size_t width = 3;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::wrapToWidth(string, width);
    }
}
//Register function as a benchmark
BENCHMARK(wrapToWidth_basic);


/*** circularIndex ***/
static void circularIndex_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "resonance!";
    size_t index = 105;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::circularIndex(string, index);
    }
}
//Register function as a benchmark
BENCHMARK(circularIndex_basic);


/*** getWhiteSpaceString ***/
static void getWhitespaceString_basic(benchmark::State & state)
{
    //Perform setup here
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::getWhitespaceString(std::locale(""));
    }
}
//Register function as a benchmark
BENCHMARK(getWhitespaceString_basic);


/*** getWhiteSpaceString ***/
static void trimWhitespace_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = " \n\t\r\v\f Hello, world! \n\t\r\v\f";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::trimWhitespace(string);
    }
}
//Register function as a benchmark
BENCHMARK(trimWhitespace_basic);


/*** charToString ***/
static void charToString_basic(benchmark::State & state)
{
    //Perform setup here
    char c = '$';
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::charToString(c);
    }
}
//Register function as a benchmark
BENCHMARK(charToString_basic);


/*** eraseNonNumericChars ***/
static void eraseNonNumericChars_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "1 pumpkin, 5 eggplant, 3 squash, 9001 nappa cabbage";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::eraseNonNumericChars(string);
    }
}
//Register function as a benchmark
BENCHMARK(eraseNonNumericChars_basic);


/*** reverse ***/
static void reverse_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "1 pumpkin, 5 eggplant, 3 squash, 9001 nappa cabbage";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::reverse(string);
    }
}
//Register function as a benchmark
BENCHMARK(reverse_basic);


/*** isPalindrome ***/
static void isPalindrome_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "racecar";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::isPalindrome(string);
    }
}
//Register function as a benchmark
BENCHMARK(isPalindrome_basic);


/*** format (vector variant) ***/
static void format_vectorVariant_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "{0}{1}{2}";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::format(string, {"Hello",", ","world!"});
    }
}
//Register function as a benchmark
BENCHMARK(format_vectorVariant_basic);


/*** format (map variant) ***/
static void format_mapVariant_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "{greeting}{punctuation}{addressee}";
    std::unordered_map<std::string,std::string> map = { {"greeting",    "Hello" },
                                                        {"punctuation", ", "    },
                                                        {"addressee",   "world!"}   };
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::format(string, map);
    }
}
//Register function as a benchmark
BENCHMARK(format_mapVariant_basic);




/*** endsWith ***/
static void endsWith_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "The quick brown fox jumps over the lazy dog";
    std::string suffix = "lazy dog";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::endsWith(string, suffix);
    }
}
//Register function as a benchmark
BENCHMARK(endsWith_basic);


/*** join ***/
static void join_basic(benchmark::State & state)
{
    //Perform setup here
    std::vector<std::string> vec = {"apple", "banana", "cherry", "date", "elderberry"};
    std::string separator = ", ";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::join(vec, separator);
    }
}
//Register function as a benchmark
BENCHMARK(join_basic);


/*** toLower ***/
static void toLower_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::toLower(string);
    }
}
//Register function as a benchmark
BENCHMARK(toLower_basic);


/*** multiply ***/
static void multiply_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "Hello";
    int times = 10;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::multiply(string, times);
    }
}
//Register function as a benchmark
BENCHMARK(multiply_basic);


/*** replaceSubstr ***/
static void replaceSubstr_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "The quick brown fox jumps over the lazy dog. The fox is quick.";
    std::string target = "fox";
    std::string replacement = "wolf";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::replaceSubstr(string, target, replacement);
    }
}
//Register function as a benchmark
BENCHMARK(replaceSubstr_basic);


/*** eraseTrailingZeroes ***/
static void eraseTrailingZeroes_basic(benchmark::State & state)
{
    //Perform setup here
    float num = 123.45000f;
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::eraseTrailingZeroes(num);
    }
}
//Register function as a benchmark
BENCHMARK(eraseTrailingZeroes_basic);


/*** csvAppend ***/
static void csvAppend_basic(benchmark::State & state)
{
    //Perform setup here
    for(auto _ : state)
    {
        std::string csvs = "apple,banana,cherry";
        std::string valueToAdd = "date";
        //Code gets timed
        stevensStringLib::csvAppend(csvs, valueToAdd);
    }
}
//Register function as a benchmark
BENCHMARK(csvAppend_basic);


/*** scramble ***/
static void scramble_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "The quick brown fox jumps over the lazy dog";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::scramble(string);
    }
}
//Register function as a benchmark
BENCHMARK(scramble_basic);


//Run the benchmark
BENCHMARK_MAIN();
#include <benchmark/benchmark.h>
#include<chrono>
#include<string>
#include "../stevensStringLib.h"

/*** contains (string variant) ***/
static void BM_contains_str_basic(benchmark::State & state)
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
BENCHMARK(BM_contains_str_basic);


/*** contains (char variant) ***/
static void BM_contains_char_basic(benchmark::State & state)
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
BENCHMARK(BM_contains_char_basic);


/*** containsOnly ***/
static void BM_containsOnly_basic(benchmark::State & state)
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
BENCHMARK(BM_containsOnly_basic);


/*** eraseCharsFromEnd ***/
static void BM_eraseCharsFromEnd_basic(benchmark::State & state)
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
BENCHMARK(BM_eraseCharsFromEnd_basic);


/*** eraseCharsFromEnd ***/
static void BM_eraseCharsFromStart_basic(benchmark::State & state)
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
BENCHMARK(BM_eraseCharsFromStart_basic);


/*** eraseCharsFromEnd ***/
static void BM_startsWith_basic(benchmark::State & state)
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
BENCHMARK(BM_startsWith_basic);


/*** findAll (string variant) ***/
static void BM_findAll_str_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "22200010000000000000101011100002220000000000000000000122200000000000000000000000000000022200000000011";
    std::string strToFind = "222";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::findAll(string,strToFind);
    }
}
//Register function as a benchmark
BENCHMARK(BM_findAll_str_basic);


/*** findAll (char variant) ***/
static void BM_findAll_char_basic(benchmark::State & state)
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
BENCHMARK(BM_findAll_char_basic);


/*** separate (char variant) ***/
static void BM_separate_char_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "67,14,633,99,,,124,6,aquatic,no,no,yes,23,23,standard";
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::separate(string);
    }
}
//Register function as a benchmark
BENCHMARK(BM_separate_char_basic);


/*** separate (char variant) ***/
static void BM_separate_str_basic(benchmark::State & state)
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
BENCHMARK(BM_separate_str_basic);


/*** cap1stChar ***/
static void BM_cap1stChar_basic(benchmark::State & state)
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
BENCHMARK(BM_cap1stChar_basic);


/*** toUpper ***/
static void BM_toUpper_basic(benchmark::State & state)
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
BENCHMARK(BM_toUpper_basic);


/*** isInteger ***/
static void BM_isInteger_basic(benchmark::State & state)
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
BENCHMARK(BM_isInteger_basic);


/*** isFloat ***/
static void BM_isFloat_basic(benchmark::State & state)
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
BENCHMARK(BM_isFloat_basic);


/*** isStandardNumber ***/
static void BM_isStandardNumber_basic(benchmark::State & state)
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
BENCHMARK(BM_isStandardNumber_basic);


/*** isScientificNumber ***/
static void BM_isScientificNumber_basic(benchmark::State & state)
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
BENCHMARK(BM_isScientificNumber_basic);


/*** isNumber ***/
static void BM_isNumber_basic(benchmark::State & state)
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
BENCHMARK(BM_isNumber_basic);


/*** stringToBool ***/
static void BM_stringToBool_basic(benchmark::State & state)
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
BENCHMARK(BM_stringToBool_basic);


/*** boolToString ***/
static void BM_boolToString_basic(benchmark::State & state)
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
BENCHMARK(BM_boolToString_basic);


/*** trim ***/
static void BM_trim_basic(benchmark::State & state)
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
BENCHMARK(BM_trim_basic);


/*** removeWhiteSpace ***/
static void BM_removeWhitespace_basic(benchmark::State & state)
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
BENCHMARK(BM_removeWhitespace_basic);


/*** mapifyString ***/
static void BM_mapifyString_basic(benchmark::State & state)
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
BENCHMARK(BM_mapifyString_basic);


/*** unorderedMapifyString ***/
static void BM_unorderedMapifyString_basic(benchmark::State & state)
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
BENCHMARK(BM_unorderedMapifyString_basic);


/*** stringifyMap ***/
static void BM_stringifyMap_basic(benchmark::State & state)
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
BENCHMARK(BM_stringifyMap_basic);


/*** countLines ***/
static void BM_countLines_basic(benchmark::State & state)
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
BENCHMARK(BM_countLines_basic);


/*** wrapToWidth ***/
static void BM_wrapToWidth_basic(benchmark::State & state)
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
BENCHMARK(BM_wrapToWidth_basic);


/*** circularIndex ***/
static void BM_circularIndex_basic(benchmark::State & state)
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
BENCHMARK(BM_circularIndex_basic);


/*** getWhiteSpaceString ***/
static void BM_getWhitespaceString_basic(benchmark::State & state)
{
    //Perform setup here
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::getWhitespaceString(std::locale(""));
    }
}
//Register function as a benchmark
BENCHMARK(BM_getWhitespaceString_basic);


/*** getWhiteSpaceString ***/
static void BM_trimWhitespace_basic(benchmark::State & state)
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
BENCHMARK(BM_trimWhitespace_basic);


/*** charToString ***/
static void BM_charToString_basic(benchmark::State & state)
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
BENCHMARK(BM_charToString_basic);


/*** eraseNonNumericChars ***/
static void BM_eraseNonNumericChars_basic(benchmark::State & state)
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
BENCHMARK(BM_eraseNonNumericChars_basic);


/*** reverse ***/
static void BM_reverse_basic(benchmark::State & state)
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
BENCHMARK(BM_reverse_basic);


/*** isPalindrome ***/
static void BM_isPalindrome_basic(benchmark::State & state)
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
BENCHMARK(BM_isPalindrome_basic);


/*** format (vector variant) ***/
static void BM_format_vectorVariant_basic(benchmark::State & state)
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
BENCHMARK(BM_format_vectorVariant_basic);


/*** format (map variant) ***/
static void BM_format_mapVariant_basic(benchmark::State & state)
{
    //Perform setup here
    std::string string = "{greeting}{punctuation}{addressee}";
    std::unordered_map<std::string,std::string> map = { {"greeting",    "Hello" },
                                                        {"punctuation", ", "    },
                                                        {"world!",       "addressee"}   };
    for(auto _ : state)
    {
        //Code gets timed
        stevensStringLib::format(string, map);
    }
}
//Register function as a benchmark
BENCHMARK(BM_format_mapVariant_basic);




//Run the benchmark
BENCHMARK_MAIN();
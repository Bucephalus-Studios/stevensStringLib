#include "stevensStringLib.h"
#include <vector>
#include <iostream>

int main()
{

    // here is an example use case
    std::string testing = stevensStringLib::replace_characters({"testing {0}{1}", "1", "This is another test"});

    std::cout << testing << std::endl;

    return 0;
}
#include "stevensStringLib.h"
#include <vector>
#include <iostream>

int main() {

    // here is an example use case
    stevensStringLib::StringTemplateReplace replace_string;

    auto vec = replace_string.multi_type_vector("testing {0}", 1);
    std::string testing = replace_string.replace_characters(vec);

    std::cout << testing << std::endl;

    return 0;
}
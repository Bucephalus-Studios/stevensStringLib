# stevensStringLib

Welcome to stevensStringLib! This is a simple C++ library full of convenient functions for working with strings. It was created to make C++ more accessible and read more like plain English.

## Demo
#### Separate a string:
```
std::string myString = "Charmander,Squirtle,Bulbasaur";
std::vector<std::string> myVector = separate( myString, "," );
// Value of myVector after separate() == {"Charmander","Squirtle","Bulbasaur"};
```






## Easy Installation!

To get started, add the following to the top of your .cpp file:

`include "<insert path to the repo folder here>/stevensStringLib.h"`


Give the library namespace a short, catchy name:

`namespace strlib = stevensStringLib;`


And then you're good to go!

`std::vector<std::string> words = strlib::separate("Hello world!, " ");`


More changes and updates to come soon! Just establishing the github page as of now. Feel free to make any changes and make pull requests!

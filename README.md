# stevensStringLib

Welcome to stevensStringLib! This is a simple C++ library full of convenient functions for working with strings. It was created to make C++ more accessible and read more like plain English.

## Demo
#### Separate a string:
```
std::string myString = "Charmander,Squirtle,Bulbasaur";

std::vector<std::string> myVector = separate( myString, "," );

for(int i=0; i < myVector.size(); i++)
{
  std::cout << myVector[i] << std::endl;
}
```
Output:
```
Charmander
Squirtle
Bulbasaur
```





## Easy Installation!

To get started, add the following to the top of your .cpp file:

`include "<insert path to the repo folder here>/stevensStringLib.h"`


Give the library namespace a short, catchy name:

`namespace strlib = stevensStringLib;`


And then you're good to go!

`std::vector<std::string> words = strlib::separate("Hello world!, " ");`


More changes and updates to come soon! Just establishing the github page as of now. Feel free to make any changes and make pull requests!

## Documentation / User Manual
To be created with an automatic documentation tool.


## Special Thanks

Julien Jorge for [his detailed code review][1]

[r/cpp][2] for their collective critiques and contributions

Rhymu for his [guide][3] on using CMake to link GoogleTest with a unit test program 



[1]: https://julien.jorge.st/posts/en/so-you-asked-for-feedback-stevensstringlib/

[2]: https://www.reddit.com/r/cpp/comments/18hlkgd/working_on_an_easytouse_c_string_library/

[3]: https://www.youtube.com/watch?v=Lp1ifh9TuFI
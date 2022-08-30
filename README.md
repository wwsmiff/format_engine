# Format engine

A `format()` function similar to that found in python.

### Requirements:
- a compiler that supports c++17

### Usage:
```cpp
#include <iostream>
#include "format_engine.hpp"

int main()
{
  std::string new_string = "My name is <std::string := 1> and I'm <int := 2> years old";
  std::cout << format_engine::format(new_string, {"Homer", 35}) << std::endl;
  
  return EXIT_SUCCESS;
 }
 ```
 
### More information:
It takes in a string and substitutes values enclosed with angular brackets containing the type and order of the variable.
eg. `"a = <int := 1>"` and a vector with the values of the variables eg. `{32}` and returns a string `a = 32`

### Types it currently supports:
  - int
  - string/std::string and const char*
  - float
  - double

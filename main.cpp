#include "format_engine.hpp"
#include <iostream>

int main()
{
	int a = 3;
	int b = 4;
	std::string test_string = "a = <int := 1>, b = <int := 2>, a * b = <int := 3> \nmy name is \"<string := 4>\" and the value of pi is <float := 5>";
	std::cout << format_engine::format(test_string , {a, b, a * b, "Homer Simpson", 3.14f}) << std::endl;

	return EXIT_SUCCESS;
}

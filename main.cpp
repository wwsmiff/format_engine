#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <initializer_list>
#include <any>
#include <variant>
#include <algorithm>

using possible_types_variant = std::variant<int, float, double, std::string>;

possible_types_variant get_value(const std::string &type, const std::any &any_)
{
	possible_types_variant temp;

	if(type == "int") temp = std::any_cast<int>(any_);
	if(type == "float") temp = std::any_cast<float>(any_);
	if(type == "double") temp = std::any_cast<double>(any_);
	if(type == "std::string" || type == "string") temp = std::any_cast<const char*>(any_);

	return temp;
}

std::string format(std::string source, const std::vector<std::any> &values)
{
	std::string::iterator current_char = source.begin();
	std::vector<std::string> types;
	std::vector<int> order_of_ints;
	std::stringstream buffer_stream;

	while(current_char++ != source.end())
	{
		if(*current_char ==  '<')
		{
			std::string type;
			std::string num;
			
			while(*(++current_char + 1) != '=')
			{
				type.push_back(*(current_char));
			}

			while(*(current_char++) != '>')
			{
				if(*current_char > '0' && *current_char < '9') 
				{
					num.push_back(*current_char);
				}
			}

			order_of_ints.push_back(std::stoi(num));

			type.erase(remove_if(type.begin(), type.end(), isspace), type.end());
			types.push_back(type);
		}
	}

	current_char = source.begin();

	static int *replace_index = new int(0);
	while(current_char != source.end())
	{
		buffer_stream << *current_char;
		current_char++;
		
		if(*current_char == '<')
		{
			possible_types_variant temp = get_value(types[*replace_index], values[*replace_index]);
			
			(*replace_index)++;

			if(auto value = std::get_if<int>(&temp))
			{
				while(*(current_char - 1) != '>') ++current_char;
				buffer_stream << *value;
			}


			else if(auto value = std::get_if<float>(&temp))
			{
				while(*(current_char - 1) != '>') ++current_char;
				buffer_stream << *value;
			}

			else if(auto value = std::get_if<std::string>(&temp))
			{
				while(*(current_char - 1) != '>') ++current_char;
				buffer_stream << *value;
			}
			
			else if(auto value = std::get_if<double>(&temp))
			{
				while(*(current_char - 1) != '>') ++current_char;
				buffer_stream << *value;
			}
		}
	}

	delete replace_index;
	
	return buffer_stream.str();	
}

int main()
{
	int a = 3;
	int b = 4;
	std::cout << format("a * b = <int := 1>", {a * b}) << std::endl;

	return EXIT_SUCCESS;
}

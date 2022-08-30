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

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &other)
{
    if(other.size())
    {
        out << "[";
        for(size_t i = 0; i < other.size() - 1; ++i)
        {
            std::cout <<  other[i] << ", ";
        }
        std::cout << other[other.size() - 1] << "]";
    }

    else out << "";

    return out;
}

void extract_data(std::string &source, std::vector<std::string> &types, std::vector<int> &declaration_order)
{
	std::string::iterator current_char = source.begin();
	while(current_char != source.end())
	{
		if(*(current_char) == '<')
		{
			std::string type;
			std::string num;
			
			while(*(++current_char + 1) != '=' && current_char != source.end())
			{
				type.push_back(*(current_char));
			}

			while(*(++current_char) != '>' && current_char != source.end())
			{
				if(*(current_char) > '0' && *(current_char) <= '9') 
				{
					num.push_back(*current_char);
				}
			}

			declaration_order.push_back(std::stoi(num));

			type.erase(remove_if(type.begin(), type.end(), isspace), type.end());
			types.push_back(type);
		}
		current_char++;
	}
}

std::string format(std::string &source, const std::vector<std::any> &values)
{
	std::vector<std::string> types;
	std::vector<int> declaration_order;
	std::stringstream buffer_stream;

	extract_data(source, types, declaration_order);
	
	std::string::iterator current_char = source.begin();
	int index = 0;
	while(current_char != source.end())
	{
		if(*(current_char) == '<') { ;; }
		else 					   { buffer_stream << *(current_char); }

		if(*(current_char) == '<')
		{
			possible_types_variant temp = get_value(types[declaration_order[index] - 1], values[declaration_order[index] - 1]);
			index++;
			if(auto value = std::get_if<int>(&temp))
			{
				while(*(current_char) != '>') ++current_char;

				buffer_stream << *value;
			}

			else if(auto value = std::get_if<float>(&temp))
			{
				while(*(current_char) != '>') ++current_char;

				buffer_stream << *value;
			}

			else if(auto value = std::get_if<std::string>(&temp))
			{
				while(*(current_char) != '>') ++current_char;

				buffer_stream << *value;
			}
			
			else if(auto value = std::get_if<double>(&temp))
			{
				while(*(current_char) != '>') ++current_char;
				buffer_stream << *value;
			}
		}
		++current_char;
	}

	return buffer_stream.str();	
}

int main()
{
	int a = 3;
	int b = 4;
	std::string test_string = "a = <int := 1>, b = <int := 2>, my name is \"<string := 3>\" and the value of pi is <float := 4>";
	std::cout << format(test_string , {a, b, "Homer Simpson", 3.14f}) << std::endl;

	return EXIT_SUCCESS;
}

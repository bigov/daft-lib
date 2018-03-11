#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// read entire file into string
std::string get_file_content(const std::string & file_name)
{
	if(std::ifstream is{file_name, std::ios::binary | std::ios::ate})
	{
  	auto size = is.tellg();
		std::string str(size, '\0'); // construct string to stream size
		is.seekg(0);
		is.read(&str[0], size);
		return str;
	} else {
		throw std::runtime_error("Could not open " + file_name);
	}
}

int main()
{
	try
	{
		auto s = get_file_content("file_read.cpp");
		std::cout << s << '\n';
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}

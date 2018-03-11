#include <iostream>
#include <cstring>


int main()
{
	const char * tst = "qwerty1234";
	size_t m = strlen(tst);

	std::string message(tst, strlen(tst)); 

	std::cout << "size of tst = " << m << std::endl;
	std::cout << "tst = " << message << std::endl;

	return 0;
}

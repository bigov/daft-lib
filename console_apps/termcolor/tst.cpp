#include "termcolor.hpp"

int main()
{
	std::cout << termcolor::reset << termcolor::on_green << termcolor::bold
		<< termcolor::yellow << " Hi! " << termcolor::reset << "\n";
	return 0;
}

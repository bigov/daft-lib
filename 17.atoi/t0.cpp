#include <iostream>
#include <cstdlib>

/* Функция atio(const char*) переводит первое обнаруженное
 * в переданной С-строке число в значение целого. Пробельные
 * символы в начале строки не учитываются.
 */
int main(int argc, char* argv[])
{
	std::string k;
	k = " 51 7 a3, 4";

	int m;
	m = atoi(k.c_str());
	m *= 10;

	std::cout << "k: '" << k << "'"  << std::endl;
	std::cout << "m = " << m << std::endl;

	return 0;
}

//
// Тестирование побитовых операций
//
#include <iostream>

int main()
{
	unsigned char
		TN = 0,
		px = 1,
		nx = 2,
		py = 4,
		ny = 8,
		pz = 16,
		nz = 32;

	TN |= nx; // 2
	TN |= pz; // 16

	std::cout << std::endl << static_cast<short>(TN) << std::endl;
	return EXIT_SUCCESS;

}

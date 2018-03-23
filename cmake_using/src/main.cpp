#include <iostream>
#include <cstring>

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

using std::cout;
using std::endl;

int main()
{
	int l = 2;
	size_t l_size = sizeof(l);

	cout << "l_size = " << l_size << endl;
	cout << "pi="   <<  glm::pi<glm::float_t>() << endl;
	cout << "pi/2=" <<  glm::half_pi<glm::float_t>() << endl;

	return 0;
}


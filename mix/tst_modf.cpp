#include <iostream>
#include <cmath>

int main(int, char**)
{
  float m = -23.0000f;
  double k = 0.f;

  std::cout << (0 == modf(m, &k));

  return 0;
}



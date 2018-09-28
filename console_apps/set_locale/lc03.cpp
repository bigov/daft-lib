#include <iostream>
#include <ctime>
#include <iomanip>
#include <codecvt>

int main()
{
  std::cout << "loc: " << std::cin.getloc().name();

  return 0;
}

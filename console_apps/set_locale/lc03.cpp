#include <iostream>
#include <wchar.h>

int main()
{
  auto c = _getwch();
  std::wcout << "pressed '" << c << "'\n";

  return 0;
}

/*
 * MS-Windows поддерживает ввод символа при помощи функции _getwch();
 *
 * В *nix это решение не работает
 */

#include <iostream>
#include <wchar.h>

int main()
{
  auto c = _getwch();
  std::wcout << "pressed '" << c << "'\n";

  return 0;
}

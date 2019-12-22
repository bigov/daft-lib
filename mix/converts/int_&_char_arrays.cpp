/**
 * Пример обмена данными между целочисленными переменными и байтовым
 * массивом (может использоваться при передаче данных).
 *
 * Функция "char_hex_out" выводит данные байтового массива в HEX формате
 *
 */

#include <cstring>
#include <iostream>
#include<iomanip>
#include <vector>

size_t sizeof_int = sizeof(int);

void char_hex_out (const std::vector<char>& V, int n)
{
  // Так как std::hex работает только с целыми числами, то надо
  // скопировать данные из входного массива <char>V в промежуточный <int>Ints

  std::vector<int> Ints(V.size()/sizeof_int + 1); // +1 если поделилось с остатком
  memcpy(Ints.data(), V.data(), V.size());

  std::cout << "size of array: " << V.size() << "\n"
    << std::hex << std::uppercase;

  int max = Ints.size();
  if(max > n) max = n;

  for(int i = 0; i < max; i++) std::cout << std::setw(sizeof_int * 2)
    << std::setfill('0') << Ints[i] << " ";
  std::cout << std::endl;

  std::cout << std::dec << std::nouppercase;
}


int main(int, char**)
{
  std::cout << std::endl;

  std::vector<char> VData (sizeof_int);

  int a = -128;
  int b = 0;

  memcpy(VData.data(), &a, sizeof_int);
  VData.push_back(18);

  char_hex_out(VData, 10);

  memcpy(&b, VData.data(), sizeof_int);

  std::cout << "\n"
    << "int a: " << a << std::endl
    << "int b: " << b << std::endl
    << std::endl;

  return EXIT_SUCCESS;
}
/*
 * 1
 * 2
 * 4
 * 8
 * 16
 * 32
 * 64
 * 128
 *
 *
 */

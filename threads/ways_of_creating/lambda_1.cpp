//
// Создание потока при помощи лямбда-функции
//

#include <thread>
#include <iostream>

int main(int, char**)
{
  std::thread R1([] {
      std::cout << "\nThe ray of light\n";
  });
  R1.join();
  return EXIT_SUCCESS;
}

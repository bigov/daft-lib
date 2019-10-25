//
// Создание потока при помощи лямбда-замыкания, хранящего лямбда-выражение
//
#include <thread>
#include <iostream>

int main(int, char**)
{
  auto Lamp = [](std::string Color) -> void { std::cout << "\nThe ray of " + Color + " light\n"; };

  std::thread R1(Lamp, std::string {"red"} );
  R1.join();

  return EXIT_SUCCESS;
}

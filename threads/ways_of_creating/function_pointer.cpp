//
// Запуск в потоке через указатель на функцию
//

#include <thread>
#include <iostream>

void lamp()
{
  std::cout << "\nI see a ray of light\n";
}

int main(int, char**)
{
  std::thread R1(lamp);
  R1.join();
  return EXIT_SUCCESS;
}

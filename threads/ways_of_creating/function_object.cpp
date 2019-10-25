//
// Запуск в потоке с использованием функционального объекта
//

#include <thread>
#include <iostream>

class lamp
{
public:
  lamp(void) = default;
  void operator() () const
  {
    std::cout << "\nI see a ray of light\n";
  }
};

int main(int, char**)
{
  lamp MyLamp {};
  std::thread R1(MyLamp);
  R1.join();
  return EXIT_SUCCESS;
}

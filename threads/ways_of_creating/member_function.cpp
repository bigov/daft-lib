//
// Запускает в отдельном потоке метод класса
//
#include <thread>
#include <iostream>

int N = 24;

class lamp
{
public:
  lamp(void) = default;
  int candles = 0;
  void glow_on(void)
  {
    std::cout << "\nI see a ray of light\n";
    N *= 2;
    candles *= 10;
  }
};

int main(int, char**)
{
  lamp MyLamp {};
  MyLamp.candles = 12;
  std::thread R1(&lamp::glow_on, &MyLamp);
  R1.join();
  std::cout << "N = " << N <<  ", candles = " << MyLamp.candles << std::endl;
  return 0;
}

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::mutex F;

void func_a(std::string& S)
{
  //std::this_thread::sleep_for(std::chrono::milliseconds(20));
  std::lock_guard<std::mutex> Hasp {F}; // блокировка с RAII
  S += ", мой дорогой!\n";
}

int main(int, char**)
{
  std::string Txt = "\nПривет";
  std::thread T0(func_a, std::ref(Txt));
  std::this_thread::sleep_for(std::chrono::microseconds(1000));

  std::lock_guard<std::mutex> Hasp {F}; // блокировка с RAII
  std::cout << Txt;
  Hasp.~lock_guard();                   // ручная разблокировка

  if (T0.joinable())
  {
    T0.join();
  }

  return EXIT_SUCCESS;
}

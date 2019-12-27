//
// Демонстрация создания при помощи класса std::lock_guard блокировки с
// использованием парадигмы RAII - при выходе из области видимости объект
// Hasp0 будет автоматически разрушен с освобождением мьютекса F.
//
// В главной функции в момент вызова join() выполнение будет приостановлено до
// возврата из потока. Если при этом поток ожидает доступа к мьютексу F, то
// программа зависнет, если F перед этим не освободить (вручную).
//
// Кроме того, тут демонстрируется использование проверки .joinable(), чтобы
// убедиться в том, что поток не был ранее отсоединен через вызов detach(). Так
// как в этом случае вызов join() приведет к аварийному завершению работы.

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::mutex F;

void func_a(std::string& S)
{
  //std::this_thread::sleep_for(std::chrono::milliseconds(20));
  std::lock_guard<std::mutex> Hasp0 {F}; // блокировка с RAII
  S += ", мой дорогой!\n";
}

int main(int, char**)
{
  std::string Txt = "\nПривет";
  std::thread T0(func_a, std::ref(Txt));
  std::this_thread::sleep_for(std::chrono::microseconds(1000));

  std::lock_guard<std::mutex> Hasp1 {F}; // блокировка с RAII
  std::cout << Txt;
  Hasp1.~lock_guard();                   // ручная разблокировка

  if (T0.joinable())
  {
    T0.join();
  }

  return EXIT_SUCCESS;
}

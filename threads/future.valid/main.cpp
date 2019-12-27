//
// Пример вызова async и проверки с помощью вызова myFuture.valid())
// того, что результат еще не считывался
//
// Кроме того: если асинхронная операция может выбросить исключение, то
// необходимо всегда оборачивать вызов std::future::get() в try/catch блок,
// потому что исключение, выброшенное в асинхронной операции прокидывается
// только тогда, когда происходит вызов метода get() у std::future объекта.
// И если метод get() вызван не будет, то исключение будет проигнорировано и
// отброшено, когда std::future объект выйдет из области видимости.

#include <future>
#include <iostream>

int main()
{
  std::future<int> myFuture = std::async(std::launch::async, []()
  {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    throw std::runtime_error("исключение в блоке лямбды");
    return 8;
  });

  std::cout << "Data process..." << std::endl;

  int val = 0;
  if(myFuture.valid())
  {
    try
    {
      val = myFuture.get();
      std::cout << "val = " << val  << std::endl;
    }
    catch (std::exception& e)
    {
      std::cout << "EXCEPTION: " << e.what() << std::endl;
    }

  }

  if(!myFuture.valid()) std::cout << "\nданные сброшены" << std::endl;
  return EXIT_SUCCESS;
}

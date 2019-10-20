//
// Техника передачи исключения в главную функцию из потока при помощи
// статической глобальной переменной типа std::exception_ptr
//

#include <iostream>
#include <thread>

static std::exception_ptr globExceptionPtr = nullptr;


// call as thread
//
void func_a(void)
{
  try
  {
    //std::this_thread::sleep_for(std::chrono::microseconds(1));
    throw std::runtime_error("ERR IN THE THREAD");
  } catch(...)
  {
    globExceptionPtr = std::current_exception();
  }
}


// Enter point
//
int main(int, char**)
{
  std::cout << "start...\n\n";

  std::thread T0(func_a);
  std::this_thread::sleep_for(std::chrono::milliseconds(2));

  if(nullptr != globExceptionPtr) try
  {
    std::rethrow_exception(globExceptionPtr);
  } catch (const std::exception& ex)
  {
    std::cout << "Перехвачено: " << ex.what() << '\n';
  }

  if (T0.joinable())
  {
    T0.join();
  }

  return EXIT_SUCCESS;
}

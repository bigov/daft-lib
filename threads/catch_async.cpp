#include <thread>
#include <future>
#include <exception>
#include <iostream>

int main()
{
  auto first = std::async([]()
  {
    throw std::bad_alloc();
  });

  auto second = std::async([]()
  {
    throw std::bad_alloc();
  });

  try
  {
    first.get();
    std::cout << "first ended\n";
  } catch(std::exception&)
  {
    std::cout << "catch exception from the first\n";
  }

  second.wait();
  std::cout << "second has been ended\n";

  return 0;
}


#include <iostream>
#include <thread>
#include <atomic>

std::atomic_int v = {30};

void v_add_2(void)
{
  v += 2;
  return;
}

void v_add_1(void)
{
  v++;
  return;
}

int main()
{
  std::thread thr2(v_add_2);
  std::thread thr1(v_add_1);

  std::cout << "\nv.load() = "<< v.load() << "\n";

  thr1.join();
  thr2.join();
  return 0;
}


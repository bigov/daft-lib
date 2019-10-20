#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

int main ()
{
  std::atomic_long v = {10};
  long m = 200;
  v.fetch_add(m);
  long res = v.load();
  std::cout << "v is lock free = " << v.is_lock_free() << "\n";
  std::cout << "v = " << res << "\n";
  return 0;
}


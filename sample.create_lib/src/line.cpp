#include <iostream>

namespace tst {

  //## просто перевод строки
  void print_blank(void)
  {
    std::cout << "\n";
    return;
  }

  //## печать линии из i символов, заданных вторым параметром
  void print_line(int i, char c)
  {
    if( i < 1 ) return;
    while(i--) std::cout << c;
    std::cout << "\n";
    return;
  }

} // namespace tst

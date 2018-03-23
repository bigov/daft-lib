#include "main.hpp"

int main() {

  const char text[] = "Testing compiling of libs\n";
  tst::print_blank();
  tst::print_line(78, '-');
  tst::print_row(text);
  tst::print_line(78, '-');

  return 0;
}

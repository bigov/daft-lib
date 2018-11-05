/*
 * Окно приветствия на основе библиотеки nana.
 *
 * От использования данной библиотеки я отказался, так как текущая версия
 * не собирается как динамическая библиотека. А статическая сборка приложения
 * из десяти строк выдает на выходе бинарник размером 42 мегабайта.
 *
 */
#include <nana/gui.hpp>
//Include a label widget, we will use it in this example.
#include <nana/gui/widgets/label.hpp>

int main(int, char**)
{
  nana::form fm  { };
  nana::label lb { fm, nana::rectangle{ 10, 10, 100, 100 } };
  lb.caption("Hello, from Nana!");

  fm.show();
  nana::exec();

  return 0;
}

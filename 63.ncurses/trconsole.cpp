//#include <iostream>
#include <ncursesw/cursesapp.h>

int main()
{
  NCursesWindow myWin = {};
  //initscr(); // инициализация ncurses

  // создаем три окна:
  // 1. Высотой 1 строка - индикатор состояния подключения/сервиса
  // 2. Все остальное пространство - журнал событий
  // 3. Высотой 1 строка - для ввода команд
  //WINDOW *

  //DEBUG
  getch();

  endwin(); // освободить память ncurses
  return 0; //EXIT_SUCCESS;
}

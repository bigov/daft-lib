#if defined(_WIN32)
//#include <ncursesw/panel.h>
#include <ncursesw/ncurses.h>
#else
//#include <panel.h>
#include <ncurses.h>
#endif

enum SCREEN_AREAS {
  AREA_STATUS,
  AREA_INFORM,
  AREA_COMMAND,
  COUNT_OF_AREAS
};

//## Создание прямоугольной области с заданными параметрами
WINDOW * create_window(int, int, int, int);

//## Точка входа
int main()
{
  initscr(); // инициализация ncurses
  if(!has_colors()) {
    endwin();
    printf("Your terminal does not support color\n");
    return 0;
  }
  start_color();
  use_default_colors();

  cbreak();  // Line buffering disabled, Pass on everty thing to me
  keypad(stdscr, TRUE); // возможность использовать функциональные кл.
  noecho();
  curs_set(0);          // спрятать курсор

  int console_width,                        // ширина консольного окна
      console_height;                        // высота консольного окна
  getmaxyx(stdscr,  console_height, console_width); // получить значения

  // создаем три окна:
  // 1. Высотой 1 строка - индикатор состояния подключения/сервиса
  // 2. Все остальное пространство - журнал событий
  // 3. Высотой 1 строка - для ввода команд

  WINDOW * win[COUNT_OF_AREAS];
  int height, width, top, left;

  height = 3; width = console_width; top = 0; left = 0;
  WINDOW *win_AREA_STATUS = create_window(height, width, top, left);
  mvwprintw( win_AREA_STATUS, 1, 2, "%s", "SERVER STATUS: ");
  wrefresh( win_AREA_STATUS );

  height = console_height - 6;
  top = 3;
  win[AREA_INFORM] = create_window(height, width, top, left);
  mvwprintw( win[AREA_INFORM], 1, 2, "%s", "STATUS_AREA");
  wrefresh(win[AREA_INFORM]);

  height = 3;
  top = console_height - 3;
  win[AREA_COMMAND] = create_window(height, width, top, left);
  mvwprintw( win[AREA_COMMAND], 1, 2, "%s", "command: ");
  wrefresh(win[AREA_COMMAND]);

  //refresh();
  //doupdate();

  //DEBUG
  getch();

  endwin(); // освободить память ncurses
  return 0; //EXIT_SUCCESS;
}

//## Создание прямоугольной области с заданными параметрами
WINDOW * create_window(int height, int width, int starty, int startx)
{
  WINDOW * win = newwin( height, width, starty, startx);
  //new_panel(win);
  box(win, 0, 0);
  wrefresh(win);
  //update_panels();
  return win;
}

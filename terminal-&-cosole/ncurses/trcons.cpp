#if defined(_WIN32)
#include <ncursesw/panel.h>
#else
#include <panel.h>
#endif

enum SCREEN_AREAS {
  STATUS_AREA,
  INFORM_AREA,
  CONTROL_AREA,
  COUNT_OF_AREAS
};

WINDOW * make_area(int h, int w, int y, int x);

int main()
{

  initscr(); // инициализация ncurses
  cbreak();                       /* Line buffering disabled, Pass on
                                   * everty thing to me           */
  keypad(stdscr, TRUE);           /* I need that nifty F1         */
  noecho();
  curs_set(0);    // спрятать курсор

  int cons_w, cons_h;
  getmaxyx(stdscr,  cons_h, cons_w);

  // создаем три окна:
  // 1. Высотой 1 строка - индикатор состояния подключения/сервиса
  // 2. Все остальное пространство - журнал событий
  // 3. Высотой 1 строка - для ввода команд

  WINDOW * windows[COUNT_OF_AREAS];

  windows[STATUS_AREA] = make_area(3, cons_w, 0, 0);
  mvwprintw( windows[STATUS_AREA], 1, 2, "%s", "SERVER STATUS: ");
  wrefresh(windows[STATUS_AREA]);

  refresh();
  doupdate();

  //DEBUG
  getch();

  endwin(); // освободить память ncurses
  return 0; //EXIT_SUCCESS;
}

WINDOW * make_area(int h, int w, int y, int x)
{
  WINDOW * win = newwin(h, w, y, x);
  new_panel(win);
  box(win, 0, 0);
  wrefresh(win);
  update_panels();
  return win;
}

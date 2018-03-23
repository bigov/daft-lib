#include <ctime>

#if defined(_WIN32)
  #include <ncursesw/ncurses.h>
#else
  #include <ncurses.h>
#endif

const int time_buf_size = 20;
char time_buf_format[] = "%Y-%m-%d %R:%S";

//## Записывает отметку времени в виде строки в буфер
void get_time_string(char * buffer)
{
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime(buffer, time_buf_size, time_buf_format, timeinfo);
  return;
}

//## Точка входа
int main()
{
  char time_row [time_buf_size];
  get_time_string(time_row);

  initscr(); // инициализация ncurses
  cbreak();  // Line buffering disabled, Pass on everty thing to me
  keypad(stdscr, TRUE); // возможность использовать функциональные кл.
  //noecho();
  refresh();

  // получить размеры консольного окна
  int console_width, console_height;
  getmaxyx(stdscr, console_height, console_width);

  WINDOW * winLog = newwin( console_height - 4, console_width, 0, 0);
  scrollok( winLog, TRUE);
  wbkgd( winLog, A_REVERSE);

  wprintw( winLog, time_row);
  wprintw( winLog, "  Start server\n");
  wrefresh( winLog );

  mvwprintw( stdscr, console_height - 4, console_width - 20,
             "%s", "server status: RUN");
  refresh();

  wprintw( winLog, time_row);
  wprintw( winLog, "  Server now runing\n");
  wrefresh( winLog );

  mvwprintw( stdscr, console_height - 2, 2, "%s", "command: ");
  refresh();

  //DEBUG
  getch();

  endwin(); // освободить память ncurses
  return 0; //EXIT_SUCCESS;
}

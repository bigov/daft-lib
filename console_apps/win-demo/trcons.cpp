#include <ncurses.h>

//## Создание прямоугольной области с заданными параметрами
WINDOW * create_window(int, int, int, int);

//## Точка входа
int main()
{
  initscr(); // инициализация ncurses
  if(!has_colors())
  {
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }

  //start_color();
  //use_default_colors();
  //init_pair(1, COLOR_BLUE, COLOR_GREEN);

  cbreak();  // Line buffering disabled, Pass on everty thing to me
  keypad(stdscr, TRUE); // возможность использовать функциональные кл.
  noecho();
  curs_set(0);          // спрятать курсор
  refresh();

  int console_width;                               // ширина консольного окна
  int console_height;                              // высота консольного окна
  getmaxyx(stdscr, console_height, console_width); // получить значения

  int height, width, top, left;

  height = 3;
  width = console_width;
  top = 0;
  left = 0;

  WINDOW * win_AREA_STATUS = create_window(height, width, top, left);
  wbkgd(win_AREA_STATUS, A_REVERSE);
  wborder(win_AREA_STATUS, ' ', ' ', '-',' ',' ',' ',' ',' ');
  mvwprintw( win_AREA_STATUS, 0, width - 18, "%s", " SERVER STATUS ");
  wrefresh( win_AREA_STATUS );
  refresh();

  //DEBUG
  getch();

  endwin(); // освободить память ncurses
  return 0; //EXIT_SUCCESS;
}

//## Создание прямоугольной области с заданными параметрами
WINDOW * create_window(int height, int width, int starty, int startx)
{
  WINDOW * win = newwin( height, width, starty, startx );
  //box(win, 0, 0);
  wrefresh(win);
  return win;
}

#include <ncurses.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(int argc, char *argv[])
{
  initscr();
  if(has_colors() == FALSE)
  {  endwin();
    printf("Your terminal does not support color\n");
    return(1);
  }

  start_color();
  init_pair(1, COLOR_BLUE, COLOR_WHITE);

  attron(COLOR_PAIR(1));
  mvwprintw(stdscr, 2, 2, "%s", "colored string");
  refresh();
  attroff(COLOR_PAIR(1));
  
  getch();
  endwin();
}


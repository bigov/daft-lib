/*
 * Based on sample from
 * 
 *    http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
 *
 */
#include <ncurses.h>

WINDOW *create_newwin(int, int, int, int);
void destroy_win(WINDOW*);

//## ENTER
int main(int argc, char *argv[])
{
  initscr();    // Start curses mode
  if(!has_colors())
  {
    endwin();
    printf("Your terminal does not support color\n");
    return(0);
  }

  WINDOW *my_win;
  int startx, starty, width, height;
  int ch;

  start_color();
  use_default_colors();
  init_pair(1, COLOR_BLUE, COLOR_GREEN);
  
  cbreak();      // Line buffering disabled, Pass on everty thing to me     */
  keypad(stdscr, TRUE);    // I need that nifty F1
  noecho();
  curs_set(0);          // спрятать курсор

  height = 3;
  width = 10;
  starty = (LINES - height) / 2;  /* Calculating for a center placement */
  startx = (COLS - width) / 2;  /* of the window    */
  printw("Press F10 to exit");
  refresh();

  WINDOW *win_stat = create_newwin(12, 24, 4, 4);
  wbkgd(win_stat, A_REVERSE);
  wrefresh(win_stat);  // Show that
  scrollok(win_stat, TRUE);
  //refresh();

//  my_win = create_newwin(height, width, starty, startx);

  while((ch = getch()) != KEY_F(10))
  {
/*    switch(ch)
    {  case KEY_LEFT:
        --startx;
        break;
      case KEY_RIGHT:
        ++startx;
        break;
      case KEY_UP:
        --starty;
        break;
      case KEY_DOWN:
        ++starty;
        break;
    }
      destroy_win(my_win);
      my_win = create_newwin(height, width, starty, startx);
      wbkgd(my_win, COLOR_PAIR(1));
*/
      wprintw(win_stat, "%s", " moved \n");
      wrefresh(win_stat);

  }
  destroy_win(win_stat);
  endwin();
  return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{  
  WINDOW *local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);
  wrefresh(local_win);
  return local_win;
}

void destroy_win(WINDOW *local_win)
{  
  /* box(local_win, ' ', ' '); : This won't produce the desired
   * result of erasing the window. It will leave it's four corners 
   * and so an ugly remnant of window. 
   */
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  /* The parameters taken are 
   * 1. win: the window on which to operate
   * 2. ls: character to be used for the left side of the window 
   * 3. rs: character to be used for the right side of the window 
   * 4. ts: character to be used for the top side of the window 
   * 5. bs: character to be used for the bottom side of the window 
   * 6. tl: character to be used for the top left corner of the window 
   * 7. tr: character to be used for the top right corner of the window 
   * 8. bl: character to be used for the bottom left corner of the window 
   * 9. br: character to be used for the bottom right corner of the window
   */
  wrefresh(local_win);
  delwin(local_win);
}


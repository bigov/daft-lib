#include <stdio.h>
#include <ncurses/ncurses.h>

int tty_break()
{
  initscr();
  cbreak();
  return 0;
}
 
int tty_getchar()
{
  return getch();
}
 
int tty_fix()
{
  endwin();
  return 0;
}

int main()
{
  int i;
  if(tty_break() != 0)
    return 1;
  for(i = 0; i < 10; i++)
    printf(" = %d\n", tty_getchar());
  tty_fix();
  return 0;
}


//
// Опрос клавиш в ncurses.
//
// gcc keys.c -lncursesw -o keys
//
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

int main()
{
  setlocale(LC_CTYPE, "");
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  int c = getch();
  endwin();
  printf("Keycode: %d\n", c);
  return 0;
}


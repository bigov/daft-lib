/*
 программа, которая выводит «Здравствуй, мир!» в ncurses с локалью ru_RU.UTF-8.

Собирается командой
g++ ./n.cpp -Wall -lncursesw -o ./n.elf && ./n.elf
*/

#define _XOPEN_SOURCE_EXTENDED
#if ENABLE_NLS != 1
  #undef ENABLE_NLS
  #define ENABLE_NLS 1
#endif
#define _GNU_SOURCE

#include <ncursesw/ncurses.h>

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// i18n support
#include <locale.h>
#include <libintl.h>
#define _(msg) gettext(msg)
#define N_(msg) msg

#define global
#define use_global extern

enum {AK_CONTIN, AK_EXIT, AK_EXITNOW};

void init_curses(void);
void deinit_ncurses(void);
void curs_anykey(int beh);
void any_key(int beh);

global char * gp_progfname = (char *)"n"; // program filename
global bool g_ncurses_inited = false; // for correct cleanup on fatal errors

//----------------------------------------------------------------------------

int main (int argc, char **argv) {

  setlocale(LC_ALL, "");

  init_curses();

  printw("Здравствуй, мир!\n");
  curs_anykey(AK_CONTIN);

  deinit_ncurses();
  return 0;

} // end function main

//----------------------------------------------------------------------------

void init_curses(void) {

  use_global char * gp_progfname;
  use_global bool g_ncurses_inited;

  if (initscr() == NULL) { // Start curses mode
    fprintf(stderr,
      _("%s: error: can't initialize ncurses (pseudographics low-level engine)\n"),
      gp_progfname
    );
    any_key(AK_EXIT);
    exit(1);
  }
  g_ncurses_inited = true;

  if (cbreak() == ERR) {  // determine that line buffering (and some other stuff) is disabled
    fprintf(stderr, _("%s: warning: can't disable line buffering\n"), gp_progfname);
    curs_anykey(AK_CONTIN);
  }

  if (noecho() == ERR) {  // symbols that user type will not be echoed on the screen
    fprintf(stderr, _("%s: warning: can't disable input symbols echoing\n"), gp_progfname);
    curs_anykey(AK_CONTIN);
  }

  if (start_color() == ERR) {
    fprintf(stderr, _("%s: warning: can't enable color mode\n"), gp_progfname);
    curs_anykey(AK_CONTIN);
  }

  if(curs_set(0) == ERR) {
    fprintf(stderr, _("%s: warning: can't hide cursor\n"), gp_progfname);
    curs_anykey(AK_CONTIN);
  }

} // end func init_curses;

//----------------------------------------------------------------------------

void curs_anykey(int beh) {

  // Эта функция выводит приглашение нажать любую клавишу
  // и ожидает её нажатия.
  //
  // Вход:
  //   beh:
  //     AK_CONTIN - продолжить работу после нажатия клавиши
  //     AK_EXITNOW - вызвать функцию exit(1) после нажатия клавиши
  //
  // Должны быть включены режимы cbreak и noecho.

  wint_t wint;

  if (beh != AK_EXITNOW) {
    printw(_("Press any key to continue...\n"));
    refresh();
    get_wch(&wint);
  } else {
    printw(_("Press any key to exit...\n"));
    refresh();
    get_wch(&wint);
    // endwin();  // End curses mode.
    // curses mode will be stopped with atexit()-registered final_cleanup()
    exit(1);
  }

} // end func curs_anykey;

//----------------------------------------------------------------------------

void any_key(int beh) {
  printf(_("(wait for any key was not made yet)\n"));
  fflush(stdout);
} // end func any_key;

//----------------------------------------------------------------------------

void deinit_ncurses(void) {

  use_global bool g_ncurses_inited;

  if (g_ncurses_inited == true) endwin();

}


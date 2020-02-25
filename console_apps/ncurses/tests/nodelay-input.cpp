/*
 * Пример неблокирующего ожидания ввода с клавиатуры
 * при помощи библиотеки ncurces
 *
 * Дополнительно: реализован корректный вывод кириллицы в консоли с любой
 * кодировкой - 866,1251, 65001 (UTF-8)
 *
 * Компилируется в GCC:
 *
 *    gcc -Wall man.cpp -lncurses
 *
 * Документация по ncurses в примерах: http://www.c-for-dummies.com/ncurses/
 *
 * */

#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses/ncurses.h>
#include <cwchar>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE,"ru_RU.UTF-8");
    wchar_t line[] = L"Привет из библиотеки \"ncrurses\"!\n\n";

    initscr();    // Initialize Ncurses
    addwstr(line);
    refresh();

    addstr("Press any key to begin:\n");
    refresh();
    getch();              // ожидание готовности

    nodelay(stdscr,TRUE); // отключить ожидание ввода в getch()
    addstr("Press any key to stop the loop!\n");
    int value = 0;
    while(getch() == ERR)
    {
        printw("%d\r",value++);
        refresh();
    }

    endwin(); // close Ncurses
    return 0;
}

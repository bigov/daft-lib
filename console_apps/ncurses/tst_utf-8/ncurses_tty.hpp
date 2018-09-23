/* File: ncurses_tty.hpp
 *
 * Модуль отображения информации в консоли и ввода данных с клавиатуры
 * на основе библиотеки ncurses
 *
 */
#ifndef NCURSES_TTY_HPP
#define NCURSES_TTY_HPP

#include <vector>
#include <string>
#include <ctime>

//#define _XOPEN_SOURCE_EXTENDED 1
#define _XOPEN_SOURCE_EXTENDED
#if ENABLE_NLS != 1
  #undef ENABLE_NLS
  #define ENABLE_NLS 1
#endif
#define _GNU_SOURCE

#if defined(_WIN32)
  #include <ncursesw/ncurses.h>
  #include <ncursesw/cursesw.h>
   #define KEY_BACKSPACE_tr KEY_BACKSPACE
#else
  #include <ncursesw.h>
  #define KEY_BACKSPACE_tr 127    // Linux
#endif

#include <locale.h> // setlocale()
#include <unistd.h> // sleep()
#include <wchar.h>

//extern NCURSES_EXPORT(int) waddwstr (WINDOW *,const wchar_t *);

namespace tr {

const char cmd_help_msg[] = "\nHELP:\n"
      "Command with prefix \":\" will be transferred to the server;\n"
      "Command without prefix will be executed locally;\n\n";
const wchar_t cmd_exit[] = L"exit";

// Записывает в строковый буфер отметку времени
// extern void get_time_string(char * buffer);

//## Управление вводом команд и отображением информации
class console
{
  public:
    console(void);
    ~console(void);
    static bool add(int);          // добавить символ в строку команды
    static int cursor_x(void);     // получить позицию курсора в строке ввода
    static const wchar_t *check_keyboard(void);  // опрос клавиатуры
    static void display_message(const wchar_t*); // вывод сообщения
    static std::vector<std::wstring> hist;     // история команд
    static std::wstring CmdRow;                // строка ввода команды

  private:
    static void arch(void);            // сохранить введенную команду
    int console_width = 0;
    int console_height = 0; // размеры терминального окна
    static int cmd_pos_y, cmd_pos_x;   // положение начала строки ввода
    static size_t cursor;              // позиция курсора в строке
    static WINDOW * winLog;            // окно ncurses
    static size_t hist_ptr;            // индекс команды в истории
};     // class console
}      // namespace tr
#endif // NCURSES_TTY_HPP

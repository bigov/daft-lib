/*
 * Заголовок тестовой библиотеки
 *
 *  Библиотека состоит из двух файлов с исходным кодом
 */

#ifndef __TST_HPP__

namespace tst {

//## файл line.cpp
extern void print_blank(void); // просто перевод строки
extern void print_line(int length, char symbol);  // печать линии символов

//## файл row.cpp
extern void print_row(const char * string);   // вывод текстовой строки

} // namespace tst


#define __TST_HPP__
#endif //__FUNC_HPP__

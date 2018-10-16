/*
 * POSIX signals
 *
 * SIGTERM  Запрос завершения программы, отправляется программе
 * SIGSEGV  Некорректное обращение к памяти (ошибка сегментации)
 * SIGINT   Внешнее прерывание, обычно вызывается пользователем
 * SIGILL   Неправильный образ программы, например некорректная инструкция
 * SIGABRT  Аварийное завершение программы, например вызванное вызовом std::abort()
 * SIGFPE   Ошибочная арифметическая операция, например деление на ноль
 */
#include <csignal>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std::chrono_literals;

sig_atomic_t sig = 0;

void sig_pass(int s)
{
  sig = s;
  return;
}

int main( int, char** )
{

  // Установка обработчика сигнала
  std::signal(SIGTERM, sig_pass);
  std::signal(SIGSEGV, sig_pass);
  std::signal(SIGINT,  sig_pass);
  std::signal(SIGILL,  sig_pass);
  std::signal(SIGABRT, sig_pass);
  std::signal(SIGFPE,  sig_pass);

/* MS-Windows specific
 *
  std::signal(SIGBREAK, sig_pass);
  std::signal(WM_CLOSE, sig_pass);
  std::signal(WM_QUIT, sig_pass);
  std::signal(WM_DESTROY, sig_pass);
 *
 */

  std::cout << "SIGTERM = " << SIGTERM << "\n";
  std::cout << "SIGSEGV = " << SIGSEGV << "\n";
  std::cout << "SIGINT  = " << SIGINT  << "\n";
  std::cout << "SIGILL  = " << SIGILL  << "\n";
  std::cout << "SIGABRT = " << SIGABRT << "\n";
  std::cout << "SIGFPE  = " << SIGFPE  << "\n";

  while(0 == sig) std::this_thread::sleep_for(50ms);

  std::cout << "Recived signal = " << sig << "\n";
  char c;
  std::cin >> c;
  std::exit(EXIT_SUCCESS);
}


#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std::chrono_literals;

#ifdef _WIN32_WINNT
#include <conio.h>
#else
/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <sys/ioctl.h>

int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
#endif

std::string line;
std::atomic<int> timeout = {0}; // Управление паузой
std::atomic<bool> expect_cmd = {false}; // Управление циклом ввода

// прием команд с клавиатуры
void listen_input(void)
{
  while(expect_cmd)
  {
    line.clear();                 // Очистить переменную для приема команд
    while( kbhit() == 0 )         // Подождать начала ввода с клавиатуры
    {
      if(!expect_cmd) return;
      std::this_thread::sleep_for(50ms);
    }
    timeout.store(50);            // Установить продолжительность паузы
    std::getline(std::cin, line); // Записать строку/команду
    timeout.store(0);          // Сбросить флажок ввода
    std::cout << "Command: " << line << "\n";
  }
  return;
}

int main()
{
  expect_cmd.store(true);
  std::thread th_input(listen_input); // включить прием команд

  int i = 20;
  bool task_on = true;

  while(task_on) {
    std::this_thread::sleep_for(1s);
    while(timeout.operator--() > 0) std::this_thread::sleep_for(1s);
    std::cout << i << ": sample string message every 1 sec.\n";
    if(--i < 0) task_on = false;
  }

  expect_cmd.store(false);
  th_input.join();

  return 0;
}


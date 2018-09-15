#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std::chrono_literals;

std::string line;
std::atomic<int> timeout = {0};  // Управление паузой
std::atomic<bool> run = {false};

// прием команд с клавиатуры
void listen_input(void)
{
  while(run)
  {
    line.clear();                 // Очистить переменную для приема команд
    char c;
    std::cin >> c;
    timeout.store(50);            // Установить продолжительность паузы
    std::getline(std::cin, line); // Записать строку/команду
    timeout.store(0);          // Сбросить флажок ввода
    std::cout << "Command: " << line << "\n";
  }
  return;
}

int main()
{
  run.store(true);
  std::thread th_input(listen_input); // включить прием команд

  int i = 20;

  while(run) {
    std::this_thread::sleep_for(1s);
    while(timeout.operator--() > 0) std::this_thread::sleep_for(1s);
    std::cout << i << ": sample string message every 1 sec.\n";
    if(--i < 0) run.store(false);
  }

  th_input.join();

  return 0;
}


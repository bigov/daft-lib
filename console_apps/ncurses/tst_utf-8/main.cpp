#include "ncurses_tty.hpp"

int main()
{
  tr::console Tty = {};
  const wchar_t *cmd = nullptr;
  const wchar_t *exit = L"exit";

  Tty.display_message(L"Кодировка UTF-8");
  bool run = true;
  while(run)
  {
    cmd = Tty.check_keyboard();
    if (nullptr != cmd)
    {
      Tty.display_message(cmd);
      if (std::wstring{cmd} == std::wstring{exit}) run = false;
    }
  }
  return 0;
}

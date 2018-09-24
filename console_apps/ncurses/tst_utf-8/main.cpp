#include "ncurses_tty.hpp"
#include <cwchar>

int main()
{
  tr::console Tty = {};
  const wchar_t *cmd = nullptr;
  const wchar_t exit[] = L"exit";

  Tty.display_message(L"Кодировка UTF-8");
  bool run = true;
  while(run)
  {
    cmd = Tty.check_keyboard();
    if (nullptr != cmd)
    {
      if (0 == wcscmp(cmd, exit)) run = false;
      Tty.display_message(cmd);
    }
  }
  return 0;
}

#include "ncurses_tty.hpp"

namespace tr {

const int time_buf_size = 20;
static const size_t cmd_max_size = 128; // ограничение команды по длине

///
/// Записывает в строковый буфер отметку времени
///
void get_time_string(char * buffer)
{
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime(buffer, time_buf_size, "%Y-%m-%d %H:%M:%S", timeinfo);
  return;
}

///
/// инициализация статических членов
///
int console::cmd_pos_y   = 0;
int  console::cmd_pos_x  = 0;       // положение начала строки ввода
size_t console::cursor   = 0;       // позиция курсора в строке
WINDOW * console::winLog = nullptr; // окно ncurses
size_t console::hist_ptr = 0;                  // индекс команды в истории
std::vector<std::wstring> console::hist = {};   // история команд
std::wstring console::CmdRow = {};              // строка ввода команды
wint_t console::input_wch[] = { L'0' };

///
///  инициализация класса
///
console::console(void)
{
  //setlocale(LC_CTYPE, "ru_RU.UTF-8");
  setlocale(LC_ALL, "");
  //signal(SIGINT, sig);
  initscr(); // инициализация ncurses

  // getmaxyx( stdscr, console_height, console_width );
  //
  // В функции getmaxyx(), которая передает размер консоли, анализатор находит
  // ошибку "zero as null pointer constant". Поэтому решено воспользоваться
  // встроенными константами количества строк и колонок терминала:
  //
  console_height = LINES;
  console_width = COLS;

  cbreak();  // Line buffering disabled, Pass on everty thing to me
  keypad(stdscr, TRUE); // возможность использовать функциональные кл.
  nodelay(stdscr,TRUE); // turn off getch() wait
  noecho();
  wbkgd( stdscr, A_REVERSE );
  addstr(" Exit: F10");
  refresh();

  // Позиция строки ввода команд
  cmd_pos_x = 1;
  cmd_pos_y = console_height - 2;

  // Построить окно вывода сообщений
  WINDOW * frame = newwin( console_height - 4, console_width - 2, 1, 1 );
  wrefresh( frame );

  winLog = newwin( console_height - 5, console_width - 4, 2, 2 );
  scrollok( winLog, TRUE );
  wrefresh( winLog );
  //------------------- /инициализация ---<

  CmdRow.clear();
  cursor = CmdRow.size();

  // ?
  wmove(stdscr, cmd_pos_y, cmd_pos_x);

  return;
}

console::~console(void)
{
  endwin(); // освободить память ncurses
  return;
}

///
/// вывод сообщения в терминальное окно
///
void console::display_message(const wchar_t *buf)
{
   waddwstr( winLog, buf );
   waddwstr( winLog, L"\n" );
   wrefresh( winLog );
   wmove(stdscr, cmd_pos_y, cmd_pos_x + cursor_x());
   return;
}

///
/// Опрос клавиатуры
///
const wchar_t *console::check_keyboard(void)
{
  //int key = getch();
  wget_wch(stdscr, input_wch);
  int key = *input_wch;

  switch (key)
  {
    case -1: case 0:
      return nullptr;
    case KEY_F(10):
      return cmd_exit;
    default:
      if( add(key) )
        return hist.back().c_str();
      else
        mvwaddwstr (stdscr, cmd_pos_y, cmd_pos_x, CmdRow.c_str());
        clrtoeol();
        wmove(stdscr, cmd_pos_y, cmd_pos_x + cursor_x());
        return nullptr;
  }
}

///
/// управление буфером команд
///
bool console::add(int key)
{
  if((key == '\n') || (key == '\r'))
  {
    if(CmdRow.empty()) return false;
    arch();                              // сохранить команду
    wmove(stdscr, cmd_pos_y, cmd_pos_x); // переустановить курсор
    clrtoeol();                          // очистить строку команд
    return true;
  }
  else if(key == KEY_HOME)
  {
    cursor = 0;
  }
  else if(key == KEY_END)
  {
    cursor = CmdRow.size();
  }
  else if(key == KEY_LEFT)
  {
    if(cursor > 0) cursor -= 1;
  }
  else if(key == KEY_RIGHT)
  {
    if(cursor < CmdRow.size()) cursor += 1;
  }
  else if(key == KEY_UP)
  {
    if(hist_ptr == 0) return false;
    hist_ptr -= 1;
    CmdRow = hist[hist_ptr];
    cursor = CmdRow.size();
  }
  else if(key == KEY_DOWN)
  {
    if(hist.empty()) return false;
    if(hist_ptr >= (hist.size()-1)) return false;
    hist_ptr += 1;
    CmdRow = hist[hist_ptr];
    cursor = CmdRow.size();
  }
  else if( (key == KEY_BACKSPACE_tr)    ||
           (key == '\b') )
  {
    if(cursor > 0)
    {
      CmdRow.erase(CmdRow.begin() + static_cast<long>(cursor)-1,
                   CmdRow.begin() + static_cast<long>(cursor) );
      cursor -= 1;
    }
  }
  else if(key == KEY_DC)
  {
    if(CmdRow.size() > cursor )
    {
      CmdRow.erase(CmdRow.begin() + static_cast<long>(cursor),
                   CmdRow.begin() + static_cast<long>(cursor) + 1);
    }
  }
  else if( ( static_cast<unsigned int>(key) < WCHAR_MAX )
        && ( CmdRow.size() < cmd_max_size) )
  {
    // Для приема двухбайтного символа "input_wch" надо вначале вернуть
    // в кэш принятый перед этим из буфера байт "key"
    unget_wch(static_cast<wchar_t>(key));
    get_wch(input_wch);
    CmdRow.insert(CmdRow.begin() + static_cast<long>(cursor),
                    static_cast<wchar_t>(*input_wch));
    cursor += 1;
  }
  return false;
}

///
/// передает позицию курсора в строке ввода
///
int console::cursor_x(void)
{
  return static_cast<int>(cursor);
}

///
/// Запись введенной команды в кэш истории
///
void console::arch(void)
{
  hist.push_back(CmdRow);
  hist_ptr = hist.size();
  CmdRow.clear();
  cursor = CmdRow.size();
  return;
}

} // tr

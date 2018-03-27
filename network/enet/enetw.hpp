//
// Обертка к библиотеке enet
//
/*

// Структура данных
event.packet->dataLength // длина пакета
event.packet->data       // данные
event.peer->data         // информация, установленая в пире
event.channelID          // по какому каналу

*/

#ifndef __ENETW_HPP__
#define __ENETW_HPP__

#include <cwctype>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <map>
#include <vector>
#include <list>

#include <enet/enet.h>

#if defined(_WIN32)
  #include <ncursesw/ncurses.h>
#else
  #include <ncurses.h>
#endif

namespace tr
{
  /* карта кодов команд для передачи по сети !пример!
  enum SRV_CMD {
    CMD_ZERO,      // нуль не используется как команда
    CMD_HELLO,     // control me
    CMD_BY,        // disconnect me
    CMD_STOP,      // stop server
    CMD_RELOAD,    // reload data
    CMD_RESTART,   // restart server
    CMD_ENUM_END,  // end of the list commands
  };
  extern std::map<SRV_CMD, std::vector<char>> CmdMap;
  */

  // Записывает в строковый буфер отметку времени
  extern void get_time_string(char * buffer);

  ///### Управление буфером команд
  class commands
  {
    public:
      commands(void);

      char* push(int);     // добавление символа в строку команды
      char* text(void);    // текущая (верхняя) строка в списке
      size_t length(void); // длина текущей строки
      void next(void);

    private:
      static const size_t cmd_max_size = 128; // предел длины команды
      static const size_t history_size = 8;  // длина истории команд
      char cmds[history_size][cmd_max_size];  // Массив строк команд
      size_t row_size[history_size];          // массив длин строк
      size_t current_row = 0;                 // текущая строка
  };

  ///### Обертка к enet
  class enetw
  {
  private:
    bool online = true;
    std::vector<char> CleanCmdLine = {}; // очистка командной строки
    tr::commands Cmd = {};

    ENetHost* nethost = nullptr;
    ENetAddress address = {};

    // настройки сервера
    int srv_conns = 8;     // количество подключений
    int srv_channels = 0;  // max число каналов для каждого подключения
    int in_bw = 0;     // скорость приема (Кбайт/с)
    int out_bw = 0;    // скорость передачи (Кбайт/с)

    int port_min = 12888; // Начальный порт сервера. Если он занят, то перебором
    int port_max = 12900; // открывается следующий до "port_max". Если все
                          // оказались заняты, генерируется ошибка
    // настройки клиента
    int cl_conns = 1;            // количество подключений
    int cl_channels = 1;         // max число каналов для каждого подключения
    ENetPeer* cl_peer = nullptr; // клиентский peer

    WINDOW * winLog = nullptr;           // окно ncurses
    int console_width, console_height;   // размеры терминального окна

    void ev_connect(ENetPeer*);
    void ev_disconnect(ENetPeer*);
    void ev_receive(ENetPeer*, ENetPacket*);
    void send_by_peer(ENetPeer*, std::vector<enet_uint8>&);
    void print_log(const char*);
    void check_keyboard(char prompt[]);
    void accept_cmd(char prompt[]);
    void check_events(int timeout);
    void open_connection(char*, enet_uint32);

  public:
    enetw(void);
    ~enetw(void);

    std::string msgError = {};

    int run_server(void);
    int run_client(char*, enet_uint32);
    void disconnect_me(void);
    void send_data(std::vector<enet_uint8>&);

  };

} // tr
#endif // __ENETW_HPP__

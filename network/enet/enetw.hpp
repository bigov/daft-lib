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

#include <enet/enet.h>

#if defined(_WIN32)
  #include <ncursesw/ncurses.h>
#else
  #include <ncurses.h>
#endif

namespace tr
{
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
  extern int admin_key; // ключ администратора TODO: сделать вычисляемым

  // Записывает в строковый буфер отметку времени
  extern void get_time_string(char * buffer);

  class enetw
  {
  private:
    bool listen_clients = false;
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
    std::vector<char> CleanCmdLine = {}; // очистка командной строки

    void ev_connect(ENetPeer*);
    void ev_disconnect(ENetPeer*);
    void ev_receive(ENetPeer*, ENetPacket*);
    void send_by_peer(ENetPeer*, std::vector<enet_uint8>&);
    void print_log(const char*);

  public:
    enetw(void);
    ~enetw(void);

    std::string msgError = {};

    int listen(void);
    int connect(char*, enet_uint32);
    void open_connection(char*, enet_uint32);
    void disconnect(void);
    void send_data(std::vector<enet_uint8>&);
    void check_events(int timeout);

  };

} // tr
#endif // __ENETW_HPP__

//
// Обертка к библиотеке enet
//
#include "enetw.hpp"

namespace tr {

  std::map<SRV_CMD, std::vector<char>> CmdMap = {
    {CMD_HELLO, {'h','e','l','l','o'}},
    {CMD_BY, {'b','y'}},
    {CMD_STOP, {'s','t','o','p'}},
    {CMD_RELOAD, {'r','e','l','o','a','d'}},
    {CMD_RESTART, {'r','e','s','t','a','r','t'}},
  };

  const int time_buf_size = 20;
  char time_buf_format[] = "%Y-%m-%d %R:%S";

  //## Записывает в строковый буфер отметку времени
  void get_time_string(char * buffer)
  {
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(buffer, time_buf_size, time_buf_format, timeinfo);
    return;
  }

  //## Default constructor
  enetw::enetw(void)
  {
    if( 0 != enet_initialize() )
      throw std::runtime_error( "An error initializing ENet" );

    address.host = ENET_HOST_ANY;  // адрес для приема пакетов
    address.port = port_min;       // какой порт слушать

    initscr(); // инициализация ncurses
    cbreak();  // Line buffering disabled, Pass on everty thing to me
    keypad(stdscr, TRUE); // возможность использовать функциональные кл.
    nodelay(stdscr,TRUE); // turn off getch() wait
    wbkgd( stdscr, A_REVERSE );
    addstr(" F1: help; F10: exit;");
    refresh();

    // Построить окно вывода сообщений
    getmaxyx( stdscr, console_height, console_width );
    WINDOW * frame = newwin( console_height - 4, console_width - 2, 1, 1 );
    wrefresh( frame );

    winLog = newwin( console_height - 5, console_width - 4, 2, 2 );
    scrollok( winLog, TRUE );
    wrefresh( winLog );

    CleanCmdLine.resize(console_width, ' ');

    return;
  }

  //## Default destructor
  enetw::~enetw(void)
  {
    if( nullptr != nethost ) enet_host_destroy( nethost );
    enet_deinitialize();
    print_log("Host was shootdown");
    endwin(); // освободить память ncurses
    return;
  }

  //## Регистратор информации о событиях
  void enetw::print_log(const char buf[])
  {
     wprintw( winLog, buf );
     wprintw( winLog, "\n" );
     wrefresh( winLog );
     return;
  }

  //## Передача команды из клиентского соединения
  void enetw::send_data(std::vector<enet_uint8>& PostData )
  {
    send_by_peer(cl_peer, PostData);
    return;
  }

  //## Передача команды в указаный peer
  void enetw::send_by_peer(ENetPeer * peer, std::vector<enet_uint8>& PostData )
  {
    enet_uint8 channel = 0; // id канала для отправки пакета

    ENetPacket * packet = enet_packet_create(
      PostData.data(), PostData.size(), ENET_PACKET_FLAG_RELIABLE );

    enet_peer_send (peer, channel, packet);
    enet_host_flush (nethost);

    return;
  }

  //## Обработчик подключения
  //
  // Пока тут только регистрация информации о подключении
  //
  void enetw::ev_connect(ENetPeer * peer)
  {
    char buf[128];
    if(0 != peer->host->address.host)
    {
      sprintf(buf, "Connected from %s:%d, ID=%u",
              peer->host->address.host, peer->address.port, peer->connectID);
    } else
    {
      sprintf(buf, "Connected from localhost:%d, ID=%u",
              peer->address.port, peer->connectID);
    }
    print_log(buf);
    return;
  }

  //## Обработчик принятых данных
  //
  // Данные приходят массивами со структурой "enet_uint8" = "unsigned char"
  // Длина принятого массива передается в переменной ENetPacket->dataLength
  //
  // Можно скопировать принятый массив при помощи:
  //
  //    memcpy(TARGET, received->data, received->dataLength);
  //
  void enetw::ev_receive(ENetPeer * peer, ENetPacket * received)
  {
    std::vector<enet_uint8> ReceivedData = {};
    if(received->dataLength > 0)
    {
      ReceivedData.resize(received->dataLength);
      memcpy(ReceivedData.data(), received->data, received->dataLength);
    }
    enet_packet_destroy( received ); // после обработки пакет следует удалить

    char buf[80];
    sprintf(buf, "Size of received data = %d", ReceivedData.size());
    print_log(buf);

    ReceivedData.empty();
    ReceivedData.emplace_back(588);
    send_by_peer(peer, ReceivedData); // ответ клиенту
    return;
  }

  //## Обработчик события отключения клиента
  //
  // Пока тут только регистрация информации о событии
  //
  void enetw::ev_disconnect(ENetPeer * peer)
  {
    char buf[80];

    if(0 != peer->host->address.host)
    {
      sprintf(buf, "%s:%d is disconnected",
              peer->host->address.host, peer->address.port);
    } else
    {
      sprintf(buf, "localhost:%d is disconnected", peer->address.port);
    }

    print_log(buf);
    return;
  }

  //## опрос событий
  void enetw::check_events(int timeout)
  {
    ENetEvent event;
    while( enet_host_service( nethost, &event, timeout ) > 0 )
    {
      switch( event.type )
      {
        case ENET_EVENT_TYPE_CONNECT:
          ev_connect(event.peer);
          break;
        case ENET_EVENT_TYPE_RECEIVE:
          ev_receive(event.peer, event.packet);
          break;
        case ENET_EVENT_TYPE_DISCONNECT:
          ev_disconnect(event.peer);
          break;
        case ENET_EVENT_TYPE_NONE:
          break;
      }
    }
    return;
  }

  //## Обработчик команд, введенных с клавиатуры
  void enetw::accept_cmd(char prompt[])
  {
    print_log(cmd_buffer.c_str());
    cmd_buffer.clear();
    mvwprintw( stdscr, console_height - 2, 0, "%s", CleanCmdLine.data());
    mvwprintw( stdscr, console_height - 1, 0, "%s", CleanCmdLine.data());
    mvwprintw( stdscr, console_height - 2, 2, "%s", prompt );
    refresh();
    return;
  }

  //## Опрос нажатий клавиатуры
  void enetw::check_keyboard(char prompt[])
  {
    int key;
    while((key = getch()) > -1)
    {
      if(key == KEY_F(10))
      {
        online = false;
      }
      else if(key == KEY_UP)
      {
        print_log("up");
        // восстановить курсор
        mvwprintw( stdscr, console_height - 2, 2, "%s", prompt );
      }
      else if((key == '\n') || (key == '\r'))
      {
        // если буфере есть набранная команда, то выполнить ее
        if(cmd_buffer.size() > 0) accept_cmd(prompt);
        // если буфер команды пустой, то только восстановить курсор
        else mvwprintw( stdscr, console_height - 2, 2, "%s", prompt );
      }
      else
      {
        cmd_buffer.push_back(key);
      }
    }
    return;
  }

  //## Открыть доступный порт и ожидать подключений
  int enetw::run_server(void)
  {
    while((nullptr == nethost) && (address.port < port_max))
    {
      nethost = enet_host_create( &address, srv_conns, srv_channels, in_bw, out_bw );
      if(nullptr == nethost) address.port += 1;
    }

    if(nullptr == nethost)
    {
      msgError = "An error on creating an ENet server host";
      print_log(msgError.c_str());
      return EXIT_FAILURE;
    }

    char buf[40];
    sprintf(buf, "Port listen: %d", address.port);
    print_log(buf);

    char prompt[] = "server: ";
    mvwprintw( stdscr, console_height - 2, 2, "%s", prompt );
    refresh();

    while(online)
    {
      check_events(50);
      check_keyboard(prompt);
    }
    //TODO: послать disconnect всем активным клиентам
    return EXIT_SUCCESS;
  }

  //## установить клиентское подключение к серверу
  //
  // char* srv_name      - имя хоста
  // enet_uint32 cl_data - число, принимаемое сервером как "event.data"
  //
  void enetw::open_connection(char* srv_name, enet_uint32 cl_data)
  {
    char buf[128];
    enet_address_set_host( &address, srv_name );

    nethost = enet_host_create( nullptr, cl_conns, cl_channels, in_bw, out_bw );
    if(nullptr == nethost)
    {
      print_log("Can't create ENet host-client");
      return;
    }

    cl_peer = enet_host_connect( nethost, &address, cl_channels, cl_data );
    if( nullptr == cl_peer )
    {
      print_log("Can't create ENet peer connection");
      enet_host_destroy(nethost);
      nethost = nullptr;
      return;
    }

    // ожидание подтверждения c сервера
    ENetEvent event = {};
    if(( enet_host_service( nethost, &event, 1000 ) > 0 )
      && ( event.type == ENET_EVENT_TYPE_CONNECT ))
    {
      sprintf(buf, "Connection to the %s:%d complete", srv_name, address.port);
      print_log(buf);
    } else
    {
      sprintf(buf, "Can't connect to the %s:%d", srv_name, address.port);
      print_log(buf);
      enet_peer_reset( cl_peer );
      cl_peer = nullptr;
      enet_host_destroy(nethost);
      nethost = nullptr;
    }
    return;
  }

  //## Цикл работы клиента
  int enetw::run_client(char* srv_name, enet_uint32 cl_data)
  {
    open_connection(srv_name, cl_data);

    char prompt[] = "client: ";
    mvwprintw( stdscr, console_height - 2, 2, "%s", prompt );
    refresh();

    while (online)
    {
      if(nullptr != cl_peer) check_events(50);
      check_keyboard(prompt);
    }

    if(nullptr != cl_peer) disconnect_me();
    return EXIT_SUCCESS;
  }

  //## Отключиться от сервера
  void enetw::disconnect_me(void)
  {
    ENetEvent event;
    enet_peer_disconnect( cl_peer, 0);
    int timeout = 200;
    while( enet_host_service( nethost, &event, timeout ) > 0 )
    {
      switch( event.type )
      {
        case ENET_EVENT_TYPE_RECEIVE:
          // все входящие пакеты отбрасываем
          enet_packet_destroy( event.packet );
          break;
        case ENET_EVENT_TYPE_DISCONNECT:
          return;
        default:
          break;
      }
    }
    // если подтверждение не было получено, то соединение сбрасывается
    enet_peer_reset( cl_peer );
    print_log("Connection was reset by timeout.");
    return;
  }

} //namespace tr

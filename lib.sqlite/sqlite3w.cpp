//----------------------------------------------------------------------------
//
// file: sqlite3w.cpp
//
// Обертка для удобства работы с Sqlite3
//
//----------------------------------------------------------------------------
#include "sqlite3w.hpp"

namespace tr
{
  // Статические члены инициализируются персонально
  std::forward_list<std::pair<std::string, std::string>> sqlw::row = {};
  std::forward_list<std::forward_list<
    std::pair<std::string, std::string>>> sqlw::rows = {};
  char sqlw::empty ='\0';
  int sqlw::num_rows = 0;
  tr::query_data sqlw::result = {0, "", "", 0};

  //## конструктор устанавливает имя файла
  sqlw::sqlw(const char *fname)
  {
    set_db_name(fname);
    return;
  }

  //## конструктор устанавливает имя файла
  sqlw::sqlw(const std::string & fname)
  {
    set_db_name(fname.c_str());
    return;
  }

  //## устанавливает имя файла базы данных Sqlite3
  void sqlw::set_db_name(const std::string & fname)
  {
    set_db_name(fname.c_str());
    return;
  }

  //## устанавливает имя файла базы данных Sqlite3
  void sqlw::set_db_name(const char * fname)
  {
    if(nullptr == fname)
    {
      ErrorsList.emplace_front("Sqlw: no specified DB to open.");
      return;
    }

    DbFileName = std::string(fname);
    if(0 == DbFileName.length())
      ErrorsList.emplace_front("Sqlw: no specified DB to open.");

    return;
  }

  //## Обработчик результатов запроса
  int sqlw::callback(void *x, int count, char **value, char **name)
  {
    row.clear();
    for(int i = 0; i < count; i++)
    {
      #ifndef NDEBUG
      if (nullptr == name[i]) ERR("sqlw::callback: nullptr name[i]");
      #endif
      row.emplace_front(std::make_pair(name[i], value[i] ? value[i] : &empty));
    }
    rows.push_front(row);
    num_rows++; // у контейнера forward_list нет счетчика элементов

    if(0 != x) return 1; // В этой реализации значение x всегда равно 0
    else return 0;
  }

  //## Обработчик запросов вставки/удаления
  void sqlw::update_callback( void* udp, int type, const char* db_name,
    const char* tbl_name, sqlite3_int64 rowid )
  {
  /* Функция вызывается при получении запросов на обновление/удаление данных
   * Регистрируется вызовом
   *
   * void* sqlite3_update_hook( sqlite3* db, update_callback, void* udp );
   *
   * db
   *   A database connection.
   * 
   * update_callback
   *   An application-defined callback function that is called when a database
   *   row is modified.
   * 
   * udp
   *   An application-defined user-data pointer. This value is made available
   *   to the update callback.
   * 
   * type
   *   The type of database update. Possible values are SQLITE_INSERT,
   *   SQLITE_UPDATE, and SQLITE_DELETE.
   * 
   * db_name
   *   The logical name of the database that is being modified. Names include
   *   main, temp, or any name passed to ATTACH DATABASE.
   * 
   * tbl_name
   *   The name of the table that is being modified.
   * 
   * rowid
   *   The ROWID of the row being modified. In the case of an UPDATE, this is
   *   the ROWID value after the modification has taken place.
   * 
   * Returns (sqlite3_update_hook()) - the previous user-data pointer,
   * if applicable.
   * 
   */
    if(udp != &empty) ERR("Error in sqlw::updade_callback");
    
    result.type = type;
    
    result.db_name.clear();
    result.db_name = db_name;
    
    result.tbl_name.clear();
    result.tbl_name = tbl_name;
    
    result.rowid = rowid;
    
    return;
  }
  
  //## Подключиться к DB
  void sqlw::open(const std::string & fname)
  {
  /* Закрывает текущий файл БД (если был открыт) и открывает новый
   */
    if(is_open) close();
    DbFileName = fname;
    open();
    return;
  }

  //## Подключиться к DB
  void sqlw::open(void)
  {
    if(DbFileName.empty())
    {
      ErrorsList.emplace_front("Sqlw: no specified DB to open.");
      return;
    }

    ErrorsList.clear();
    if(0 != sqlite3_open(DbFileName.c_str(), &db))
    {
      ErrorsList.emplace_front("Can't open database: "
        + std::string(sqlite3_errmsg(db))
        + "\nDatabase file name: " + DbFileName);
      close();
    } else
    {
      is_open = true;
    }
    
    sqlite3_update_hook(db, update_callback, &empty);
    
    return;
  }

  //## Выполнение запроса
  void sqlw::exec(const std::string &query)
  {
    exec(query.c_str());
    return;
  }

  //## Выполнение запроса
  void sqlw::exec(const char *query)
  {
    if(!is_open) open();
    char *err_msg = nullptr;
    ErrorsList.clear();
    rows.clear();
    num_rows = 0;
    if(SQLITE_OK != sqlite3_exec(db, query, callback, 0, &err_msg))
    {
      ErrorsList.emplace_front("sqlw::exec: " + std::string(err_msg));
      sqlite3_free(err_msg);
    }
    return;
  }

  //## Закрывает соединение с файлом базы данных
  void sqlw::close(void)
  {
    sqlite3_close(db);
    is_open = false;
    return;
  }

  //## Деструктор
  sqlw::~sqlw(void)
  {
    if(is_open) close();
    return;
  }
}

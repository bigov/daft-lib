//----------------------------------------------------------------------------
//
// file: sqlw.hpp
//
// Обертка для удобства работы с Sqlite3
//
//----------------------------------------------------------------------------
#ifndef __SQLITE3W_HPP__
#define __SQLITE3W_HPP__

#include "main.hpp"
#include "sqlite3.h"

namespace tr{
  
struct query_data {
  int type;
  std::string db_name;
  std::string tbl_name;
  sqlite3_int64 rowid;
};

class sqlw
{
  public:
    sqlw(void) { DbFileName.clear(); }
    sqlw(const char *);
    sqlw(const std::string &);
    ~sqlw(void);

    static std::forward_list<std::pair<std::string, std::string>> row;
    static std::forward_list<
           std::forward_list<std::pair<std::string, std::string>>> rows;
    static int num_rows; // число строк в результате запроса

    std::forward_list<std::string> ErrorsList = {};
    static tr::query_data result;

    void set_db_name(const char *);
    void set_db_name(const std::string &);
    void open(void);
    void open(const std::string &);
    void close(void);
    void exec(const char *);
    void exec(const std::string &);

  private:
    static char empty;

    sqlw(const sqlw &) = delete;
    sqlw& operator=(const sqlw &) = delete;

    sqlite3 *db = nullptr;
    bool is_open = false;
    std::string DbFileName = "";

    static int callback(void*, int, char**, char**);
    static void update_callback(void*, int, const char*, const char*,
      sqlite3_int64);

}; // class sqlw
}  // ns tr::
#endif

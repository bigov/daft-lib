/*
  Пример из краткого введения в API Sqlite на странице документации
  http://www.sqlite.org/quickstart.html

Тестовая база данных: test.db содержит одну таблицу:

tst_CPP_dev>sqlite3.exe test.db
SQLite version 3.21.0 2017-10-24 18:55:49
Enter ".help" for usage hints.
sqlite> create table list (
   ...> rowid INTEGER PRIMARY KEY,
   ...> event TEXT,
   ...> year INTEGER(2));
sqlite> insert into list(event,year) values('now year is', 2017);
sqlite> select * from list;
1|now year is|2017
sqlite> .quit
tst_CPP_dev>

*/
#include "main.hpp"
#include "sqlite3w.hpp"

//## Пример записи бинарных данных в базу данных sqlite.
int InsertFile(const string& db_name)
{
    ifstream file("Sql.pdf", ios::in | ios::binary);
    if (!file) {
        cerr << "An error occurred opening the file\n";
        return 12345;
    }
    file.seekg(0, ifstream::end);
    streampos size = file.tellg();
    file.seekg(0);

    char* buffer = new char[size];
    file.read(buffer, size);

    sqlite3 *db = NULL;
    int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
    if (rc != SQLITE_OK) {
        cerr << "db open failed: " << sqlite3_errmsg(db) << endl;
    } else {
        sqlite3_stmt *stmt = NULL;
        rc = sqlite3_prepare_v2(db,
                                "INSERT INTO ONE(ID, NAME, LABEL, GRP, FILE)"
                                " VALUES(NULL, 'fedfsdfss', NULL, NULL, ?)",
                                -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            cerr << "prepare failed: " << sqlite3_errmsg(db) << endl;
        } else {
            // SQLITE_STATIC because the statement is finalized
            // before the buffer is freed:
            rc = sqlite3_bind_blob(stmt, 1, buffer, size, SQLITE_STATIC);
            if (rc != SQLITE_OK) {
                cerr << "bind failed: " << sqlite3_errmsg(db) << endl;
            } else {
                rc = sqlite3_step(stmt);
                if (rc != SQLITE_DONE)
                    cerr << "execution failed: " << sqlite3_errmsg(db) << endl;
            }
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);

    delete[] buffer;
}

int main()
{
  const char *fname = "test.db";
  tr::sqlw Db;
  Db.open(fname);

  std::string myQuery = "SELECT * FROM list WHERE year > 0;";
  Db.exec(myQuery.c_str());
  if(Db.num_rows < 1) std::cout << "что-то не так...\n";
  else
  {
    for(auto &row: Db.rows)
    {
      std::cout << std::endl;
      for(auto &pair: row)
      {
        std::cout << pair.first << ": " << pair.second << "\n";
      }
    }
  }
	
  myQuery = "UPDATE `list` SET `event`='History year' WHERE `year`=2016;";
  myQuery = "INSERT INTO `list` (`event`, `year`) VALUES ('Prev year', 2017);";
  Db.exec(myQuery.c_str());
  
  if(Db.result.rowid > 0)
  {
    std::cout
      << "\ndb name: " << Db.result.db_name << std::endl
      << "table: "   << Db.result.tbl_name << std::endl
      << "row id: "  << Db.result.rowid << std::endl;
  }

  Db.close();
  return 0;
}

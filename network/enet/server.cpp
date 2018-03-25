/*
 * Серверная часть на базе библиотеки enet
 *
 */
#include "enetw.hpp"

//## Enter point
int main()
{
  tr::enetw EnetServer = {};
  int res = EnetServer.listen();
  if(res != EXIT_SUCCESS) std::cout << EnetServer.msgError;
  return res;
}

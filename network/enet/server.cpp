/*
 * Серверная часть на базе библиотеки enet
 *
 */
#include "enetw.hpp"

//## Enter point
int main()
{
  tr::enetw Enet = {};
  int res = Enet.run_server();
  if(res != EXIT_SUCCESS) std::cout << Enet.msgError;
  return res;
}

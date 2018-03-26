/*
 * 
 * Контрольная часть (клиент) на базе библиотеки enet
 *
 */
#include "enetw.hpp"

//## Enter point
int main()
{
  char srv_name[] = "localhost";
  tr::enetw Enet = {};
  int res = Enet.run_client(srv_name, 0);
  if(res != EXIT_SUCCESS) std::cout << Enet.msgError;
  return res;
}

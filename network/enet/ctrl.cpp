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
  tr::enetw EnetClient = {};
  int res = EnetClient.connect(srv_name, 0);
  if(res != EXIT_SUCCESS) std::cout << EnetClient.msgError;
  return res;
}

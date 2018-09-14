/* Демка по переключению режимов работы консоли.
 * - в Win'7 широкие символы не отображаются
 * */

#include <cstdio>
#include <iostream>

int main()
{
  int mode = fwide(stdout,0);
  std::cout<<"0.mode="<<mode<<std::endl;
  std::cout<<"ABC"<<std::endl;
  mode = fwide(stdout,0);
  std::cout<<"1.mode="<<mode<<std::endl;
  freopen(NULL,"w",stdout);
  setlocale(LC_ALL, "en_US.UTF-8");
  mode = fwide(stdout,0);
  std::wcout<<L"2.mode="<<mode<<std::endl;
  std::wcout<<L"Ура"<<std::endl;
  mode = fwide(stdout,0);
  std::wcout<<L"3.mode="<<mode<<std::endl;
  freopen(NULL,"w",stdout);
  mode = fwide(stdout,0);
  std::cout<<"4.mode="<<mode<<std::endl;
  std::cout<<"Again"<<std::endl;
  mode = fwide(stdout,0);
  std::cout<<"5.mode="<<mode<<std::endl;
  getchar();
  return 0;
}

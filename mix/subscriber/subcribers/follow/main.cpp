/**
 *
 * Пример реализации шаблона проектирования "подписчик"
 *
 **/

#include "follow.hpp"

// Объявление клиентского класса
class Dummy: public EvClient
{
  public:
    virtual void pop(const EvInterface & ref);
};

// Определение метода клиента
void Dummy::pop(const EvInterface & ref)
{
  string msg = ref.get();
  cout << msg.c_str() << endl;
  return;
}

int main()
{
  EvInterface * content = new EvInterface();
  Dummy * client = new Dummy();

  cout << endl;
  content->subscribe(*client);
  content->push("Hello, my world!");
  content->push("My big world, hello!");
  cout << endl;

  delete client;
  delete content;

  return 0;
}

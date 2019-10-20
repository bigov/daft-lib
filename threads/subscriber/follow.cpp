/**
 * шаблон проектирования "подписчик"
 */
#include "follow.hpp"

// Интерфейс
// Конструктор интерфейса
EvInterface::EvInterface(void) : message(), clients() {;}
// Разослать всем подписчикам
void EvInterface::anounce(void) {for(auto it: clients) it->pop(*this);}
// добавление клиента в список рассылки 
void EvInterface::subscribe(EvClient & ref) {clients.push_back(&ref);}
// удаление клиента из подписки
void EvInterface::remove(EvClient & ref) {clients.remove(&ref);}
// передача содержимого сообщения клиенту
const string & EvInterface::get() const {return message;}
// Рассылка сообщения подписчикам
void EvInterface::push(string m) {message = m; anounce();}

// наследуемый класс клиента
EvClient::~EvClient(void) {;}
void EvClient::pop(const EvInterface &) {;}


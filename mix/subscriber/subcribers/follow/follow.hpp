/**
 * шаблон проектирования "подписчик"
 */
#ifndef _FOLLOW_HPP_
#define _FOLLOW_HPP_

#include <iostream>
#include <string>
#include <list>

using namespace std;
class EvInterface;

// наследуемый класс клиента
class EvClient
{
	public:
		virtual ~EvClient(void);
		virtual void pop(const EvInterface &);
};

// интерфейс обмена сообщениями
class EvInterface
{
	private:
		string message;
		list<EvClient *> clients;
		void anounce(void);
	public:
		EvInterface(void);
		void subscribe(EvClient & ref);
		void remove(EvClient & ref);
		const string & get(void) const;
		void push(string message);
};

#endif

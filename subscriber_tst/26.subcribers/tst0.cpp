/**
 *
 * Пример реализации шаблона проектирования "подписчик"
 *
 **/

#include <iostream>
#include <string>
#include <list>

using namespace std;

//// Объявление интерфейса
class EvInterface;

////////
// Базовый класс для создания подписчиков-клиентов
//
class EvClient
{
	public:
		virtual ~EvClient(void) {}
  	virtual void ev_get(const EvInterface &) {}
};

////////
// Определение интерфейса методов оповещения клиентов-наблюдателей
//
class EvInterface
{
	private:
		string ev_message;
		list<EvClient *> ev_clients;

		////
		// Разослать всем подписчикам
		void anounce_all()
		{
			for(auto it: ev_clients)
			{
				anounce(it);
			}
		}

		////
		// Отправить одному
		void anounce(EvClient * client)
		{
				client->ev_get(*this);
		}

	public:
		EvInterface() : ev_message(), ev_clients() {}

		////
		// добавление клиента в список рассылки
		void subscribe(EvClient & ref)
		{
			ev_clients.push_back(&ref);
			// после добавления отправить клиенту последнее сообщение
			anounce(&ref);
    }

		////
		// удаление клиента из подписки
		void remove(EvClient & ref)
		{
			ev_clients.remove(&ref);
		}

		////
		// чтение сообщения клиентом
		const string & get() const
		{
			return ev_message;
		}

		////
		// Рассылка сообщения подписчикам
		void push(string message)
		{
			ev_message = message;
			anounce_all();
		}
};

////////
// Реализация клиента - печать текста сообщения
//
class Reflector: public EvClient
{
	public:
		virtual void ev_get(const EvInterface & ref)
  	{
  		cout << ref.get() << endl;
  	}
};

////////
// Реализация клиента - вывод длины сообщения
//
class Counter: public EvClient
{
	public:
		virtual void ev_get(const EvInterface & ref)
		{
  		cout << "length = " << ref.get().length() << endl;
		}
};

////////
// MAIN
//
int main()
{
    EvInterface * content = new EvInterface();

    Reflector * client_R = new Reflector();
    Counter client_C = Counter();

    content->subscribe(*client_R);
    content->push("Hello, my world!");
    cout << endl;

    content->remove(*client_R);
    content->subscribe(client_C);
    content->push("My big world, hello!");
    cout << endl;

		delete client_R;
		delete content;

    return 0;
}

/**
 *
 * Пример 2 
 *
 * реализации шаблона проектирования "подписчик"
 * для нескольких типов событий
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
  	virtual void ev1(const EvInterface &) = 0;
  	virtual void ev2(const EvInterface &) = 0;

};

////////
// Определение интерфейса методов оповещения клиентов-наблюдателей
//
class EvInterface
{
	private:
		string ev_message;
		list<EvClient *> ev_clients;
		int digit;

		////
		// Разослать всем подписчикам
		void anounce_all_m()
		{
			for(auto it: ev_clients)
			{
				anounce(it);
			}
		}

		////
		// Разослать всем подписчикам
		void anounce_all_d()
		{
			for(auto it: ev_clients)
			{
				anounce_d(it);
			}
		}

		////
		// Отправить одному тип 1
		void anounce(EvClient * client)
		{
				client->ev1(*this);
		}

		////
		// Отправить одному тип 2
		void anounce_d(EvClient * client)
		{
				client->ev2(*this);
		}

	public:
		EvInterface() : ev_message(), ev_clients(), digit(0) {}

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
		// Чтение текста сообщения для клиента
		const string & get() const
		{
			return ev_message;
		}

		////
		// ПЕРЕГРУЖЕНО Рассылка подписчикам сообщения
		void push(string message)
		{
			ev_message = message;
			anounce_all_m();
		}

		//// 
		// ПЕРЕГРУЖЕНО Рассылка подписчикам числа
		void push(int m)
		{
			digit = m;
			anounce_all_d();
		}

};

////////
// Реализация клиента - печать текста сообщения
//
class ClientA: public EvClient
{
	public:
		virtual void ev1(const EvInterface & ref)
  	{
			string msg = ref.get();
			if(msg.empty()) msg = "empty message";
  		cout << msg << endl;
			return;
  	}
		virtual void ev2(const EvInterface &)
		{
			cout << "Client R get event type 2" << endl;
			return;
		}

};

////////
// Реализация клиента - вывод длины сообщения
//
class ClientB: public EvClient
{
	public:
		virtual void ev1(const EvInterface & ref)
		{
  		cout << "length = " << ref.get().length() << endl;
		}
		virtual void ev2(const EvInterface &) { return; }
};

////////
// MAIN
//
int main()
{
    EvInterface * content = new EvInterface();

    ClientA * client_a = new ClientA();
    ClientB   client_b = ClientB();

    cout << endl;
		cout << "add client A" << endl;
    content->subscribe(*client_a);
    cout << endl;

		cout << "add client B" << endl;
    content->subscribe(client_b);
    cout << endl;

		cout << "push event 1" << endl;
		content->push("Hello, my world!");
    cout << endl;

		cout << "push event 2" << endl;
		content->push(21);
    cout << endl;

		cout << "remove client B" << endl;
    content->remove(client_b);

		cout << "push event 1" << endl;
    content->push("My big world, hello!");
    cout << endl;

		// очистка памяти
    content->remove(*client_a);
		delete client_a;

		delete content;

    return 0;
}

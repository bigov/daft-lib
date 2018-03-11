////
// пример создания потока и управления им через интерфейс шаблона
// проектирования "Слушатель"
//

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include "follow.hpp"

// Объявление клиентского класса
class Dummy: public EvClient
{
	private:
		int sleep;
	public:
		Dummy() : sleep(0) {};
		virtual void pop(const EvInterface & ref);
		void thread(int);
};
////////

////
void Dummy::pop(const EvInterface & ref)
{
	string msg = ref.get();
	if(msg == "alert") sleep = 0;
	cout << msg.c_str() << endl;
	return;
}
////
void Dummy::thread(int i)
{
	sleep = i;
	while (sleep > 0)
	{
    std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "dummy is sleep: " << to_string(sleep) << endl;
		--sleep;
	}
	std::cout << "Dummy don't sleep!" << endl;
	return;
}

int main() 
{
	EvInterface * content = new EvInterface();
	Dummy client = Dummy();

	cout << endl;
	content->subscribe(client);
	content->push("Hello, my world!");
	std::thread t(&Dummy::thread, &client, 25);
	t.detach();

	std::this_thread::sleep_for(std::chrono::seconds(5));
	content->push("alert");
	std::this_thread::sleep_for(std::chrono::seconds(5));

	content->remove(client);
	//delete client;
	delete content;
	return EXIT_SUCCESS;
}


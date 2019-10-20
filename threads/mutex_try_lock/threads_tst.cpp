//
// Тест обработки ввода и вывода через стандартные потоки с использованием
// раздельных потоков с блокировкий (mutex) общего ресурса
//

#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>

std::chrono::milliseconds ms50(50);
std::chrono::seconds sec10(10);
std::mutex mutex_cmd;
bool run = true;
std::queue<std::string> messages;

////////
// прием данных из стандартного потока
//
void cmd_cin() 
{
	while(run)
	{
		std::string cmd;
		std::cin >> cmd;
		while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms50);
		messages.push(cmd);
		mutex_cmd.unlock();
		if(cmd == "q") run = false;
	}
	std::cout << "Input was terminated." << std::endl;
	return;
}
////////
// Вывод данных
void cmd_cout()
{
	bool loop = true;
	while (loop)
	{
		std::this_thread::sleep_for(sec10);
		std::string cmd;
		while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms50);
		if(!messages.empty())
		{
			cmd = messages.front();
			messages.pop();
		} else {
			cmd = "Command queue is empty.";
			loop = run; // разрешить выход только если очередь пуста
		}
		mutex_cmd.unlock();
		std::cout << "state: " << cmd << std::endl;
	}
	std::cout << "Output was terminated." << std::endl;
	return;
}

int main() 
{
	std::thread input(cmd_cin);
 	input.detach();
	cmd_cout();

	std::cout << "Application was closed." << std::endl;
	return 0;
}

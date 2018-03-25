//////////////////////////////////////////////////////////////////////////////
//
// file: client_udp.cpp
//
//
// Модуль для тестирования сокетов, проверки подключений к UDP серверу
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include "sock.hpp"

//std::chrono::milliseconds ms50(50);
std::chrono::milliseconds ms10(10);
std::chrono::milliseconds ms20(20);

std::mutex mutex_cmd;
bool run = true;

// очередь сообщений
std::queue<std::string> messages;

////////
// прием данных из стандартного потока
//
void cmd_cin() 
{
	std::string s;
	int l;
	int max = 128;
	while(run)
	{
		std::cout << "|_| ";
		l = lib::cinString(s, max); // прием из консоли текстовой строки
		if(l > 0)
		{
			while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms10);
			messages.push(s);
			mutex_cmd.unlock();
			// приостановить для обработки и вывода результата другим потоком
			std::this_thread::sleep_for(ms20);
		}
		if(l < 0) std::cout <<"exceed the length limit = " <<max <<cR;
		if(s == "/Q") run = false;
		std::this_thread::sleep_for(ms10);
	}
	std::cout << "Input was terminated." << std::endl;
	return;
}

void recieve_response(SOCKET s)
{
	int buf_len = 128;
	char * buf = new char[buf_len];
	sockaddr_in a;
	socklen_t a_len = sizeof(&a);
	int received = lib::SocketReceiveChars(s, buf, buf_len, &a, &a_len);
	
	if (received > 0 )
	{
		std::string msg(buf, strlen(buf)); 
		msg = "RESP: " + msg + cR;
		std::cout << msg;
	}
	
	delete [] buf;
	return;
}


////////
// Вывод данных
void cmd_cout()
{
	bool loop = true;

	lib::SocketsLibInit();
	lib::SocketNonBlockUDP socket;

	if(!socket.open())
	{
		std::cout << socket.err << std::endl;
		loop = false;
	} else 
	{
		std::cout <<"Using port " <<socket.port <<std::endl <<std::endl;
	}
	
	// адрес получателя
	sockaddr_in address = lib::makeSockaddrIn("127.0.0.1", 4422);
	
	while (loop)
	{
		recieve_response(socket.soc);
		std::string msg_text;
		while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms10);

		if(!messages.empty())
		{
			msg_text = messages.front();
			messages.pop();
		} else {
			loop = run; // разрешить выход только если очередь пуста	
		}
		mutex_cmd.unlock();

		if(msg_text.length() > 0)
		{
			// отправить данные
			char * data = new char[msg_text.length() + 1];
			data[msg_text.copy(data, std::string::npos)] = '\0';
			if(!lib::SocketSendChars(socket.soc, data, (sockaddr*)&address))
			{
				std::cout << "failure to send UDP packet." << std::endl;
				loop = false;
			} 
			delete [] data;
		}
	}
	std::cout << "\nSocket close." << std::endl;
	lib::SocketsLibClose();			 // освободить ресурсы
	return;
}

int main() 
{
	std::thread input(cmd_cout);
 	input.detach();
	std::this_thread::sleep_for(ms10);
	cmd_cin();

	std::cout << "Application was closed." << std::endl;
	return 0;
}

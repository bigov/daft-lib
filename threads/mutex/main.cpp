#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex i_lock;
std::chrono::milliseconds int_hs(500);

void calc(int * ptri)
{	
	for(int n = 0; n < 5; ++n)
	{
		if(i_lock.try_lock())
		{
			++(*ptri);
			i_lock.unlock();
			std::this_thread::sleep_for(int_hs);
		}
		else
		{
			std::cout << "calc sleep n=" + std::to_string(n) << std::endl;
			std::this_thread::sleep_for(int_hs/50);

			--n;
		}
	}
	return;
}

void print(int * ptri)
{
	int e = 0;

	while(e < 5)
	{
		if(i_lock.try_lock())
		{
			if(e != *ptri)
			{
				e = *ptri;
				std::cout << "*ptri = " + std::to_string(e) << std::endl;
			}
			i_lock.unlock();
		}
	}
	return;
}

int main()
{
	std::cout << std::endl << "Start the test -------------------"
		<< std::endl << std::endl;
	// start code ==============
	
	int * ptri = new int(0);
	i_lock.lock();

	std::thread mat(calc, std::cref(ptri));
	std::thread gav(print, std::cref(ptri));

	mat.detach();
	gav.detach();

	std::this_thread::sleep_for(int_hs/100);
	i_lock.unlock();


	std::this_thread::sleep_for(5 * int_hs);
	std::cout << "Final *ptri = " + std::to_string(*ptri) << std::endl;

	// end code ==============
	std::cout << std::endl << "----------- the test was completed" << std::endl;
	
	return EXIT_SUCCESS;
}

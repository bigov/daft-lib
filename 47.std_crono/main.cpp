#include <iostream>
#include <chrono>

int main()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >
		(std::chrono::system_clock::now().time_since_epoch());

	// миллисекунд в сутках
	int k = 1000 * 60 * 60 * 24;
	long long int f_now = ms.count();
	// число миллисекунд от начала суток
	int ms_res = ms.count() % k;

	std::cout << "ms_res=" << ms_res << "\n";

	return 0;
}


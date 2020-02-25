#include <iostream>
#include <chrono>

int main()
{
	auto ms = std::chrono::duration_cast< std::chrono::milliseconds >
		(std::chrono::system_clock::now().time_since_epoch());

	auto sec = std::chrono::duration_cast< std::chrono::seconds >
		(std::chrono::system_clock::now().time_since_epoch());

	std::cout
    << "ms="    << ms.count()
    << "\nsec=" << sec.count()
    << "\n";

	return 0;
}


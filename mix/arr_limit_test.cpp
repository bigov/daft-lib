#include <iostream>
#include <memory>
#include <limits>
#include <valarray>

using std::cout;
using std::endl;

size_t V_V = std::numeric_limits<int>::max(); // creating array size
int step = 100000000; // step for search

bool step_setup()
{
	if(step > 1)
	{
		V_V += step;
		step = step / 10;
		return false;
	} else
	{
		return true;
	}
}
// Display only first error message
void show_err(std::exception & e)
{
	static std::string err{};
	if(err != e.what())
	{
		err = e.what();
		cout << V_V << ": " << err << endl;
	}
	return;
}

int main()
{ 
	cout << endl;
	bool found = false;

	while (!found)
	{
		try {
			std::unique_ptr<short[]> space{new short[V_V]};
			//std::valarray<short> space(V_V);
			found = step_setup();
			if (found)
			{
				cout << V_V << ": array created on " << &space[0] << endl;
				//cout << space.size() << ": valarray size " << endl;
				//V_V += 10000;
				//space.resize(V_V);
				//cout << space.size() << ": valarray resized " << endl;

				space[0] = 88;
				space[V_V] = 11;
				int m;
				std::cin >> m;
				cout << m << ", " << space[0] << ", " << space[V_V] << endl;
			}
		}
		catch(std::exception & e)
		{
			show_err(e);
			V_V -= step;
		}
	}
	return EXIT_SUCCESS;
}


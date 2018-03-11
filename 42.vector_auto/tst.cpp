#include <iostream>
#include <string>
#include <vector>

using std::cout;
#define R std::endl

std::string foo(std::initializer_list<int> l)
{
	std::string rez = "length of list = " + std::to_string(l.size());
	return rez;
}

int main()
{
	std::vector<int> v;
	v.resize(7);
	v.assign(7, 0);
	for (const auto& s : v) cout << s;
	cout << R << v.size() << R;
	return true;
}

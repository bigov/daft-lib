//
// Пример использования контейнера std::map
// с произвольной структурой в качестве ключа
//
//
#include <iostream>
#include <map>

struct f3d
{
    float
        x = 0.f,
        y = 0.f,
        z = 0.f;
};

bool operator< (f3d const& left, f3d const& right)
{
    if (left.x != right.x)      {return left.x < right.x;}
    else if (left.y != right.y) {return left.y < right.y;}
    else                        {return left.z < right.z;}
}

int main()
{
    std::map<f3d, std::string> names;
    names[{0.f, 0.f, 0.f}] = "empty";
    names[{0.f, 1.f, 0.f}] = "y = 1.0";

    std::cout 
		<<     "--------------------------------------------\n"

    << "\nsay:" << names[{0.f, 0.f, 0.f}]
    << "\nsay:" << names[{0.f, 1.f, 0.f}]

    << "\n\n--------------------------------------------\n";
    return 0;
}


#include <sstream>
#include <string>
#include <iostream>
 
int main()
{
    std::wstring str{L"magic is "};
    int magic = 245;

    std::wstringstream stream;
    stream << "Some " << str << magic;
    std::wcout << stream.str().c_str() << "\n";
    return 0;
}


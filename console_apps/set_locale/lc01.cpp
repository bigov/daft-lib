#include <iostream>
#include <locale>

// работа с локалью взята отсюда 
// https://ru.cppreference.com/w/cpp/locale/locale
int main() {
    std::locale::global(std::locale("en_US.UTF-8") );
    std::wcout.imbue(std::locale());
    std::cout.imbue(std::locale());
    std::wcout << L"добро" << std::endl;

    return 0;
}

//
// test std::any from c++17
//
#include <iostream>
#include <vector>
#include <any>

int main()
{
  std::cout << "\nstart...\n\n";
  std::vector<std::any> AnyVect {};
  
  AnyVect.push_back(std::any(12.4f));
  AnyVect.push_back(std::any(21.5f));
  AnyVect.push_back(std::any(std::vector<char>({'B','-','8','8','8'})));
  
  try
  {
    std::cout << std::any_cast<float>(AnyVect[0]) << "\n";
    std::cout << std::any_cast<float>(AnyVect[1]) << "\n";
    
    auto V = std::any_cast<std::vector<char>>(AnyVect[2]);
    std::cout << V.data() << "\n";
  } 
  catch(const std::bad_any_cast& e)
  {
    std::cout << e.what() << '\n';
  }
  
  return 0;
}

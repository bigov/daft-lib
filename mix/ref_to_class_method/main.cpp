#include <iostream>

int iVar = 0;

class TestCall
{
  public:
    TestCall() {};
    static void dri(int);
};

void TestCall::dri(int m)
{
  std::cout << "Method \"TestCall::dri()\" get arg = " << m << "\n";
  return;
}

////
void caller(void(fn_call)(int))
{
  fn_call(iVar);
  return;
};

////
int main()
{
  std::cout << '\n';

  iVar = 77;
  TestCall T = {};
  caller(T.dri);

  std::cout << " Готово.\n";

  return EXIT_SUCCESS;
}

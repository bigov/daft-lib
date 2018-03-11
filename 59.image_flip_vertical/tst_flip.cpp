///
/// Тестирование алгоритма переворота изображения.
///
/// Исходный массив - битовый набор, имитирующий данные картинки размером 6х5.
/// Алгоритм зеркально переворачивает изображение по вертикали.
///
#include <vector>
#include <iostream>

int main()
{
  size_t h = 5;

  std::vector<unsigned char> data =
    {'a','b','c','d','e','f',
     'g','h','i','j','k','l',
     '1','2','3','4','5','6',
     'm','n','o','p','q','r',
     's','t','u','v','w','x',};

  auto tmp = data;
  auto w = data.size()/h;
  size_t i = 0;
  size_t x = 0;
  for (size_t y = h; y > 0;)
  {
    y -= 1;
    for(x = 0; x < w; x++) data[i++] = tmp[x + w * y];
  }

/* вывод результата */

  std::cout << "\ndata:\n------\n";
  i = 0;
  for (int y = 0; y < h; y++)
    {
    for(int x = 0; x < w; x++)
      std::cout << data[i++] << " ";
    std::cout << "\n";
    }
  
  std::cout << "\ntmp:\n------\n";
  i = 0;
  for (int y = 0; y < h; y++)
    {
    for(int x = 0; x < w; x++)
      std::cout << tmp[i++] << " ";
    std::cout << "\n";
    }

  return 0;
}
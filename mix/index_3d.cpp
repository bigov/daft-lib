////////
//
// Пример преобразования трехмерных кординат
// в одномерный индекс и обратно для хранения в линейной базе данных
//
// На территории 20.000.000 Х 20.000.000 Х 40.000
// количество элементов: 16.000.401.600.040.040.000
//
// Максимально возможное значение типа
// unsigned long long = 18.446.744.073.709.551.615
//
// Если использовать индекс типа "unsigned int" (4.294.967.295)
// то максимально адресуемый объем составит 4.026.610.160 
// для прямоугольника 5000 X 5000 X 160 элементов
//

#include <iostream>

long long x_max = 10000000;
long long y_max = 10000000;
long long z_max = 20000;

long long x_min = 0 - x_max;
long long y_min = 0 - y_max;
long long z_min = 0 - z_max;

unsigned long long cols   = (unsigned long long)x_max * 2 + 1;
unsigned long long rows   = (unsigned long long)y_max * 2 + 1;
unsigned long long levels = (unsigned long long)z_max * 2 + 1;
unsigned long long max_3d = cols * rows * levels ;
unsigned long long rocs = rows*cols;

using std::cout;
using std::endl;

//////
// преобразование 3-д координаты в индекс
//
unsigned long long _index(long long x, long long y, long long z) 
{
	if(x > x_max || x < x_min ||
		 y > y_max || y < y_min ||
		 z > z_max || z < z_min ) throw std::invalid_argument("bad coordinate");
	return
		(unsigned long long)(x + x_max) +
		(unsigned long long)(y + y_max) * cols +
		(unsigned long long)(z + z_max )* cols * rows;
}

//////
// преобразование индекса в 3-д координаты
//
void _coord(unsigned long long _3d, long long * rez)
{
	if(_3d > max_3d) throw std::invalid_argument("bad coordinate index");
	rez[2] = (long long)(_3d / rocs) - z_max;
	unsigned long long _2d = _3d % rocs; 
	rez[1] = (long long)(_2d / cols) - y_max;
  rez[0] = (long long)(_2d % cols) - x_max;
	return;
}

int main()
{
	unsigned long long _3d;
	long long * ar = new long long[3];

	try {
	_3d = _index(x_max, y_max, z_max);
	_coord(_3d, ar);
	}
	catch (const std::exception& e)
	{
    std::cout << e.what() << '\n';
		return 0;
	}
	
	cout << "_index(x_max, y_max, z_max) = " << _3d << endl ;
	cout << "ar = (" << ar[0] << "," << ar[1] << ","<< ar[2] << ")" << endl ;

	delete [] ar;
	return 0;
}

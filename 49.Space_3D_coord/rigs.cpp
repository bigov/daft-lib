#include <iostream>
#include <vector>

using std::cout;
using std::endl;

struct Co3D // 3D-координаты (декартовы и эйлеровы)
{
	float x=0.f, y=0.f, z=0.f;
	Co3D(void) {};
	Co3D(float x, float y, float z): x(x), y(y), z(z) {};
	Co3D& operator= (const Co3D&) = default;
	bool operator== (const Co3D& N) { return(x==N.x && y==N.y && z==N.z);};
};

struct Rig // элемент пространства
{
	Co3D loc{};	    // положение
	short int t = 0; // тип элемента (текстура, поведение, физика и т.п)
	float g = 1.f;  // масштаб элемента
	Co3D rot{};	    // углы поворота
	int msec = 0;   // время создания
	
	Rig() {};       // конструктор по-умолчанию
	Rig(float x, float y, float z, short t): loc(x, y, z), t(t) {}
	Rig& operator= (const Rig&) = default;
};

//## База данных элементов пространства
//
class Rigs
{
	private:
		size_t size = 0;
		std::vector<Rig> db{};

	public:
		Rigs()
		{
			size = 0;
			db.clear();
		};

		//## Доступ к элементу по указанным координатам
		Rig* operator[] (const Co3D& coord)
		{
			for(size_t i = 0; i < size; i++)
			{
				if(db[i].loc == coord) return &db[i];
			}
			return nullptr;
		}

		//## Вставка нового элемента в базу данных
		//
		void place(float x, float y, float z, short t)
		{
			//TODO: вначале проверить наличие элемента в указанных координатах.
			// Если есть, то обновить тип; Иначе - вставить новый
			db.emplace(db.begin(), x, y, z, t);
			size++;
		}
};

int main()
{ 
	Rigs space{};
	space.place(1.f, 1.f, 0.f, 1);

	//Co3D p0{1.f, 1.f, 0.f};
	Rig* r = space[{1.f, 1.f, 0.f}];

	if( nullptr != r )
	{
		r->rot.x = 2.0;
		r->loc.y = 10.0;
		cout << r->g << endl;
	}
	else
	{
		cout << "not found" << endl;
	}

	r = space[{1.f, 10.f, 0.f}];

	if( nullptr != r )
	{
		cout << r->rot.x << endl;
	}
	else
	{
		cout << "not found" << endl;
	}



	return EXIT_SUCCESS;
}


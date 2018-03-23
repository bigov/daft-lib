#include <iostream>

using namespace std;

class Tst
{

	public:

	int n, m;

	int *p, *q;

	Tst(){
		n = 1;
		m = 2;

		p = new int(51);
		q = new int(53);
		return;
	}

	~Tst() {
		delete p;
		delete q;
	}

	inline int get_n(void){ return n;}
	inline int get_m(void){ return m;}

  inline int get_p(void){ return *p;}
	inline int get_q(void){ return *q;}

};


int main( int argc, char* argv[]) {
	cout << endl;

	Tst *t = new Tst;
	//t = Tst::Tst();

	cout << t->get_m() << endl;
	cout << t->m << endl;

	cout << t->get_p() << endl;
	cout << *t->p << endl;;

	*t->q = 648;
	cout << *t->q;


	delete t;

	cout << endl;
	return 0;
}

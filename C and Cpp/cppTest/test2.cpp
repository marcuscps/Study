#include <iostream>

using namespace std;


class C {
	int *i;
	int j;

public:
	bool CREATE() {
		cout << "C creator..." << endl;

		this->i = new (std::nothrow) int;
		if (this->i == NULL) {
			return false;
		}

		// ....
		//throw 1;
		// ...
		return false;

		return true;
	}

	C() : i(NULL) {
		cout << "C constructor..." << endl;
	}

	~C() {
		cout << "C destructor" << endl;
		if (i != NULL) {
			delete i;
		}
	}

	void method1() {
		cout << "C method 1 " << endl;
	}
};



int main() {
	{
		C c;
		if (!c.CREATE()) {
			cout << "Failed while creating C instance" << endl;
		}
	}


	C *c2 = NULL;
//	try {
		c2 = new (std::nothrow) C();
		if (c2 && !c2->CREATE()) {
			cout << "-- Failed while creating C instance" << endl;
			delete c2;
			c2 = 0;
		}
//	} catch (...) {
//		cout << "-- Caught an exception" << endl;
//	}

	if (c2 != NULL) {
		cout << "C2 is NOT NULL!" << endl;
		delete c2;
	} else {
		cout << "C2 is NULL!" << endl;
	}


	return 0;
}

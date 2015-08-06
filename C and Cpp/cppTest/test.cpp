#include <iostream>

using namespace std;

class Base {
public:
	Base() {
		cout << "  Called Base constructor" << endl;
	}

	virtual ~Base() {
		cout << "  Called Base destructor" << endl;
	}

	virtual void method1() {
		cout << "  Method1 from Base!" << endl;
	};
};

class Derived : public Base {
public:
	Derived() : Base() {
		cout << "  Called Derived constructor" << endl;
	}

	virtual ~Derived() {
		cout << "  Called Derived destructor" << endl;
	}

	void method1() {
		cout << "  Method1 from Derived!" << endl;
	}
};

class Derived2 : public Base {
public:
	Derived2() : Base() {
		cout << "  Called Derived2 constructor" << endl;
	}
	
	Derived2(int ii) : Base() {
		cout << "  Called Derived2 constructor (ii = " << ii << ")" << endl;
	}

	virtual ~Derived2() {
		cout << "  Called Derived2 destructor" << endl;
	}

	void method1() {
		cout << "  Method1 from Derived2!" << endl;
	}
};


class Base2 {
public:
	Base2() {
		cout << "  Called Base2 constructor" << endl;
	}

	virtual ~Base2() {
		cout << "  Called Base2 destructor" << endl;
	}

	virtual char method1() {
		cout << "  Method1 from Base2!" << endl;
		return 'a';
	};
};

template<typename T>
class SmartPtr1 {
	T *p;
	mutable int *c;

public:
	SmartPtr1(T *_p) : p(_p), c(new int (1)) {
		cout << "SmartPtr1 constructor" << endl;
	}


	SmartPtr1(const SmartPtr1 &x) : p(x.p), c(x.c) {
		++(*c);
		cout << "SmartPtr1 copy constructor" << endl;
	}

	void set(const SmartPtr1 &x) {
		cout << "SmartPtr1 destructor" << endl;
		if (--(*c) == 0 && p != NULL) {
			cout << "Destroying resource..." << endl;
			delete p;
			delete c;
		} else {
			cout << "NOT Destroying resource (someone else is still pointing to that." << endl;
		}

		p = x.p;
		c = x.c;
		++(*c);
	}

	~SmartPtr1() {
		cout << "SmartPtr1 destructor" << endl;
		if (--(*c) == 0) {
			cout << "Destroying resource..." << endl;
			delete p;
			delete c;
		} else {
			cout << "NOT Destroying resource (someone else is still pointing to that." << endl;
		}
	}

	T & operator*() {
		return *p;
	}

	T * operator->() {
		return p;
	}
};


template<typename T>
class Holder {
	SmartPtr1<T> p;
public:
	Holder() : p(NULL) {
	}

	~Holder() {
		cout << "Holder destructor" << endl;
	}

	void set(SmartPtr1<T> ptr) {
		p.set(ptr);
	}

	void method1() {
		p->method1();
	}
};


int main() {
	Base *bs[2];

	bs[0] = new Derived();
	bs[1] = new Derived2();

	for (int ii = 0; ii < 2; ++ii) {
		cout << "Calling method1 for " << ii << endl;
		bs[ii]->method1();
	}

	for (int ii = 0; ii < 2; ++ii) {
		cout << "Destroying object " << ii << endl;
		delete bs[ii];
	}

	cout << "Working with Base2..." << endl;
	auto p = new Base2();
	auto ret = p->method1();
	cout << "  Method1 return value = " << ret << endl;
	delete p;

	Holder<Derived2> h;

	cout << "Outside context..." << endl;
	{
		cout << "Entering context..." << endl;
		SmartPtr1<Derived2> d(new Derived2(10));
		h.set(d);

		{
			cout << "Entering context 2 ..." << endl;
			SmartPtr1<Derived2> d2 = d;
			d->method1();
			(*d).method1();
			cout << "Leaving context 2..." << endl;
		}
		cout << "Leaving context..." << endl;
	}
	cout << "Outside context..." << endl;

	h.method1();

	Holder<Derived> h2;

	cout << "-- Outside context..." << endl;
	{
		cout << "-- Entering context..." << endl;
		SmartPtr1<Derived> d(new Derived);
		h2.set(d);

		{
			cout << "-- Entering context 2 ..." << endl;
			SmartPtr1<Derived> d2 = d;
			d->method1();
			(*d).method1();
			cout << "-- Leaving context 2..." << endl;
		}
		cout << "-- Leaving context..." << endl;
	}
	cout << "-- Outside context..." << endl;

	h2.method1();

	return 0;
}

int x () {
	int ii;
	int *jj = new int;

}

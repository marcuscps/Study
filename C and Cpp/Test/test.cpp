#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class X {
	private:
		int x;

	public:

		X(int x) : x(x) {
			cout << "X constructor: " << this->x << " ..." << endl;
		}

		~X() {
			cout << "X destructor: " << this->x << " ..." << endl;
		}

		void Info() {
			cout << "X is in " << (void *)this;
			cout << ", x = " << this->x << endl;
		}

		int Get() {
			return x;
		}

		void Set(int x) {
			this->x = x;
		}
};


class Y {
	private:
		std::string x;

	public:

		Y(const std::string &x) : x(x) {
			cout << "Y constructor: " << this->x << " ..." << endl;
		}

		~Y() {
			cout << "Y destructor: " << this->x << " ..." << endl;
		}

		void Info() {
			cout << "X is in " << (void *)this;
			cout << ", x = " << this->x << endl;
		}

		std::string Get() {
			return x;
		}

		void Set(const std::string &x) {
			this->x = x;
		}
};


template<typename T> class Smart {
	public:
		typedef void (*CustomDeleter)(T *);
	
	protected:

		T *ptr;
		unsigned long *refCount;
		CustomDeleter customDeleter;

	public:
		Smart(T *ptr) :
			ptr(ptr),
			refCount(new unsigned long(1)),
			customDeleter(NULL)
		{
			cout << "SmartX constructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
		}

		Smart(T *ptr, CustomDeleter customDeleter) :
			ptr(ptr),
			refCount(new unsigned long(1)),
			customDeleter(customDeleter)
		{
			cout << "SmartX constructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
		}

		Smart(const Smart<T> &rhs) {
			this->ptr = rhs.ptr;
			this->refCount = rhs.refCount;
			this->customDeleter = rhs.customDeleter;
			this->IncRef();
			cout << "SmartX copy constructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
		}

		~Smart() {
			cout << "SmartX destructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
			this->DecRef();
		}

		void IncRef() {
			++(*refCount);
		}

		void DecRef() {
			if (--(*refCount) == 0) {
				if (this->customDeleter) {
					cout << "DecRef (CUSTOM DELETER): " << ptr->Get() << " ..." << endl;
					(*this->customDeleter)(this->ptr);
				} else {
					cout << "DecRef (DELETER): " << ptr->Get() << " ..." << endl;
					delete ptr;
				}
				delete refCount;
			} else {
				cout << "DecRef (SIMPLE): " << this->ptr->Get();
				cout << " - refCount " << *this->refCount << " ..." << endl;
			}
		}


		T& operator*() {
			cout << "SmartX dereferencing operator..." << endl;
			return *ptr;
		}

		T* operator->() {
			cout << "SmartX reference operator..." << endl;
			return ptr;
		}

		Smart<T>& operator=(const Smart<T> &rhs) {
			cout << "SmartX assign operator (ref)..." << endl;
			if (&rhs == this) {
				cout << "Same object!!! WARNING!!" << endl;
			} else {
				this->DecRef();
				this->ptr = rhs.ptr;
				refCount = rhs.refCount;
				this->IncRef();
				cout << "Different objects: value: " << this->ptr->Get();
				cout << " - refCount = " << *refCount << "..." << endl;
			}

			return *this;
		}

		unsigned long GetRefCounter() {
			return *this->refCount;
		}

};


class MyDeleter {
	public:
		void operator()(X* instance) const {
			cout << "Deleter operator..." << endl;
			delete instance;
		}
};

class MyFunctor {
	int value;

	public:
		MyFunctor(int value) : value(value) { }

		void operator()(X* instance) const {
			cout << "X is " << instance->Get() << " but will be " << instance->Get() + this->value << endl;
			instance->Set(instance->Get() + this->value);
		}
};


class EvenCounter {
	int counter;

	public:

		EvenCounter() : counter(0) {
		}

		void operator()(int value) {
			if (value % 2 == 0) {
				cout << value << " is even." << endl;
				++this->counter;
			} else {
				cout << value << " is odd." << endl;
			}
		}

		int Get() {
			return this->counter;
		}
};


void deleterFunc(X* instance) {
	cout << "Deleter function..." << endl;
	delete instance;
}


void x3func() {
	cout << "Creating x3..." << endl;
	Smart<X> x3(new X(3));

	if (x3->Get() == 3) {
		cout << "Accessing it (1)..." << endl;
		(*x3).Info();
		return;
	}

	cout << "Accessing it (2)..." << endl;
	x3->Info();
	return;
}


int main() {
	MyDeleter deleter;
	MyFunctor adder(220000);

	{
		cout << "-------------------------------------------- Creating x1..." << endl;
		X x1(1);
		x1.Info();
	}

	{
		cout << "-------------------------------------------- Creating x2..." << endl;
		X *x2 = new X(2);
		x2->Info();
		delete x2;
	}

	x3func();

	{
		cout << "-------------------------------------------- Vector example 1..." << endl;
		vector<X*> vec1;
		vec1.push_back(new X(4));
		vec1.push_back(new X(5));
		cout << "--------------------------------------------   Destroying all elements..." << endl;
		std::for_each(vec1.begin(), vec1.end(), adder);
		std::for_each(vec1.begin(), vec1.end(), deleter);
	}

	{
		cout << "-------------------------------------------- Vector example 2..." << endl;
		vector<Smart<X> > vec2;
		cout << "--------------------------------------------   Adding first element..." << endl;
		vec2.push_back(Smart<X>(new X(6)));
		cout << "--------------------------------------------   Adding second element..." << endl;
		vec2.push_back(Smart<X>(new X(7)));
		cout << "--------------------------------------------   Going out of context..." << endl;
	}

	{
		cout << "-------------------------------------------- Smart pointer example..." << endl;
		Smart<X> x8(new X(8));
		cout << "--------------------------------------------   Assigning..." << endl;
		x8 = x8;
		cout << "--------------------------------------------   Going out of context..." << endl;
	}

	{
		cout << "-------------------------------------------- Smart pointer example 2..." << endl;
		Smart<X> x9(new X(9));
		Smart<X> x10(new X(10));
		x9 = x10;
		cout << "--------------------------------------------   Reference counters..." << endl;
		cout << "x10 has " << x10.GetRefCounter() << endl;
		cout << "--------------------------------------------   Going out of context..." << endl;
	}

#if 0
	{
		cout << "-------------------------------------------- Smart pointer with Custom Deleter example 1..." << endl;
		Smart<X> x11(new X(11), deleterFunc);
		Smart<X> x12(new X(12), deleter);
		cout << "--------------------------------------------   Going out of context..." << endl;
	}
#endif

	X *x13 = new X(13);
	deleter(x13);

	{
		cout << "-------------------------------------------- Vector example with strings..." << endl;
		vector<Smart<Y> > vec2;
		cout << "--------------------------------------------   Adding first element..." << endl;
		vec2.push_back(Smart<Y>(new Y("Element1")));
		cout << "--------------------------------------------   Adding second element..." << endl;
		vec2.push_back(Smart<Y>(new Y("Element2")));
		cout << "--------------------------------------------   Going out of context..." << endl;
	}

	{
		vector<int> vec2;
		int begin = 0;
		int end = 100;
		for (int ii = begin; ii < end; ++ii) {
			vec2.push_back(ii);
		}
		EvenCounter evenC;
		std::for_each(vec2.begin(), vec2.end(), evenC);
		cout << "There is " << evenC.Get() << " even numbers from " << begin << " to " << endl << "." << endl;
	}


	return 0;
}


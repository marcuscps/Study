#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


namespace detail {
	class deleter_base {
	public:
		virtual ~deleter_base() { }
		virtual void dispose() = 0;
	};


	template<typename P>
	class deleter_p : public deleter_base {
	private:
		P *ptr;

	public:
		deleter_p(P *p) : ptr(p) {
			cout << "deleter_p constructor (1)..." << endl;
		}

		virtual void dispose() {
			cout << "Standard deleter (delete ptr)..." << endl;
			delete ptr;
		}
	};


	template<typename P, class D>
	class deleter_pd : public deleter_base {
	private:
		P *ptr;
		D del;

	public:
		deleter_pd(P *p) : ptr(p), del() {
			cout << "deleter_pd constructor (1)..." << endl;
		}

		deleter_pd(P *p, D & d ) : ptr(p), del(d) {
			cout << "deleter_pd constructor (2)..." << endl;
		}

		virtual void dispose() {
			cout << "Overrided deleter (del(ptr))..." << endl;
			del(ptr);
		}
	};
}


template<typename T> class Smart {
	protected:
		
		T* ptr;
		unsigned long* refCount;
		detail::deleter_base *deleter;

	public:

		template<typename U>
		Smart(U *ptr) :
			ptr(ptr),
			refCount(new unsigned long(1)),
			deleter(new detail::deleter_p<U>(ptr))
		{
			cout << "Smart constructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
		}


		template<typename U, class D>
		Smart(U* p, D d) :
			ptr(p),
			refCount(new unsigned long(1)),
			deleter(new detail::deleter_pd<U, D>(p, d))
		{
			cout << "Smart constructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
		}


		Smart(const Smart<T> &rhs) {
			this->ptr = rhs.ptr;
			this->refCount = rhs.refCount;
			this->deleter = rhs.deleter;
			this->IncRef();
			cout << "Smart copy constructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
		}

		~Smart() {
			cout << "Smart destructor: value: " << this->ptr->Get();
			cout << " - refCount = " << *this->refCount << "..." << endl;
			this->DecRef();
		}

		void IncRef() {
			++(*refCount);
		}

		void DecRef() {
			if (--(*refCount) == 0) {
				cout << "DecRef (ZERO REFS): " << this->ptr->Get() << " ..." << endl;
				this->deleter->dispose();
				delete this->refCount;
				delete this->deleter;
			} else {
				cout << "DecRef (SIMPLE): " << this->ptr->Get();
				cout << " - refCount " << *this->refCount << " ..." << endl;
			}
		}


		T& operator*() {
			cout << "Smart dereferencing operator..." << endl;
			return *ptr;
		}


		T* operator->() {
			cout << "Smart reference operator..." << endl;
			return ptr;
		}


		Smart<T>& operator=(const Smart<T> &rhs) {
			cout << "Smart assign operator (ref)..." << endl;
			if (&rhs == this) {
				cout << "Same object!!! WARNING!!" << endl;
			} else {
				this->DecRef();
				this->ptr = rhs.ptr;
				this->refCount = rhs.refCount;
				this->IncRef();
				this->deleter = rhs.deleter;
				cout << "Different objects: value: " << this->ptr->Get();
				cout << " - refCount = " << *refCount << "..." << endl;
			}

			return *this;
		}


		unsigned long GetRefCounter() {
			return *this->refCount;
		}

};


class X {
	private:
		int x;

	public:

		X(int x) : x(x) { cout << "X constructor: " << this->x << " ..." << endl; }

		~X() { cout << "X destructor: " << this->x << " ..." << endl; }

		void Info() { cout << "X is in " << (void *)this << ", x = " << this->x << endl; }

		int Get() { return x; }

		void Set(int x) { this->x = x; }
};


class Y {
	private:
		std::string x;

	public:

		Y(const std::string &x) : x(x) { cout << "Y constructor: \"" << this->x << "\" ..." << endl; }

		~Y() { cout << "Y destructor: \"" << this->x << "\" ..." << endl; }

		void Info() { cout << "X is in " << (void *)this << ", x = \"" << this->x << "\"" << endl; }

		std::string Get() { return x; }

		void Set(const std::string &x) { this->x = x; }
};


template<typename T>
class DeleterFunctor {
	public:
		void operator()(T* instance) const {
			cout << "Deleter operator..." << endl;
			delete instance;
		}
};


template<typename T>
void deleterFunc(T* instance) {
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


class XAdderFunctor {
	private:
		int m_AddValue;
	public:
		XAdderFunctor(int addValue) : m_AddValue(addValue) { }

		void operator()(X *instance) {
			cout << "Before: "; instance->Info();
			instance->Set(instance->Get() + m_AddValue);
			cout << "After:  "; instance->Info();
		}
};


class IsMultipleOfFunctor {
	private:
		int m_Base;
		int m_Tests;
		int m_Positives;

	public:
		IsMultipleOfFunctor(int base) : m_Base(base), m_Tests(0), m_Positives(0) { }

		bool operator()(int value) {
			++this->m_Tests;
			if (value % m_Base == 0) {
				++this->m_Positives;
				return true;
			}
			return false;
		}

		bool operator()(Smart<X> instance) {
			++this->m_Tests;
			if (instance->Get() % m_Base == 0) {
				++this->m_Positives;
				return true;
			}
			return false;
		}

		int GetBase() {
			return this->m_Base;
		}

		operator double() const {
			return this->m_Positives * 1.0 / this->m_Tests;
		}

		operator int() const {
			return this->m_Positives;
		}
};


int main() {
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
		DeleterFunctor<X> deleterX;
		XAdderFunctor adder(220000);
		vector<X*> vec1;
		vec1.push_back(new X(4));
		vec1.push_back(new X(5));
		cout << "--------------------------------------------   Adding to all elements..." << endl;
		std::for_each(vec1.begin(), vec1.end(), adder);
		cout << "--------------------------------------------   Destroying all elements..." << endl;
		std::for_each(vec1.begin(), vec1.end(), deleterX);
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

	{
		DeleterFunctor<X> deleterX;
		cout << "-------------------------------------------- Smart pointer with Custom Deleter example 1..." << endl;
		Smart<X> x11(new X(11), &deleterFunc<X>);
		Smart<X> x12(new X(12), deleterX);
		Smart<X> x13(new X(13));
		cout << "--------------------------------------------   Going out of context..." << endl;
	}

	{
		DeleterFunctor<Y> deleterY;
		cout << "-------------------------------------------- Smart pointer with Custom Deleter example 2..." << endl;
		Smart<Y> y1(new Y("1"), &deleterFunc<Y>);
		Smart<Y> y2(new Y("2"), deleterY);
		Smart<Y> y3(new Y("3"));
		cout << "--------------------------------------------   Going out of context..." << endl;
	}

	{
		cout << "-------------------------------------------- Calling deleter..." << endl;
		DeleterFunctor<X> deleterX;
		X *x14 = new X(14);
		deleterX(x14);
	}

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
		cout << "-------------------------------------------- Functor example with ints..." << endl;
		vector<int> vec2;
		int begin = 0;
		int end = 100;
		for (int ii = begin; ii < end; ++ii) {
			vec2.push_back(ii);
		}

		IsMultipleOfFunctor evenDetector(2);
		int numEvens = std::count_if(vec2.begin(), vec2.end(), evenDetector);
		cout << "There is " << numEvens << " even numbers from " << begin << " to " << end << "." << endl;

		IsMultipleOfFunctor m7Detector(7);
		int mult = std::count_if(vec2.begin(), vec2.end(), m7Detector);
		cout << "There is " << mult << " multiples of " << m7Detector.GetBase() << " numbers from " << begin << " to " << end << "." << endl;

		IsMultipleOfFunctor m9Detector(9);
		int    positives = std::for_each(vec2.begin(), vec2.end(), m9Detector);
		double ratio = std::for_each(vec2.begin(), vec2.end(), m9Detector);
		cout << "There is " << positives << " (" << ratio * 100 << "%%) of multiples of " << m9Detector.GetBase() << " numbers from " << begin << " to " << end << "." << endl;
	}

	{
		cout << "-------------------------------------------- Functor example with complex types..." << endl;
		vector<Smart<X> > vec2;
		int begin = 0;
		int end = 8;
		for (int ii = begin; ii < end; ++ii) {
			vec2.push_back(Smart<X>(new X(ii)));
		}

		IsMultipleOfFunctor evenDetector(2);
		int numEvens = std::count_if(vec2.begin(), vec2.end(), evenDetector);
		cout << "There is " << numEvens << " even numbers from " << begin << " to " << end << "." << endl;

		IsMultipleOfFunctor m7Detector(3);
		int mult = std::count_if(vec2.begin(), vec2.end(), m7Detector);
		cout << "There is " << mult << " multiples of " << m7Detector.GetBase() << " numbers from " << begin << " to " << end << "." << endl;

		IsMultipleOfFunctor m9Detector(9);
		int    positives = std::for_each(vec2.begin(), vec2.end(), m9Detector);
		double ratio = std::for_each(vec2.begin(), vec2.end(), m9Detector);
		cout << "There is " << positives << " (" << ratio * 100 << "%%) of multiples of " << m9Detector.GetBase() << " numbers from " << begin << " to " << end << "." << endl;
	}

	return 0;
}


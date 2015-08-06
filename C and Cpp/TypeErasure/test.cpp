#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class X {
	private:
		int x;
	public:
		X(int x) : x(x) { cout << "X constructor: " << x << endl; }

		~X() { cout << "X desstructor: " << x << endl; }

		int Get() { return x; }

		void Set(int val) { x = val; }
};


class Y {
	private:
		std::string x;
	public:
		Y(const std::string &x) : x(x) { cout << "Y constructor: \"" << x << "\"" << endl; }

		~Y() { cout << "Y destructor: \"" << this->x << "\" ..." << endl; }

		std::string Get() { return x; }

		void Set(const std::string &val) { x = val; }
};


class ActionBase {
	public:
		virtual ~ActionBase() { }
		virtual bool DoIt() = 0;
};


template<typename P>
class ActionP : public ActionBase {
	private:
		P *ptr;
	public:
		ActionP(P *p) : ptr(p) { }

		virtual bool DoIt() {
			cout << "Standard action (nothing to do)..." << endl;
			return true;
		}
};


template<typename P, class A>
class ActionPA : public ActionBase {
	private:
		P *ptr;
		A action;

	public:
		ActionPA(P *p, A & a ) : ptr(p), action(a) { }

		virtual bool DoIt() { return action(ptr); }
};


template<typename T> class Holder {
	private:
		Holder<T>& operator=(const Holder<T> &rhs);
		Holder(const Holder<T> &rhs);
	protected:
		T* ptr;
		ActionBase *action;
	public:
		template<typename U> Holder(U *ptr) : ptr(ptr), action(new ActionP<U>(ptr)) { }

		template<typename U, class A> Holder(U* p, A a) : ptr(p), action(new ActionPA<U, A>(p, a)) { }
		
		virtual ~Holder() { delete ptr; delete action; }


		bool DoAction() {
			return this->action->DoIt();
		}

};


template<typename T>
class ActionFunctor {
	public:
		bool operator()(T* instance) const {
			cout << "Action operator..." << endl;
			instance->Set(instance->Get() + instance->Get());
			return true;
		}
};


template<typename T>
bool ActionFunc(T* instance) {
	cout << "Action function..." << endl;
	instance->Set(instance->Get() + instance->Get() + instance->Get());
	return true;
}



int main() {
	{
		ActionFunctor<X> actionX;
		Holder<X> x1(new X(1), &ActionFunc<X>);
		Holder<X> x2(new X(10), actionX);
		Holder<X> x3(new X(100));
		x1.DoAction();
		x2.DoAction();
		x3.DoAction();
	}

	{
		ActionFunctor<Y> actionY;
		Holder<Y> y1(new Y("A"), &ActionFunc<Y>);
		Holder<Y> y2(new Y("BB"), actionY);
		Holder<Y> y3(new Y("CCC"));
		y1.DoAction();
		y2.DoAction();
		y3.DoAction();
	}

	return 0;
}


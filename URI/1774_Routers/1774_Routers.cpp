#include <iostream>
#include <cstdio>
#include <limits>
#include <vector>
#include <list>

#ifndef ONLINE_JUDGE
	#define DEBUG_ON
#endif
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
#else
	#define DEBUG_ST(x)
	#define DEBUG(...)
	#define ODEBUG(...)
	#define MDEBUG(...)
	#define OMDEBUG(...)
#endif

using namespace std;

//================================================================================================
template<class Iterator, class Manager>
void heapBackRefUp(Iterator begin, Iterator end, Iterator pos, Manager manager, bool test = false) {
	if (pos == begin) {
		return;
	}

	Iterator p = begin;
	advance(p, distance(begin, pos - 1) / 2);

	if (manager.before(*p, *pos) == test) {
		typename iterator_traits<Iterator>::value_type &a = *p;
		typename iterator_traits<Iterator>::value_type &b = *pos;
		swap(a, b);
		manager.swap_index(a, b);

		heapBackRefUp(begin, end, p, manager, test);
	}
}

template<class Iterator, class Manager>
void heapfyBackRef(Iterator begin, Iterator end, Iterator pos, Manager manager, bool test = false) {
	Iterator l = begin;
	advance(l, (distance(begin, pos) * 2) + 1);

	Iterator r = begin;
	advance(r, (distance(begin, pos) + 1) * 2);

	Iterator managerSel = pos;
	if (l < end && manager.before(*managerSel, *l) == test)
		managerSel = l;
	if (r < end && manager.before(*managerSel, *r) == test)
		managerSel = r;

	if (managerSel != pos) {
		typename iterator_traits<Iterator>::value_type &a = *pos;
		typename iterator_traits<Iterator>::value_type &b = *managerSel;
		swap(a, b);
		manager.swap_index(a, b);

		heapfyBackRef(begin, end, managerSel, manager, test);
	}
}

template<class Iterator, class Manager>
void buildBackRefHeap(Iterator begin, Iterator end, Manager manager) {
	Iterator ii = begin;
	advance(ii, distance(begin, end - 1) / 2);

	for (; ii >= begin; --ii)
		heapfyBackRef(begin, end, ii, manager);

	ii = begin;
	for (size_t idx = 0; ii != end; ++idx, ++ii) {
		typename iterator_traits<Iterator>::value_type &a = *ii;
		manager.set_index(a, idx);
	}
}

template<class Iterator, class Manager>
void upKeyBackRefHeap(Iterator begin, Iterator end, Iterator pos, Manager manager) {
	Iterator p = begin;
	advance(p, distance(begin, pos - 1) / 2);

	while (pos != begin && manager.before(*p, *pos) == false) {
		typename iterator_traits<Iterator>::value_type &a = *pos;
		typename iterator_traits<Iterator>::value_type &b = *p;
		swap(a, b);
		manager.swap_index(a, b);

		pos = p;
		p = begin;
		advance(p, distance(begin, pos - 1) / 2);
	}
}

//================================================================================================
template<class Queue, class Manager>
typename Queue::value_type pop_prio_queue(Queue &q, Manager manager) {
	typename Queue::iterator begin = q.begin();
	typename Queue::iterator end = q.end();

	typename Queue::value_type ret = *begin;
	if (distance(begin, end) > 1) {
		typename Queue::iterator last = end - 1;

		typename Queue::value_type &a = *begin;
		typename Queue::value_type &b = *last;
		swap(a, b);
		manager.swap_index(a, b);

		heapfyBackRef(begin, last, begin, manager);
	}

	manager.set_index(ret, -1);
	q.pop_back();
	return ret;
}

//================================================================================================
template<class Queue, class Manager>
void push_prio_queue(Queue &q, typename Queue::value_type &&value, Manager manager) {
	size_t index = q.size();
	manager.set_index(value, index);
	q.push_back(value);
	heapBackRefUp(q.begin(), q.end(), prev(q.end()), manager);
}

//================================================================================================
template<class Iterator, class OutputStream>
inline void printResult(Iterator a, Iterator b, OutputStream &output, const string &prefix) {
	cout << prefix;
	copy(a, b, output);
	cout << endl;
}

//================================================================================================
// Forward declaration
struct Router;

//================================================================================================
struct Cable {
	Router *to;
	int weigth;

	// Declared later.
	Cable(Router *from, Router *to, int weigth);

	~Cable() {
		ODEBUG("Deleted cable with weigth " << weigth << endl);
	}

};

//================================================================================================
struct Router {
	// Required by Back Ref Heap.
	int heapPos;

	int id;
	bool mark;
	list<Cable *> cables;

	Router *parent;
	int weigth;

	Router(int id) : heapPos(-1), id(id), mark(false), parent(nullptr), weigth(numeric_limits<int>::max()) {
		ODEBUG("New Router: " << id << endl);
	}

	~Router() {
		for (auto it = cables.begin(); it != cables.end(); ++it) {
			delete *it;
		}
		ODEBUG("Deleted router " << id << endl);
	}

	Cable * add_cable(Router *to, int weight) {
		Cable *cable = new Cable(this, to, weight);
		cables.push_back(cable);
		return cable;
	}

	friend ostream& operator<<(ostream& os, const Router& r) {
		os << r.id << "(" << r.weigth << " @ " << r.heapPos << ")";
		return os;
	}
};

//================================================================================================
struct RouterManager {
	bool before(const Router *a, const Router *b) {
		return a->weigth < b->weigth;
	}

	void swap_index(Router *a, Router *b) {
		swap(a->heapPos, b->heapPos);
	}

	void set_index(Router *a, size_t index) {
		a->heapPos = index;
	}
} routerManager;

//================================================================================================
Cable::Cable(Router *from, Router *to, int weigth) : to(to), weigth(weigth) {
	ODEBUG("New Cable: " << from->id << " -> " << to->id << " : " << weigth << endl);
}

//================================================================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int r, c, v, w, p, cost;
	vector <Router *> routers;
	vector<Router *> q;

	cin >> r >> c;
	ODEBUG("R = " << r << "  -  C = " << c << endl);

	// Creating routers
	for (int ii = 0; ii < r; ++ii) {
		routers.push_back(new Router(ii + 1));
		q.push_back(routers[ii]);
	}

	// Reading and creating cables
	for (int ii = 0; ii < c; ++ii) {
		cin >> v >> w >> p;
		routers[v - 1]->add_cable(routers[w - 1], p);
		routers[w - 1]->add_cable(routers[v - 1], p);
	}

	// Initializing Prim's queue
	cost = 0;
	routers[0]->weigth = 0;
	buildBackRefHeap(q.begin(), q.end(), routerManager);

	// Prim's loop
	while (q.empty() == false) {
		DEBUG_ST(ODEBUG("Queue:"); for (auto it = q.begin(); it != q.end(); ++it) OMDEBUG(" " << **it); OMDEBUG(endl));
		Router *current = pop_prio_queue(q, routerManager);
		current->mark = true;
		cost += current->weigth;
		ODEBUG("Current = " << current->id << "  -  weigth = " << current->weigth << "  -  cost = " << cost << endl);

		for (auto it = current->cables.begin(); it != current->cables.end(); ++it) {
			Cable *c = *it;
			Router *to = c->to;
			if (to->mark == false && c->weigth < to->weigth) {
				to->parent = current;
				to->weigth = c->weigth;
				ODEBUG("  MODIFIED: " << to->id << "  -  weigth = " << to->weigth << endl);

				auto pos = q.begin();
				advance(pos, to->heapPos);
				upKeyBackRefHeap(q.begin(), q.end(), pos, routerManager);
			}
		}
	}
	
	// Result.
	cout << cost << endl;

	// Tear down.
	for (auto it = routers.begin(); it != routers.end(); ++it) {
		delete *it;
	}
	
    return 0;
}


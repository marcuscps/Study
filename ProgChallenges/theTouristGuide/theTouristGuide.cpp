#include <iostream>
#include <cstdio>
#include <limits>
#include <vector>
#include <cmath>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

//================================================================================================
template<class Iterator, class Compare>
void heapfyBackRef(Iterator begin, Iterator end, Iterator pos, Compare pred, bool test = false) {
	Iterator l = begin;
	advance(l, (distance(begin, pos) * 2) + 1);

	Iterator r = begin;
	advance(r, (distance(begin, pos) + 1) * 2);

	Iterator predSel = pos;
	if (l < end && pred(*predSel, *l) == test)
		predSel = l;
	if (r < end && pred(*predSel, *r) == test)
		predSel = r;

	if (predSel != pos) {
		swap(*pos, *predSel);

		typename iterator_traits<Iterator>::value_type a = *pos;
		typename iterator_traits<Iterator>::value_type b = *predSel;
		swap(a->heapPos, b->heapPos);

		heapfyBackRef(begin, end, predSel, pred);
	}
}

template<class Iterator, class Compare>
void buildBackRefHeap(Iterator begin, Iterator end, Compare pred) {
	Iterator ii = begin;
	advance(ii, distance(begin, end - 1) / 2);

	for (; ii >= begin; --ii)
		heapfyBackRef(begin, end, ii, pred);
}


template<class Iterator, class Compare>
void upKeyBackRefHeap(Iterator begin, Iterator end, Iterator pos, Compare pred) {
	Iterator p = begin;
	advance(p, distance(begin, pos - 1) / 2);

	while (pos != begin && pred(*p, *pos) == false) {
		swap(*p, *pos);

		typename iterator_traits<Iterator>::value_type a = *pos;
		typename iterator_traits<Iterator>::value_type b = *p;
		swap(a->heapPos, b->heapPos);

		pos = p;
		p = begin;
		advance(p, distance(begin, pos - 1) / 2);
	}
}

//================================================================================================
template<class Iterator, class Compare>
typename iterator_traits<Iterator>::value_type pop_queue(Iterator begin, Iterator end, Compare pred) {
	typename iterator_traits<Iterator>::value_type ret = *begin;

	if (distance(begin, end) > 1) {
		Iterator last = end - 1;
		swap(*begin, *last);

		typename iterator_traits<Iterator>::value_type a = *begin;
		typename iterator_traits<Iterator>::value_type b = *last;
		swap(a->heapPos, b->heapPos);

		heapfyBackRef(begin, last, begin, pred);
	}

	ret->heapPos = -1;
	return ret;
}

//================================================================================================
struct City {
	// Required by Back Ref Heap.
	int heapPos;

	int id;
	int maxFlow;

	City() : heapPos(-1), id(0), maxFlow(numeric_limits<int>::min()) {
	}

	City(int id) : heapPos(-1), id(id), maxFlow(numeric_limits<int>::min()) {
	}
};

//================================================================================================
struct CityComparator {
	bool operator()(const City *a, const City *b) {
		return a->maxFlow > b->maxFlow;
	}
} comp;

//================================================================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	City *cities[100];
	int  roads[100][100];

	int v, e;
	scanf("%d %d", &v, &e);

	for (int ii = 0; ii < e; ++ii) {
		for (int jj = 0; jj < e; ++jj) {
			roads[ii][jj] = 0;
		}
	}

	for (int ii = 0; ii < v; ++ii) {
		cities[ii] = new City(ii);
	}

	for (int ii = 0; ii < e; ++ii) {
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);
		--x;
		--y;
		roads[x][y] = d;
		roads[y][x] = d;
	}

	int t = 1;
	int a, b, n;
	while (true) {
		scanf("%d %d %d", &a, &b, &n);
		if (a == 0 && b == 0) break;
		--a;
		--b;

		vector<bool> visited;
		visited.reserve(v);
		for (int ii = 0; ii < v; ++ii) {
			visited[ii] = false;
		}

		City *origin = cities[a];
		origin->maxFlow = numeric_limits<int>::max();

		vector<City *> q;
		q.push_back(origin);
		heapfyBackRef(q.begin(), q.end(), q.begin(), comp);

		while (q.empty() == false) {
			City *current = pop_queue(q.begin(), q.end(), comp);
			q.pop_back();
			visited[current->id] = true;

			for (int ii = 0; ii < v; ++ii) {
				if (roads[current->id][ii] != 0) {
					int roadFlow = roads[current->id][ii];
					City *target = cities[ii];
					if (visited[target->id] == true) continue;

					int flow = min(current->maxFlow, roadFlow);
					if (flow > target->maxFlow) {
						target->maxFlow = flow;
						vector<City *>::iterator pos;
						if (target->heapPos == -1) {
							target->heapPos = q.size();
							q.push_back(target);
							pos = q.end() - 1;
						} else {
							pos = q.begin();
							advance(pos, target->heapPos);
						}
						upKeyBackRefHeap(q.begin(), q.end(), pos, comp);
					}
				}
			}
		}

		int flow = cities[b]->maxFlow;
		int trips = ceil(1.0 * n / (flow - 1));

		printf("Scenario #%d\n", t++);
		printf("Minimum Number of Trips = %d\n\n", trips);
	}

    return 0;
}


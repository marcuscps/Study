#include <iostream>
#include <cstdio>
#include <list>
#include <map>
#include <string>
#include <limits>
#include <vector>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

struct City;

struct Route {
	City *dest;
	int dep;
	int dur;

	Route(City *dest, int dep, int dur);
};

struct City {
	string name;
	list<Route> routes;

	int travelTime;
	int currTime;

	int heapPos;

	City(const char *name) : name(name), travelTime(numeric_limits<int>::max()),
			currTime(numeric_limits<int>::max()), heapPos(-1) {
		DEBUG("New city created: \"%s\"\n", name);
	}

	void addRoute(City *dest, int dep, int dur) {
		DEBUG("  City: \"%s\": ", name.c_str());
		routes.push_back(Route(dest, dep, dur));
	}
};

Route::Route(City *dest, int dep, int dur) : dest(dest), dep(dep), dur(dur) {
#ifdef DEBUG_ON
	int arr = (dep + dur) % 24;
	DEBUG("New route to \"%s\": DEP: %d, DUR: %d, ARR: %d\n", dest->name.c_str(), dep, dur, arr);
#endif
}


typedef map<string, City *> Map;
typedef pair<string, City *> MapI;


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
struct CityComparator {
	bool operator()(const City *a, const City *b) {
		return(a->travelTime < b->travelTime);
	}
} comp;

//================================================================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t, n;
	char orig[33], dest[33];
	int dep, dur, arr;


	scanf("%d", &t);
	for (int tn = 1; tn <= t; ++tn) {
		Map cities;

		scanf("%d", &n);

		for (int ii = 0; ii < n; ++ii) {
			scanf("%s %s %d %d", orig, dest, &dep, &dur);
			arr = (dep + dur) % 24;
			if ((dep >= 6 && dep < 18) || (arr > 6 && arr < 18)) {
				DEBUG("Route from %s to %s, Dep: %d, Dur: %d, Arr: %d --> Ignored!\n",
						orig, dest, dep, dur, arr);
				continue;
			}
			if (dep <= 6 && arr >= 18) {
				DEBUG("Route from %s to %s, Dep: %d, Dur: %d, Arr: %d --> Ignored - DAY TRAVEL!\n",
						orig, dest, dep, dur, arr);
				continue;
			}

			Map::iterator o = cities.find(orig);
			City *ori;
			if (o == cities.end()) {
				ori = new City(orig);
				cities.insert(MapI(orig, ori));
			} else {
				ori = o->second;
			}

			Map::iterator d = cities.find(dest);
			City *de;
			if (d == cities.end()) {
				de = new City(dest);
				cities.insert(MapI(dest, de));
			} else {
				de = d->second;
			}

			ori->addRoute(de, dep, dur);
		}

		DEBUG("Searching for routes...\n");
		scanf("%s %s", orig, dest);

		printf("Test Case %d.\n", tn);
		Map::iterator o = cities.find(orig);
		Map::iterator d = cities.find(dest);
		if (o == cities.end() || d == cities.end()) {
			printf("There is no route Vladimir can take.\n");
			continue;
		}

		City *ori = o->second;
		City *de = d->second;

		DEBUG("Travel: \"%s\" --> \"%s\"\n", ori->name.c_str(), de->name.c_str());

		ori->travelTime = 0;
		ori->currTime = 18;
		vector<City *> q;
		q.push_back(ori);

		while (q.empty() == false) {
			City *current = pop_queue(q.begin(), q.end(), comp);
			q.pop_back();

			for (list<Route>::iterator ii = current->routes.begin(); ii != current->routes.end(); ++ii) {
				City *target = ii->dest;

				DEBUG("Trying route: \"%s\" : %d --> \"%s\" : %d  +%d\n",
						current->name.c_str(), current->currTime, target->name.c_str(), ii->dep, ii->dur);
				int dur = ii->dur;
				dur += (ii->dep - current->currTime);
				if (ii->dep < current->currTime) {
					dur += 24;
				}
				int tt = current->travelTime + dur;

				if (target->travelTime > tt) {
					target->travelTime = tt;
					target->currTime = (current->currTime + dur) % 24;

					vector<City *>::iterator pos;
					if (target->heapPos == -1) {
						target->heapPos = q.size();
						q.push_back(target);
						pos = q.end() - 1;
					} else {
						pos = q.begin();
						advance(pos, target->heapPos);
					}

					DEBUG("  Travel to \"%s\" updated to %d (arrive at %d)\n", 
							target->name.c_str(), target->travelTime, target->currTime);
					upKeyBackRefHeap(q.begin(), q.end(), pos, comp);
				}
			}
		}

		int dur = de->travelTime;
		DEBUG("Total travel time: %d\n", dur);
		printf("Vladimir needs %d litre(s) of blood.\n", dur / 24);

		for (Map::iterator ii = cities.begin(); ii != cities.end(); ++ii) {
			delete ii->second;
		}
		cities.clear();

	}

    return 0;
}

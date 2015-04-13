#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

//================================================================================================
template<class Iterator, class Compare>
void bubbleSort(Iterator begin, Iterator end, Compare pred) {
	for (Iterator ii = begin; ii != end - 1; ++ii)
		for (Iterator jj = ii + 1; jj != end; ++jj)
			if (pred(*ii, *jj) == false)
				swap(*ii, *jj);
}

//================================================================================================
template<class Iterator, class Compare>
void insertionSort(Iterator begin, Iterator end, Compare pred) {
	for (Iterator ii = begin + 1; ii != end; ++ii) {
		typename iterator_traits<Iterator>::value_type x = *ii;
		Iterator jj = ii;
		for (; jj != begin && pred(*(jj - 1), x) == false; --jj)
			*jj = *(jj - 1);
		*jj = x;
	}
}

//================================================================================================
template<class Iterator, class Compare>
void mergeSortMerge(Iterator begin, Iterator middle, Iterator end,
		typename iterator_traits<Iterator>::value_type *temp, Compare pred) {
	Iterator li = begin;
	Iterator ri = middle;

	size_t ii = 0;

	while (li != middle && ri != end)
		temp[ii++] = ((pred(*ri, *li) == false)) ? *(li++) : *(ri++);

	while (li != middle) temp[ii++] = *(li++);
	while (ri != end) temp[ii++] = *(ri++);

	for (ii = 0; begin != end; ++begin, ++ii) *begin = temp[ii];
}

template<class Iterator, class Compare>
void mergeSort(Iterator begin, Iterator end,
		typename iterator_traits<Iterator>::value_type *temp, Compare pred) {
	if (distance(begin, end) <= 1) return;

	Iterator middle = begin;
	advance(middle, distance(begin, end) / 2);

	mergeSort(begin, middle, temp, pred);
	mergeSort(middle, end, temp + distance(begin, middle), pred);
	mergeSortMerge(begin, middle, end, temp, pred);
}

template<class Iterator, class Compare>
void mergeSort(Iterator begin, Iterator end, Compare pred) {
	typename iterator_traits<Iterator>::value_type *temp =
		new typename iterator_traits<Iterator>::value_type[distance(begin, end)];
	mergeSort(begin, end, temp, pred);
	delete [] temp;
}

//================================================================================================
template<class Iterator, class Compare>
Iterator quickSortPartition(Iterator begin, Iterator end, Compare pred) {
	Iterator middle = begin;
	advance(middle, distance(begin, end) / 2);

	--end;
	swap(*end, *middle);

	typename iterator_traits<Iterator>::value_type p = *end;
	Iterator jj = begin - 1;
	for (Iterator ii = begin; ii != end; ++ii) {
		if (pred(p, *ii) == false) {
			++jj;
			swap(*ii, *jj);
		}
	}
	++jj;
	swap(*jj, *end);
	return jj;
}

template<class Iterator, class Compare>
void quickSort(Iterator begin, Iterator end, Compare pred) {
	if (distance(begin, end) <= 1) return;

	Iterator p = quickSortPartition(begin, end, pred);
	quickSort(begin, p, pred);
	quickSort(p + 1, end, pred);
}

//================================================================================================
template<class Iterator, class Compare>
Iterator quickSortPartitionRandomized(Iterator begin, Iterator end, Compare pred) {

	Iterator middle = begin;
	size_t pi = (rand() % distance(begin, end));
	advance(middle, pi);

	--end;
	swap(*end, *middle);

	typename iterator_traits<Iterator>::value_type p = *end;
	Iterator jj = begin - 1;
	for (Iterator ii = begin; ii != end; ++ii) {
		if (pred(p, *ii) == false) {
			++jj;
			swap(*ii, *jj);
		}
	}
	++jj;
	swap(*jj, *end);
	return jj;
}

template<class Iterator, class Compare>
void quickSortRandomized(Iterator begin, Iterator end, Compare pred) {
	if (distance(begin, end) <= 1) return;

	Iterator p = quickSortPartitionRandomized(begin, end, pred);
	quickSortRandomized(begin, p, pred);
	quickSortRandomized(p + 1, end, pred);
}

//================================================================================================
template<class Iterator, class Compare>
void heapfy(Iterator begin, Iterator end, Iterator pos, Compare pred, bool test) {
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
		heapfy(begin, end, predSel, pred, test);
	}
}

template<class Iterator, class Compare>
void buildHeap(Iterator begin, Iterator end, Compare pred, bool test) {
	Iterator ii = begin;
	advance(ii, distance(begin, end - 1) / 2);

	for (; ii >= begin; --ii)
		heapfy(begin, end, ii, pred, test);
}

template<class Iterator, class Compare>
void upKeyHeap(Iterator begin, Iterator end, Iterator pos, Compare pred) {
	Iterator p = begin;
	advance(p, distance(begin, pos - 1) / 2);

	while (pos != begin && pred(*p, *pos) == false) {
		swap(*p, *pos);
		pos = p;
		p = begin;
		advance(p, distance(begin, pos - 1) / 2);
	}
}

template<class Iterator, class Compare>
void heapSort(Iterator begin, Iterator end, Compare pred) {
	buildHeap(begin, end, pred, true);

	Iterator ii = end - 1;
	for (; ii >= begin; --ii) {
		swap(*ii, *begin);
		--end;
		heapfy(begin, end, begin, pred, true);
	}
}

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
struct MyObj {
private:
	size_t heapPos;
	int value;

public:
	friend struct MyObjManager;
	friend struct MyObjManager2;

	MyObj(int value) : value(value) {
	}

	friend ostream & operator<<(ostream &os, const MyObj &rhs) {
		os << rhs.value;
		return os;
	}

	friend ostream & operator<<(ostream &os, const MyObj *rhs) {
		os << rhs->value;
		return os;
	}
};

struct MyObjManager {
	bool before(const MyObj &a, const MyObj &b) {
		return a.value < b.value;
	}

	void swap_index(MyObj &a, MyObj &b) {
		swap(a.heapPos, b.heapPos);
	}

	void set_index(MyObj &a, size_t index) {
		a.heapPos = index;
	}

	bool before(const MyObj *a, const MyObj *b) {
		return a->value < b->value;
	}

	void swap_index(MyObj *a, MyObj *b) {
		swap(a->heapPos, b->heapPos);
	}

	void set_index(MyObj *a, size_t index) {
		a->heapPos = index;
	}
} myObjManager;

struct MyObjManager2 {
	bool before(const MyObj &a, const MyObj &b) {
		return b.value < a.value;
	}

	void swap_index(MyObj &a, MyObj &b) {
		swap(a.heapPos, b.heapPos);
	}

	void set_index(MyObj &a, size_t index) {
		a.heapPos = index;
	}

	bool before(const MyObj *a, const MyObj *b) {
		return b->value < a->value;
	}

	void swap_index(MyObj *a, MyObj *b) {
		swap(a->heapPos, b->heapPos);
	}

	void set_index(MyObj *a, size_t index) {
		a->heapPos = index;
	}
} myObjManager2;

//================================================================================================
int main() {
	int t, n;

	srand(time(NULL));

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);

		int *unsortedI = new int[n]();
		int *sortedI = new int[n]();
		ostream_iterator<int> intPrinter(cout, " ");

		for (int ii = 0; ii < n; ++ii) scanf("%d", &unsortedI[ii]);

		// System sort - Non decreasing
		copy(unsortedI, unsortedI + n, sortedI);
		sort(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "SS:   ");

		// Bubble sort - Non decreasing
		copy(unsortedI, unsortedI + n, sortedI);
		bubbleSort(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "BS:   ");

		// Insertion Sort - Non decreasing
		copy(unsortedI, unsortedI + n, sortedI);
		insertionSort(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "IS:   ");

		// Merge sort - Non decreasing
		copy(unsortedI, unsortedI + n, sortedI);
		mergeSort(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "MS:   ");

		// Quick sort - Non decreasing
		copy(unsortedI, unsortedI + n, sortedI);
		quickSort(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "QS:   ");

		// Quick sort - Randomized - Non decreasing
		copy(unsortedI, unsortedI + n, sortedI);
		quickSortRandomized(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "QSR:  ");

		// Heap sort - Non decreasing
 		copy(unsortedI, unsortedI + n, sortedI);
		heapSort(sortedI, sortedI + n, less<int>());
		printResult(sortedI, sortedI + n, intPrinter, "HS:   ");

		// Buble sort - Non increasing
		copy(unsortedI, unsortedI + n, sortedI);
		bubbleSort(sortedI, sortedI + n, greater<int>());
		printResult(sortedI, sortedI + n, intPrinter, "BSI:  ");

		// Insertion Sort - Non increasing
		copy(unsortedI, unsortedI + n, sortedI);
		insertionSort(sortedI, sortedI + n, greater<int>());
		printResult(sortedI, sortedI + n, intPrinter, "ISI:  ");

		// Merge sort - Non increasing
		copy(unsortedI, unsortedI + n, sortedI);
		mergeSort(sortedI, sortedI + n, greater<int>());
		printResult(sortedI, sortedI + n, intPrinter, "MSI:  ");

		// Quick sort - Non increasing
		copy(unsortedI, unsortedI + n, sortedI);
		quickSort(sortedI, sortedI + n, greater<int>());
		printResult(sortedI, sortedI + n, intPrinter, "QSI:  ");

		// Quick sort - Randomized - Non increasing
		copy(unsortedI, unsortedI + n, sortedI);
		quickSortRandomized(sortedI, sortedI + n, greater<int>());
		printResult(sortedI, sortedI + n, intPrinter, "QSRI: ");

		// Heap sort - Non increasing
 		copy(unsortedI, unsortedI + n, sortedI);
		heapSort(sortedI, sortedI + n, greater<int>());
		printResult(sortedI, sortedI + n, intPrinter, "HSI:  ");

		scanf("%d", &n);

		float *unsortedF = new float[n]();
		float *sortedF = new float[n]();
		ostream_iterator<float> floatPrinter(cout, " ");

        for (int ii = 0; ii < n; ++ii) scanf("%f", &unsortedF[ii]);

		// Bubble Sort - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		sort(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "SS:   ");

		// Bubble Sort - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		bubbleSort(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "BS:   ");

		// Insertion Sort - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		insertionSort(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "IS:   ");

		// Merge Sort - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		mergeSort(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "MS:   ");
	
		// Quick Sort - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		quickSort(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "QS:   ");

		// Quick Sort - Randomized - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		quickSortRandomized(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "QSR:  ");

		// Heap Sort - Non decreasing
		copy(unsortedF, unsortedF + n, sortedF);
		heapSort(sortedF, sortedF + n, less<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "HS:   ");

		// Bubble Sort - Non increasing
		copy(unsortedF, unsortedF + n, sortedF);
		bubbleSort(sortedF, sortedF + n, greater<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "BSI:  ");

		// Insertion Sort - Non increasing
		copy(unsortedF, unsortedF + n, sortedF);
		insertionSort(sortedF, sortedF + n, greater<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "ISI:  ");

		// Merge Sort - Non increasing
		copy(unsortedF, unsortedF + n, sortedF);
		mergeSort(sortedF, sortedF + n, greater<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "MSI:  ");

		// Quick Sort - Non increasing
		copy(unsortedF, unsortedF + n, sortedF);
		quickSort(sortedF, sortedF + n, greater<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "QSI:  ");

		// Quick Sort - Randomized - Non increasing
		copy(unsortedF, unsortedF + n, sortedF);
		quickSortRandomized(sortedF, sortedF + n, greater<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "QSRI: ");

		// Heap Sort - Non increasing
		copy(unsortedF, unsortedF + n, sortedF);
		heapSort(sortedF, sortedF + n, greater<float>());
		printResult(sortedF, sortedF + n, floatPrinter, "HSI:  ");

		delete [] sortedF;
		delete [] unsortedF;
	}

	ostream_iterator<MyObj> myObjPrinter(cout, " ");
	ostream_iterator<MyObj *> myObjPPrinter(cout, " ");

	{
		vector<MyObj> q;
		q.push_back(MyObj(5));
		q.push_back(MyObj(3));
		q.push_back(MyObj(4));
		q.push_back(MyObj(1));
		q.push_back(MyObj(2));

		buildBackRefHeap(q.begin(), q.end(), myObjManager);
		printResult(q.begin(), q.end(), myObjPrinter, "Increasing object priority queue: ");

		while (q.empty() == false) {
			MyObj obj = pop_prio_queue(q, myObjManager);
			cout << "Removed element: " << obj << endl;
		}
	}

	{
		vector<MyObj> q;
		for (int ii = 5; ii > 0; --ii) {
			push_prio_queue(q, MyObj(ii), myObjManager);
		}
		printResult(q.begin(), q.end(), myObjPrinter, "Increasing object priority queue: ");

		while (q.empty() == false) {
			MyObj obj = pop_prio_queue(q, myObjManager);
			cout << "Removed element: " << obj << endl;
		}
	}

	{
		vector<MyObj> q;
		q.push_back(MyObj(5));
		q.push_back(MyObj(3));
		q.push_back(MyObj(4));
		q.push_back(MyObj(1));
		q.push_back(MyObj(2));

		buildBackRefHeap(q.begin(), q.end(), myObjManager2);
		printResult(q.begin(), q.end(), myObjPrinter, "Decreasing object priority queue: ");

		while (q.empty() == false) {
			MyObj obj = pop_prio_queue(q, myObjManager2);
			cout << "Removed element: " << obj << endl;
		}
	}

	{
		vector<MyObj> q;
		for (int ii = 5; ii > 0; --ii) {
			push_prio_queue(q, MyObj(ii), myObjManager2);
		}
		printResult(q.begin(), q.end(), myObjPrinter, "Decreasing object priority queue: ");

		while (q.empty() == false) {
			MyObj obj = pop_prio_queue(q, myObjManager2);
			cout << "Removed element: " << obj << endl;
		}
	}

	{
		vector<MyObj *> q;
		q.push_back(new MyObj(5));
		q.push_back(new MyObj(3));
		q.push_back(new MyObj(4));
		q.push_back(new MyObj(1));
		q.push_back(new MyObj(2));

		buildBackRefHeap(q.begin(), q.end(), myObjManager);
		printResult(q.begin(), q.end(), myObjPPrinter, "Increasing pointer priority queue: ");

		while (q.empty() == false) {
			MyObj *obj = pop_prio_queue(q, myObjManager);
			cout << "Removed element: " << obj << endl;
			delete obj;
		}
	}

	{
		vector<MyObj *> q;
		for (int ii = 5; ii > 0; --ii) {
			push_prio_queue(q, new MyObj(ii), myObjManager);
		}
		printResult(q.begin(), q.end(), myObjPPrinter, "Increasing pointer priority queue: ");

		while (q.empty() == false) {
			MyObj *obj = pop_prio_queue(q, myObjManager);
			cout << "Removed element: " << obj << endl;
			delete obj;
		}
	}

	{
		vector<MyObj *> q;
		q.push_back(new MyObj(5));
		q.push_back(new MyObj(3));
		q.push_back(new MyObj(4));
		q.push_back(new MyObj(1));
		q.push_back(new MyObj(2));

		buildBackRefHeap(q.begin(), q.end(), myObjManager2);
		printResult(q.begin(), q.end(), myObjPPrinter, "Decreasing pointer priority queue: ");

		while (q.empty() == false) {
			MyObj *obj = pop_prio_queue(q, myObjManager2);
			cout << "Removed element: " << obj << endl;
			delete obj;
		}
	}

	{
		vector<MyObj *> q;
		for (int ii = 5; ii > 0; --ii) {
			push_prio_queue(q, new MyObj(ii), myObjManager2);
		}
		printResult(q.begin(), q.end(), myObjPPrinter, "Decreasing pointer priority queue: ");

		while (q.empty() == false) {
			MyObj *obj = pop_prio_queue(q, myObjManager2);
			cout << "Removed element: " << obj << endl;
			delete obj;
		}
	}

	return 0;
}

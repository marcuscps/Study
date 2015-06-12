#include <iostream>
#include <cstdio>

#ifndef ONLINE_JUDGE
//	#define DEBUG_ON
#endif
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __LINE__ << ": " << __VA_ARGS__
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

typedef char Type;

static const Type Unknown = 0, Income = 1, Expense = 2, Both = 3, Impossible = 4;

string TypeToString(Type t) {
	if ((t & Impossible)) return "Impossible";
	if ((t & Both) == Both) return "Both";
	if ((t & Income))  return "Income";
	if ((t & Expense)) return "Expense";
	return "Unknown";
}

size_t n;
int f;
int transactions[41], partialSum[41];
Type results[41];

bool doIt(size_t index, int acc) {
	ODEBUG("Index: " << index << " - acc: " << acc << "  -->  ");

	// base case
	if (index == 0) {
		OMDEBUG("Base case: " << acc << " == " << f << "  -->  " << ((acc == f) ? "TRUE" : "FALSE") << endl);
		return acc == f;
	}

	Type &result = results[index];

	int upperBound = acc + partialSum[index];
	int lowerBound = acc - partialSum[index];
	if (lowerBound > f || upperBound < f) {
		if (result == Unknown || result == Impossible) {
			result = Impossible;
			OMDEBUG(lowerBound << " <= " << f << " <= " << upperBound << "  FALSE  -->  IMPOSSIBLE." << endl);
		} else {
			OMDEBUG(lowerBound << " <= " << f << " <= " << upperBound << "  FALSE  -->  LEAVE IT: " << TypeToString(result) << endl);
		}
		return false;
	}

	OMDEBUG(lowerBound << " <= " << f << " <= " << upperBound << "  OK  -->  Recursive!" << endl);

	bool incomeOk  = doIt(index - 1, acc + transactions[index]);
	bool expenseOk = doIt(index - 1, acc - transactions[index]);

	if (incomeOk && expenseOk) {
		result = Both;
		ODEBUG("Index: " << index << " -->  Both" << endl);
	} else if (incomeOk) {
		result |= Income;
		result &= ~Impossible;
		ODEBUG("Index: " << index << " - IncomeOK  -->  " << TypeToString(result) << endl);
	} else if (expenseOk) {
		result |= Expense;
		result &= ~Impossible;
		ODEBUG("Index: " << index << " - ExpenseOK  -->  " << TypeToString(result) << endl);
	} else if (result == Unknown || (result & Impossible)) {
		result = Impossible;
		ODEBUG("Index: " << index << " -->  Impossible" << endl);
	}

	return incomeOk || expenseOk;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	transactions[0] = partialSum[0] = 0;

	while (true) {
		cin >> n >> f;
		if (n == 0 && f == 0) break;

		ODEBUG("N = " << n << "  -  F = " << f << endl);

		ODEBUG("Transactions:");
		// Read transactions and update the partial sum array.
		for (size_t ii = 1; ii <= n; ++ii) {
			cin >> transactions[ii];
			partialSum[ii] = partialSum[ii - 1] + transactions[ii];
			results[ii] = Unknown;
			OMDEBUG(" " << transactions[ii]);
		}
		OMDEBUG(endl);

		DEBUG_ST(ODEBUG("Partial Sum: "); for (size_t ii = 1; ii <= n; ++ii) OMDEBUG(" " << partialSum[ii]); OMDEBUG(endl));

		if (doIt(n, 0) == false) {
			cout << "*";
		} else {
			for (size_t ii = 1; ii <= n; ++ii) {
				Type &t = results[ii];
				if ((t & Both) == Both) cout << "?";
				else if ((t & Income))  cout << "+";
				else if ((t & Expense)) cout << "-";
				else cout << " ERROR " << ii << " ";
			}
		}
		cout << "\n";
		cout.flush();
	}

    return 0;
}


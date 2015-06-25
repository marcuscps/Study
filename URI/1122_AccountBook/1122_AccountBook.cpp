#include <iostream>
#include <cstdio>
#include <iomanip>

#ifndef ONLINE_JUDGE
	#define DEBUG_ON
#endif
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << setw(5) << setfill('0') << __LINE__ << ": " << __VA_ARGS__
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

#if 1
#define MAXT 41
#define MAXV 80001

int n;
int f;
int transactions[MAXT + 1];
bool dp1[MAXT][MAXV];
bool dp2[MAXT + 1][MAXV];
int maxv;

void doIt() {
	int zero = maxv;
	maxv <<= 1;

	for (int ii = 0; ii <= n; ++ii) {
		fill(dp1[ii], dp1[ii] + maxv, false);
		fill(dp2[ii], dp2[ii] + maxv, false);
	}

	dp1[0][zero] = true;
	for (int ii = 0; ii < n; ++ii) {
		int t = transactions[ii + 1];
		for (int vv = 0; vv <= maxv; ++vv) {
			if (dp1[ii][vv] == true) {
				dp1[ii + 1][vv + t] = true;
				dp1[ii + 1][vv - t] = true;
			}
		}
	}
	if (dp1[n][f + zero] == false) {
		cout << "*\n";
		return;
	}

	dp2[n + 1][f + zero] = true;
	for (int ii = n + 1; ii > 1; --ii) {
		int t = transactions[ii - 1];
		for (int vv = 0; vv <= maxv; ++vv) {
			if (dp2[ii][vv] == true) {
				if (vv + t < MAXV) dp2[ii - 1][vv + t] = true;
				if (vv - t >= 0)   dp2[ii - 1][vv - t] = true;
			}
		}
	}

	ODEBUG("TRAN   0");
	for (int ii = 1; ii <= n; ++ii) {
		OMDEBUG(" " << setw(3) << setfill(' ') << transactions[ii]);
	}
	OMDEBUG(endl);
	
	ODEBUG("POSSIBLE VALUES:" << endl);
	int gg = -zero;
	for (int vv = 0; vv <= maxv; ++vv) {
		ODEBUG(setw(4) << setfill(' ') << gg);

		for (int ii = 0; ii <= n; ++ii) {
			OMDEBUG(" " << setw(3) << setfill(' ') << (dp1[ii][vv] ? "X" : "-") );
		}
		
		OMDEBUG(endl);
		++gg;
	}

	ODEBUG("REACHABLE:" << endl);
	gg = -zero;
	for (int vv = 0; vv <= maxv; ++vv) {
		ODEBUG(setw(4) << setfill(' ') << gg);

		for (int ii = 0; ii <= n; ++ii) {
			OMDEBUG(" " << setw(3) << setfill(' ') << (dp2[ii][vv] ? "X" : "-") );
		}
		
		OMDEBUG(endl);
		++gg;
	}

	for (int ii = 1; ii <= n; ++ii) {
		bool neg = false;
		bool pos = false;

		int t = transactions[ii];
		for (int vv = 0; vv <= maxv; ++vv) {
			if (dp1[ii - 1][vv] == true) {
				int v = vv - t;
				if (v >= 0 && v <= maxv && dp2[ii][v] == true) {
					neg = true;
				}
				v = vv + t;
				if (v >= 0 && v <= maxv && dp2[ii][v] == true) {
					pos = true;
				}
			}
		}

		if (neg && pos) cout << "?";
		else if (pos)   cout << "+";
		else            cout << "-";
	}
	cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	transactions[0] = 0;

	while (true) {
		cin >> n >> f;
		if (n == 0 && f == 0) break;

		ODEBUG("N = " << n << "  -  F = " << f << endl);

		ODEBUG("Transactions:");
		maxv = 0;
		for (int ii = 1; ii <= n; ++ii) {
			cin >> transactions[ii];
			maxv += transactions[ii];
			OMDEBUG(" " << transactions[ii]);
		}
		OMDEBUG(endl);

		doIt();
		cout.flush();
	}

    return 0;
}


#else
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
#endif


#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

typedef std::map<unsigned int, unsigned long long> Memo;

Memo memo;

//=================================================================================================
unsigned int maxUSD(unsigned int v) {
	if (v == 0) {
		return 0;
	}

	Memo::iterator it = memo.find(v);
	if (it != memo.end()) { return it->second; }

	unsigned long long r = std::max(v, maxUSD(v/2) + maxUSD(v/3) + maxUSD(v/4));
	memo.insert(std::make_pair(v, r));
	return r;
}

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	unsigned int val;
	while (scanf("%u", &val) == 1) {
		printf("%u\n", maxUSD(val));
	}

	return 0;
}


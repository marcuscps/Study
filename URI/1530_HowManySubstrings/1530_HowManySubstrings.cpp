#include <iostream>
#include <cstdio>
#include <map>

#ifndef ONLINE_JUDGE
//	#define DEBUG_ON
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	string input;

	while (getline(cin, input)) {
		ODEBUG("Input: " << input << endl);
		map<string, bool> items;
		size_t count = 0;
		string word;

		for (size_t ii = 0; ii < input.size(); ++ii) {
			if (input[ii] == '?') {
				cout << count << endl;
				continue;
			}

			word.push_back(input[ii]);
			ODEBUG("Word: " << word << endl);
			for (size_t jj = 0; jj < word.size(); ++jj) {
				string l = word.substr(jj);
				if (items.find(l) == items.end()) {
					ODEBUG("New item: " << l << endl);
					++count;
					items[l] = true;
				}
			}
		}
	}

    return 0;
}


#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	string input;
	while (getline(cin, input)) {
		size_t ii = 0;
		while (ii < input.size() && input[ii] == ' ') {
			++ii;
		}

		if (ii >= input.size()) {
			cout << input << endl;
			continue;
		}
		
		char last = 'z';
		for (; ii < input.size(); ++ii) {
			if (input[ii] == ' ') continue;
			if (last >= 'a') {
				if (input[ii] >= 'a') input[ii] += 'A' - 'a';
			} else {
				if (input[ii] <= 'Z') input[ii] += 'a' - 'A';
			}
			last = input[ii];
		}

		cout << input << endl;
	}	

    return 0;
}


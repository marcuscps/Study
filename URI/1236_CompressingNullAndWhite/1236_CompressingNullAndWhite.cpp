#include <iostream>
#include <cstdio>

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

inline void genOut(string &output, char c, size_t size) {
#if 0
	// This solution is WRONG! But this is what the judge is expecting.
	// When the number of repetitions exceed 255. it should be #chr(255)0 instead of #chr(255)#1 for 256 0s.
	// Also, it should be #chr(255)00 instead of #chr(255)#chr(2) for 257 0s.
	char escapeChar = (c == ' ') ? '$' : c;
	escapeChar = (c == '0') ? '#' : escapeChar;
    if (escapeChar == c || size < 3) {
        output.resize(output.size() + size, c);
    } else {
		size_t chunkSize;
        while (size != 0) {
            chunkSize = (size > 255) ? 255 : size;
            output.push_back(escapeChar);
            output.push_back(static_cast<char>(chunkSize));
            size -= chunkSize;
        }
    }
#else
	char escapeChar = (c == ' ') ? '$' : c;
	escapeChar = (c == '0') ? '#' : escapeChar;

	if (escapeChar == c || size < 3) {
		output.resize(output.size() + size, c);
		return;
	}

	size_t chunkSize;
	while (size != 0) {
		chunkSize = (size > 255) ? 255 : size;
		if (chunkSize < 3) {
			output.resize(output.size() + chunkSize, c);
		} else {
			output.push_back(escapeChar);
			output.push_back(static_cast<char>(chunkSize));
		}
		size -= chunkSize;
	}
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	size_t pivot;
	string input, output;
	input.reserve(2010);
	output.reserve(2010);

	cin >> t;
	cin.ignore(1, '\n');
	while (t--) {
		getline(cin, input);
		output = "";
		pivot = 0;
		for (size_t ii = 1; ii < input.size(); ++ii) {
			if (input[ii] != input[pivot]) {
				genOut(output, input[pivot], ii - pivot);
				pivot = ii;
			}
		}
		genOut(output, input[pivot], input.size() - pivot);
		cout << output << endl;
	}
	
    return 0;
}


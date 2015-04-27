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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	bool isValid[] = {
		false, false, false, false, false, false, false, false,	false, false,
		false, false, false, false, false, false, false, false, false, true,
		true,  true,  true,  true,  true,  true,  true,  true,  true,  true,
		true,  true,  true,  true,  true,  true,  true,  true,  true,  true,
		true,  true,  true,  true,  true,  false, false, false, false, false,
		false, true,  true,  true,  true,  true,  true,  true,  true,  true,
		true,  true,  true,  true,  true,  true,  true,  true,  true,  true,
		true,  true,  true,  true,  true,  true,  true };

	std::string input;
	input.reserve(51);

	size_t counter, sum, avg;
	string::iterator lastIt, cend, it, auxit;
	bool isWord;
	ptrdiff_t size;

	while (getline(cin, input)) {
		// Add a space in the end to force analysing the last word.
		input.push_back(' ');

		counter = 0;
		sum = 0;
		lastIt = input.begin();
		for (it = input.begin(); it != input.end(); ++it) {
			if (*it == ' ') {
				size = distance(lastIt, it);
				if (size > 0) {
					auxit = prev(it);
					if (*auxit == '.') {
						cend = auxit;
						--size;
					} else {
						cend = it;
					}

					if (size > 0) {
						isWord = true;
						for (auxit = lastIt; auxit != cend; ++auxit) {
							if (isValid[static_cast<int>(*auxit - '.')] == false) {
								isWord = false;
								break;
							}
						}

						if (isWord) {
							sum += size;
							++counter;
						}
					}
				}

				lastIt = next(it);
			}
		}

		avg = 0;
		if (counter != 0) {
			avg = sum / counter;
		}

		if (avg <= 5) {
			if (avg <= 3) {
				cout << "250" << endl;
			} else {
				cout << "500" << endl;
			}
		} else {
			cout << "1000" << endl;
		}
	}

    return 0;
}


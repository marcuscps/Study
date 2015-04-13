#include <iostream>
#include <cstdio>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

class Problem {
private:
	bool solved;
	int score;

public:
	Problem() : solved(false), penalty(0) {
	}

	void addSubmission(int time, char status) {
		switch (status) {
		case 'C': solved = true; score += 10000 - time; break;
		case 'I': score -= 20; break;
		default: break;
		}
	}

	int getScore() {
		return solved ? score : 0;
	}
};

class Contestant {
private:
	int id;
	Problem *problems[100];
	int score;

public:
	Contestant(int id) : id(id), score(0) {
		for (int ii = 0; ii < 100; ++ii) {
			problems[ii] = NULL;
		}
	}

	void addProblemSubmission(int problem, int time, char status) {
		if (problems[problem] == NULL) {
			problems[problem] = new Problem(problem);
		}
		problems[problem]->addSubmission(time, status);
	}

	int calculateScore() {
		score = 0;
		for (int ii = 0; ii < 100; ++ii) {
			if (problems[ii] != NULL) {
				problems[ii].calculateScore();
				score += problems[ii].calculateScore();
			}
		}
		return score;
	}

	int getScore() {
		return score;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	scanf("%d", &t);
	while (t--) {

	}

    return 0;
}

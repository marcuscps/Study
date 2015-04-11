#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>

using namespace std;

struct BaseNode {
	virtual ~BaseNode() {
	}

	static const size_t DICT_SIZE = 26;
	static const size_t MAX_WORDS = 100;

	BaseNode() {
	}

	virtual void addWordHelper(string &word, size_t index) = 0;

	virtual int getMinCostHelper(size_t remaining, size_t level, bool &possible) = 0;
};

struct Sentinel : public BaseNode {
	Sentinel() : BaseNode() {
	}

	void addWordHelper(string &word, size_t index) {
	}

	int getMinCostHelper(size_t remaining, size_t level, bool &possible) {
		possible = remaining == 0;
		return 0;
	}
};

struct Node : public BaseNode {
	Node(BaseNode *leftSibling = nullptr) : BaseNode(), childCounter(0), lastChild(new Sentinel()), leftSibling(leftSibling) {
		initMe();
	}

	inline void addWord(string &word) {
		addWordHelper(word, 0);
	}

	inline int getMinCost(size_t n) {
		bool possible;
		return n * lastChild->getMinCostHelper(n, 1, possible);
	}

	void initMe() {
		fill(children, children + DICT_SIZE, nullptr);
		fill(dp, dp + MAX_WORDS + 1, -1);
	}

	void addWordHelper(string &word, size_t index) {
		if (index >= word.size()) {
			++childCounter;
			return;
		}

		++childCounter;
		BaseNode *&child = children[getKey(word[index])];
		if (child == nullptr) {
			child = new Node(lastChild);
			lastChild = child;
		}

		child->addWordHelper(word, index + 1);
	}
	
	int getMinCostHelper(size_t remaining, size_t level, bool &possible) {
		int &result = dp[remaining];
		if (result != -1) return result;

		result = 100000000;//numeric_limits<int>::max();
		for (size_t used = 0; used <= min(childCounter, remaining); ++used) {
			bool myPossible = true;
			int value = leftSibling->getMinCostHelper(remaining - used, level, myPossible);
			if (myPossible == false) continue;

			if (used == 1) value += level;
			if (childCounter - used == 1) value += level;

			if (childCounter > 1) {
				value += lastChild->getMinCostHelper(used, level + 1, possible);

				if (used == 1) value -= level + 1;
				if (childCounter - used == 1) value -= level + 1;
			}

			result = min(result, value);
		}

		possible = true;
		return result;
	}

	static inline size_t getKey(char c) { return c - 'A'; }

	BaseNode * children[DICT_SIZE];		// Child nodes (indexed by char: A-Z)
	size_t childCounter;				// The number of children added to this node.
	BaseNode * lastChild;				// Last inserted child
	BaseNode * leftSibling;				// Left sibling in the Trie
	int dp[MAX_WORDS + 1];				// Dynamic programming storage.
};


int main() {
	size_t n;
	string s;
	Node root;

	cin >> n;
	for (size_t ii = 0; ii < 2 * n; ++ii) {
		cin >> s;
		root.addWord(s);
	}
	cout << root.getMinCost(n) << endl;

    return 0;
}


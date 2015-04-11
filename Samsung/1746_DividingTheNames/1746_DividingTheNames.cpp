#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <memory>

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

class Sentinel;

//================================================================================================
class BaseNode {
public:
	// To allow calling Helpers from derived classes.
	friend class Node;

	virtual ~BaseNode() {
	}

protected:
	// Protected constructor to avoid instantiation.
	BaseNode(char c) : c(c) {
	}

	/**
	 * Helper for the addWord method.
	 */
	virtual void addWordHelper(const string &word, size_t index) = 0;

	/**
	 * Dynamic programming implementation.
	 */
	virtual int getMinCostHelper(size_t remaining, size_t level, bool &possible) const = 0;

protected:
	static const size_t DICT_SIZE    = 26;
	static const size_t MAX_WORD_LEN = 18;
	static const size_t MAX_WORDS    = 100;
	static const size_t SAFE_MAX     = 100000000;
//	static const size_t SAFE_MAX     = 2 * MAX_WORDS * MAX_WORD_LEN + 10000;
//	static const size_t SAFE_MAX     = numeric_limits<int>::max();

	char c;
};

//================================================================================================
/**
 * Sentinel node - Represented by #.
 * It is just a stack holder.
 */
class Sentinel : public BaseNode {
public:
	Sentinel() : BaseNode('#') { }

protected:
	void addWordHelper(const string &word, size_t index) {
		// does nothing.
	}

	int getMinCostHelper(size_t remaining, size_t level, bool &possible) const {
		possible = remaining == 0;
		ODEBUG("  LEVEL: " << level << " - SENTINEL: possible? " << (possible ? "YES" : "NO") << endl);
		return 0;
	}
} sentinel;

//================================================================================================
/**
 * Root and ordinary nodes.
 * It allocates all 26 slots for children (all nullptr).
 * It keeps a sentinel as the leftmost node, used during the Dynamic Programming phase.
 */
class Node : public BaseNode {
public:
	/**
	 * Constructor (Root is represented by +) - the only public available node.
	 */
	Node(char c = '+', BaseNode *leftSibling = nullptr) :
		BaseNode(c), childCounter(0), lastChild(&sentinel), leftSibling(leftSibling)
	{
		// Initialize all 26 slots for children
		fill(children, children + DICT_SIZE, nullptr);
		// Initialize all 26 slots for children
		fill(dp, dp + MAX_WORDS + 1, -1);
	}

	/**
	 * Destructor
	 */
	~Node() {
		ODEBUG("Deleting node: " << c << endl);
		for_each(children, children + DICT_SIZE, default_delete<BaseNode>());
	}

	inline void addWord(const string &word) {
		ODEBUG("Adding word " << word << " to ROOT!" << endl);
		// Insert the word into this node starting with the first char.
		addWordHelper(word, 0);
	}

	/**
	 * Get minimum cost of of streets and avenues attribution.
	 * It is only callable for the root node.
	 */
	inline int getMinCost(size_t n) const {
		ODEBUG("Getting minimal cost!" << endl);
		bool possible;
		return n * lastChild->getMinCostHelper(n, 1, possible);
	}

protected:

	/**
	 * Helper for the addWord method.
	 * The index only represents the current char to be added to this node.
	 */
	void addWordHelper(const string &word, size_t index) {
		++childCounter;
	
		// Base case: end of the word.
		if (index >= word.size()) {
			ODEBUG("  Adding " << c << " to node: " << c << "  -  # of children: " << childCounter << endl);
			return;
		}

		// Get the desired child or create it if not existing
		char cur = word[index];
		ODEBUG("  Adding " << cur << " to node: " << c << "  -  # of children: " << childCounter);
		BaseNode *&child = children[getKey(cur)];
		if (child == nullptr) {
			// Create the node and also updates it in the array (child is a reference).
			OMDEBUG("  -  New node!" << endl);
			child = new Node(cur, lastChild);
			lastChild = child;
		}
		DEBUG_ST(else OMDEBUG(endl));

		// Insert the rest of the word recursively.
		child->addWordHelper(word, index + 1);
	}
	
	/**
	 * Dynamic programming implementation.
	 */
	int getMinCostHelper(size_t remaining, size_t level, bool &possible) const {
		// Check for previous calculated values (Dynamic programming).
		int &result = dp[remaining];
		if (result != -1) return result;

		result = SAFE_MAX;

		// Any change this variable will affect the DP value also (it is a reference).
		// Try naming all possible number of streets. 0 is the minimum.
		// The maximum is limited by remaining streets to be named and the number of children for this node.
		for (size_t used = 0; used <= min(childCounter, remaining); ++used) {
			bool myPossible = true;
			int value = leftSibling->getMinCostHelper(remaining - used, level, myPossible);
			if (myPossible == false) continue;

			ODEBUG("  LEVEL: " << level << " - " << c << " - Trying " << used << endl);

			// If naming only one item to streets, the prefix is the current level (no recurssion needed here).
			if (used == 1) value += level;
			// If it remains only one, so it will name an avenue, the cost for the avenue is the level (analogous).
			if (childCounter - used == 1) value += level;

			if (childCounter > 1) {
				value += lastChild->getMinCostHelper(used, level + 1, possible);

				if (used == 1) value -= level + 1;
				if (childCounter - used == 1) value -= level + 1;
			}

			result = min(result, value);
			
			ODEBUG("  LEVEL: " << level << " - " << c << " - Trying " << used << " - RESULT = " << result << endl);
		}

		possible = true;
		return result;
	}

	static inline size_t getKey(char c) { return c - 'A'; }

private:

	BaseNode * children[DICT_SIZE];		// Child nodes (indexed by char: A-Z)
	size_t childCounter;				// The number of children added to this node.
	BaseNode * lastChild;				// Last inserted child
	BaseNode * leftSibling;				// Left sibling in the Trie
	mutable int dp[MAX_WORDS + 1];				// Dynamic programming storage.
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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


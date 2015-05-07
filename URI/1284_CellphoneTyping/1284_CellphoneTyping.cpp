#include <iostream>
#include <cstdio>
#include <iomanip>
#include <list>

using namespace std;

struct Node {
	Node *parent;
	size_t childrenc;
	bool word;
	Node *children[26];

	Node(Node *parent = nullptr) : parent(parent), childrenc(0), word(false) {
		for (size_t ii = 0; ii < 26; ++ii) {
			children[ii] = nullptr;
		}
	}

	~Node() {
		for (size_t ii = 0; ii < 26; ++ii) {
			if (children[ii] != nullptr) {
				delete children[ii];
			}
		}
	}

	Node * add(char c) {
		size_t index = static_cast<size_t>(c - 'a');
		if (children[index] == nullptr) {
			children[index] = new Node(this);
			++childrenc;
		}
		return children[index];
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	size_t n;
	string word;

	while (cin >> n) {
		Node root(nullptr);
		list<Node *> words;

		cin.ignore(1);

		for (size_t kk = 0; kk < n; ++kk) {
			getline(cin, word);

			Node *node = &root;
			for (size_t ii = 0; ii < word.size(); ++ii) {
				node = node->add(word[ii]);
			}
			node->word = true;
			words.push_back(node);
		}

		size_t total = 0;
		for (auto it = words.begin(); it != words.end(); ++it) {
			Node *node = *it;
			size_t cost = 0; 
			while (node->parent != nullptr) {
				if (node->word == true || node->childrenc > 1) {
					++cost;
				}
				node = node->parent;
			}
			total += cost;
		}
		cout << fixed << setprecision(2) << ((1.0f) * total / words.size()) << endl;
	}

    return 0;
}


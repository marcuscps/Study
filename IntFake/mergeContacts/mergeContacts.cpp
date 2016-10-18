#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <list>
#include <iterator>


/** 
 * Merge the contacts based on common emails:
 *
 * C1 -> a@fb.com, b@fb.com
 * C2 -> c@fb.com, d@fb.com,
 * C3 -> e@fb.com,
 * C4 -> a@fb.com, e@fb.com
 * C5 -> g@fb.com
 *
 * [ (c1, c4, c3), (c2), (c5) ]
 */


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


class Node {
public:
	string value;

protected:
    list<Node *> children;
	bool marked;

    Node(string value) : value(value), children(), marked(false) { }
	virtual ~Node() { }

public:
    void addChildren(Node *child) {
        children.push_back(child);
    }

    virtual void visit(vector<string> &result) {
        if (marked) return;
        marked = true;
        for (auto child : children) {
            child->visit(result);
        }
	}
};


class NodeEmail;

class NodeUser : public Node {
public:
    NodeUser(string userId) : Node(userId) { }
	~NodeUser() { }
    
    void addEmail(NodeEmail *email);
    
	virtual void visit(vector<string> &result) {
        if (!marked) result.push_back(value);
		Node::visit(result);
    }
};


class NodeEmail : public Node {
public:
    NodeEmail(string email) : Node(email) { }
	~NodeEmail() { }
	void addUser(NodeUser *user);
};


void NodeUser::addEmail(NodeEmail *email) {
	addChildren(email);
    email->addUser(this);
}
    
void NodeEmail::addUser(NodeUser *user) {
	addChildren(user);
}


typedef unordered_map<string, NodeEmail *> MyMap;
typedef vector<vector<string>> Result;


class Input {
public:
    string userId;
    list<string> emails;
	
	Input(string userId, list<string> emails) : userId(userId), emails(emails) { }
};


list<Node *> users;
MyMap emails;


void build_graph(vector<Input *> &inputs) {
    for (auto input : inputs) {
        NodeUser *nodeUser = new NodeUser(input->userId);

		for (auto email : input->emails) {
			NodeEmail *nodeEmail;
            auto email_it = emails.find(email);
            if (email_it == emails.end()) {
                emails[email] = nodeEmail = new NodeEmail(email);
            } else {
                nodeEmail = email_it->second;
            }
            nodeUser->addEmail(nodeEmail);
        }

		users.push_back(nodeUser);
    }
}


Result merge_contacts(vector<Input *> &inputs) {
    build_graph(inputs);
    
    Result result;
    for (auto user : users) {
        vector<string> items;                
		// Transverse DFS
        user->visit(items);
		// If result is not empty (UserNode not visited)
        if (!items.empty()) {
            result.push_back(items);
        }
    }
    return result;
}


template <typename T, class Op>
void print_items(T& items, const char* prefix, const char* sep, const char* suffix, Op op) {
	bool addSep = false;
	cout << prefix << " ";
	for (auto item : items) {
		if (addSep) cout << sep << " ";
		addSep = true;
		op(item);
	}
	cout << " " << suffix;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	while (true) {
		size_t t;
		cin >> t;
		if (t == 0) break;

		vector<Input *> inputs;
		inputs.reserve(t);
		while (t--) {
			string userId, email;
			list<string> emails;
			size_t nemails;

			cin >> userId >> nemails;
			while (nemails--) {
				cin >> email;
				emails.push_back(email);
			}
			inputs.push_back(new Input(userId, emails));
		}

		Result result = merge_contacts(inputs);
		print_items(result, "[", ",", "]", [](vector<string>& items) {
			print_items(items, "(", ",", ")", [](string& item) {
				cout << item;
			});
		});
		cout << endl;
	}
    return 0;
}


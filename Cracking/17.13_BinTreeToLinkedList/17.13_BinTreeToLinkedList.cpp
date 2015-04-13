#include <iostream>
#include <cstdio>

using namespace std;

class Node {
	private:
		int val;
		Node *p1;
		Node *p2;

	public:
		Node(int val) : val(val), p1(nullptr), p2(nullptr) { }

		void setP1(Node *p) { p1 = p; }
		void setP2(Node *p) { p2 = p; }

		int getValue() { return val; }
		Node * getP1() { return p1;  }
		Node * getP2() { return p2;  }
};

#if 0
pair<Node *, Node*> convertBinTreeToLinkedList(Node *node) {
	if (node == nullptr) return make_pair(nullptr, nullptr);

	auto leftTree = convertBinTreeToLinkedList(node->getP1());
	Node *leftTreeL = leftTree.first;
	Node *leftTreeR = leftTree.second;

	auto rightTree = convertBinTreeToLinkedList(node->getP2());
	Node *rightTreeL = rightTree.first;
	Node *rightTreeR = rightTree.second;

	// Merge node to the resulting list from the left child.
	node->setP1(leftTreeR);
	if (leftTreeR != nullptr) {
		leftTreeR->setP2(node);
	}

	// Merge node (and the left list) to the resulting list from the right child.
	if (rightTreeL != nullptr) {
		rightTreeL->setP1(node);
	}
	node->setP2(rightTreeL);

	// Return lest-most and right-most tree nodes.
	// In other words, the first and last nodes of the resulting list.
	Node *leftMost  = (leftTreeL  == nullptr) ? node : leftTreeL;
	Node *rightMost = (rightTreeR == nullptr) ? node : rightTreeR;
	return make_pair(leftMost, rightMost);
}

#else
struct Visitor {
	Node *first, *last;
	
	Visitor() : first(nullptr), last(nullptr) { }

	void operator()(Node *node) {
		if (last  == nullptr) first = node;
		else last->setP2(node);

		node->setP1(last);
		last = node;
	}
};

void convertBinTreeToLinkedList(Node *node, Visitor &visitor) {
	if (node == nullptr) return;
	convertBinTreeToLinkedList(node->getP1(), visitor);
	visitor(node);
	convertBinTreeToLinkedList(node->getP2(), visitor);
}

pair<Node *, Node*> convertBinTreeToLinkedList(Node *node) {
	Visitor visitor;
	convertBinTreeToLinkedList(node, visitor);
	return make_pair(visitor.first, visitor.last);
}
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	auto n0 = new Node(0), n1 = new Node(1), n2 = new Node(2), n3 = new Node(3), n4 = new Node(4);
	auto n5 = new Node(5), n6 = new Node(6), n7 = new Node(7), n8 = new Node(8);

	/*       4       */
	/*     /   \     */
	/*    2     6    */
	/*   / \   / \   */
	/*  0   3 5   8  */
	/*   \       /   */                                      
	/*    1     7    */

	n4->setP1(n2); n4->setP2(n6);
	n2->setP1(n0); n2->setP2(n3);
	n0->setP2(n1);
	n6->setP1(n5); n6->setP2(n8);
	n8->setP1(n7);

	auto result = convertBinTreeToLinkedList(n4);
	Node *first = result.first;
	Node *last = result.second;

	cout << "List --> :"; for (Node *p = first; p != nullptr; p = p->getP2()) cout << " " << p->getValue(); cout << endl;
	cout << "List <-- :"; for (Node *p = last;  p != nullptr; p = p->getP1()) cout << " " << p->getValue(); cout << endl;

    return 0;
}


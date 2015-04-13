#include <iostream>
#include <cstdio>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define EDEBUG(...)		std::cerr << "## " << __VA_ARGS__

	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
	#define EMDEBUG(...)	std::cerr << __VA_ARGS__
#else
	#define DEBUG(...)
	#define ODEBUG(...)
	#define EDEBUG(...)

	#define MDEBUG(...)
	#define OMDEBUG(...)
	#define EMDEBUG(...)
#endif

using namespace std;

struct Node {
    int value;
    Node* next;

	Node(int v) : value(v) { }
};

//  1 -> 2 -> 3 -> 5
//  ^--------------|

//  0 -> 1 -> 2 -> 3 -> 4 -> 5
//  ^------------------------|

//  1 -> 2 -> 3 -> 5
//  ^--------------|

void printList( Node *head ) {
	if (head == nullptr) {
		printf("\n");
		return;
	}

	Node *n = head;
	printf("%d", n->value);
	for (n = n->next; n != head; n = n->next) {
		printf(" %d", n->value);
	}
	printf("\n");
}

Node * insert( Node *head, int new_value) {
	Node *new_node = new Node(new_value);

    if (head == nullptr) {
		new_node->next = new_node;
		return new_node;
	}

	Node *node = head;
	Node *prev = nullptr;
	while (node->next != head && node->value < new_value) {
		prev = node;
		node = node->next;
	}

	new_node->next = node->next;
	if (node->value < new_value) {
		node->next = new_node;
		return head;
	}

	new_node->value = node->value;
	node->value = new_value;
	node->next = new_node;
	
	if (prev == nullptr) {
		head = node;
	}
	
	return head;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	Node *head = nullptr;

	head = insert(head, 1);
	head = insert(head, 2);
	head = insert(head, 5);

	printList(head);

	head = insert(head, 6);
	DEBUG("After inserting 6:\n");
	printList(head);

	head = insert(head, 4);
	DEBUG("After inserting 4:\n");
	printList(head);

	head = insert(head, 3);
	DEBUG("After inserting 3:\n");
	printList(head);

	head = insert(head, 0);
	DEBUG("After inserting 0:\n");
	printList(head);

    return 0;
}


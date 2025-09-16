#pragma once
template <typename t>
class List {
private:
	class Node {
		t data;
		Node* prev;
		Node* next;
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	void setupList() {
		Node* newNode = new Node();
		head = newNode;
		tail = newNode;
	};
	void deleteListContents() {
		Node* current = head;
		Node* temp = nullptr;
		while (current != nullptr) {
			temp = current.next;
			delete current;
			current = temp;
		};
	};
public:
	List() {
		setupList();
	};
	List(t newData) {
		setupList();
		head->data = newData;
	};
	List(List& rhs) {
		deleteListContents();
		head = rhs.head;
		tail = rhs.tail;
	};
	~List() {
		deleteListContents();
	};
	bool empty();
	void push_front(t data) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = head;
		newNode->prev = nullptr;
		head = newNode;
	};
	void push_back(t data) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = tail;
		tail = newNode;
	};
	t front() { return(head->data); };
	t back() { return(tail->data); };
	void pop_back() {
		Node* lastNode = tail;
		tail = tail.prev;
		tail.next = nullptr;
		delete lastNode;
	};
	void pop_front() {
		Node* firstNode = head;
		head = head.next;
		head.prev = nullptr;
		delete firstNode;
	};
	void traverse(void (*doIt)(t data)) {
		Node* currentNode = head;
		while (currentNode != tail) {
			doIt(data);
			currentNode = currentNode.tail;
		};
	};
	void printList() {
		Node* current = head;
		while (current != tail) {
			std::cout << current->data << "";
		};
		std::cout << std::endl;
	};
};
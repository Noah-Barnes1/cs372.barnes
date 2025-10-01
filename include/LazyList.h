#pragma once
#include <iostream>
template <typename T>
class List {
private:
	struct Node {
		T data; 
		Node* prev;
		Node* next;
		bool deleted;
		Node(const T& d): data(d), prev(nullptr), next(nullptr), deleted(false)
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	int activeCounter = 0;
	int deleteCounter = 0;
	void deleteListContents() {
		Node* current = head;
		while (current) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}
		head = tail = nullptr;
		activeCounter = deleteCounter = 0;
	}
	void copyFrom(const List& rhs) {
		for (Node* i = rhs.head; i; i = i->next) {
			if (!i->deleted) {
				push_back(i->data);
			}
		}
	}
	void cleanup() {
		Node* a = head;
		while (a) {
			Node* nextNode = a->next;
			if (a->deleted) {
				if (a->prev) {
					a->prev->next = a->next;
				}else {
					head = a->next;
				}
				if (a->next) {
					a->next->prev = a->prev;
				}else {
					tail = a->prev;
				}
				delete a;
			}
			a = nextNode;
		}
		deleteCounter = 0;
	}
	void maybeClean() {
		if (deleteCounter >= activeCounter) {
			cleanup();
		}
	}
public:
	List() = default;
	List(const T& newData) {
		push_back(newData);
	}
	List(const List& rhs) {
		copyFrom(rhs);
	}
	List& operator=(const List& rhs) {
		if (this != &rhs) {
			deleteListContents();
			copyFrom(rhs);
		};
		return *this;
	}
	~List() {
		deleteListContents();
	}
	bool empty() const { return activeCounter == 0; }
	void push_front(const T& data) {
		Node* newNode = new Node(data);
		newNode->next = head;
		if (head) {
			head->prev = newNode;
		}
		head = newNode;
		if (!tail) {
			tail = newNode;
		}
		activeCounter++;
	}
	void push_back(const T& data) {
		Node* newNode = new Node(data);
		newNode->prev = tail;
		if (tail) tail->next = newNode;
		tail = newNode;
		if (!head) head = newNode;
		activeCount++;
	}
	void pop_front() {
		Node* pf = head;
		while (pf && pf->deleted) pf = pf->next;
		if (!pf) return;
		pf->deleted = true;
		activeCount--;
		deletedCount++;
		maybeCleanup();
	}
	void pop_back() {
		Node* pb = tail;
		while (pb && pb->deleted) pb = pb->prev;
		if (!pb) return;
		bp->deleted = true;
		activeCount--;
		deletedCount++;
		maybeCleanup();
	}
	T front() const {
		Node* f = head;
		while (f && f->deleted) f = f->next;
		if (!f) throw std::runtime_error("List is empty");
		return f->data;
	}
	T back() const {
		Node* b = tail;
		while (b && b->deleted) b = b->prev;
		if (!b) throw std::runtime_error("List is empty");
		return b->data;
	}
	void traverse(void (*doIt)(T)) {
		for (Node* t = head; t; t = t->next) {
			if (!t->deleted) doIt(t->data);
		}
	}
	void printList() {
		for (Node* pl = head; pl; pl = pl->next) {
			if (!pl->deleted)
				std::cout << pl->data << " ";
		}
		std::cout << std::endl;
	}
}
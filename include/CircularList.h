#pragma once
#include <iostream>
#include "List.h"

template <typename T>
class CircularList : public List<T> {
private:
    using Node = typename List<T>::Node;  // reuse base Node

public:
    CircularList() : List<T>() {}

    // Override push_back to maintain circular links
    void push_back(T data) {
        Node* newNode = new Node();
        newNode->data = data;

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        };
        else {
            newNode->prev = this->tail;
            newNode->next = this->head;
            this->tail->next = newNode;
            this->head->prev = newNode;
            this->tail = newNode;
        };
    };

    // Override push_front to maintain circular links
    void push_front(T data) {
        Node* newNode = new Node();
        newNode->data = data;

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        };
        else {
            newNode->next = this->head;
            newNode->prev = this->tail;
            this->head->prev = newNode;
            this->tail->next = newNode;
            this->head = newNode;
        };
    };

    // Circular traversal: starts at given node index
    void traverse(void (*doIt)(T), int startIndex = 0) {
        if (this->head == nullptr) return;

        Node* current = this->head;
        // move to start index
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        };

        Node* startNode = current;
        do {
            doIt(current->data);
            current = current->next;
        } while (current != startNode);
    };

    // Debug print
    void printListOnce() {
        if (this->head == nullptr) return;
        Node* current = this->head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != this->head);
        std::cout << std::endl;
    };
};
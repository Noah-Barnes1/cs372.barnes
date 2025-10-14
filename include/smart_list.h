#pragma once
#include <iostream>
#include <memory>

template <typename T>
class List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next; 
        Node* prev = nullptr;        

        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    std::unique_ptr<Node> head;  
    Node* tail = nullptr;        

    void setupList() {
        head = nullptr;
        tail = nullptr;
    }

public:
    List() { setupList(); }
    explicit List(const T& newData) {
        push_back(newData);
    }
    List(const List& rhs) {
        for (Node* current = rhs.head.get(); current != nullptr; current = current->next.get()) {
            push_back(current->data);
        }
    }
    List(List&& rhs) noexcept = default;
    List& operator=(const List& rhs) {
        if (this != &rhs) {
            clear();
            for (Node* current = rhs.head.get(); current != nullptr; current = current->next.get()) {
                push_back(current->data);
            }
        }
        return *this;
    }
    List& operator=(List&& rhs) noexcept = default;
    ~List() { clear(); }
    bool empty() const { return head == nullptr; }

    void clear() {
        while (head) {
            head = std::move(head->next);
        }
        tail = nullptr;
    }
    void push_front(const T& data) {
        auto newNode = std::make_unique<Node>(data);
        if (head) {
            head->prev = newNode.get();
            newNode->next = std::move(head);
        }
        else {
            tail = newNode.get();
        }
        head = std::move(newNode);
    }
    void push_back(const T& data) {
        auto newNode = std::make_unique<Node>(data);
        newNode->prev = tail;
        if (tail) {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        else {
            head = std::move(newNode);
            tail = head.get();
        }
    }
    T& front() { return head->data; }
    const T& front() const { return head->data; }

    T& back() { return tail->data; }
    const T& back() const { return tail->data; }

    void pop_back() {
        if (!tail) return;
        if (tail->prev == nullptr) {
            head.reset();
            tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next.reset();
        }
    }
    void pop_front() {
        if (!head) return;
        if (!head->next) {
            head.reset();
            tail = nullptr;
        }
        else {
            head = std::move(head->next);
            head->prev = nullptr;
        }
    }
    void traverse(void (*doIt)(T data)) const {
        for (Node* current = head.get(); current != nullptr; current = current->next.get()) {
            doIt(current->data);
        }
    }
    void printList() const {
        for (Node* current = head.get(); current != nullptr; current = current->next.get()) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

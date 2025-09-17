#include <iostream>
#include <vector>
#include "CircularList.h"

template <typename T>
class JosephusSolver {
private:
    using Node = typename List<T>::Node;  // reuse base Node
public:
    static std::pair<std::vector<T>, T> solve(int N, int M) {
        CircularList<T> circle;
        // build the circle
        for (int i = 1; i <= N; i++) {
            circle.push_back(i);
        };
        std::vector<T> eliminated;
        Node* current = circle.head;
        // keep going until only one remains
        while (circle.head != circle.tail) {
            // move M steps
            for (int i = 0; i < M; i++) {
                current = current->next;
            };
            // eliminate current
            eliminated.push_back(current->data);
            Node* toDelete = current;
            // if removing head or tail, adjust
            if (toDelete == circle.head) circle.head = circle.head->next;
            if (toDelete == circle.tail) circle.tail = circle.tail->prev;
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            current = toDelete->next;
            delete toDelete;
            // if only one left, break
            if (circle.head == circle.tail) break;
        };
        T winner = circle.head->data;
        return { eliminated, winner };
    };
};

int main() {
    int N = 5, M = 1;
    auto result = JosephusSolver<int>::solve(N, M);
    std::cout << "Elimination order: ";
    for (auto x : result.first) {
        std::cout << x << " ";
    };
    std::cout << "\nWinner: " << result.second << std::endl;
    return 0;
};
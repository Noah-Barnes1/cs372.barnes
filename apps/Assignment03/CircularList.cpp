#include <iostream>
#include "CircularList.h"

static void printInt(int x) {
    std::cout << x << " ";
}

int main() {
    CircularList<int> cl;
    cl.push_back(10);
    cl.push_back(20);
    cl.push_back(30);
    cl.push_back(40);

    std::cout << "Print list once: ";
    cl.printListOnce();  // 10 20 30 40

    std::cout << "Traverse from start: ";
    cl.traverse(printInt);  // 10 20 30 40

    std::cout << "\nTraverse starting at index 2: ";
    cl.traverse(printInt, 2);  // 30 40 10 20

    std::cout << std::endl;
    return 0;
}

#pragma once
#include "Tree.h"
#include <queue>
#include <functional>
template<typename T>
void levelOrder(const Tree<T>& tree, std::function<void(T)> visit) {
    if (tree.isEmpty()) return;

    std::queue<Tree<T>> q;
    q.push(tree);

    while (!q.empty()) {
        Tree<T> current = q.front();
        q.pop();
        visit(current.root());
        if (!current.left().isEmpty())
            q.push(current.left());
        if (!current.right().isEmpty())
            q.push(current.right());
    }
}

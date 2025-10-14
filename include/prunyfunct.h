#pragma once
#include "Tree.h"
template <typename T>
Tree<T> pruny(const Tree<T>& tree) {
    if (tree.isEmpty()) {
        return Tree<T>();
    }
    if (tree.left().isEmpty() && tree.right().isEmpty()) {
        return Tree<T>();
    }
    Tree<T> prunedLeft = pruny(tree.left());
    Tree<T> prunedRight = pruny(tree.right());
    return Tree<T>(prunedLeft, tree.root(), prunedRight);
}

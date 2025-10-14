#pragma once
#include <memory>
#include <functional>
#include <cassert>
#include <initializer_list>
#include <iostream>

template<typename T>
class Tree {
private:
    struct Node : public std::enable_shared_from_this<Node> {
        std::shared_ptr<const Node> _lft;
        T _val;
        std::shared_ptr<const Node> _rgt;
        std::weak_ptr<const Node> _parent;

        Node(std::shared_ptr<const Node> lft, T val, std::shared_ptr<const Node> rgt,
            std::weak_ptr<const Node> parent = std::weak_ptr<const Node>())
            : _lft(std::move(lft)), _val(val), _rgt(std::move(rgt)), _parent(std::move(parent)) {
        }
    };

    std::shared_ptr<const Node> _root;

    explicit Tree(std::shared_ptr<const Node> node) : _root(std::move(node)) {}

public:
    Tree() : _root(nullptr) {}
    Tree(Tree const&) = default;
    Tree& operator=(Tree const&) = default;
    Tree(Tree&&) noexcept = default;
    Tree& operator=(Tree&&) noexcept = default;
    ~Tree() = default;

    Tree(Tree lft, T val, Tree rgt)
    {
        auto newNode = std::make_shared<Node>(lft._root, val, rgt._root);
        _root = newNode;
        if (lft._root) {
            const_cast<std::shared_ptr<Node>&>(
                reinterpret_cast<const std::shared_ptr<Node>&>(lft._root)
                )->_parent = _root;
        }
        if (rgt._root) {
            const_cast<std::shared_ptr<Node>&>(
                reinterpret_cast<const std::shared_ptr<Node>&>(rgt._root)
                )->_parent = _root;
        }
    }

    Tree(std::initializer_list<T> init) {
        Tree t;
        for (T v : init) {
            t = t.insert(v);
        }
        _root = t._root;
    }
    bool isEmpty() const { return !_root; }

    size_t size() const {
        if (isEmpty()) return 0;
        return 1 + left().size() + right().size();
    }

    T root() const {
        assert(!isEmpty());
        return _root->_val;
    }

    Tree left() const {
        assert(!isEmpty());
        return Tree(_root->_lft);
    }

    Tree right() const {
        assert(!isEmpty());
        return Tree(_root->_rgt);
    }
    Tree parent() const {
        if (isEmpty()) return Tree();
        auto parentPtr = _root->_parent.lock();
        return Tree(parentPtr);
    }
    template <typename Compare = std::greater<T>>
    Tree insert(T x, Compare comp = std::greater<T>()) const {
        if (isEmpty()) {
            return Tree(Tree(), x, Tree());
        }
        T y = root();
        if (comp(x, y)) {
            auto newLeft = left().insert(x, comp);
            return Tree(newLeft, y, right());
        }
        else if (comp(y, x)) {
            auto newRight = right().insert(x, comp);
            return Tree(left(), y, newRight);
        }
        else {
            return *this;
        }
    }
    template <typename Compare = std::greater<T>>
    bool member(T x, Compare comp = std::greater<T>()) const {
        if (isEmpty()) return false;
        T y = root();
        if (comp(x, y)) return left().member(x, comp);
        else if (comp(y, x)) return right().member(x, comp);
        else return true;
    }

    template<typename Compare = std::greater<T>>
    bool find(T x, Tree& subtreeWhereFound, Compare comp = std::greater<T>()) const {
        if (isEmpty()) {
            subtreeWhereFound = Tree();
            return false;
        }
        T y = root();
        if (comp(x, y)) return left().find(x, subtreeWhereFound, comp);
        else if (comp(y, x)) return right().find(x, subtreeWhereFound, comp);
        else {
            subtreeWhereFound = *this;
            return true;
        }
    }
    void preorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        visit(root());
        left().preorder(visit);
        right().preorder(visit);
    }

    void inorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().inorder(visit);
        visit(root());
        right().inorder(visit);
    }

    void postorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().postorder(visit);
        right().postorder(visit);
        visit(root());
    }
    friend std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
        if (tree.isEmpty()) {
            os << "[]";
            return os;
        }
        os << "[";
        tree.preorder([&os](T val) { os << val << " "; });
        os << "]";
        return os;
    }
};

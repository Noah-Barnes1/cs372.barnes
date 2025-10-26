#pragma once
#include <iostream>
#include "AVLTree.h"  
#include "Pair.h"     
#include <stdexcept>  
#include <vector>     

template <typename Key, typename Value>
class Dictionary {
private:
    AVLTree<Pair<Key, Value>> tree;
    size_t count = 0;
    bool findKey(const Key& key, Value& outValue) const {
        return findKeyRecursive(treeRoot(), key, outValue);
    }
    typename AVLTree<Pair<Key, Value>>::AVLNode* treeRoot() const {
        return tree.getRoot();
    }

    bool findKeyRecursive(auto* node, const Key& key, Value& outValue) const {
        if (!node) return false;
        if (key == node->key.first) {
            outValue = node->key.second;
            return true;
        }
        if (key < node->key.first)
            return findKeyRecursive(node->left, key, outValue);
        else
            return findKeyRecursive(node->right, key, outValue);
    }

public:
    Dictionary() = default;
    ~Dictionary() = default;
    Dictionary(const Dictionary&) = default;
    Dictionary(Dictionary&&) noexcept = default;
    Dictionary& operator=(const Dictionary&) = default;
    Dictionary& operator=(Dictionary&&) noexcept = default;

    bool isEmpty() const { return count == 0; }
    size_t size() const { return count; }

    void clear() {
        tree.~AVLTree();
        new(&tree) AVLTree<Pair<Key, Value>>();
        count = 0;
    }

    void insert(const Key& key, const Value& value) {
        Pair<Key, Value> p(key, value);
        tree.insert(p);
        count++;
    }

    void erase(const Key& key) {
        Pair<Key, Value> p(key, Value());
        tree.remove(p);
        if (count > 0) count--;
    }

    Value& operator[](const Key& key) {
        Value tmp;
        if (findKey(key, tmp)) {
            return at(key);
        }
        else {
            insert(key, Value());
            return at(key);
        }
    }

    Value& at(const Key& key) {
        auto* node = treeRoot();
        while (node) {
            if (key == node->key.first)
                return node->key.second;
            else if (key < node->key.first)
                node = node->left;
            else
                node = node->right;
        }
        throw std::out_of_range("Key not found in Dictionary");
    }

    const Value& at(const Key& key) const {
        auto* node = treeRoot();
        while (node) {
            if (key == node->key.first)
                return node->key.second;
            else if (key < node->key.first)
                node = node->left;
            else
                node = node->right;
        }
        throw std::out_of_range("Key not found in Dictionary");
    }

    std::vector<Key> keys() const {
        std::vector<Key> result;
        collectKeys(treeRoot(), result);
        return result;
    }

    std::vector<Value> values() const {
        std::vector<Value> result;
        collectValues(treeRoot(), result);
        return result;
    }

private:
    void collectKeys(auto* node, std::vector<Key>& result) const {
        if (!node) return;
        collectKeys(node->left, result);
        result.push_back(node->key.first);
        collectKeys(node->right, result);
    }

    void collectValues(auto* node, std::vector<Value>& result) const {
        if (!node) return;
        collectValues(node->left, result);
        result.push_back(node->key.second);
        collectValues(node->right, result);
    }
};

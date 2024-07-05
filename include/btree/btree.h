#pragma once

#include "./node.h"
#include <cstddef>

template<typename Key, size_t C = 2>
class BTree {
public:
    using Node = Node<Key, C>;
    static constexpr size_t MIN_CHILDREN = Node::MIN_CHILDREN;
    static constexpr size_t MAX_CHILDREN = Node::MAX_CHILDREN;
    static constexpr size_t MIN_KEYS = Node::MIN_KEYS;
    static constexpr size_t MAX_KEYS = Node::MAX_KEYS;

    void inspect() const;
    void insert(Key key);

private:
    void balance();
    Node root;
};

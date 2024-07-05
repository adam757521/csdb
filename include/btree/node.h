#pragma once

#include <cstddef>
#include <vector>

template<typename Key, size_t C>
class BTree;

template<typename Key, size_t C>
class Node {
public:
    friend class BTree<Key, C>;
    static constexpr size_t MIN_CHILDREN = C;
    static constexpr size_t MAX_CHILDREN = 2 * C;
    static constexpr size_t MIN_KEYS = C - 1;
    static constexpr size_t MAX_KEYS = 2 * C - 1;

private:
    void inspect(size_t depth);
    void insert_key(Key key);
    void balance_children();

};

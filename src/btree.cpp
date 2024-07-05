#include "btree/btree.h"

#include <cstddef>

template<typename Key, size_t C>
void BTree<Key, C>::insert(Key key) {
    this->root.insert_key(key);
}

template<typename Key, size_t C>
void BTree<Key, C>::balance() {
}

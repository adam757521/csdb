#include "btree/node.h"

#include <algorithm>

template<typename Key, size_t C>
void Node<Key, C>::insert_key(Key key) {
    typename decltype(this->keys)::const_iterator iter = std::lower_bound(this->keys.cbegin(), this->keys.cend(), key);
    if (*iter != key) {
        this->keys.insert(iter, key);
    }
}

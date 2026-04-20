#ifndef MULTISET_H_
#define MULTISET_H_

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

template <typename K>
class Multiset {
 public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size();
  // Returns true if multiset is empty --O(1)
  bool Empty();

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K& key);
  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K& key);

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K& key);
  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K& key);

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K& Floor(const K& key);
  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K& Ceil(const K& key);

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Max();
  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Min();

 private:
  int size = 0;

  struct Node {
    K key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    int occurences = 1;
  };
  std::unique_ptr<Node> root;

  // Useful recursive helper methods
  Node* Min(Node* n);
  void Insert(std::unique_ptr<Node>& n, const K& key);
  void Remove(std::unique_ptr<Node>& n, const K& key);
  void Print(Node* n, int level);
};

//
// Your implementation of the class should be located below
//

// * Capacity
// Returns number of items in multiset --O(1)
template <typename K>
size_t Multiset<K>::Size() {
  return size;
}
// Returns true if multiset is empty --O(1)
template <typename K>
bool Multiset<K>::Empty() {
  return size == 0;
}

// * Modifiers
// Inserts an item corresponding to @key in multiset --O(log N) on average
template <typename K>
void Multiset<K>::Insert(const K& key) {
  size++;
  Insert(root, key);
}

template <typename K>
void Multiset<K>::Insert(std::unique_ptr<Node>& n, const K& key) {
  if (!n)
    n = std::unique_ptr<Node>(new Node{key});
  else if (key < n->key)
    Insert(n->left, key);
  else if (key > n->key)
    Insert(n->right, key);
  else
    n.get()->occurences++;
}

// Removes an item corresponding to @key from multiset --O(log N) on average
//  Throws exception if key doesn't exist
template <typename K>
void Multiset<K>::Remove(const K& key) {
  size--;
  Remove(root, key);
}

template <typename K>
void Multiset<K>::Remove(std::unique_ptr<Node>& n, const K& key) {
  // Key not found
  if (!n) throw std::logic_error("key doesnt exist");

  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
    Remove(n->right, key);
  } else {
    // reduce occurences, skip if >0
    n->occurences--;

    if (n->occurences <= 0) {
      // remove the node
      if (n->left && n->right) {
        // Two children: replace with min node in right subtree
        Node* min = Min(n->right.get());
        n->key = min->key;
        n->occurences = min->occurences;
        min->occurences = 1;
        Remove(n->right, n->key);
      } else {
        // Replace with only child or with nullptr
        n = std::move((n->left) ? n->left : n->right);
      }
    }
  }
}

// * Lookup
// Return whether @key is found in multiset --O(log N) on average
template <typename K>
bool Multiset<K>::Contains(const K& key) {
  // skip if the tree is empty
  if (root == nullptr) return false;

  Node* parent = root.get();

  while (parent != nullptr) {
    if (key == parent->key) {
      return true;
    } else if (key < parent->key) {
      // less than parent? traverse left
      parent = parent->left.get();
    } else if (key > parent->key) {
      // greater than parent? traverse right
      parent = parent->right.get();
    } else {
      // key not found
      break;
    }
  }

  return false;
}
// Returns number of items matching @key in multiset --O(log N) on average
//  Throws exception if key doesn't exist
template <typename K>
size_t Multiset<K>::Count(const K& key) {
  Node* parent = root.get();

  while (parent != nullptr) {
    if (parent->key == key) {
      // node found
      return parent->occurences;
    } else if (key < parent->key) {
      parent = parent->left.get();
    } else {
      parent = parent->right.get();
    }
  }

  throw std::logic_error("node does not exist");
}

// Return greatest key less than or equal to @key --O(log N) on average
//  Throws exception if multiset is empty or no floor exists for key
template <typename K>
const K& Multiset<K>::Floor(const K& key) {
  if (!root) throw std::logic_error("multiset is empty");

  Node* node = root.get();
  Node* min = nullptr;

  while (node) {
    if (key == node->key) {
      return node->key;
    } else if (key < node->key) {
      node = node->left.get();
    } else {
      min = node;
      node = node->right.get();
    }
  }

  if (!min) throw std::logic_error("no floor found");
  return min->key;
}
// Return least key greater than or equal to @key --O(log N) on average
//  Throws exception if multiset is empty or no ceil exists for key
template <typename K>
const K& Multiset<K>::Ceil(const K& key) {
  Node* parent = root.get();
  Node* max = nullptr;

  while (parent) {
    if (key == parent->key) {
      return parent->key;
    } else if (key > parent->key) {
      parent = parent->right.get();
    } else {
      max = parent;
      parent = parent->left.get();
    }
  }

  if (!max) throw std::logic_error("no ceil found");
  return max->key;
}

// Return max key in multiset --O(log N) on average
//  Throws exception if multiset is empty
template <typename K>
const K& Multiset<K>::Max() {
  if (!root) throw std::logic_error("multiset is empty");

  Node* n = root.get();
  while (n->right) n = n->right.get();
  return n->key;
}

// Return min key in multiset --O(log N) on average
//  Throws exception if multiset is empty
template <typename K>
const K& Multiset<K>::Min() {
  if (!root) throw std::logic_error("multiset is empty");

  return Min(root.get())->key;
}

template <typename K>
typename Multiset<K>::Node* Multiset<K>::Min(Node* n) {
  if (n->left)
    return Min(n->left.get());
  else
    return n;
}

#endif
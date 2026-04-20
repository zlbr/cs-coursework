#ifndef CUCKOO_HASHING_H
#define CUCKOO_HASHING_H

#include <array>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename K>
class CuckooHashing {
 public:
  // Check if @key exists in one of the two hash tables
  bool Contains(const K& key);
  // Insert @key into any one of the hash tables
  void Insert(const K& key);
  // Remove @key from one of the tables if it exists
  void Remove(const K& key);
  // Print hashtable's contents
  void PrintTable();

 private:
  // TODO: Q 1.1 - Define Node structure to hold key and taken status
  struct Node {
    K key;
    bool taken;

    Node(const K& k) : key(k), taken(true) {}
    Node() : taken(false) {}
  };

  // TODO: Q 1.1 - Declare two hash tables with initial capacity
  // Initialize each table with init_capacity size
  // Initialize cur_size to 0
  size_t cur_size = 0;
  size_t cur_capacity = 37;
  std::vector<Node> table1 = std::vector<Node>(cur_capacity);
  std::vector<Node> table2 = std::vector<Node>(cur_capacity);

  // Hash function for first table
  size_t Hash1(const K& key);
  // Hash function for second table
  size_t Hash2(const K& key);

  // Resize to new capacity
  void Resize(size_t capacity);

  // Recursively insert @key to table @id (either 0 or 1)
  // TODO: Q 2.3 - Implement InsertRecur
  // Note: depth parameter is used to prevent infinite loops
  void InsertRecur(const K& key, size_t id, int depth = 0);

  Node* GetNode(const K& key);
};

// TODO: Q 1.2 - Implement Hash1
template <typename K>
size_t CuckooHashing<K>::Hash1(const K& key) {
  // Implement your first hash function here
  // Suggestion: h(k) = k mod size
  return key % cur_capacity;
}

// TODO: Q 1.2 - Implement Hash2
template <typename K>
size_t CuckooHashing<K>::Hash2(const K& key) {
  // Implement your second hash function here
  // Suggestion: h(k) = (k/size) mod size
  return (key / cur_capacity) % cur_capacity;
}

// TODO: Q 2.1 - Implement Contains
template <typename K>
bool CuckooHashing<K>::Contains(const K& key) {
  return GetNode(key) != nullptr;
}

// TODO: Q 2.3 - Implement InsertRecur
template <typename K>
void CuckooHashing<K>::InsertRecur(const K& key, size_t id, int depth) {
  // if depth exceeds 2 * table_size, resize
  if (size_t(depth) > 2 * cur_capacity) {
    Resize(cur_capacity * 2);
    InsertRecur(key, 1, 0);
    return;
  }

  // try to insert to the current table then recurse
  size_t index1 = Hash1(key);
  size_t index2 = Hash2(key);

  Node& n = (id == 1 ? table1 : table2).at(id == 1 ? index1 : index2);

  if (n.taken) {
    K removed = n.key;
    n.key = key;
    // bump the element at the index to the other table
    InsertRecur(removed, id == 1 ? 2 : 1, (int)(depth) + 1);
  } else {
    n.key = key;
    n.taken = true;
  }
}

// TODO: Q 2.2 - Implement Insert
template <typename K>
void CuckooHashing<K>::Insert(const K& key) {
  // skip if it's already in the table
  if (Contains(key)) {
    return;
  }

  InsertRecur(key, 1, 0);
  cur_size++;
}

// TODO: Q 2.4 - Implement Resize
template <typename K>
void CuckooHashing<K>::Resize(size_t capacity) {
  // copy & clear tables
  std::vector<Node> t1Copy = table1;
  std::vector<Node> t2Copy = table2;

  table1.clear();
  table2.clear();

  // Double the size of hashtables and rehash the entire collection
  table1.resize(capacity);
  table2.resize(capacity);
  cur_capacity = capacity;
  cur_size = 0;

  for (int id = 1; id <= 2; ++id) {
    for (Node n : id == 1 ? t1Copy : t2Copy) {
      // only insert taken (non-empty) nodes
      if (n.taken) Insert(n.key);
    }
  }
}

// TODO: Q 2.5 - Implement Remove
template <typename K>
void CuckooHashing<K>::Remove(const K& key) {
  // Find key and clear it from the table
  Node* n = GetNode(key);

  if (n != nullptr) {
    n->taken = false;
    cur_size--;
  }
}

template <typename K>
void CuckooHashing<K>::PrintTable() {
  for (int i = 0; i < 2; i++) {
    std::cout << "Hash table #" << i << std::endl;
    auto table = i == 0 ? table1 : table2;

    for (auto& k : table) {
      if (k.taken)
        std::cout << "[" << std::setfill('0') << std::setw(3) << k.key << "]";
      else
        std::cout << "[---]";
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename K>
typename CuckooHashing<K>::Node* CuckooHashing<K>::GetNode(const K& key) {
  // table 1 check
  Node* n = nullptr;
  try {
    n = &table1.at(Hash1(key));
    if (n->taken && n->key == key) return n;
  } catch (std::out_of_range&) {
    // intentionally empty branch (fall through)
  }

  // table 2 check
  try {
    n = &table2.at(Hash2(key));
    if (n->taken && n->key == key) return n;
  } catch (std::out_of_range&) {
    // intentionally empty branch (fall through)
  }

  return nullptr;
}

#endif

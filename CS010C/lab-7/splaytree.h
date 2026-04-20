#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include <iostream>
#include <stack>
#include <stdexcept>

template <typename K>
struct Node {
 public:
  K key;
  Node* left;
  Node* right;

  Node(K k) : key(k), left(nullptr), right(nullptr) {}
};

template <typename K>
class SplayTree {
 private:
  Node<K>* root = nullptr;

  // TODO: define internal data structure
  // helper methods
  Node<K>* Splay(Node<K>* node, const K& key);
  Node<K>* RotateRight(Node<K>* node);
  Node<K>* RotateLeft(Node<K>* node);
  void RecursivePrint(Node<K>* node, int level);
  void RecursiveInsert(Node<K>*& n, const K& key);
  void clear();

 public:
  // public API
  bool Contains(const K& key);
  void Insert(const K& key);
  void Print();

  // implement rule of three
  SplayTree();
  ~SplayTree();
  SplayTree(const SplayTree<K>& other);

  SplayTree<K>& operator=(const SplayTree<K>& other) {
    if (this == &other) return *this;

    this->clear();

    if (other.root == nullptr) return *this;

    // the stack holds nodes to be processed
    std::stack<Node<K>*> stack;
    stack.push(other.root);

    while (!stack.empty()) {
      Node<K>* top = stack.top();
      stack.pop();
      if (top->right != nullptr) stack.push(top->right);
      if (top->left != nullptr) stack.push(top->left);

      Insert(top->key);
    }

    return *this;
  }
};

template <typename K>
SplayTree<K>::SplayTree() : root(nullptr) {}

template <typename K>
SplayTree<K>::~SplayTree() {
  clear();
}

template <typename K>
void SplayTree<K>::clear() {
  if (root == nullptr) return;

  // the stack holds nodes to be processed
  std::stack<Node<K>*> stack;
  stack.push(root);

  while (!stack.empty()) {
    Node<K>* top = stack.top();
    stack.pop();
    if (top->right != nullptr) stack.push(top->right);
    if (top->left != nullptr) stack.push(top->left);

    delete top;
  }

  root = nullptr;
}

template <typename K>
SplayTree<K>::SplayTree(const SplayTree<K>& other) : root(nullptr) {
  if (other.root == nullptr) return;

  // the stack holds nodes to be processed
  std::stack<Node<K>*> stack;
  stack.push(other.root);

  while (!stack.empty()) {
    Node<K>* top = stack.top();
    stack.pop();
    if (top->right != nullptr) stack.push(top->right);
    if (top->left != nullptr) stack.push(top->left);

    Insert(top->key);
  }
}

template <typename K>
Node<K>* SplayTree<K>::Splay(Node<K>* node, const K& key) {
  if (node == nullptr || node->key == key) {
    return node;
  }

  // search key is less than current key, so it's to the left
  if (key < node->key) {
    // left tree is empty
    if (!node->left) return node;

    // left-left: recursively splay the left-left then rotate grandparent
    // right
    if (node->left->key > key) {
      node->left->left = this->Splay(node->left->left, key);
      node = this->RotateRight(node);
    } else if (node->left->key < key) {  // left-right: recursively splay the
                                         // left-right then rotate
                                         // grandparent left
      node->left->right = this->Splay(node->left->right, key);
      if (node->left->right) node->left = this->RotateLeft(node->left);
      // node = this->RotateLeft(node);
    }

    if (node->left == nullptr)
      return node;
    else
      return RotateRight(node);

  } else if (key > node->key) {  // right subtree
    // right subtree is empty
    if (!node->right) return node;

    // right-right: recursively splay the right-right then rotate grandparent
    // right
    if (node->right->key < key) {
      node->right->right = this->Splay(node->right->right, key);
      node = this->RotateLeft(node);
    } else if (node->right->key > key) {  // right-left: recursively splay the
                                          // right-left then rotate
                                          // grandparent left
      node->right->left = this->Splay(node->right->left, key);
      if (node->right->left) node->right = this->RotateRight(node->right);
    }

    if (node->right == nullptr) return node;
    // else if (node->right->left)
    //   node->right = this->RotateRight(node->right);
    return RotateLeft(node);
  }

  return node;
}

template <typename K>
Node<K>* SplayTree<K>::RotateRight(Node<K>* node) {
  Node<K>* other = node->left;
  node->left = other->right;
  other->right = node;
  return other;
}

template <typename K>
Node<K>* SplayTree<K>::RotateLeft(Node<K>* node) {
  Node<K>* other = node->right;
  node->right = other->left;
  other->left = node;
  return other;
}

// TODO: Implement the Contains method
template <typename K>
bool SplayTree<K>::Contains(const K& key) {
  root = Splay(root, key);

  return (root != nullptr && root->key == key);
}

// TODO: Implement the Insert method (public version)
template <typename K>
void SplayTree<K>::Insert(const K& key) {
  RecursiveInsert(root, key);
  root = this->Splay(root, key);
}

template <typename K>
void SplayTree<K>::RecursiveInsert(Node<K>*& n, const K& key) {
  if (n == nullptr) {
    n = new Node<K>(key);
  } else if (key < n->key) {
    RecursiveInsert(n->left, key);
  } else if (key > n->key) {
    RecursiveInsert(n->right, key);
  } else {
    throw std::logic_error("Splay tree already contains node");
  }
}

// TODO: Implement the Print method
// This should print an in-order traversal of the tree
// in this format: "key1 (level), key2 (level), ..."
// You may use this code: std::cout << key << " (" << level << "), ";
template <typename K>
void SplayTree<K>::Print() {
  RecursivePrint(root, 0);
  return;
}

template <typename K>
void SplayTree<K>::RecursivePrint(Node<K>* node, int level) {
  if (node == nullptr) return;

  RecursivePrint(node->left, level + 1);
  std::cout << node->key << " (" << level << "), ";
  RecursivePrint(node->right, level + 1);
}

// TODO: Q2.1 What are the different **splay rotation cases** that must be
// considered? Your answer: We must handle double left/right
// (zig-zig/zag-zag), or either left-right or right-left mixed rotztions
// (zig-zag)

// TODO: Q2.2 Implement RotateLeft and RotateRight

// TODO: Q2.3 Implement Splay

#endif  // SPLAYTREE_H_

#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <utility>

template <typename K>
class BST {
 public:
  // Return whether @key is found in tree
  bool Contains(const K& key);
  // Return max key in tree
  const K& Max();
  // Return min key in tree
  const K& Min();
  // Insert @key in tree
  void Insert(const K& key);
  // Remove @key from tree
  void Remove(const K& key);
  // Print tree in-order
  void Print();
  // Lowest common ancestor
  const K& LCA(const K& key1, const K& key2);
  // Check if tree is BST
  bool CheckBST();

 private:
  struct Node {
    K key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
  std::unique_ptr<Node> root;

  // Useful recursive helper methods
  Node* Min(Node* n);
  void Insert(std::unique_ptr<Node>& n, const K& key);
  void Remove(std::unique_ptr<Node>& n, const K& key);
  void Print(Node* n, int level);
};

// Comtains checks if @key is included in the tree
template <typename K>
bool BST<K>::Contains(const K& key) {
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

// LCA finds the least common ancestor of @key1 and @key2, returning its pointer
template <typename K>
const K& BST<K>::LCA(const K& key1, const K& key2) {
  // skip if the tree is empty
  if (root == nullptr)
    throw std::runtime_error("LCA cannot be used on empty tree");

  Node* lca = root.get();

  while (lca != nullptr) {
    if (key1 < lca->key && key2 < lca->key) {
      // both keys less than lca? new lca is on left
      lca = lca->left.get();
    } else if (key1 > lca->key && key2 > lca->key) {
      // both keys greater than lca? new lca is on right
      lca = lca->right.get();
    } else {
      // base case: the nodes are on either side of the lca, or the lca is equal
      // to one of them
      break;
    }
  }

  return lca->key;
}

// TODO: Q2.3
template <typename K>
bool BST<K>::CheckBST() {
  // skip if the tree is empty
  if (root == nullptr) return true;

  std::stack<Node*> stack;
  stack.push(root.get());
  while (!stack.empty()) {
    Node* top = stack.top();
    stack.pop();

    if (top->right != nullptr) {
      // right node must be greater than its parent
      if (top->right->key < top->key) return false;
      stack.push(top->right.get());
    }

    if (top->left != nullptr) {
      // left node must be less than its parent
      if (top->left->key > top->key) return false;
      stack.push(top->left.get());
    }
  }

  return true;
}

template <typename K>
const K& BST<K>::Max(void) {
  Node* n = root.get();
  while (n->right) n = n->right.get();
  return n->key;
}

template <typename K>
const K& BST<K>::Min(void) {
  return Min(root.get())->key;
}

template <typename K>
typename BST<K>::Node* BST<K>::Min(Node* n) {
  if (n->left)
    return Min(n->left.get());
  else
    return n;
}

template <typename K>
void BST<K>::Insert(const K& key) {
  Insert(root, key);
}

template <typename K>
void BST<K>::Insert(std::unique_ptr<Node>& n, const K& key) {
  if (!n)
    n = std::unique_ptr<Node>(new Node{key});
  else if (key < n->key)
    Insert(n->left, key);
  else if (key > n->key)
    Insert(n->right, key);
  else
    std::cerr << "Key " << key << " already inserted!\n";
}

template <typename K>
void BST<K>::Remove(const K& key) {
  Remove(root, key);
}

template <typename K>
void BST<K>::Remove(std::unique_ptr<Node>& n, const K& key) {
  // Key not found
  if (!n) return;

  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
    Remove(n->right, key);
  } else {
    // Found node
    if (n->left && n->right) {
      // Two children: replace with min node in right subtree
      n->key = Min(n->right.get())->key;
      Remove(n->right, n->key);
    } else {
      // Replace with only child or with nullptr
      n = std::move((n->left) ? n->left : n->right);
    }
  }
}

template <typename K>
void BST<K>::Print() {
  Print(root.get(), 1);
  std::cout << std::endl;
}

template <typename K>
void BST<K>::Print(Node* n, int level) {
  if (!n) return;

  Print(n->left.get(), level + 1);
  std::cout << n->key << " [" << level << "] ";
  Print(n->right.get(), level + 1);
}

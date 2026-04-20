#include "bt.h"

#include <iostream>
#include <queue>
#include <stack>
#include <utility>

// Make a type alias
using Node = BinaryTree<char>::Node;

// PreorderIter prints the tree at @root in pre-order
void PreorderIter(Node* root) {
  // no action if the tree is empty
  if (root == nullptr) return;

  // the stack holds nodes to be processed
  std::stack<Node*> stack;
  stack.push(root);

  while (!stack.empty()) {
    Node* top = stack.top();
    stack.pop();
    if (top->right != nullptr) stack.push(top->right.get());
    if (top->left != nullptr) stack.push(top->left.get());

    std::cout << top->item << std::endl;
  }
}

// LevelIter prints the tree starting at @root by level
void LevelIter(Node* root) {
  // no action if the tree is empty
  if (root == nullptr) return;

  std::queue<Node*> queue;
  queue.push(root);

  while (!queue.empty()) {
    Node* current = queue.front();
    queue.pop();

    // print the current level
    std::cout << current->item << std::endl;

    // check children
    if (current->left != nullptr) queue.push(current->left.get());
    if (current->right != nullptr) queue.push(current->right.get());
  }
}

#ifndef NO_MAIN  // Only compile main if NO_MAIN is not defined
int main() {
  // Statically build a binary tree
  std::unique_ptr<Node> nj(new Node{'j'});
  std::unique_ptr<Node> ni(new Node{'i'});
  std::unique_ptr<Node> nh(new Node{'h'});
  std::unique_ptr<Node> ng(new Node{'g'});
  std::unique_ptr<Node> nf(new Node{'f', std::move(nj)});
  std::unique_ptr<Node> ne(new Node{'e'});
  std::unique_ptr<Node> nd(new Node{'d', std::move(nh), std::move(ni)});
  std::unique_ptr<Node> nc(new Node{'c', std::move(nf), std::move(ng)});
  std::unique_ptr<Node> nb(new Node{'b', std::move(nd), std::move(ne)});
  std::unique_ptr<Node> na(new Node{'a', std::move(nb), std::move(nc)});
  BinaryTree<char> bin_tree{std::move(na)};

  std::cout << "Iterative pre-order: \n";
  PreorderIter(bin_tree.root.get());
  std::cout << std::endl;

  std::cout << "Iterative level-order: \n";
  LevelIter(bin_tree.root.get());
  std::cout << std::endl;

  return 0;
}
#endif

#ifndef LIST_DOUBLY_LINKED_H
#define LIST_DOUBLY_LINKED_H

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class ListDoublyLinked {
 private:
  struct Node {
    T item;

    // the next pointer owns its child, but the prev does not own its parent,
    // since this circular dependency would make deallocation require more steps
    // than just deleting the first / last pointers' references
    std::unique_ptr<Node> next;
    Node* prev;
  };

  // smart pointers are a good design because it removes some footguns of normal
  // pointers like dangling pointers & memory leaks.
  // the head and tail pointers own their respective nodes to ensure they're
  // always referenced. once unassigned, all nodes are deleted
  std::unique_ptr<Node> head = nullptr;
  Node* tail = nullptr;
  size_t cur_size = 0;

  // GetNode returns a pointer to a node in the list at @pos
  Node* GetNode(unsigned int pos) {
    unsigned int i = 0;
    Node* n = head.get();
    while (n) {
      if (i == pos) return n;

      n = n->next.get();
      i++;
    }

    throw std::invalid_argument("invalid node position");
  }

 public:
  ListDoublyLinked() = default;
  ~ListDoublyLinked() = default;

  // Return number of items in list
  int Size() { return cur_size; }

  // Return item at position @pos
  const T& Get(const unsigned int pos) {
    // invalid index
    if (pos >= cur_size) {
      throw std::out_of_range("Get: pos out of range");
    }

    return GetNode(pos)->item;
  }

  // Return position of first occurrence of @item (-1 if not found)
  int Find(const T& item) {
    Node* n = head.get();
    unsigned int i = 0;
    while (n) {
      if (n->item == item) return i;

      n = n->next.get();
      i++;
    }

    return -1;
  }

  // Remove item at position @pos
  void Remove(const unsigned int pos) {
    if (pos >= cur_size) {
      throw std::out_of_range("pos out of range");
    }

    // item is only element
    if (cur_size == 1) {
      head = nullptr;
      tail = nullptr;
      cur_size--;
      return;
    }

    // item is the head
    if (pos == 0) {
      head = std::move(head->next);
      head->prev = nullptr;
      cur_size--;
      return;
    }

    // item is tail
    if (pos == cur_size - 1) {
      tail = tail->prev;
      tail->next = nullptr;
      cur_size--;
      return;
    }

    // item is in middle
    Node* curr = GetNode(pos);
    Node* prev = curr->prev;

    prev->next = std::move(curr->next);
    prev->next->prev = prev;
    cur_size--;
  }

  // Insert @item at position @pos
  void Insert(const T& item, const unsigned int pos) {
    std::unique_ptr<Node> node = std::make_unique<Node>();
    node->item = item;

    if (pos > cur_size) {
      throw std::out_of_range("pos is out of range");
    }

    // empty list
    if (cur_size == 0) {
      head = std::move(node);
      tail = head.get();
      cur_size++;
      return;
    }

    // pos is head
    if (pos == 0) {
      node->next = std::move(head);
      node->next->prev = node.get();
      head = std::move(node);
      cur_size++;
      return;
    }

    // pos is end
    if (pos == cur_size) {
      node->prev = tail;
      tail->next = std::move(node);
      tail = tail->next.get();
      cur_size++;
      return;
    }

    // pos is in the middle
    Node* next = GetNode(pos);
    Node* prev = next->prev;

    node->next = std::move(prev->next);
    node->prev = prev;
    node->next->prev = node.get();
    prev->next = std::move(node);
    cur_size++;
  }
};

#endif

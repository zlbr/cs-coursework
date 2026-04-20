#include <iostream>

#include "deque.h"

int main() {
  Deque<int> dq;

  // [22, 42]

  dq.PushBack(23);
  dq.PushBack(42);

  std::cout << dq.Front() << std::endl;
}
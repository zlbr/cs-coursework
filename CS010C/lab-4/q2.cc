#include <iostream>
// You can only use stack_vector.h to implement this queue
#include "stack_vector.h"

template <typename T>
class Queue {
 private:
  Stack<T> mainStack;
  Stack<T> tmpStack;

 public:
  void Push(const T& item) {  // time complexity: O(N)
    // move all items of mainStack to tmpStack
    while (mainStack.Size() != 0) {
      tmpStack.Push(mainStack.Top());
      mainStack.Pop();
    }

    // add the item to the back of the stack (LI FO)
    mainStack.Push(item);

    // move all items of tmpStack back to mainStack (now in proper order)
    while (tmpStack.Size() != 0) {
      mainStack.Push(tmpStack.Top());
      tmpStack.Pop();
    }
  }

  T Pop() {  // time complexity: O(1)
    T item = mainStack.Top();
    mainStack.Pop();

    return item;
  }

  size_t Size() { return mainStack.Size(); }
};

#ifndef NO_MAIN  // Only compile main if NO_MAIN is not defined
int main() {
  Queue<int> q1;

  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v) {
    q1.Push(i);
  }
  // print q1
  while (q1.Size() != 0) {
    std::cout << q1.Pop() << ", ";
  }
  std::cout << std::endl;

  return 0;
}
#endif

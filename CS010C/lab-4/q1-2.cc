#include <iostream>

#include "stack_vector.h"

template <typename T>
void DeleteMiddleElement(Stack<T>& s, unsigned int size,
                         unsigned int curr = 0) {
  // TODO: Implement this function
  // @s: stack
  // @size: size of the stack
  // @curr: current index
  Stack<T> tmp;
  unsigned int middle = size / 2;

  while (s.Size() != 0) {
    if (curr != middle) {
      tmp.Push(s.Top());
    }

    s.Pop();
    curr++;
  }

  while (tmp.Size() != 0) {
    s.Push(tmp.Top());
    tmp.Pop();
  }

  return;
}

/*
What is the time complexity and overall space complexity of the function?:

The time complexity would be O(n), since the two while loops can only execute up
to n times each. The space complexity would be O(n) since each of the n items
only exist in one place total.

*/

#ifndef NO_MAIN  // Only compile main if NO_MAIN is not defined
int main() {
  Stack<int> s1;

  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v) s1.Push(i);

  // remove middle item (49)
  DeleteMiddleElement(s1, s1.Size());

  // print s1
  while (s1.Size() != 0) {
    std::cout << s1.Top() << ", ";
    s1.Pop();
  }
  std::cout << std::endl;

  return 0;
}
#endif

#include <iostream>

#include "stack_vector.h"

template <typename T>
Stack<T> Sort(Stack<T>& s1) {
  // tmp is the sorted stack
  Stack<T> tmp;

  // iterate over every item in the stack &
  while (s1.Size() != 0) {
    T item = s1.Top();
    s1.Pop();

    // iterate over temporary stack
    while (tmp.Size() != 0 && tmp.Top() < item) {
      s1.Push(tmp.Top());
      tmp.Pop();
    }

    tmp.Push(item);
  }

  return tmp;
}

/*
What is the time complexity and overall space complexity of the
function?:

The overall time complexity would be O(n^2), because there are two while loops.
In the worst case, where the array is sorted from high to low, all elements must
be added and removed from tmp. Since each item is only in one stack at once, the
space complexity is O(n)

*/

#ifndef NO_MAIN  // Only compile main if NO_MAIN is not defined
int main() {
  Stack<int> s1;

  std::vector<int> v{44, 12, 59, 41};
  for (auto i : v) s1.Push(i);

  // sort
  Stack<int> s2 = Sort(s1);

  // print s2
  while (s2.Size() != 0) {
    std::cout << s2.Top() << ", ";
    s2.Pop();
  }
  std::cout << std::endl;

  return 0;
}
#endif

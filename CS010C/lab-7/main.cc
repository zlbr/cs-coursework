#include <vector>

#include "splaytree.h"

int main() {
  std::vector<int> v{15, 10, 20, 8, 12, 17, 25};
  SplayTree<int> set;

  // insertion of keys
  for (auto i : v) {
    set.Insert(i);
    set.Print();
    std::cout << std::endl << "insert" << i << std::endl;
  }

  // test contains
  std::cout << std::endl;
  std::cout << "Contains 8: " << set.Contains(8) << std::endl;
  set.Print();
  std::cout << std::endl;

  std::cout << "Contains 100: " << set.Contains(100) << std::endl;
  set.Print();
  std::cout << std::endl;

  return 0;
}

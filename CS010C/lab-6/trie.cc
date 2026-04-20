#include "trie.h"

#include <iostream>

void testSearch(Trie& t, const std::string word, int expectedValue);
void testStartsWith(Trie& t, const std::string word, int expectedValue);

int main() {
  // TODO: Q3.1 - Write a tester for your Trie implementation
  // 1. Create a Trie object
  // 2. Insert a few words
  // 3. Test searching for exact words using Search()
  // 4. Test searching for word prefixes using StartsWith()

  Trie t;

  t.Insert("ho");
  t.Insert("how");
  t.Insert("hot");
  t.Insert("home");
  t.Insert("i");
  t.Insert("in");
  t.Insert("inn");
  t.Insert("igloo");

  testSearch(t, "how", 1);
  testSearch(t, "hey", 0);
  testSearch(t, "genius", 0);
  testSearch(t, "iglo", 0);

  testStartsWith(t, "hom", 1);
  testStartsWith(t, "hey", 0);
  testStartsWith(t, "igl", 1);
  testStartsWith(t, "igloo", 1);

  return 0;
}

void testSearch(Trie& t, const std::string word, int expectedValue) {
  int result = t.Search(word);
  std::string status = expectedValue == result ? "PASS" : "FAIL";

  std::cout << "trie.Search(\"" << word << "\"): " << result << " -- " << status
            << std::endl;
}

void testStartsWith(Trie& t, const std::string word, int expectedValue) {
  int result = t.StartsWith(word);
  std::string status = expectedValue == result ? "PASS" : "FAIL";

  std::cout << "trie.StartsWith(\"" << word << "\"): " << result << " -- "
            << status << std::endl;
}

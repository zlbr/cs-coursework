#ifndef TRIE_H_
#define TRIE_H_

#include <array>
#include <iostream>
#include <string>
#include <vector>

class TrieNode {
 private:
  // vector of children. children[i] = node, i = ascii code
  std::vector<TrieNode*> children;
  bool isWordEnd;

 public:
  TrieNode() { children = std::vector<TrieNode*>(26); }

  TrieNode* Get(const char c) {
    int i = CharASCII(c);  // convert letter to ascii

    if (i < 0 || i > 25) {
      throw std::out_of_range("character is not in range a-z");
    }

    return children.at(i);
  }

  void Put(const char c, TrieNode* n) {
    int i = CharASCII(c);  // convert letter to ascii

    if (this->ContainsKey(c)) {
      throw std::range_error("char c already exists");
    }

    if (i < 0 || i > 25) {
      throw std::out_of_range("character is not in range a-z");
    }

    children.at(i) = n;
  }

  bool ContainsKey(const char c) { return this->Get(c) != nullptr; }

  void SetEnd() { isWordEnd = true; }
  bool IsEnd() { return isWordEnd; }

  // TODO: Add helper function(s)
  // Hint: Create a function that transforms an ASCII character into an integer
  // 0-25

  int CharASCII(const char c) { return c - 97; }
};

// TODO: Implementations of TrieNode methods

class Trie {
 private:
  // TODO: Add root node
  TrieNode* head;

  // TODO: Add helper function to search against a certain prefix
  // Hint: This should be used by both Search() and StartsWith()

  TrieNode* TraverseDown(const std::string& word) {
    TrieNode* parent = head;

    for (int i = 0; i < word.length(); ++i) {
      char c = word[i];

      TrieNode* thisNode = nullptr;

      if (parent->ContainsKey(c)) {
        thisNode = parent->Get(c);
      } else {
        return nullptr;
      }

      if (i == word.length() - 1) return thisNode;
      parent = thisNode;
    }

    return nullptr;
  }

 public:
  Trie() { head = new TrieNode(); }

  // Inserts @word to the trie
  void Insert(const std::string& word) {
    TrieNode* parent = head;

    for (int i = 0; i < word.length(); ++i) {
      char c = word[i];

      TrieNode* thisNode = nullptr;

      if (parent->ContainsKey(c)) {
        thisNode = parent->Get(c);
      } else {
        thisNode = new TrieNode();
        parent->Put(word[i], thisNode);
      }

      if (i == word.length() - 1) thisNode->SetEnd();
      parent = thisNode;
    }
  };

  // Returns whether @word is found in the trie
  bool Search(const std::string& word) {
    TrieNode* last = TraverseDown(word);

    return last != nullptr ? last->IsEnd() : false;
  }

  // Returns whether the trie contains a word that begins with @prefix
  bool StartsWith(const std::string& prefix) {
    TrieNode* last = TraverseDown(prefix);

    return last != nullptr;
  }

  // TODO: Implementations of Trie methods

  // Q4.1 Trie Usage
  // TODO: Answer the question about Trie usage for other languages
  // Your answer: Our implementation using vectors/arrays would not be efficient
  // for space complexity of a large alphabet which could be changed to
  // a linked list and long words would cause overhead with time complexity
  // which be O(N) words saved instead of O(L) length of word
};

#endif

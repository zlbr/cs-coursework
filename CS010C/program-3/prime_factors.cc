#include <iostream>
#include <string>

#include "multiset.h"

// pre-declarations so the compiler wont complain
void findFactors(unsigned int number, Multiset<unsigned int>& set);
void printNumber(unsigned int number, Multiset<unsigned int>& set);

int main(int argc, char** argv) {
  //
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <number> <command> [<args>]"
              << std::endl;
    return 1;
  }

  unsigned int number;
  std::string command;
  Multiset<unsigned int> set;

  // parse args
  try {
    number = std::stoi(argv[1]);

  } catch (std::logic_error&) {
    std::cerr << "Invalid number" << std::endl;
    return 1;
  }

  command = argv[2];

  // find all factors
  findFactors(number, set);

  // command handling
  if (command == "min") {
    printNumber(set.Min(), set);
    return 0;
  }
  if (command == "max") {
    printNumber(set.Max(), set);
    return 0;
  }

  if (command == "all") {
    unsigned int min, count;

    while (!set.Empty()) {
      min = set.Min();
      count = set.Count(min);

      std::cout << min << " (x" << count << "), ";

      for (unsigned int i = 0; i < count; ++i) {
        set.Remove(min);
      }
    }
    return 0;
  }
  if (command == "near") {
    if (argc < 4) {
      std::cerr << "Command 'near' expects another argument: [+/-]prime"
                << std::endl;
      return 1;
    }

    std::string prime = argv[3];
    char sign = prime[0];
    int primeValue;
    unsigned int result;

    try {
      primeValue = std::stoi(prime);
    } catch (std::logic_error&) {
      std::cerr << "Invalid prime" << std::endl;
      return 1;
    }

    try {
      if (sign == '+') {
        result = set.Ceil(primeValue + 1);
      } else if (sign == '-') {
        primeValue *= -1;
        result = set.Floor(primeValue - 1);
      } else {
        result = primeValue;
      }
    } catch (std::logic_error&) {
      std::cout << "No match" << std::endl;
      return 1;
    }

    printNumber(result, set);

    return 0;
  }

  // error message in default case
  std::cerr << "Command '" << command << "' is invalid" << std::endl;
  std::cerr << "Possible commands are: all|min|max|near" << std::endl;

  return 1;
}

void findFactors(unsigned int number, Multiset<unsigned int>& set) {
  // factors of 2
  while (number % 2 == 0) {
    set.Insert(2);
    number /= 2;
  }

  // check odd numbers starting from 3
  for (unsigned int i = 3; i * i <= number; i += 2) {
    while (number % i == 0) {  // if it's a factor, insert it to mset
      set.Insert(i);
      number /= i;
    }
  }

  // if n > 1, it's a prime number, so add itself
  if (number > 1) {
    set.Insert(number);
  }
}

void printNumber(unsigned int number, Multiset<unsigned int>& set) {
  std::cout << number << " (x" << set.Count(number) << ")" << std::endl;
}
#include <iostream>
#include <sstream>
#include <string>

#include "stack.h"

int main(int argc, char const* argv[]) {
  std::string line = "";
  std::string input = "";
  Stack<double> operands;

  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    bool isErr = false;

    while (ss >> input) {
      // handle operators
      if (input == "+" || input == "-" || input == "*" || input == "/") {
        if (operands.Size() < 2) {
          continue;
        }

        double rhs = operands.Pop();
        double lhs = operands.Pop();
        double result = 0;

        if (input == "+") {
          result = lhs + rhs;
        } else if (input == "-") {
          result = lhs - rhs;
        } else if (input == "*") {
          result = lhs * rhs;
        } else if (input == "/") {
          result = lhs / rhs;
        }

        operands.Push(result);
      } else {
        // handle operands (insert to stack)
        try {
          double d = std::stod(input);
          operands.Push(d);
        } catch (const std::invalid_argument& e) {
          std::cerr << "Error: unknown symbol '" << input << "'" << std::endl;
          isErr = true;
          continue;
        }
      }
    }

    if (!isErr && operands.Size() == 1) {
      std::cout << operands.Pop() << std::endl;
    } else if (!isErr) {
      std::cerr << "Error: invalid expression" << std::endl;
    }

    // clear the stack
    while (operands.Size() != 0) {
      operands.Pop();
    }
  }

  std::cout << "Bye!" << std::endl;
  return 0;
}
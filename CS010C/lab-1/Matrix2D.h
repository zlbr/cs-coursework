#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <iostream>
#include <string>
#include <utility>

class Matrix2D {
 private:
  std::string makeDisplayable() const;

 public:
  Matrix2D();
  Matrix2D(const Matrix2D& other);
  ~Matrix2D();

  Matrix2D& operator=(Matrix2D other);
  void Display() const;

  friend std::ostream& operator<<(std::ostream&, const Matrix2D&);
};

std::ostream& operator<<(std::ostream& out, const Matrix2D& matrix);

#endif

#include <iostream>
#include <string>
#include <utility>

template <typename T>
class Matrix2D {
 private:
  T** matrix;

 public:
  Matrix2D() {
    matrix = new T*[3];
    for (int i = 0; i < 3; ++i) {
      matrix[i] = new T[4];
    }

    for (int c = 0; c < 4; ++c) {
      for (int r = 0; r < 3; ++r) {
        matrix[r][c] = r * 2 + c;
      }
    }
  }

  Matrix2D(const Matrix2D& other) {
    matrix = new T*[3];
    for (int i = 0; i < 3; ++i) {
      matrix[i] = new T[4];
    }

    for (int c = 0; c < 4; ++c) {
      for (int r = 0; r < 3; ++r) {
        matrix[r][c] = other.matrix[r][c];
      }
    }
  }

  ~Matrix2D() {
    for (int i = 0; i < 3; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  Matrix2D& operator=(Matrix2D other) {
    std::swap(this->matrix, other.matrix);
    return *this;
  }

  void Display() const { std::cout << this; }

  friend std::ostream& operator<<(std::ostream&, const Matrix2D&);
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const T& matrix) {
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 4; ++c) {
      out << std::to_string(matrix.matrix[r][c]) + " ";
    }
    out << std::endl;
  }

  return out;
}
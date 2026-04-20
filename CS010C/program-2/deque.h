#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>
#include <stdexcept>

template <typename T>
class Deque {
 public:
  //
  // @@@ The class's public API below should NOT be modified @@@
  //

  // Constructor
  Deque();
  // Destructor
  ~Deque();

  //
  // Capacity
  //

  // Return true if empty, false otherwise
  // Complexity: O(1)
  bool Empty() const noexcept;

  // Return number of items in deque
  // Complexity: O(1)
  size_t Size() const noexcept;

  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  // Complexity: O(N)
  void ShrinkToFit();

  //
  // Element access
  //

  // Return item at pos @pos
  // Complexity: O(1)
  T& operator[](size_t pos);

  // Return item at front of deque
  // Complexity: O(1)
  T& Front();

  // Return item at back of deque
  // Complexity: O(1)
  T& Back();

  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  // Complexity: O(1)
  void Clear(void) noexcept;

  // Push item @value at front of deque
  // Complexity: O(1) amortized
  void PushFront(const T& value);

  // Push item @value at back of deque
  // Complexity: O(1) amortized
  void PushBack(const T& value);

  // Remove item at front of deque
  // Complexity: O(1) amortized
  void PopFront();

  // Remove item at back of deque
  // Complexity: O(1) amortized
  void PopBack();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //
  size_t head = 0;
  size_t tail = 0;
  size_t capacity = 4;
  size_t size = 0;
  T* arr;

  // TODO: Add private member variables
  // Hint: You'll need to implement a circular array
  // Consider: array storage, capacity, size, head/tail indices

  // TODO: Add private constants
  // Hint: Initial capacity for the internal array

  // TODO: Add private helper methods if needed
  // Hint: Methods for resizing, wrapping indices, etc.

  // get the index before @pos
  int NextIndex(size_t pos) { return (pos + 1) % capacity; }
  // get the index after @pos
  int PrevIndex(size_t pos) {
    return (((pos - 1) % capacity) + capacity) % capacity;
  }

  void Resize(size_t size) {
    if (size < this->size)
      throw std::runtime_error("specified size is too small for array");

    T* newArr = new T[size];

    for (size_t i = 0; i < this->size; ++i) {
      newArr[i] = arr[(head + i) % capacity];
    }

    capacity = size;
    head = 0;
    tail = this->size - 1;

    delete[] arr;
    arr = newArr;
  };
};

//
// Implementation of Deque methods
// TODO: Implement all public methods below
//

template <typename T>
Deque<T>::Deque() {
  arr = new T[capacity];
}

template <typename T>
Deque<T>::~Deque() {
  delete[] arr;
}

template <typename T>
bool Deque<T>::Empty() const noexcept {
  return size == 0;
}

template <typename T>
size_t Deque<T>::Size() const noexcept {
  return size;
}

template <typename T>
void Deque<T>::ShrinkToFit() {
  // TODO: Resize internal array to fit exactly the current number of items
  Resize(size);
}

template <typename T>
T& Deque<T>::operator[](size_t pos) {
  // @todo: bounds checking
  if (pos < 0 || pos >= size)
    throw std::range_error("pos is invalid for this deque");

  return arr[(head + pos) % capacity];
}

template <typename T>
T& Deque<T>::Front() {
  if (size == 0)
    throw std::underflow_error("cannot return item from empty dequeue");

  return arr[head];
}

template <typename T>
T& Deque<T>::Back() {
  if (size == 0)
    throw std::underflow_error("cannot return item from empty dequeue");

  return arr[tail];
}

template <typename T>
void Deque<T>::Clear(void) noexcept {
  head = 0;
  tail = 0;
  size = 0;
}

template <typename T>
void Deque<T>::PushFront(const T& value) {
  if (size + 1 >= capacity) Resize(capacity * 2);

  if (size == 0) {
    head = 0;
    tail = 0;
  } else {
    head = PrevIndex(tail);
  }

  arr[head] = value;
  size++;
}

template <typename T>
void Deque<T>::PushBack(const T& value) {
  if (size + 1 >= capacity) Resize(capacity * 2);

  if (size == 0) {
    head = 0;
    tail = 0;
  } else {
    tail = NextIndex(tail);
  }

  // [23, 42,            ]

  // [23    ]
  //  h   t

  arr[tail] = value;
  size++;
}

template <typename T>
void Deque<T>::PopFront() {
  if (size == 0) throw std::underflow_error("deque is empty, no item to pop");

  // resize the array if too empty
  if (size < capacity / 2) {
    Resize(size);
  }

  head = NextIndex(head);
  size--;
}

template <typename T>
void Deque<T>::PopBack() {
  if (size == 0) throw std::underflow_error("deque is empty, no item to pop");

  // resize the array if too empty
  if (size < capacity / 2) {
    Resize(size);
  }

  tail = PrevIndex(tail);
  size--;
}

#endif
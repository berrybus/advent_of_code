#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T> class CoolVector {
private:
  T *arr;
  size_t capacity;
  size_t current;

  void resize() {
    T *tmp = new T[2 * capacity];
    for (size_t i = 0; i < current; i++) {
      tmp[i] = arr[i];
    }
    delete[] arr;
    arr = tmp;
    capacity *= 2;
  }

public:
  CoolVector() {
    capacity = 1;
    current = 0;
    arr = new T[1];
  }

  // Destructor
  ~CoolVector() { delete[] arr; }

  // Copy constructor - current object does not already exit
  CoolVector(const CoolVector &other)
      : capacity(other.capacity), current(other.current) {
    arr = new T[capacity];
    for (size_t i = 0; i < current; i++) {
      // This triggers the copy assignment. Does a copy assignment always do a
      // deep copy?
      arr[i] = other.arr[i];
    }
  }

  // Copy assignment - current object already exists, so replace inside contents
  // with that of the other object
  CoolVector &operator=(const CoolVector &other) {
    if (this == &other) {
      // I guess the compiler automagically converts the `this` object into a
      // reference of it? Is it because the return type is a reference?
      return *this;
    }
    capacity = other.capacity;
    current = other.current;
    delete arr;
    arr = new T[capacity];
    for (size_t i = 0; i < current; i++) {
      arr[i] = other.arr[i];
    }
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &out, const CoolVector<T> &vec) {
    out << "[";
    for (size_t i = 0; i < vec.current; i++) {
      out << vec.arr[i];
      if (i < vec.current - 1) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  void push_back(const T &val) {
    if (current == capacity) {
      resize();
    }
    // Does arr now "own" val? meaning does val's data now belong in arr?
    arr[current] = val;
    current++;
  }

  void insert(size_t index, const T &val) {
    if (index < 0) {
      throw std::out_of_range("cannot insert below 0");
    }

    // I guess we'll let them insert at position 999999
    index = std::min(current, index);

    if (current == capacity) {
      resize();
    }
    for (size_t i = current; i > index; i--) {
      arr[i] = arr[i - 1];
    }

    arr[index] = val;
    current++;
  }

  T &pop_at(size_t index) {
    if (index < 0 || index >= current) {
      throw std::out_of_range("cannot pop from nonexistent index!");
    }

    T &ret = arr[index];

    for (size_t i = index; i < current - 1; i++) {
      arr[i] = arr[i + 1];
    }

    current--;
    return ret;
  }

  T &pop() {
    if (current == 0) {
      throw std::out_of_range("popping from empty array");
    }
    current--;
    return arr[current];
  }

  T &at(size_t index) {
    if (index < 0 || index >= current) {
      throw std::out_of_range("index not valid");
    }
    return arr[index];
  }

  size_t size() { return current; }
};

int main() {
  CoolVector<int> vec = CoolVector<int>();
  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
  }

  vec.insert(0, 20);
  vec.pop_at(2);
  std::cout << vec << std::endl;
  return 0;
}

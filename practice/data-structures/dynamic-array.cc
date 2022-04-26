#include <iostream>

namespace dsa {

class DArray {
  static const int kDefaultCapacity = 16;
  int size_;
  int capacity_;
  int* head_;

  void DArrayInit(int size) {
    capacity_ = kDefaultCapacity;
  	size_ = size;

    while (size_ > capacity_) {
      capacity_ *= 2;
    }
    head_ = new int[capacity_];
  }

  void Expand() {
    if (size_ >= capacity_) {
      capacity_ *= 2;
      int* new_head = new int[capacity_];
      for (int *old_iterator = head_, *new_iterator = new_head; old_iterator != head_ + size_; ++old_iterator, ++new_iterator) {
        *new_iterator = *old_iterator;
      }

      delete[] head_;
      head_ = new_head;
      std::cout << "expanded from " << capacity_ / 2 << " to " << capacity_ << '\n';
    }
  }

  void Reduce() {
    if (size_ <= capacity_ / 4) {
      capacity_ /= 4;
      int* new_head = new int[capacity_];
      for (int *old_iterator = head_, *new_iterator = new_head; old_iterator != head_ + size_; ++old_iterator, ++new_iterator) {
        *new_iterator = *old_iterator;
      }

      delete[] head_;
      head_ = new_head;
      std::cout << "reduced from " << capacity_ * 4 << " to " << capacity_ << '\n';
    }
  }

 public:
  DArray() {
  	capacity_ = kDefaultCapacity;
    head_ = new int[capacity_];
    size_ = 0;
  }

  DArray(int size) {
    DArrayInit(size);
  }

  DArray(int size, int initial_value) {
  	DArrayInit(size);

    for (int* index = head_; index != head_ + size_; ++index) {
      *index = initial_value;
    }
  }
  
  ~DArray() {
    delete[] head_;
  }
  
  int Size() {
    return size_;
  }

  bool Empty() {
    return size_ == 0;
  }

  int Capacity() {
    return capacity_;
  }

  void Set(int index, int value) {
    *(head_ + index) = value;
  }

  int Get(int index) {
    return *(head_ + index);
  }

  void PushBack(int value) {
    Expand();
    *(head_ + size_) = value;
    ++size_;
  }

  int PopBack() {
    if (Empty()) {
      std::cout << "ERROR: Array is empty!\n";
      return 0;
    }    

    int last_value = *(head_ + size_ - 1);
    --size_;
    Reduce();

    return last_value;
  }

  void Erase(int index) {
    if (Empty()) {
      std::cout << "ERROR: Array is empty!\n";
      return;
    }

    if (not (index >= 0 and index < size_)) {
      std::cout << "ERROR: Array index out of bounds.\n";
    }

    --size_;
    for (int* iterator = head_ + index; iterator != head_ + size_; ++iterator) {
      *iterator = *(iterator + 1);
    }
  }

  void Remove(int value) {
    int remove_count = 0;
    for (int *forward_pointer = head_, *update_pointer = head_; forward_pointer != head_ + size_; ++forward_pointer, ++update_pointer) {
      while (forward_pointer != head_ + size_ and *forward_pointer == value) {
        ++remove_count;
        ++forward_pointer;
      }

      if (forward_pointer == head_ + size_) {
        break;
      }

      *update_pointer = *forward_pointer;
    }
    size_ -= remove_count;
    Reduce();
  }

  void Print() {
    std::cout << "Array Capacity: " << capacity_ << '\n';
    std::cout << "Array Size: " << size_ << '\n';
    for (int* index = head_; index != head_ + size_; ++index) {
      std::cout << *index << ' ';
    }

    std::cout << '\n';
  }
};

}

int main() {
  int i = 0;  
  dsa::DArray d_array = dsa::DArray(10);  
  while (i < 1000) {
    d_array.PushBack(i);
    ++i;
  }
  i = 0;  
  while (i < 1000) {
    d_array.PopBack();
    ++i;
  }
  d_array.Set(0, 4);
  d_array.Set(1, 4);
  d_array.Set(2, 4);
  d_array.Set(3, 4);
  d_array.Set(4, 4);
  d_array.Set(5, 4);
  d_array.Set(6, 4);
  d_array.Set(7, 3);
  d_array.Set(8, 2);
  d_array.Set(9, 1);
  d_array.Remove(4);
  d_array.Print();
  return 0;
}

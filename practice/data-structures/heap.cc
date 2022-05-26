#include <iostream>
#include <vector>
#include <algorithm>

class MaxHeap {
  std::vector<int> heap_;
  int size_;

  int Parent(int node) {
    return (node - 1) / 2;
  }

  int LeftChild(int node) {
    return node * 2 + 1;
  }

  int RightChild(int node) {
    return node * 2 + 2;
  }

  void Swap(int node_1, int node_2) {
    int swap_temp = heap_[node_1];
    heap_[node_1] = heap_[node_2];
    heap_[node_2] = swap_temp;
  }

 public:
  MaxHeap() {}

  MaxHeap(std::vector<int> const& array) {
    Heapify(array);
  }

  void SiftUp(int node) {
    if (heap_[Parent(node)] < heap_[node]) {
      Swap(node, Parent(node));
      SiftUp(Parent(node));
    }
  }

  void SiftDown(int node) {
    int max_node = node;    

    if (LeftChild(node) < heap_.size() and heap_[LeftChild(node)] > heap_[max_node]) {
      max_node = LeftChild(node);
    }

    if (RightChild(node) < heap_.size() and heap_[RightChild(node)] > heap_[max_node]) {
      max_node = RightChild(node);
    }

    if (max_node != node) {
      Swap(node, max_node);
      SiftDown(max_node);
    }
  }

  void Insert(int new_element) {
    heap_.push_back(new_element);
    SiftUp(heap_.size() - 1);
  }

  int Top() {
    return heap_[0];
  }

  void PopMax() {
    Swap(0, heap_.size() - 1);
    heap_.pop_back();
    if (heap_.size() > 0) {
      SiftDown(0);
    }
  }

  int Size() {
    return heap_.size();
  }

  bool isEmpty() {
    return heap_.size() == 0;
  }

  void Remove(int node) {
    Swap(node, heap_.size() - 1);
    heap_.pop_back();
    SiftDown(node);
  }

  void Heapify(std::vector<int> const& array) {
    heap_.clear();
    for (int element : array) {
      heap_.push_back(element);
    }

    for (int node = Parent(heap_.size() - 1); node >= 0; --node) {
      SiftDown(node);
      Print();
    }
    std::cout << '\n';
  }

  void HeapSort(std::vector<int> const& array) {
    Heapify(array);
    std::vector<int> sorted_array;
    
    while (heap_.size() > 0) {
      sorted_array.push_back(Top());
      for (int e : sorted_array) std::cout << e << ' '; std::cout << '\n';
      PopMax();
    }

    std::reverse(sorted_array.begin(), sorted_array.end());
    heap_ = sorted_array;
  }

  void Print() {
    for (int element : heap_) {
      std::cout << element << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  std::vector<int> array{1, 2, 23, 4, 5, 2343, 345, 8, 9, 0};
  MaxHeap heap = MaxHeap(array);
  heap.Print();
  heap.HeapSort(array);
  heap.Print();

  return 0;
}

#include <iostream>
#include <cassert>
#include <stack>

struct Node {
  int data;
  Node* next = NULL;

  Node(int data, Node* next) : data(data), next(next) {}
};

class LinkedList {
  Node* head_ = NULL;

 public:
  ~LinkedList() {    
    while (head_ != NULL) {
      Node* node = head_->next;      
      delete head_;
      head_ = node;
    }
    std::cout << "Inside destructor.\n";
  }

  int Size() {
    if (head_ == NULL) {
      return 0;
    }

    int size = 1;
    Node* node = head_->next;

    while (node != NULL) {
      ++size;
    }

    return size;
  }

  void PushBack(int data) {
    Node* new_node = new Node(data, NULL);
    Node* node = head_;
    if (head_ == NULL) {
      head_ = new_node;
      return;
    }

    while (node->next != NULL) {
      node = node->next;
    }

    node->next = new_node;
  }

  void PushFront(int data) {
    Node* new_node = new Node(data, head_);
    head_ = new_node;
  }

  bool Empty() {
    return (head_ == NULL);
  }

  void PopFront() {
    try {
      if (Empty()) {
        throw "Can't pop an empty list.\n";
      }
  
      Node* node = head_;
      head_ = head_->next;
      delete node;
    }
    catch (char const* message) {
      std::cout << message;
    }
  }

  int DataAt(int index) {
    int cur_index = 0;
    Node* node = head_;
    while (node != NULL) {
      if (cur_index == index) {
        return node->data;
      }
      ++cur_index;
      node = node->next;
    }

    std::cout << "Index out of bounds.\n";
  }

  void Insert(int index, int data) {
    if (index == 0) {
      PushFront(data);
      return;
    }

    Node* node = head_->next;
    Node* prev_node = head_;
    int curr_index = 1;

    while (prev_node != NULL) {
      if (curr_index == index) {
        Node* new_node = new Node(data, node);
        prev_node->next = new_node;
        return;
      }
      ++curr_index;
      prev_node = node;
      node = (node != NULL) ? node->next : NULL;
    }
  }

  void Remove(int index) {
    if (index == 0) {
      PopFront();
      return;
    }

    Node* node = head_->next;
    Node* prev_node = head_;
    int curr_index = 1;

    while (prev_node != NULL) {
      if (curr_index == index) {
        prev_node->next = (node != NULL) ? node->next : NULL;
        if (node != NULL) {
          delete node;
        }
        return;
      }

      ++curr_index;
      prev_node = node;
      node = (node != NULL) ? node->next : NULL;
    }
  }

  void Reverse() {
    if (head_ == NULL or head_->next == NULL) {
      return;
    }

    Node* node = head_->next;
    Node* prev_node = head_;
    while (node != NULL) {
      Node* next_node = node->next;
      node->next = prev_node;

      prev_node = node;
      node = next_node;
    }

    head_->next = NULL;
    head_ = prev_node;
  }

  void Print() {
    Node* node = head_;
    while (node != NULL) {
      std::cout << node->data << ' ';
      node = node->next;
    }

    std::cout << '\n';
  }
};

int main () {
  LinkedList list = LinkedList();
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);
  list.PushBack(4);
  list.PushBack(5);
  list.PushFront(100);
  list.PushFront(1000);
  list.PushBack(6);
  list.PushBack(7);
  list.PushBack(8);
  list.PushBack(9);
  list.Insert(0, 50);
  list.Insert(2, 100000);
  list.Insert(13, 700);
  list.Remove(13);
  list.Remove(0);
  list.Remove(2);

  list.Print();

  list.Reverse();

  list.Print();
  std::stack<int> s;
  return 0;
}

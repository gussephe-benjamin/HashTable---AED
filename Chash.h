#include <iostream>
#define MAX_COLUMS 3
using namespace std;

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node() : val(0), next(nullptr) {}
  Node(T x) : val(x), next(nullptr) {}
  Node(T x, Node<T> *next) : val(x), next(next) {}
};

template <typename T>
class List {
private:
  Node<T> *head;
  int count;

public:
  List() : head(nullptr), count(0) {}

  bool empty() {
    return head == nullptr;
  }

  Node<T> *getHead() const {
    return head;
  }

  T front() {
    if (!head)
      return T();
    return head->val;
  }

  void push_front(T val) {
    head = new Node<T>(val, head);
    count++;
  }

  void pop_front() {
    if (head) {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
      count--;
    }
  }

  void clear() {
    while (head) {
      pop_front();
    }
  }

  int size() const {
    return count;
  }

  ~List() {
    clear();
  }
};

template <typename TK, typename TV>
struct Pair {
  TK key;
  TV value;
  Pair() : key(TK()), value(TV()) {}
  Pair(TK k, TV v) : key(k), value(v) {}
};


bool is_prime(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

template <typename TK, typename TV>
class HashTable{
private:
  List<Pair<TK, TV>> *table;
  int size;
  int capacity;

  int hash(string key) {
    int hash = 0;
    for (char c : key) {
      hash = (hash * 31 + c) % capacity;
    }
    return hash;
  }

  int hash(int key) {
    return key % capacity;
  }

  void rehash() {
    int oldCapacity = capacity;
    capacity = 2 * oldCapacity;
    while (!is_prime(capacity)) {
      capacity++;
    }
    List<Pair<TK, TV>> *newTable = new List<Pair<TK, TV>>[capacity];

    for (int i = 0; i < oldCapacity; i++) {
      Node<Pair<TK, TV>> *current = table[i].getHead();
      while (current) {
        Pair<TK, TV> pair = current->val;
        int index = hash(pair.key);
        newTable[index].push_front(pair);
        current = current->next;
      }
      table[i].clear();
    }

    delete[] table;
    table = newTable;
  }

public:

  HashTable(): size(0), capacity(5) {
    table = new List<Pair<TK, TV>>[capacity];
  }

  HashTable(int capacity): size(0), capacity(capacity) {
    table = new List<Pair<TK, TV>>[capacity];
  }

  ~HashTable() {
    delete[] table;
  }

  void insert(TK key, TV value){
    int index = hash(key);
    Node<Pair<TK, TV>> *current = table[index].getHead();

    while (current) {
      if (current->val.key == key) {
        current->val.value = value;
        return;
      }
      current = current->next;
    }

    table[index].push_front(Pair<TK, TV>(key, value));
    size++;

    if (size >= capacity) {
      rehash();
    }
  }

  TV search(TK key) {
    int index = hash(key);
    Node<Pair<TK, TV>> *current = table[index].getHead();

    while (current) {
      if (current->val.key == key) {
        return current->val.value;
      }
      current = current->next;
    }

    return TV();
  }

  void remove(TK key) {
    int index = hash(key);
    Node<Pair<TK, TV>> *current = table[index].getHead();
    Node<Pair<TK, TV>> *prev = nullptr;

    while (current) {
      if (current->val.key == key) {
        if (prev) {
          prev->next = current->next;
        } else {
          table[index].pop_front();
          return;
        }
        delete current;
        size--;
        return;
      }
      prev = current;
      current = current->next;
    }
  }

  bool empty() {
    return size == 0;
  }

  int getSize() {
    return size;
  }

  void display() {
    for (int i = 0; i < capacity; i++) {
      cout << i << ": ";
      Node<Pair<TK, TV>>* current = table[i].getHead();
      while (current) {
        cout << "(" << current->val.key << ", " << current->val.value << ") ";
        current = current->next;
      }
      cout << endl;
    }
  }
};
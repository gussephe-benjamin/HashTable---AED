#include <iostream>
#define MAX_LOAD_FACTOR 0.7
using namespace std;

template <typename TK, typename TV>
struct Pair {
  TK key;
  TV value;
  bool isOccupied;
  bool isDeleted;

  Pair() : key(TK()), value(TV()), isOccupied(false), isDeleted(false) {}
  Pair(TK k, TV v) : key(k), value(v), isOccupied(true), isDeleted(false) {}
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
class HashTable {
private:
  Pair<TK, TV> *table;
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
    Pair<TK, TV> *newTable = new Pair<TK, TV>[capacity];

    for (int i = 0; i < oldCapacity; i++) {
      if (table[i].isOccupied && !table[i].isDeleted) {
        int index = hash(table[i].key);
        while (newTable[index].isOccupied) {
          index = (index + 1) % capacity;
        }
        newTable[index] = table[i];
      }
    }

    delete[] table;
    table = newTable;
  }

public:
  HashTable() : size(0), capacity(5) {
    table = new Pair<TK, TV>[capacity];
  }

  HashTable(int capacity) : size(0), capacity(capacity) {
    table = new Pair<TK, TV>[capacity];
  }

  ~HashTable() {
    delete[] table;
  }

  void insert(TK key, TV value) {
    if ((float)size / capacity >= MAX_LOAD_FACTOR) {
      rehash();
    }

    int index = hash(key);
    while (table[index].isOccupied && !table[index].isDeleted) {
      if (table[index].key == key) {
        table[index].value = value;
        return;
      }
      index = (index + 1) % capacity;
    }

    table[index] = Pair<TK, TV>(key, value);
    size++;
  }

  TV search(TK key) {
    int index = hash(key);
    int startIndex = index;
    while (table[index].isOccupied) {
      if (table[index].key == key && !table[index].isDeleted) {
        return table[index].value;
      }
      index = (index + 1) % capacity;
      if (index == startIndex) {
        break;
      }
    }
    return TV();
  }

  void remove(TK key) {
    int index = hash(key);
    int startIndex = index;
    while (table[index].isOccupied) {
      if (table[index].key == key && !table[index].isDeleted) {
        table[index].isDeleted = true;
        size--;
        return;
      }
      index = (index + 1) % capacity;
      if (index == startIndex) {
        break;
      }
    }
  }

  bool empty() const {
    return size == 0;
  }

  int getSize() const {
    return size;
  }

  void display() const {
    for (int i = 0; i < capacity; i++) {
      cout << i << ": (" << table[i].key << ", " << table[i].value << ") " << endl;
    }
  }
};

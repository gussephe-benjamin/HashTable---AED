#include "Ohash.h"

int main() {
  HashTable<string, int> hashTable;

  hashTable.insert("K1", 10);
  hashTable.insert("K2", 20);
  hashTable.insert("K3", 30);
  hashTable.insert("K4", 40);
  hashTable.insert("K5", 50);


  cout<<hashTable.search("K2")<<endl;

  cout<<endl;

  hashTable.display();

  hashTable.remove("K3");
  cout << endl;
  hashTable.display();

  return 0;
}
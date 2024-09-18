#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <type_traits>

// Implementación de ForwardList y Node
template <typename T, typename Q>
struct Node {
    T key;
    Q val;
    Node* next;
};

template <typename T, typename Q>
class ForwardList {
private:
    Node<T, Q>* head;
public:
    ForwardList() : head(nullptr) {} // Constructor
    ~ForwardList() { clear(); } // Destructor

    Node<T, Q>* front() { return head; }

    void push_front(T key, Q val) {
        Node<T, Q>* newNode = new Node<T, Q>{key, val, head};
        head = newNode;
    }

    void pop_front() {
        if (head != nullptr) {
            Node<T, Q>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Q findKey(T key) {
        Node<T, Q>* temp = head;
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->val;
            }
            temp = temp->next;
        }
        throw std::runtime_error("Key not found");
    }

    void deleteKey(T key) {
        Node<T, Q>* temp = head;
        Node<T, Q>* prev = nullptr;
        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    void clear() {
        while (head != nullptr) {
            pop_front();
        }
    }

    void printList() {
        Node<T, Q>* temp = head;
        while (temp != nullptr) {
            std::cout << "(" << temp->key << ", " << temp->val << ") -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

// Implementación de TablaHash

template <typename T, typename V>
class TablaHash {
    int m = 20;
    std::vector<ForwardList<T, V>> LlistVector;
    int nelements;
    int P = 97; // numero primoo
    float fillfactor;
    int a;
    int b;

public:
    // Constructor
    TablaHash() : nelements(0), LlistVector(m) { 
        a = getRandomNumber(1, P - 1);
        b = getRandomNumber(0, P - 1);
    }

    int getRandomNumber(int lower, int P) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(lower, P - 1);
        return distrib(gen);
    }

// Sobrecarga para std::string
int newkey(const std::string& key) {
    int nkey = 0;
    int size = key.size();
    for (char c : key) {
        nkey += (static_cast<int>(c)) * (1 << (size - 1));
        size--;
    }
    return nkey;
}

// Sobrecarga para char
int newkey(char key) {
    return static_cast<int>(key);
}

// Sobrecarga para int
int newkey(int key) {
    return key;
}

// Sobrecarga para otros tipos no soportados (opcional)
template<typename R>
int newkey(R key) {
    return int(key);
}


    int hashingfunction(T key) {
        int nkey = newkey(key);
        int index;
        index = ((a * nkey + b) % P) % m;
        return index;
    }

    void insert(T key, V value) {
        int index = hashingfunction(key);
        LlistVector[index].push_front(key, value);
        nelements++;
        fillfactor = static_cast<float>(nelements) / m;
        
        if (fillfactor > 0.7) {
            
        }
    }

    V search(T key) {
        int index = hashingfunction(key);
        return LlistVector[index].findKey(key);
    }

    void Delete(T key) {
        int index = hashingfunction(key);
        LlistVector[index].deleteKey(key);
        nelements--;
    }


    void showLists(T key) {
        int index = hashingfunction(key);
        LlistVector[index].printList();
    }
};

// Uso de ejemplo
int main() {
    TablaHash<std::string, std::string> table;

table.insert("a", ".-"); 
table.insert("b", "-...");
table.insert("c", "-.-.");
table.insert("d", "-..");
table.insert("e", ".");
table.insert("f", "..-.");
table.insert("g", "--.");
table.insert("h", "....");
table.insert("i", "..");
table.insert("j", ".---");
table.insert("k", "-.-");
table.insert("l", ".-..");
table.insert("m", "--");
table.insert("n", "-.");
table.insert("o", "---");
table.insert("p", ".--.");
table.insert("q", "--.-");
table.insert("r", ".-.");
table.insert("s", "...");
table.insert("t", "-");
table.insert("u", "..-");
table.insert("v", "...-");
table.insert("w", ".--");
table.insert("x", "-..-");
table.insert("y", "-.--");
table.insert("z", "--..");

table.showLists("a");

table.showLists("u");

}

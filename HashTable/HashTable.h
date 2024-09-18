#include<iostream>
using namespace std;


template <typename T, typename Q>
struct Node {
    T key;
    Q val
    Node* next;
};


template <typename T>
class ForwardList {
private:
    Node<T>* head;
public:
    ForwardList();
    ~ForwardList();

    Node<T>* front();
    Node<T>* back();

    void push_front(T);
    void push_back(T);

    void pop_front();
    void pop_back();

    T operator[](int);

    bool empty();
    int size();

    void clear();
    void sort();
    void reverse();
    void printList();
};

template <typename T>
Node<T>* ForwardList<T>::front() {
    Node<T>* temp = head;
    return temp;
}

template <typename T>
Node<T>* ForwardList<T>::back() {
    Node<T>* temp = head;
    while (temp != nullptr) {
        temp = temp->next;
    }
    return temp;
}

template <typename T>
void ForwardList<T>::push_back(T val) {
    Node<T>* nodo_val = new Node<T>(val);
    Node<T>* temp = head;

    if (temp == nullptr) {
        head = nodo_val;
    } else {
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodo_val;
    }
}

template <typename T>
void ForwardList<T>::push_front(T val) {
    Node<T>* nodo_val = new Node<T>(val);
    Node<T>* temp = head;

    if (temp == nullptr) {
        head = nodo_val;
    } else {
        nodo_val->next = head;
        head = nodo_val;
    }
}

template <typename T>
void ForwardList<T>::printList() {
    Node<T>* temp = head;
    while (temp != nullptr) {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

template <typename T>
ForwardList<T>::ForwardList() : head(nullptr) {
    // Inicializa head como nullptr
}

template <typename T>
ForwardList<T>::~ForwardList() {
    clear();  // Libera todos los nodos al destruir el objeto
}

template <typename T>
void ForwardList<T>::pop_front() {
    Node<T>* temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
void ForwardList<T>::pop_back() {
    Node<T>* temp = head;

    if (temp == nullptr) return; // Lista vacía

    if (temp->next == nullptr) { // Solo un elemento
        delete temp;
        head = nullptr;
        return;
    }

    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

template <typename T>
T ForwardList<T>::operator[](int index) {
    Node<T>* temp = head;

    if (index == 0) {
        return head->val;
    } else if (index < 0 || head == nullptr) {
        throw out_of_range("Index out of range");
    } else {
        int count = 0;
        while (count < index && temp != nullptr) {
            count++;
            temp = temp->next;
        }
        if (temp == nullptr) throw out_of_range("Index out of range");
        return temp->val;
    }
}

template <typename T>
bool ForwardList<T>::empty() {
    return head == nullptr;
}

template <typename T>
int ForwardList<T>::size() {
    Node<T>* temp = head;
    int count = 0;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

template <typename T>
void ForwardList<T>::clear() {
    while (head != nullptr) {
        Node<T>* auxiliar = head;
        head = head->next;
        delete auxiliar;
    }
}

template <typename T>
Node<T>* getMiddle(Node<T>* head) {
    if (head == nullptr) return head;

    Node<T>* slow = head;
    Node<T>* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

template <typename T>
Node<T>* merge(Node<T>* left, Node<T>* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node<T>* result = nullptr;

    if (left->val <= right->val) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

template <typename T>
Node<T>* mergeSort(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node<T>* middle = getMiddle(head);
    Node<T>* nextToMiddle = middle->next;

    middle->next = nullptr;

    Node<T>* left = mergeSort(head);
    Node<T>* right = mergeSort(nextToMiddle);

    Node<T>* sortedList = merge(left, right);

    return sortedList;
}

template <typename T>
void ForwardList<T>::sort() {
    head = mergeSort(head);
}

template <typename T>
void ForwardList<T>::reverse() {
    Node<T>* temp = head;
    Node<T>* retro = nullptr;
    Node<T>* prev = nullptr;

    while (temp != nullptr) {
        prev = retro;
        retro = temp;
        temp = temp->next;
        retro->next = prev;
    }

    head = retro;
}


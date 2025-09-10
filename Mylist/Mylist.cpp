#include "MyList.h"

// ===== Node =====
template <typename T>
Node<T>::Node(T val) : data(val), prev(nullptr), next(nullptr) {}

template <typename T>
T Node<T>::getdata() const { return data; }

template <typename T>
void Node<T>::setdata(T val) { data = val; }

template <typename T>
Node<T>* Node<T>::getprev() { return prev; }

template <typename T>
Node<T>* Node<T>::getnext() { return next; }

// ===== Mylist =====
template <typename T>
Mylist<T>::Mylist() : head(nullptr), tail(nullptr), n(0) {}

template <typename T>
Mylist<T>::~Mylist() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
bool Mylist<T>::IsEmpty() { return n == 0; }

template <typename T>
int Mylist<T>::size() { return n; }

template <typename T>
void Mylist<T>::push_back(T value) {
    Node<T>* node = new Node<T>(value);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    n++;
}

template <typename T>
void Mylist<T>::push_front(T value) {
    Node<T>* node = new Node<T>(value);
    if (IsEmpty()) {
        head = tail = node;
    } else {
        head->prev = node;
        node->next = head;
        head = node;
    }
    n++;
}

template <typename T>
void Mylist<T>::insert(T value, int index) {
    if (index < 0 || index > n) {
        cout << "Vi tri chen khong hop le\n";
        return;
    }

    if (index == 0) {
        push_front(value);
        return;
    }
    if (index == n) {
        push_back(value);
        return;
    }

    Node<T>* node = new Node<T>(value);
    Node<T>* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    node->next = current->next;
    node->prev = current;
    current->next->prev = node;
    current->next = node;
    n++;
}

template <typename T>
void Mylist<T>::pop_back() {
    if (IsEmpty()) return;
    Node<T>* temp = tail;
    tail = tail->prev;
    n--;
    if (!IsEmpty()) tail->next = nullptr;
    else head = tail = nullptr;
    delete temp;
}

template <typename T>
void Mylist<T>::pop_front() {
    if (IsEmpty()) return;
    Node<T>* temp = head;
    head = head->next;
    n--;
    if (!IsEmpty()) head->prev = nullptr;
    else head = tail = nullptr;
    delete temp;
}

template <typename T>
void Mylist<T>::erase(int index) {
    if (index < 0 || index >= n) return;

    if (index == 0) {
        pop_front();
        return;
    }
    if (index == n - 1) {
        pop_back();
        return;
    }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    n--;
}

template <typename T>
void Mylist<T>::print() {
    Node<T>* current = head;
    cout << "Danh sach lien ket: ";
    while (current) {
        cout << current->getdata() << " ";
        current = current->getnext();
    }
    cout << endl;
}

template <typename T>
void Mylist<T>::printReverse() {
    Node<T>* current = tail;
    cout << "Danh sach nguoc: ";
    while (current) {
        cout << current->getdata() << " ";
        current = current->getprev();
    }
    cout << endl;
}

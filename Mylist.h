#ifndef MYLIST_H
#define MYLIST_H

#include<iostream>
#include"pair.hpp"
using namespace std;

template <typename T>
class Mylist;

template <typename T>
class Node {
private:
    T data;
    Node<T>* prev;
    Node<T>* next;
public:
    Node(T val);
    T getdata() const;
    T& refgetdata();
    void setdata(T val);
    Node* getprev();
    Node* getnext();
    bool operator == (const Node<T>&) const;
    bool operator != (const Node<T>&) const;
    friend class Mylist<T>;
};

template <typename T>
class Mylist {
private:
    Node<T>* head;
    Node<T>* tail;
    int n;
public:
    Mylist();
    ~Mylist();

    bool IsEmpty();
    int size();
    Node<T>* getNodeByValue(T value);

    void push_back(T value);
    void push_front(T value);
    void insert(T value, int index);
    void insert(Node<T>* position, T value);
    void pop_back();
    void pop_front();
    void erase(int index);
    void erase(Node<T>* index);
    void erase(const T &value);
    void print();
    Node<T>* begin();
    Node<T>* end();
    bool operator==(const Mylist<T>& other) const;
    bool operator!=(const Mylist<T>& other) const;
};

template <typename T>
Node<T>::Node(T val) : data(val), prev(nullptr), next(nullptr) {}

template <typename T>
T Node<T>::getdata() const { return data; }
template <typename T>
T& Node<T>::refgetdata() { return data; } 

template <typename T>
void Node<T>::setdata(T val) { data = val; }

template <typename T>
Node<T>* Node<T>::getprev() { return prev; }

template <typename T>
Node<T>* Node<T>::getnext() { return next; }

template <typename T>
bool Node<T>::operator == (const Node<T>& other) const{
    return this->getdata() == other.getdata();
}

template <typename T>
bool Node<T>::operator != (const Node<T>& other) const{
    return this->getdata() != other.getdata();
}

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
Node<T>* Mylist<T>::getNodeByValue(T value) {
    Node<T>* current = head;
    while (current) {
        if (current->getdata() == value)
            return current;
        current = current->getnext();
    }
    return nullptr;
}

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
        cout << "Vi tri chen khong hop le" << endl;
        return;
    }
    if (index == 0) { push_front(value); return; }
    if (index == n) { push_back(value); return; }

    Node<T>* node = new Node<T>(value);
    Node<T>* current = head;
    for (int i = 0; i < index - 1; i++) current = current->next;

    node->next = current->next;
    node->prev = current;
    current->next->prev = node;
    current->next = node;
    n++;
}

template <typename T>
void Mylist<T>::insert(Node<T>* position, T value) {
    if (position == nullptr) {
        cout << "Node chi dinh khong hop le!" << endl;
        return;
    }

    Node<T>* node = new Node<T>(value);

    if (position == tail) { 
        position->next = node;
        node->prev = position;
        tail = node;
    } else {
        node->next = position->next;
        node->prev = position;
        position->next->prev = node;
        position->next = node;
    }
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
    if (index == 0) { pop_front(); return; }
    if (index == n - 1) { pop_back(); return; }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) current = current->next;

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    n--;
}

template <typename T>
void Mylist<T>::erase(Node<T>* position) {
    if (position == nullptr) return;

    if (position == head) { pop_front(); return; }
    if (position == tail) { pop_back(); return; }

    position->prev->next = position->next;
    position->next->prev = position->prev;
    delete position;
    n--;
}

template <typename T>
void Mylist<T>::erase(const T& value) {
    Node<T>* nodeToDelete = getNodeByValue(value);
    
    if (nodeToDelete != nullptr) {
        erase(nodeToDelete); 
    }
}

template <typename T>
void Mylist<T>::print() {
    Node<T>* current = head;
    while (current) {
        cout << current->getdata() << " ";
        current = current->getnext();
    }
    cout << endl;
}

template <typename T>
Node<T>* Mylist<T>::begin(){
    return head;
}

template <typename T>
Node<T>* Mylist<T>::end(){
    return nullptr;
}

template <typename T>
bool Mylist<T>::operator==(const Mylist<T>& other) const {
    if (this->n != other.n) 
        return false;

    Node<T>* cur1 = this->head;
    Node<T>* cur2 = other.head;

    while (cur1 && cur2) {
        if (!(cur1->getdata() == cur2->getdata()))
            return false;
        cur1 = cur1->getnext();
        cur2 = cur2->getnext();
    }
    return true;
}

template <typename T>
bool Mylist<T>::operator!=(const Mylist<T>& other) const {
    return !(*this == other);
}

#endif

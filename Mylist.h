#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
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
    void setdata(T val);
    Node* getprev();
    Node* getnext();
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
    void print();
};

#include "mylist.cpp"
#endif

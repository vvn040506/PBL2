#ifndef MYLIST_H
#define MYLIST_H

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node {
private:
    T data;
    Node* prev;
    Node* next;
public:
    Node(T val);
    T getdata() const;
    void setdata(T val);
    Node* getprev();
    Node* getnext();
    template <typename U> friend class Mylist;
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
    void push_back(T value);
    void push_front(T value);
    void insert(T value, int index);
    void pop_back();
    void pop_front();
    void erase(int index);
    void print();
    void printReverse();
};

#include "MyList.cpp"

#endif // MYLIST_H

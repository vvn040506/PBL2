#include "HashTable.h"
#include "Person.h"
#include <QDebug>

void searchByCCCD(const QString& cccd, HashTable<Person>& ds){
    int pos = ds.hash_function(cccd);

    for(Node<Person> *x = ds.buckets[pos].begin(); x != nullptr; x = x->getnext()) {
        if(x->getdata().getCCCD() == cccd){
            Person &p = x->refgetdata();
            qDebug() << p;
            return;
        }
    }

    qDebug() << "Khong tim thay CCCD:" << cccd;
}

Person& getByCCCD(const QString& cccd, HashTable<Person>& ds) {
    int pos = ds.hash_function(cccd);
    for (Node<Person>* x = ds.buckets[pos].begin(); x != nullptr; x = x->getnext()) {
        if (x->getdata().getCCCD() == cccd)
            return x->refgetdata();
    }
    throw std::runtime_error("Khong tim thay CCCD");
}

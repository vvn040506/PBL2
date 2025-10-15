#include"Person.h"
#include"pair.hpp"
#include"HashTable.h"
class Police: public Person{
    private:
        string id_police;
    public:
        static HashTable<Pair>* dsPolice;
        Police(){ id_police = " "; }
        Police(const string& id) : id_police(id) {}
        ~Police() {}
        string getID() { return id_police; }
        //thêm thông tin CA nhập
        static void addPoliceWork(const string& id_police, const string& bienso, const string& ngay){
            if(dsPolice != nullptr){
                dsPolice->insert(id_police, Pair(bienso, ngay));
            }
        }
        static void showPoliceWork(const string& id){
            int pos = dsPolice->hash_function(id);
            for(Node<Pair> *x = dsPolice->buckets[pos].begin(); x != dsPolice->buckets[pos].end(); x = x->getnext()){
                cout << "Da nhap vao bien so: " << x->getdata().key << " - Ngay: " << x->getdata().value << endl;
            }
        }
        static Mylist<Pair> getPoliceWork(const string& id){
            if(dsPolice != nullptr){
                int pos = dsPolice->hash_function(id);
                return dsPolice->buckets[pos];
            }
            return Mylist<Pair>();
        }
};

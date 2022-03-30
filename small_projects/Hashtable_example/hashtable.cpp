#include "hashtable.h"

Hash::Hash(int size) {
    this -> bucket = size;
    table = new list<int>[bucket];
}

void Hash::insertItem(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}
void Hash::deleteItem(int key) {
    int index = hashFunction(key);
    list<int>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) break;
    }
    if (i != table[index].end()) {
        table[index].erase(i);
    } else {
        cout << "Item does not exist" << endl;
    }
}

void Hash::displayTable() {
    for(int i = 0; i < bucket; ++i){
        cout << i;
        for(auto x:table[i]){
            cout << " --> " << x;
        }
        cout << endl;
    }
}

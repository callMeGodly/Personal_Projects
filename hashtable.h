#ifndef STUDY_HASHTABLE_H
#define STUDY_HASHTABLE_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Hash{
public:
    explicit Hash(int size);
    void insertItem(int key);
    void deleteItem(int key);
    void displayTable();

    int hashFunction(int x) const {
        return (x % bucket);
    }
private:
    int bucket;
    list<int>* table;
};

#endif

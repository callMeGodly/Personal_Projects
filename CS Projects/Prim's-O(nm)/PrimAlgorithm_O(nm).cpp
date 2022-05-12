#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <set>

using namespace std;

#define Edge pair<int,int>

long long int primAlgorithm(string filename){

    map< int, set<Edge >* > adjacencyList;
    set<int> X;
    fstream newfile;

    int numNode = 0;
    int numEdges = 0;
    int v1, v2, cost;

    long long int minval = 0;

    string tp;
    newfile.open(filename,ios::in);
    if (newfile.is_open()){ //  reads in all the data from jobs.txt
        getline(newfile, tp);
        sscanf(tp.c_str(),"%d %d", &numNode, &numEdges);
        for(int i = 1; i <= numNode; ++i){
            set< Edge >* newSet = new set< Edge >();
            adjacencyList.insert(make_pair(i, newSet));
        }
        while(getline(newfile, tp)){
            sscanf(tp.c_str(),"%d %d %d", &v1, &v2, &cost);
            Edge new_edge;
            new_edge.first = v2;
            new_edge.second = cost;
            map< int, set<Edge >* >::iterator it = adjacencyList.find(v1);
            map< int, set<Edge >* >::iterator itr = adjacencyList.find(v2);
            it->second->insert(new_edge);
            new_edge.first = v1;
            new_edge.second = cost;
            itr->second->insert(new_edge);
            
        }
        newfile.close();
    }

    int to_find = adjacencyList.begin()->first;
    X.insert(to_find);

    while(X.size() != numNode){
        int min_cost = INT_MAX;
        for(auto i: X){
            set< Edge > check = *adjacencyList[i];
            for(auto j: check){
                if((X.find(j.first) == X.end()) && (min_cost > j.second)){
                    to_find = j.first;
                    min_cost = j.second;
                }
            }
        }
        X.insert(to_find);
        minval += min_cost;
    }
    
    for(auto i: adjacencyList){
        delete i.second;
    }

    return minval;
}


int main(void){

    cout << primAlgorithm("edges.txt") << endl;

    return 0;
}
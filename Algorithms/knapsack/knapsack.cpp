#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

ll knapsack_helper(int weight, unsigned ll** table, vector<pair<int,int> >& list, int step){

    if (step < 0)
        return 0;
    if (table[step][weight] != -1)
        return table[step][weight];

    int toTest = list[step].second;
    int vi = list[step].first;
 
    if (toTest > weight) {
        table[step][weight] = knapsack_helper(weight, table, list, step-1);
        return table[step][weight];
    }
    else {
        table[step][weight] = max(vi + knapsack_helper(weight - toTest, table, list, step-1), knapsack_helper(weight, table, list, step-1));
        return table[step][weight];
    }


}

ll knapsack(string input){

    int W = 0;
    int numberItems = 0;
    fstream newfile;
    string tp;
    newfile.open("knapsack_big.txt",ios::in);
    vector<pair<int,int > > list;

    int value;
    int weight;
    ll retval = 0;

    if (newfile.is_open()){ //  reads in all the data from jobs.txt
        getline(newfile, tp);
        sscanf(tp.c_str(),"%d %d", &W, &numberItems);
        while(getline(newfile, tp)){
            sscanf(tp.c_str(),"%d %d", &value, &weight);
            pair<int, int> to_add = make_pair(value, weight);
            list.push_back(to_add); 
        }
        newfile.close();
    }

    unsigned ll **table;
    table = new unsigned ll *[numberItems];
    for(int i = 0; i < numberItems; i++) table[i] = new unsigned ll[W+1];

    for(int i = 0; i < numberItems; ++i){
        for(int j = 0; j <= W; ++j){
            table[i][j] = -1;
        }
    }

    retval = knapsack_helper(W, table, list, numberItems-1);

    return retval;
}


int main(){
    
    cout << knapsack("knapsack_big.txt") << endl;

    return 0;
}
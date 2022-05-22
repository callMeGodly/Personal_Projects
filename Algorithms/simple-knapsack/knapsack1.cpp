#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

int main(void){

    ll W = 0;
    ll numberItems = 0;
    fstream newfile;
    string tp;
    newfile.open("knapsack_big.txt",ios::in);
    vector<pair<ll,ll > > input;

    ll value;
    ll weight;

    if (newfile.is_open()){ //  reads in all the data from jobs.txt
        getline(newfile, tp);
        sscanf(tp.c_str(),"%lld %lld", &W, &numberItems);
        while(getline(newfile, tp)){
            sscanf(tp.c_str(),"%lld %lld", &value, &weight);
            pair<ll, ll> to_add = make_pair(value, weight);
            input.push_back(to_add); 
        }
        newfile.close();
    }

    ll table [numberItems][W];

    for(ll i = 0; i < W; ++i){
        table[0][i] = 0;
    }

    for(ll i = 1; i < numberItems; ++i){
        ll toTest = input[i].second;
        ll vi = input[i].first;
        for(ll x = 0; x < W; ++x){
            if(toTest > x){
                table[i][x] = table[i-1][x];
            }
            else{
                table[i][x] = max(table[i-1][x], table[i-1][x-toTest] + vi);
            }
        }
    }

    ll retval = table[numberItems-1][W-1];

    cout << retval << endl;
    cout << "got" << endl;
    return 0;
}
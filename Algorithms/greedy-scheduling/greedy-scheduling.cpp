#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

//  a struct to hold the values of a job (weight, length) then computes its difference and ratio
struct item{
    int weight;
    int length;
    int difference;
    double ratio;
    item(int w, int l): weight(w), length(l), difference(w-l), ratio((double)w/l)
    {}
};

// greedy algorithm that schedules jobs in decreasing order of the difference (weight - length)
// if two jobs have equal difference (weight - length), you should schedule the job with higher weight first
bool compare1(item* i, item*j){
    if(i->difference > j->difference){
            return true;
        }
    else if(i->difference == j->difference && i->weight > j->weight){
        return true;
    }
    return false;
}

// the greedy algorithm that schedules jobs (optimally) in decreasing order of the ratio (weight/length)
// it does not matter how you break ties
bool compare2(item* i, item*j){
    return i->ratio > j->ratio;
}

long long int schedule(string filename, int comparison){
    long long int sumtime = 0;
    long long int sumlength = 0;
    vector<item*> allJobs;
    fstream newfile;
    string tp;
    int w, l;
    newfile.open("jobs.txt",ios::in);
    if (newfile.is_open()){ //  reads in all the data from jobs.txt
        getline(newfile, tp);
        while(getline(newfile, tp)){
            sscanf(tp.c_str(),"%d %d", &w, &l);
            item* newItem = new item(w,l);
            allJobs.push_back(newItem);
        }
        newfile.close();
    }
    if(comparison == 1) sort(allJobs.begin(), allJobs.end(), compare1); // sorts all the jobs based on a given greedy algorithm
    else sort(allJobs.begin(), allJobs.end(), compare2); // sorts all the jobs based on a given greedy algorithm
    
    for(auto i: allJobs){
        sumlength += i->length; // records the previous completion time
        sumtime += i->weight * sumlength; // stores the sum of weighted completion times of the resulting schedule
    }
    
    for(auto i: allJobs){
        delete i;
    }

    return sumtime;
}

int main(void){

    cout << schedule("jobs.txt", 1) << endl;
    return 0;
}
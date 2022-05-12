
#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

void wordle_helper(std::set<std::string>& possible, std::string in, std::string floating, const std::set<std::string>& dict, unsigned int position, const unsigned int size, unsigned int remaining, unsigned int fixed);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating, 
    const std::set<std::string>& dict)
{
    //  creates a set for the helper function to add possible answers
    std::set<std::string> answers;
    unsigned int position = 0;
    unsigned int size = in.length();
    unsigned int remaining = floating.length();
    unsigned int fixed = 0;
    for(char i : in){
        if(i != '-') ++fixed;
    }
    wordle_helper(answers, in, floating, dict, position, size, remaining, fixed); //  calls the wordle helper function
    return answers;
}

void wordle_helper(std::set<std::string>& possible, std::string in, std::string floating, const std::set<std::string>& dict, unsigned int position, const unsigned int size, unsigned int remaining, unsigned int fixed){

    const string albet{"abcdefghijklmnopqrstuvwxyz"}; // string for the alphabet

    if(position == size){ //    if the position is at the size, the word gets tested in the dictionary to see if valid
        if(dict.find(in) != dict.end()) possible.insert(in);
        return;
    }
    
    if(in[position] == '-'){ // if the position is clear to add
        string next_f = floating;
        for(char j : floating){ // tries all the floating first
            in[position] = j;
            next_f.erase(0,1); // manipulates a stack like structure, so when one removes from the front, the float gets added back
                               // after testing it
            char add_back = j;
            wordle_helper(possible, in, next_f, dict, position+1, size, remaining-1, fixed); // remaining floats decreases by 1
            next_f += add_back;
        }
        if(position + remaining + fixed < size){ // if the position plus remaining floats plus fixed is less than the size
                                                 // we can test the alphabet
            for(char k : albet){
                in[position] = k;
                wordle_helper(possible, in, floating, dict, position+1, size, remaining, fixed);
            }  
        }
    }
    else{ // case where encountered a fix, increase to the next position then minus one from future fixed
        wordle_helper(possible, in, floating, dict, position+1, size, remaining, fixed - 1);
    }
}

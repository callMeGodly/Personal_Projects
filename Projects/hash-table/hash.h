#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {   
        unsigned long long retval = 0;
        unsigned long long w[5] = {0}; // stores the conversion to base 36
        unsigned long long to_convert[6] = {0}; // stores the characters' conversion to base 36
        unsigned int index = 5; //  indexing is reversed
        unsigned int w_index = 4; //  indexing is reversed
        unsigned int to_count = 0; // if 6 then compute value

        for(int i = k.length()-1; i >= 0; --i){
            to_convert[index] = letterDigitToNumber(k[i]);
            --index;
            ++to_count;
            // if 6 compute the value, then decrement w's index
            if(to_count == 6){

                // uses a linear time way of computing a power
                for(int j = 0; j < 6; ++j){
                    w[w_index] = w[w_index]* 36 + to_convert[j];
                    to_convert[j] = 0;
                }
                --w_index;

                //  resets the value to count for 6 characters, index for to_convert
                to_count = 0;
                index = 5;
            }
        }

        // adds remaining in w, even if all 0, still good to check in case of any non-zero values
        for(int j = 0; j < 6; ++j) w[w_index] = w[w_index]* 36 + to_convert[j];

        // creates the hashvalue by using rvalues and w
        for(int i = 0; i < 5; ++i) retval += (w[i] * rValues[i]);

        return retval;                
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char to_convert = tolower(letter);
        if((int)to_convert >= 97) return (int)to_convert - 97; // 97 because 'a' ascii value is 97
        else return (int)to_convert - 22; // 22 comes from -48 + 26

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

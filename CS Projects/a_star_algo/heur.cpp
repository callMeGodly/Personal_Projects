#include <cmath>
#include "heur.h"
#include <vector>
#include <set>
using namespace std;

// Complete
size_t BFSHeuristic::compute(const Board& b)
{
    return 0U;
}


//  computes only the cars the escape car hits on its row
//  To be completed
size_t DirectHeuristic::compute(const Board& b)
{
    
    //  sets up the staring coordinates to check the row
    set<char> found_cars;
    Vehicle escape = b.escapeVehicle();
    int c = escape.startc;
    int r = escape.startr;
    
    //  if there is a car, checks if already added in set
    //  if not then insert the car into cars that block the escape car
    for(int i = c+2; i < b.size(); ++i){
        char name = b.at(r, i);
        if(name != '.'){
            found_cars.insert(name);
        }
    }
    
    return found_cars.size();
    
}

size_t IndirectHeuristic::compute(const Board& b)
{
    //  sets up the starting coordinates
    set<char> found_cars;
    Vehicle escape = b.escapeVehicle();
    int c = escape.startc;
    int r = escape.startr;
    
    for(int i = c+2; i < b.size(); ++i){
        
        //  finds the cars that directly block the escape car
        //  if the car blocks then find if it is indirectly blocked by any
        char name = b.at(r, i);
        set<char> s1_found;
        set<char> s2_found;
        if(name != '.'){
            found_cars.insert(name);
            
            //  retrieves the information of the directly block
            Vehicle direct = b.vehicle(name);
            int dc = direct.startc;
            int dr = direct.startr;
            int l = direct.length;
            s1_found.clear();
            s2_found.clear();
            bool side1 = false;
            bool side2 = false;
                
                //  checks if the car can move up
                //  if so then check how many cars block it
                if((r - l) >= 0){
                    side1 = true;
                    for(int k = dr; k >= r-l; --k){
                        char ind = b.at(k, dc);
                        if(ind != '.'){
                            s1_found.insert(ind);
                        }
                    }
                }
                
                //  checks if the car can move down
                //  if so then check how many cars block it
                if((r + l) < b.size()){
                    side2 = true;
                    for(int k = dr+l; k <= r+l; ++k){
                        char ind = b.at(k, dc);
                        if(ind != '.'){
                            s2_found.insert(ind);
                        }
                    }
                }
            
            //  the result will not be inserted if
            //  either top or bottom have cars blocking
            //  if both sides are blocked it is not added
            //  if one side is free of block and the other is blocked
            
            //  else starts retriveing the number of indirectly blocked cars
            if((s1_found.size() != 0) && !side2 && (s2_found.size() == 0)){
                for(char i: s1_found){
                    found_cars.insert(i);
                }
            }
            if((s2_found.size() != 0) && !side1 && (s1_found.size() == 0)){
                for(char i: s2_found){
                    found_cars.insert(i);
                }
            }
        }
    }
    
    return found_cars.size();
}


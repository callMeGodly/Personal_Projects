

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

static const Worker_T INVALID_ID = (unsigned int)-1;


//  schedule_helper function prototype
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    unsigned int day,
    const unsigned int number_workers,
    unsigned int shift_num[]
);


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    //  initializes the variables for the helper
    unsigned int number_workers = avail[0].size();
    unsigned int shift_num[number_workers] = {0};
    //  calls the helper
    return schedule_helper(avail, dailyNeed, maxShifts, sched, 0, number_workers, shift_num);
}

//  schedule_helper function
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    unsigned int day,
    const unsigned int number_workers,
    unsigned int shift_num[]
)
{
    if(day == avail.size()) return true; //     base case when all days are filled
    vector<Worker_T> current; //    current line-up
    vector<Worker_T> to_skip; //    those who cant be in the combination but potentially may be again
    vector<Worker_T> perm_skip; //  those who never can be in the combination

    for(unsigned int i = 0; i < number_workers; ++i){


        if((avail[day][i] == true) //   checks if the worker can be in a combination
            && (shift_num[i] < maxShifts) 
            && (find(to_skip.begin(), to_skip.end(), i) == to_skip.end()) 
            && (find(perm_skip.begin(), perm_skip.end(), i) == perm_skip.end())
        )
        {
            current.push_back(i);
            shift_num[i] += 1;
            if(current.size() == dailyNeed){ // if the size matches the daily need recurse on
                sched.push_back(current);
                bool can_do = schedule_helper(avail, dailyNeed, maxShifts, sched, day+1, number_workers, shift_num); // recurses
                if(!can_do){
                    sched.pop_back();
                    if(i + 1 == number_workers){    //  if at the end remove what the second one can be then continue
                        if(dailyNeed > 1) to_skip.push_back(current[1]); // eliminating the one case, for invalid read
                        if(dailyNeed <= 2){ //  if daily need is less than 2 need to add to perm right now, since no more possible combinations after the end
                            perm_skip.push_back(current[0]); // makes the first item permanently skipped so we don't get duplicate combinations
                            to_skip.clear();
                        }
                        for(auto j: current) shift_num[j] -= 1; // resets the shift count for the day
                        current.clear();
                        i = 0;
                        continue;
                    }
                    else{ //    if not at the end of the loop simply just remove the last and keep finding
                        shift_num[i] -= 1;
                        current.pop_back();
                        continue;
                    }
                }
                else return true;
            }
        }
        if((i + 1 == number_workers) && !current.empty()){
            perm_skip.push_back(current[0]); // makes the first item permanently skipped so we don't get duplicate combinations
            to_skip.clear();
            for(auto j: current) shift_num[j] -= 1; // resets the shift count for the day
            current.clear();
            i = 0;
            continue;
        }
    }

    // removes the shift count of the failed line-up
    for(auto i: current) shift_num[i] -= 1;
    return false;
}

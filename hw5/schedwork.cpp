

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t> daysWorking,
    size_t day
);

// Add your implementation of schedule() and other helper functions here

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
    // Add your code below
    std::vector<size_t> daysWorking;
    for (size_t i = 0; i < avail[0].size(); i ++)
        daysWorking.push_back(0);

    for (size_t i = 0; i < avail.size(); i ++){
        std::vector<Worker_T> empty;
        sched.push_back(empty);
    }
    std::cout << sched.size() << std::endl;
    return scheduleHelper (avail, dailyNeed, maxShifts, sched, daysWorking, 0);

}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t> daysWorking,
    size_t day
)
{
    //when sched size is the same as availability matrix size, return true
    //?? do i need to check if null
    //if (sched.size() >= avail.size())
    if (day >= avail.size()){  //size of the vectors
        std::cout <<"you're done!" << std::endl;
        return true;
    }        
    //else, you already sched everything today
    else if (sched[day].size() >= dailyNeed){
        //push back today's arrangement into your schedule
        //call recursive function again to work on another day's schedule
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, daysWorking, day+1);

    }
    //else, you were trying to fill in todays arrangement
    else {
        //for loop (wordle) iterates through everyone available in that day
        bool alreadyWorkingToday = false;
        for (Worker_T id = 0; id < avail[0].size(); id ++){
            if (!sched[day].empty()){
                for (size_t i = 0; i < sched[day].size(); i ++){
                    if (sched[day][i] == id)
                        alreadyWorkingToday = true;
                }
            }
            //insert person there if availability is 1 and max days hasn't been reached
            bool works = false;
            if (avail[day][id] == 1 && daysWorking[id] < maxShifts 
                && !alreadyWorkingToday){
                sched[day].push_back(id);
                daysWorking[id]++;
                //call your recursive function
                works = scheduleHelper(avail, dailyNeed, maxShifts, sched, 
                    daysWorking, day);
                //erase the person from the schedule again //backtracing 1
                //if return value is true then your function returns true 2
                if (works == true)
                    return true;
                sched[day].pop_back();
                daysWorking[id]--;
                
            }
        }        
    } 
    //when you try every single combination and nothing works, just return false 
    return false;
}

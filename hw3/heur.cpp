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


// To be completed
size_t DirectHeuristic::compute(const Board& b)
{
    // Avoid compiler warnings -- replace this
    //how many are directly in the way to the right of the a

    //startr +length 
    //check if there's a vehicle 
    //add everything you find to a set inside compute function and look at size of set

    int row = b.vehicle('a').startr; //always same
    int col = b.vehicle('a').startc + b.vehicle('a').length;
    //std::cout << row << " " << col << " " << b.vehicle('a').length << endl;
    set<char> direct_blocks;

    for (int col = b.vehicle('a').startc + b.vehicle('a').length; col < b.size(); col++){
        if (b.at(row, col) != '.'){
            direct_blocks.insert(b.at(row,col));
        }
    }
    return direct_blocks.size();

    //return 0;
}

// To be completed
size_t IndirectHeuristic::compute(const Board& b)
{
    // Avoid compiler warnings -- replace this
    // 

    std::cout << "SWAG NEW BROSKI" << std::endl;
    //copy paste direct algorithm to find a set of all direct blcoking car
    int row = b.vehicle('a').startr; //always same
    int col = b.vehicle('a').startc + b.vehicle('a').length;
    set<char> direct_blocks;
    set<char> total_blocks;
    set<char> total_blocks_down;
    set<char> total_blocks_up;

    for (int col = b.vehicle('a').startc + b.vehicle('a').length; col < b.size(); col++){
        if (b.at(row, col) != '.'){
            int car_length = b.vehicle(b.at(row, col)).length; 
            std::cout << b.at(row, col) << " " << car_length << std::endl;

            bool top_unable = false;
            if (car_length >= b.vehicle(b.at(row, col)).startr)
                top_unable = true;
            bool bottom_unable = false;
            if ((b.size() - car_length) <= b.vehicle(b.at(row, col)).startr)
                bottom_unable = true;

            std::cout << top_unable << " " << bottom_unable << std::endl;
            if (top_unable && bottom_unable){
                continue;
            }
            direct_blocks.insert(b.at(row,col));
            total_blocks.insert(b.at(row,col));
            std::cout << "direct and total blocks " << b.at(row,col) << std::endl;
        }
    }
    //indirects will be horizontal but they will only be hit by vertical directs

    if (direct_blocks.empty())
        return 0;
    
    int indirect_block = 0;
    //loop through a set of directs
    set<char>::iterator itr;
    for (itr = direct_blocks.begin(); itr != direct_blocks.end(); itr++) {
        const int starting_top_i = b.vehicle(*itr).startr;
        const int starting_bottom_i = starting_top_i + b.vehicle(*itr).length;
        std::cout << starting_top_i << " " << starting_bottom_i << std::endl;

        if (b.escapeVehicle().startr >= b.vehicle(*itr).length &&
            (b.size()-b.escapeVehicle().startr) >= (b.vehicle(*itr).length))
            continue;
        

        //row index of top of directly blocking car
        int top_i = b.vehicle(*itr).startr;
        //row index of bottom of directly blocking car
        int bottom_i = starting_top_i + b.vehicle(*itr).length-1; //changeed
        //column index of directly blocking car
        int c = b.vehicle(*itr).startc;
        
        std::cout << top_i << " " << bottom_i << " " << c << std::endl;        
        
        int amount = 1;
        //when bottom hits the bottom of the grid, stop moving car
        int bottom_moved = starting_bottom_i + amount;
        std::cout << b.size()-1 << std::endl;

        while (bottom_moved <= b.size()-1) {
            std::cout <<"bottom moved " << bottom_moved << std::endl;
            if (b.at(bottom_moved,c) != '.'){
                std::cout << "car blocked " << b.at(bottom_moved,c) << std::endl;
                top_i = starting_top_i+amount;    
                if (top_i < b.escapeVehicle().startr){
                    total_blocks.insert(b.at(bottom_moved,c));
                    total_blocks_down.insert(b.at(bottom_moved,c));
                }
                break;
            }
            amount ++;
            bottom_moved = starting_bottom_i + amount;
        }

        //up
        amount = 1;
        int top_moved = starting_top_i - amount;
        while (top_moved >= 0) {
            std::cout <<"top moved " << top_moved << std::endl;
            char this_car = b.at(top_moved, c);
            if (b.at(top_moved,c) != '.'){
                std::cout << "car blocked" << b.at(top_moved,c) << std::endl;
                bottom_i = starting_bottom_i-amount;
                if (bottom_i >= b.escapeVehicle().startr){
                    total_blocks.insert(b.at(top_moved,c));
                    total_blocks_up.insert(b.at(top_moved,c));
                }
                break;
            }
            amount ++;
            top_moved = starting_top_i - amount;

        }


    }

    //move car down by creating a bottom_moved
    //edge case: bottom hits the bottom of the grid, don't care
    //if car found, move top down by same amount
    //see top <= escape row, add to indirect set
    //or if bottom is less than escape row
    //add the car that it hits to set

    //see if you can go up enough to get out of the way car

//up indirects same as down indirects
    //create a moved with top
    //if car found, move bottom up 
    //if bottom >= escape, add vehicle 

//if one car is being indirectly blocked by one above and below it it cancels each other out

    
    
    std::cout << "total blocks {";
    for (std::set<char>::iterator c = total_blocks.begin(); c != total_blocks.end(); ++c){

        std::cout << " " << *c;
    }
    std::cout << " }" << std::endl;

    std::cout << "total blocks down {";
    for (std::set<char>::iterator c = total_blocks_down.begin(); c != total_blocks_down.end(); ++c){
        
        std::cout << " " << *c;
    }
    std::cout << " }" << std::endl;

     std::cout << "total blocks up {";
    for (std::set<char>::iterator c = total_blocks_up.begin(); c != total_blocks_up.end(); ++c){
        
        std::cout << " " << *c;
    }
    std::cout << " }" << std::endl;

    //don't remove, wrong
    /*if (total_blocks_down.empty()){
        for (std::set<char>::iterator i = total_blocks_up.begin(); i != total_blocks_up.end(); ++i){
            total_blocks.erase(*i);
        }
    }
    else if (total_blocks_up.empty()){
        for (std::set<char>::iterator i = total_blocks_down.begin(); i != total_blocks_down.end(); ++i){
            total_blocks.erase(*i);
        }
    }*/

    return total_blocks.size();
}


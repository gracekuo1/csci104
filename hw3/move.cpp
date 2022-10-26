#include "move.h"


// Complete
Move::Move(Board* board)
{
    m.first = Vehicle::INVALID_ID;
    m.second = 0;
    b = board;
    g = 0;
    h = 0;
    prev = NULL;
}

// To be completed
Move::Move(const Board::MovePair& move, Board* b,  Move *parent)
{
    m.first = move.first;
    m.second = move.second;
    this->b = b;
    g = 0;
    h = 0; 
    prev = parent;
}

// To be completed
Move::~Move()
{
    //deallocated boards
}

// To be completed
bool Move::operator<(const Move& rhs) const
{
    // Replace this
    //return false;
    int this_f_score = this->h + this->g;
    int rhs_f_score = rhs.h + rhs.g;

    if (this_f_score < rhs_f_score)
        return true;
    else if (this_f_score == rhs_f_score){
        if (this->h < rhs.h)
            return true;
        else if (this->h == rhs.h){
            if (this->b < rhs.b)
                return true;
        }
    } 
    else
        return false;


}

// To be completed
void Move::score(Heuristic *heur) 
{
    h = heur->compute(*b);
}

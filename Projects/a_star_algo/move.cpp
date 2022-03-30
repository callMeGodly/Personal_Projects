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


// Constructor
// To be completed
Move::Move(const Board::MovePair& move, Board* b,  Move *parent)
{
    this->m = move;
    this->b = b;
    this->g = (parent->g) + 1;
    this->prev = parent;

}

// To be completed
Move::~Move()
{
    delete this->b;
}

// To be completed
bool Move::operator<(const Move& rhs) const
{
    
    //  if f is smaller return true
    //  if same f but smaller h return true
    //  if same f and same h return true if board is smaller
    int g_ = this->g;
    int h_ = this->h;
    int f = rhs.g + rhs.h;
    int f_ = g_ + h_;
    if(f_ < f) return true;
    if((f_ == f) && (h_ < rhs.h)) return true;
    if((f_ == f) && (h_ == rhs.h) && (this->b < rhs.b)) return true;
    
    return false;
}

// To be completed
void Move::score(Heuristic *heur) 
{
    //  computes the h value for every board using heuristic compute function
    this->h = heur->compute(*(this->b));
}

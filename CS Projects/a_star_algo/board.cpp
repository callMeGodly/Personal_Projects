#include "board.h"
#include <iomanip>
#include <string>
#include <stdexcept>
#include <set>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

const Board::VID_T Board::escapeID_ = 'a';

Board::Board()
{
    
}

Board::Board(std::istream& is)
{
    vector<string > rawBoard;
    string line;
    while(getline(is, line)) {
        // skip empty lines
        stringstream ss(line);
        string temp;
        // Skip if no text on this line
        if(!(ss << temp)){
            continue;
        }
        // Must have contents, let's add it
        rawBoard.push_back(line);
    }
    // Error check
    if(rawBoard.size() == 0) {
        throw std::logic_error("0 size board");
    }
    unsigned i = 0;
    // Ensure same number of columns and rows
    while(i < rawBoard.size()) {
        if(rawBoard[i].size() != rawBoard.size()) {
            throw std::logic_error("Invalid row size");
        }
        i++;
    }

    // allocate rows for the 2D board
    grid_.resize(rawBoard.size());

    // Find and build all the Vehicle objects from the 2D grid
    for(int r = 0; r < (int)rawBoard.size(); r++) {
        // allocate columns for each row
        grid_[r].resize(rawBoard[r].size());
        for(int c = 0; c < (int)rawBoard[r].size(); c++) {
            
            // If we have vehicle in this location, update the vehicle
            if( isalpha(rawBoard[r][c] )) {
                grid_[r][c] = rawBoard[r][c];
                map<char, Vehicle>::iterator it = vehicles_.find(rawBoard[r][c]);
                if(it == vehicles_.end()) {
                    vehicles_.insert(make_pair(rawBoard[r][c], Vehicle(r, c, rawBoard[r][c])));
                }
                else {
                    if(it->second.startr == r) {
                        it->second.direction = Vehicle::HORIZONTAL;
                        it->second.length = (c - it->second.startc + 1);
#ifdef DEBUG
                        cout << "Increasing " << it->second.id << " to len " << it->second.length
                             << " and dir=" << it->second.direction << endl;
#endif
                    }
                    else {
                        it->second.direction = Vehicle::VERTICAL;
                        it->second.length = (r - it->second.startr + 1);
#ifdef DEBUG
                        cout << "Increasing " << it->second.id << " to len " << it->second.length
                             << " and dir=" << it->second.direction << endl;
#endif
                    }
                }
            }
            // Blank space
            else if( Vehicle::INVALID_ID  == rawBoard[r][c] )
            {
                grid_[r][c] = rawBoard[r][c];
            }
            else {
                throw std::logic_error("Invalid character in board");
            }
        }
    }
}

Board::Board(const Board& b) :
    vehicles_(b.vehicles_), grid_(b.grid_), history(b.history)
{
    
}

Board::~Board()
{
    
}

int Board::size() const 
{
    return (int) grid_.size();
}

Board::VID_T Board::at(int r, int c) const
{
    if(r >= (int)grid_.size() || c >= (int)grid_.size() || r < 0 || c < 0)
    {
        throw std::invalid_argument("Out of bounds index to at()");
    }
    return grid_[r][c];
}

const Vehicle& Board::vehicle(VID_T vid) const
{
    // can't use operator[] since it isn't a const member of map
    return vehicles_.at(vid);
}

const Vehicle& Board::escapeVehicle() const
{
    // can't use operator[] since it isn't a const member of map
    return vehicles_.at(escapeID_);
}

bool Board::solved() const
{
    // can't use operator[] since it isn't a const member of map
    const Vehicle& v = vehicles_.at(escapeID_);
    int r = v.startr;
    for(int c = v.startc + v.length; c < (int)grid_[r].size(); c++)
    {
        if(grid_[r][c] != Vehicle::INVALID_ID){
            return false;
        }
    }
    return true;
}

bool Board::isLegalMove(VID_T vid, int amount) const
{
    // can't use operator[] since it isn't a const member of map
    const Vehicle& v = vehicles_.at(vid);
    if(v.direction == Vehicle::VERTICAL) {
        int newr = v.startr + amount;
        // Is target location still on the board
        if( (newr < 0) || ((newr + v.length) > (int) grid_.size()) ) {
            return false;
        }

        // Check if any other vehicle is blocking
        if(amount < 0)
        { 
            for(int r = v.startr-1; r >= newr; r--)
            {
                if(grid_[r][v.startc] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
        else 
        {
            for(int r = v.startr + v.length; r < v.startr + v.length + amount; r++)
            {
                if(grid_[r][v.startc] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
    }
    if(v.direction == Vehicle::HORIZONTAL) {
        int newc = v.startc + amount;

        // Is target location still on the board
        if( (newc < 0) || ((newc + v.length) > (int) grid_.size()) ) {
            return false;
        }

        // Check if any other vehicle is blocking
        if(amount < 0)
        { 
            for(int c = v.startc-1; c >= newc; c--)
            {
                if(grid_[v.startr][c] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
        else 
        {
            for(int c = v.startc + v.length; c < v.startc + v.length + amount; c++)
            {
                if(grid_[v.startr][c] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::move(VID_T vid, int amount)
{
    
    if(isLegalMove(vid, amount)) {
        Vehicle& v = vehicles_[vid];
        if(v.direction == Vehicle::VERTICAL) {
            v.startr += amount;
        }
        else {
            v.startc += amount;
        }
        updateBoard();
        
        //  adds into the history stack to record all made moves
        MovePair back = make_pair(vid, -amount);
        history.push(back);
        return true;
    }
    else {
        return false;
    }

}


void Board::undoLastMove()
{
    
    //  if the stack is empty can not undo
    if(!history.size()) throw std::underflow_error("no move to undo");
    
    //  move to return to previous move on the top of the stack
    MovePair m = history.top();
    move(m.first, m.second);
    
    //  removes the additional move from undoing then removes the moved move
    history.pop();
    history.pop();
    
}

Board::MovePairList Board::potentialMoves() const
{
    MovePairList retval;
    
    for(auto i: vehicles_){
        
        //  retrieves info from vehicle
        Vehicle check = i.second;
        int d = check.direction;
        int r = check.startr;
        int c = check.startc;
        
        //  if vertical
        if(d == 1){
            
            //  finds upwards
            int way = -1;
            while(r + way >= 0){
                if(isLegalMove(i.first, way)){
                    retval.push_back(make_pair(i.first, way));
                }
                --way;
            }
            
            //  finds downwards
            way = 1;
            while(r+check.length-1+way < this->size()){
                if(isLegalMove(i.first, way)){
                    retval.push_back(make_pair(i.first, way));
                }
                ++way;
            }
        }
        //  else horizontal
        else{
            
            //  finds leftwards
            int way = -1;
            while(c+way >= 0){
                if(isLegalMove(i.first, way)){
                    retval.push_back(make_pair(i.first, way));
                }
                --way;
            }
            
            //  finds rightwards
            way = 1;
            while(c+check.length-1+way < this->size()){
                if(isLegalMove(i.first, way)){
                    retval.push_back(make_pair(i.first, way));
                }
                ++way;
            }
        }
    }
    
    return retval;
}

bool Board::operator<(const Board& other) const
{
    //  loads the boards into 2 stringstreams to compare;
    stringstream ss;
    stringstream ss2;
    ss << *this;
    ss2 << other;
    
    //  compares the two strings if not the same return true
    if(ss.str() < ss2.str()) return true;
    
    return false;
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for(int r = 0; r < (int)b.grid_.size(); r++) {
        for(int c = 0; c < (int)b.grid_[r].size(); c++) {
            os << b.grid_[r][c];
        }
        os << endl;
    }
    return os;
}

void Board::updateBoard()
{
    for(int r = 0; r < (int)grid_.size(); r++) {
        for(int c = 0; c < (int)grid_[r].size(); c++) {
            grid_[r][c] = '.';
        }
    }
    for (auto mypair : vehicles_)
    {
        if(mypair.second.direction == Vehicle::VERTICAL)
        {
            for(int r = 0; r < mypair.second.length; r++)
            {
                grid_[mypair.second.startr + r][mypair.second.startc] = mypair.second.id;
            }
        }
        else 
        {
            // horizontal
            for(int c = 0; c < mypair.second.length; c++)
            {
                grid_[mypair.second.startr][mypair.second.startc + c] = mypair.second.id;
            }
        }
    }
}

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "solver.h"

using namespace std;

//  constructor
// To be completed
Solver::Solver(const Board& b, Heuristic *heur)
{
    this->b_ = b;
    this->heur_ = heur;
}

//  destructor
// To be completed
Solver::~Solver()
{
    for(auto i : closed_list){
        delete i;
    }
}

// To be completed
bool Solver::run()
{
    
    // initiates the start state for A*
    Board* newBoard = new Board(b_);
    Move* start = new Move(newBoard);
    start->score(heur_);
    open_list.push(start);
    closed_list.insert(start);
    expansions_++;
    
    
    //  while not empty find the solution
    //  if empty but not found return no solution
    while(!open_list.empty()){
        
        
        //  retrieves the best move
        Move* best_move = open_list.top();
        open_list.pop();
        closed_list.insert(best_move);
        
        //  checks if the board is solved
        if(best_move->b->solved()){
            while(best_move->prev != NULL){
                solutions_.push_back(best_move->m);
                best_move = best_move->prev;
            }
            reverse(solutions_.begin(), solutions_.end());
            return true;
        }
        
        
        //  uses uniform A*
        Board::MovePairList possible_moves = best_move->b->potentialMoves();
        for(auto i : possible_moves){
            Board* to_move = new Board(*(best_move->b));
            to_move->move(i.first, i.second);
            
            Move* newMove = new Move(i, to_move, best_move);
          
            //  if not in closed list add it to the open_list to explore new possibilities
            if(closed_list.find(newMove) == closed_list.end()){
                newMove->score(heur_);
                open_list.push(newMove);
                closed_list.insert(newMove);
                expansions_++;
            }
            else{
                delete newMove;
            }
        }
    }
    
    return false;
}

// To be completed
Board::MovePairList Solver::solution() const
{
    
    //  returns the solution of A* algorithm
    //  if not found returns empty list
    return solutions_;
}

// Complete
size_t Solver::numExpansions() const
{
    return expansions_;
}

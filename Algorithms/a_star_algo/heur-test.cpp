#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "heur.h"
#include "board.h"
#include "solver.h"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Provide the input file name and heuristic" << endl;
        return 1;
    }

    Heuristic *h=NULL;
    int heurID = atoi(argv[2]);
    if(heurID == 0) {
        h = new BFSHeuristic;
    }
    else if(heurID == 1) {
        h = new DirectHeuristic;
    }
    else if(heurID == 2){
        h = new IndirectHeuristic;
    }
    else {
        cerr << "Heuristic must be in the range 0 to 2...exiting" << endl;
        return 1;
    }
    
    // Start the game by reading in the board
    ifstream ifile(argv[1]);
    Board b1(ifile);
    cout << h->compute(b1) << endl;
    
    delete h;
    
    return 0;
}

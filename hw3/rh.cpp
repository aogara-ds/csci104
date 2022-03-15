#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "heur.h"
#include "board.h"
#include "solver.h"
using namespace std;

void doSolver(Board& b, Heuristic* h);

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
    bool won = false;
    cout << b1;
    // Main gameplay loop
    while( !won ) {
        Board::VID_T vid;
        int amount;
        cout << "Enter a vehicle and move amount (+ = dn/rt, - = up/lt), 'Q', '?', or 'Z' : ";
        cin >> vid;

        if(vid == 'Q' )
        {
            break;
        }
        else if(vid == '?') {
            doSolver(b1, h);
        }
        else if(vid == 'Z')
        {
            try {
                b1.undoLastMove();
            }
            catch (std::underflow_error&){
                cout << "No move to undo" << endl;
            }
        }
        else {
            cin >> amount;
            bool res = b1.move(vid, amount);
            if(false == res) {
                cout << "Illegal move...try again!" << endl;
            }
            else {
                won = b1.solved();
            }
        }
        cout << "\n";
        cout << b1;
    }
    if(won)
    {
        cout << "You win!" << endl;
    }
    else 
    {
        cout << "Don't give up that easily!" << endl;
    }
    delete h;
    return 0;
}

void doSolver(Board& b, Heuristic* h)
{
    Solver s(b, h);
    if(s.run()) {
        cout << "Solution found with expansions: " << s.numExpansions() << endl;
        Board::MovePairList sol = s.solution();
        for(unsigned i = 0; i < sol.size(); i++) {
            cout << sol[i].first << " " << sol[i].second << endl;
        }
    }
    else {
        cout << "No Solution exists!" << endl;
    }
}

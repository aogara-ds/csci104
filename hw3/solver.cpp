#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "solver.h"

using namespace std;

// To be completed
Solver::Solver(const Board& b, Heuristic *heur)
{

}

// To be completed
Solver::~Solver()
{

}

// To be completed
bool Solver::run()
{
    // Avoid compiler warnings - replace this
    return false;
}

// To be completed
Board::MovePairList Solver::solution() const
{
    // Avoid compiler warnings - replace this
    return Board::MovePairList();
}

// Complete
size_t Solver::numExpansions() const
{
    return expansions_;
}

#ifndef HEUR_H
#define HEUR_H

#include "board.h"

class Heuristic
{
public:
    virtual ~Heuristic() { }
    virtual size_t compute(const Board& b) = 0;
};

class BFSHeuristic : public Heuristic
{
public:
    size_t compute(const Board& b);
};


class DirectHeuristic : public Heuristic
{
public:
    size_t compute(const Board& b);
};

class IndirectHeuristic : public Heuristic
{
public:
    size_t compute(const Board& b);
};


#endif

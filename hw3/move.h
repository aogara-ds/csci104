#ifndef MOVE_H
#define MOVE_H
#include <functional>
#include "heur.h"
#include "board.h"

using namespace std;

struct Move
{
    // Data members are public by default in a struct
    Board::MovePair m; // Vehicle ID and amount to move
    Board *b;          // Pointer to a board representing the updated state
    int g;             // distance from the start board
    int h;             // heuristic distance to the goal
    Move *prev;        // Pointer to parent Move

    /**
     * @brief Constructor for first Move (initial board) with no parent.
     *        (i.e. the root of the A* search tree)
     * @param board 
     */
    Move(Board* board);

    /**
     * @brief Constructor for subsequent moves (after the root) which
     *        have a parent and a move that led to the new board
     *        (those returned from Board::potentialMoves())
     * 
     * @param move   Vehicle and amount moved from the parent board to this board
     * @param board  New board state for this move
     * @param parent Parent move from which this move was made
     */
    Move(const Board::MovePair& move, Board *board, Move *parent);

    /**
     * @brief Destroy the Move object
     * 
     */
    ~Move();

    /**
     * @brief Compares moves based on f score breaking ties according
     *        to the documentation in the writeup
     * 
     * @param p Right-hand side board to compare
     * @return true if this move is *less-than* p
     * @return false otherwise
     */
    bool operator<(const Move& rhs) const;

    /**
     * @brief Uses the given heuristic to score the Board that is
     *        part of the move and set the h score.
     * 
     * @param heur 
     */
    void score(Heuristic* heur);

};

// Compare based on F-score of a move
struct MoveScoreComp
{
    bool operator()(const Move *m1, const Move *m2) const
    {
        // Add code to check if m1's f-score is less than m2's by utilizing
        //  the Move's operator<()
        return *m1 < *m2;
    }
};

struct MoveBoardComp
{
    bool operator()(const Move *m1, const Move *m2) const
    {
        // Add code to check if m1's board is "less-than" m2's board by
        // using the Board class' operator<()
        return (*(m1->b) < *(m2->b));
    }
};

#endif

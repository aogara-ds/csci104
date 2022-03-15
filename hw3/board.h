#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <map>
#include <vector>
#include "vehicle.h"
// Add other includes as necessary

class Board {
public:
    // Make our VID_T type the same as Vehicle's VID_T type
    typedef Vehicle::VID_T VID_T;
    // Map to store vehicles based on their ID
    typedef std::map<Vehicle::VID_T, Vehicle> VehicleMap;
    // One row of the Grid
    typedef std::vector<Vehicle::VID_T> GridRow;
    // 2D Grid where we can store the layout fo the vehicles
    typedef std::vector<GridRow> VehicleGrid;
    // A Move is a Vehicle ID (to move) and the amount it should move
    typedef std::pair<Board::VID_T, int> MovePair;
    // List of MovePairs
    typedef std::vector< MovePair > MovePairList;

    /**
     * @brief Construct a new Board object
     * 
     */
    Board();
    /**
     * @brief Construct a new Board object from the contents of
     *        the given input stream (e.g. a file or stringstream)
     * 
     * @param is 
     */
    Board(std::istream& is);

    /**
     * @brief Copy constructor
     * 
     * @param b 
     */
    Board(const Board& b);

    /**
     * @brief Destroy the Board object
     * 
     */
    ~Board();

    /**
     * @brief Returns the dimension of one side of the grid/board
     *        (e.g. for a 6x6 board, this would return 6)
     * 
     * @return int 
     */
    int size() const;

    /**
     * @brief Returns the ID of the vehicle at the given coordinates
     * 
     * @param r row coordinate
     * @param c column coordinate
     * @return VID_T 
     */
    VID_T at(int r, int c) const;


    /**
     * @brief Returns a const reference to a specified vehicle
     * 
     * @param vid ID of the vehicle to retrieve
     * @return const Vehicle& 
     * @throws std::out_of_range if the ID doesn't exist
     */
    const Vehicle& vehicle(VID_T vid) const;

    /**
     * @brief Returns a const reference to the escape ('a') vehicle
     * 
     * @return const Vehicle& 
     */
    const Vehicle& escapeVehicle() const;

    /**
     * @brief Returns true if the escape vehicle has a free path to escape 
     *        (i.e. no vehicle blocks it to the right)
     * 
     * @return true 
     * @return false 
     */
    bool solved() const;

    /**
     * @brief Checks if moving a vehicle by a certain amount is possible
     *        or legal
     * 
     * @param vid ID of the vehicle to move
     * @param amount Amount to move the vehicle
     * @return true if the move is legal
     * @return false otherwise
     */
    bool isLegalMove(VID_T vid, int amount) const;

    /**
     * @brief Attempts to move the specified vehicle by the given amount. 
     *        If the move was legal and able to be performed, the internal 
     *        state of the vehicles is updated and `true` is returned. 
     *        If the move cannot be legally performed, `false` is returned.
     * 
     * @param vid  ID of the vehicle to move (e.g. 'a')
     * @param amount Amount (positive or negative) to move the the vehicle
     * @return true if the move was able to be performed
     * @return false if the move could not be pefromed
     */
    bool move(VID_T vid, int amount);

    /**
     * @brief Restores the vehicles and grid to their prior state
     *        before the last call to move()
     * @throw std::underflow_error If there is no move to undo 
     */
    void undoLastMove();

    /**
     * @brief Finds all possible vehicle moves from the current Board state.
     *        Returns all legal vehicle, amount combinations.
     * 
     * @return MovePairList 
     */
    MovePairList potentialMoves() const;

    /**
     * @brief Provides a less-than comparison of this board with some other
     *        board using a technique of your choice. Two boards with the same
     *        vehicle locations should cause !(b1 < b2) && !(b2 < b1)
     *        to yield true. 
     * 
     * @param other 
     * @return true if this board is "less-than" other
     * @return false otherwise
     */
    bool operator<(const Board& other) const;

    /**
     * @brief Friend ostream function to output the board in a 2D text format
     * 
     * @param os output stream to use 
     * @param b Board to output
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, const Board& b);


private:
    static const VID_T escapeID_;
    /**
     * @brief Updates the 2D grid/matrix based on the Vehicle object info
     * 
     */
    void updateBoard();

    /// Data members
    VehicleMap vehicles_;
    VehicleGrid grid_;

    ///  You may ADD data members below as necessary, but should not alter
    ///  those already given


};
#endif

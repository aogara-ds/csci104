#ifndef VEHICLE_H
#define VEHICLE_H

struct Vehicle {
    enum DIR { VERTICAL=1, HORIZONTAL };
    typedef char VID_T;
    static const VID_T INVALID_ID = '.'; // blank space

    /// Data members
    VID_T id;
    int startr;
    int startc;
    int length;
    DIR direction;
    Vehicle() { id = INVALID_ID; }
    Vehicle(unsigned sr, unsigned sc, char vid) :
        id(vid), startr(sr), startc(sc), length(1), direction(VERTICAL)
    {
    }
};

#endif
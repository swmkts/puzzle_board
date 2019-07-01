#ifndef ASTAR_8_PAZZLE_H
#define ASTAR_8_PAZZLE_H

#include "puzzle_board.h"

class Astar_Puzzle{
    public:
    Puzzle_Board current_b;//current board
    Astar_Puzzle(Puzzle_Board&);
    int f;
    bool operator < (const Astar_Puzzle &a_pz) const{
        return f > a_pz.f;
    }
};
#endif
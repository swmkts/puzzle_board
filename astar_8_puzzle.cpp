#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include "astar_8_puzzle.h"
#include "puzzle_board.h"

using namespace std;

Astar_Puzzle::Astar_Puzzle(Puzzle_Board &pz){
    current_b = pz;
}


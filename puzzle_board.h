#ifndef PUZZLE_BOARD_H
#define PUZZLE_BOARD_H

#include <string>

using namespace std;

#define S 3
#define N 9

class Puzzle_Board{
    public:
    int board[N];//board
    int score;
    int zero_index;
    Puzzle_Board();
    Puzzle_Board(int*);
    string path;
    bool operator < (const Puzzle_Board &pz) const;
    bool operator == (const Puzzle_Board &pz) const;
};
#endif
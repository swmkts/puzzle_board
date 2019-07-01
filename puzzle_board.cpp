#include <iostream>
#include <string>
#include "puzzle_board.h"

using namespace std;

Puzzle_Board::Puzzle_Board(){
    
}

Puzzle_Board::Puzzle_Board(int *b){
    for(int i = 0; i < N; ++i){
        board[i] = b[i];
        if(b[i] == 0){
            zero_index = i;
        }
    }
}
bool Puzzle_Board::operator == (const Puzzle_Board &pz) const{
    for(int i = 0; i < N; ++i){
        if(board[i] == pz.board[i]){
            continue;
        }
        return false;
    }
    return true;
}

bool Puzzle_Board::operator < (const Puzzle_Board &pz) const{
    for(int i = 0; i < N; ++i){
        if(board[i] == pz.board[i]){
            continue;
        }
        return board[i] < pz.board[i];
    }
    return false;
}

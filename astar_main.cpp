#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <algorithm>
#include <queue>
#include <map>
#include "puzzle_board.h"
#include "astar_8_puzzle.h"

using namespace std;

int calc_manhattan_distance(int* ans, int* bd){
    int dist = 0;
    for(int i = 0; i < N; ++i){
        dist += abs(ans[i] - bd[i]);
    }
    return dist;
}
void print_board(int *brd){
    int ct = 0;
    for(int i = 0; i < N; ++i){
        if(ct < S - 1){
            cout << brd[i] << " ";
            ct++;
        }else if(ct == S - 1){
            cout << brd[i] << endl;
            ct = 0;
        }
    }
    cout << endl;
}

int main(){
    cout << "This is 8-pazzle game." << endl;
    cout << "Put '0' where a pazzle does not exist." << endl;
    cout << "Separate character is ','." << endl;
    int i = 0;
    string s;
    int board[N];
    int n = 0;
    while(i < S){
        cout << "Input row " << i + 1 << " below." << endl;
        cin >> s;
        stringstream ss(s);
        string buf;
        while(getline(ss, buf, ',')){
            board[n] = stoi(buf);
            n++;
        }
        i++;
    }
    
    int ans[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    Puzzle_Board ans_pz(ans);

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {1, -1, 0, 0};
    char direction[4] = {'r', 'l', 'u', 'd'};

    Puzzle_Board initial_pz(board);
    initial_pz.score = 0;
    initial_pz.path = 's';
    map<Puzzle_Board, bool> open_or_closed;//This means if value=="true" then key is in open. else in clsed.
    open_or_closed[initial_pz] = true;
    priority_queue<Astar_Puzzle> PQ;
    Astar_Puzzle initial_pz_f(initial_pz);
    initial_pz_f.f = initial_pz.score + calc_manhattan_distance(ans, initial_pz.board);
    PQ.push(initial_pz_f);
    
    // map<Puzzle_Board, bool> open;
    // map<Puzzle_Board, bool> closed;
    // open[initial_pz] = true;

    Puzzle_Board now, next;

    int ii = 0;

    while(!PQ.empty()){
        Astar_Puzzle puz_f = PQ.top();
        PQ.pop();
        now = puz_f.current_b;
        open_or_closed[now] = false;//add puz_f to Closed list.
        if(puz_f.current_b == ans_pz){
            cout << "The number of search: " << puz_f.current_b.score << endl;
            print_board(puz_f.current_b.board);
            cout << "The optimal path is: " << puz_f.current_b.path << endl;
            Astar_Puzzle pz_f = puz_f;
            cout << "Found Answer!!!!!!!!!!!" << endl;
            break;
        }
        int zero_x = now.zero_index / S;
        int zero_y = now.zero_index % S;
        for(int i = 0; i < 4; ++i){
            int zero_x_after = zero_x + dx[i];
            int zero_y_after = zero_y + dy[i];
            if(zero_x_after < 0 || zero_x_after > S - 1 || zero_y_after < 0 || zero_y_after > S - 1){
                continue;
            }
            next = now;
            swap(next.board[zero_x * S + zero_y], next.board[zero_x_after * S + zero_y_after]);
            next.zero_index = zero_x_after * S + zero_y_after;
            next.score++;
            next.path += direction[i];
            Astar_Puzzle puz_f_next(next);
            puz_f_next.f = puz_f_next.current_b.score + calc_manhattan_distance(ans_pz.board, puz_f_next.current_b.board);
            ////////////////////////////////////////////
            //////rewrite/////////
            ////////////////////////////////////////////
            if(open_or_closed.count(next) == 0){
            // if(!open_or_closed[next]){
                open_or_closed[next] = true;
                PQ.push(puz_f_next);

            }else if(open_or_closed[next] == true){
                auto itr = open_or_closed.find(next);
                if(itr != open_or_closed.end()){
                    if(next.score < itr->first.score){//rewrite the f of next board.
                        Puzzle_Board old_b;
                        old_b = itr->first;
                        open_or_closed.erase(itr);
                        old_b.score = next.score;
                        old_b.path = next.path;
                        open_or_closed[old_b] = true;
                        Astar_Puzzle puz_f_old_b(old_b);
                        puz_f_old_b.f = puz_f_old_b.current_b.score + calc_manhattan_distance(ans_pz.board, puz_f_old_b.current_b.board);
                        PQ.push(puz_f_old_b);

                    }
                }
            }else if(open_or_closed[next] == false){
                auto itr = open_or_closed.find(next);
                if(itr != open_or_closed.end()){
                    if(next.score < itr->first.score){
                        Puzzle_Board old_b;
                        old_b = itr->first;
                        open_or_closed.erase(itr);
                        old_b.score = next.score;
                        old_b.path = next.path;
                        open_or_closed[old_b] = true; 
                        PQ.push(puz_f_next);
                    }
                }
            }
        }
        ii++;
    }
}
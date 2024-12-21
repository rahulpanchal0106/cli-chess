#include "pieceslogic.h"
#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

unordered_map<int, char> Pieces::pieces_map = {
    {0, '.'}, {1, 'R'}, {2, 'N'}, {3, 'B'}, {4, 'K'}, {5, 'Q'}, {6, 'P'},
    {-1, 'r'}, {-2, 'n'}, {-3, 'b'}, {-4, 'k'}, {-5, 'q'}, {-6, 'p'}
};

unordered_map<int, int> Pieces::pieces_value = {
    {0, 0}, {1, 4}, {2, 3}, {3, 3}, {4, 200}, {5, 9}, {6, 1},
    {-1, 4}, {-2, 3}, {-3, 3}, {-4, 200}, {-5, 9}, {-6, 1}
};

Pieces::Pieces() {}

bool Pieces::validate_move(
    int &start_piece, 
    int &end_piece,
    vector<vector<int>> &board, 
    vector<vector<int>> &positions,
    bool p1sturn
){
    int x1=positions[0][0];
    int y1=positions[0][1];
    int x2=positions[1][0];
    int y2=positions[1][1];

    vector<vector<int>> allowed_pos = {};

    if((p1sturn==true && start_piece<0) || (p1sturn==false && start_piece>0)){
        return false;
    }

    if(start_piece==6){
        if(board[x1-1][y1]==0){
            allowed_pos.push_back({x1-1,y1});
        }
        if(x1==6 && board[x1-2][y1]==0){ // starting rank
            allowed_pos.push_back({x1-2,y1}); 
        }
        if(board[x1-1][y1-1]<0){
            allowed_pos.push_back({x1-1,y1-1});
        }
        if(board[x1-1][y1+1]<0){
            allowed_pos.push_back({x1-1,y1+1});
        }
    }else if(start_piece==-6){
        if(board[x1+1][y1]==0){
            allowed_pos.push_back({x1+1,y1});
        }
        if(x1==1 && board[x1+2][y1]==0){ // starting rank
            allowed_pos.push_back({x1+2,y1}); 
        }
        if(board[x1+1][y1-1]>0){
            allowed_pos.push_back({x1+1,y1-1});
        }
        if(board[x1+1][y1+1]>0){
            allowed_pos.push_back({x1+1,y1+1});
        }
    }else if(start_piece==1){
        //up
        for(int i=x1-1; i>=0; i--){
            if(board[i+1][y1]<0 || board[i][y1]>0){
                break;
            }
            allowed_pos.push_back({i,y1});
            cout<<i<<" ";
        }
        //down
        for(int i=x1+1; i<8; i++){
            if(board[i-1][y1]<0 || board[i][y1]>0){
                break;
            }
            allowed_pos.push_back({i,y1});
            cout<<i<<" ";
        }
        //right
        for(int j=y1+1; j<8; j++){
            if(board[x1][j-1]<0 || board[x1][j]>0){
                break;
            }
            allowed_pos.push_back({x1,j});
            cout<<j<<" ";
        }
        //left
        for(int j=y1-1; j>=0; j--){
            if(board[x1][j+1]<0 || board[x1][j]>0){
                break;
            }
            allowed_pos.push_back({x1,j});
            cout<<j<<" ";
        }          
    }else if(start_piece==-1){
        //up
        for(int i=x1-1; i>=0; i--){
            if(board[i+1][y1]>0 || board[i][y1]<0){
                break;
            }
            allowed_pos.push_back({i,y1});
            cout<<i<<" ";
        }
        //down
        for(int i=x1+1; i<8; i++){
            if(board[i-1][y1]>0 || board[i][y1]<0){
                break;
            }
            allowed_pos.push_back({i,y1});
            cout<<i<<" ";
        }
        //right
        for(int j=y1+1; j<8; j++){
            if(board[x1][j-1]>0 || board[x1][j]<0){
                break;
            }
            allowed_pos.push_back({x1,j});
            cout<<j<<" ";
        }
        //left
        for(int j=y1-1; j>=0; j--){
            if(board[x1][j+1]>0 || board[x1][j]<0){
                break;
            }
            allowed_pos.push_back({x1,j});
            cout<<j<<" ";
        }

    }else if(start_piece==2 || start_piece==-2){
        //up
        if(x1-2>=0){
            if(y1-1>=0){
                allowed_pos.push_back({x1-2,y1-1});
            }
            if(y1+1<8){
                allowed_pos.push_back({x1-2,y1+1});
            }
        }
        //down
        if(x1+2<8){
            if(y1-1>=0){
                allowed_pos.push_back({x1+2,y1-1});
            }
            if(y1+1<8){
                allowed_pos.push_back({x1+2,y1+1});
            }
        }
        //left
        if(y1-2>=0){
            if(x1-1>=0){
                allowed_pos.push_back({x1-1,y1-2});
            }
            if(x1+1<8){
                allowed_pos.push_back({x1+1,y1-2});
            }
        }
        //right
        if(y1+2<8){
            if(x1-1>=0){
                allowed_pos.push_back({x1-1,y1+2});
            }
            if(x1+1<8){
                allowed_pos.push_back({x1+1,y1+2});
            }
        }
    }else if(start_piece==3 || start_piece==-3){
        //up-left
        for(int i=x1-1, j=y1-1; i>=0 && j>=0; i--, j--){
            if(board[i+1][j+1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
        //up-right
        for(int i=x1-1, j=y1+1; i>=0 && j<8; i--, j++){
            if(board[i+1][j-1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
        //down-left
        for(int i=x1+1, j=y1-1; i<8 && j>=0; i++, j--){
            if(board[i-1][j+1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
        //down-right
        for(int i=x1+1, j=y1+1; i<8 && j<8; i++, j++){
            if(board[i-1][j-1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
    }else if(start_piece==5 || start_piece==-5){
        //up
        for(int i=x1-1; i>=0; i--){
            if(board[i+1][y1]<0 || board[i][y1]>0){
                break;
            }
            allowed_pos.push_back({i,y1});
        }
        //down
        for(int i=x1+1; i<8; i++){
            if(board[i-1][y1]<0 || board[i][y1]>0){
                break;
            }
            allowed_pos.push_back({i,y1});
        }
        //right
        for(int j=y1+1; j<8; j++){
            if(board[x1][j-1]<0 || board[x1][j]>0){
                break;
            }
            allowed_pos.push_back({x1,j});
        }
        //left
        for(int j=y1-1; j>=0; j--){
            if(board[x1][j+1]<0 || board[x1][j]>0){
                break;
            }
            allowed_pos.push_back({x1,j});
        }
        //up-left
        for(int i=x1-1, j=y1-1; i>=0 && j>=0; i--, j--){
            if(board[i+1][j+1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
        //up-right
        for(int i=x1-1, j=y1+1; i>=0 && j<8; i--, j++){
            if(board[i+1][j-1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
        //down-left
        for(int i=x1+1, j=y1-1; i<8 && j>=0; i++, j--){
            if(board[i-1][j+1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
        //down-right
        for(int i=x1+1, j=y1+1; i<8 && j<8; i++, j++){
            if(board[i-1][j-1]<0 || board[i][j]>0){
                break;
            }
            allowed_pos.push_back({i,j});
        }
    }else if(start_piece==4 || start_piece==-4){
        //king moves
        vector<vector<int>> king_moves = {
            {x1-1, y1-1}, {x1-1, y1}, {x1-1, y1+1},
            {x1, y1-1}, {x1, y1+1},
            {x1+1, y1-1}, {x1+1, y1}, {x1+1, y1+1}
        };
        for(auto move : king_moves){
            int x = move[0];
            int y = move[1];
            if(x >= 0 && x < 8 && y >= 0 && y < 8){
                if((p1sturn && board[x][y] <= 0) || (!p1sturn && board[x][y] >= 0)){
                    allowed_pos.push_back({x, y});
                }
            }
        }
    }

    for(vector<int> position : allowed_pos){ 
        if(positions[1]==position){
            return true;
        }
    }
    return false;
}

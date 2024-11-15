#include<iostream>
#include<vector>
#include<cstdlib>
#include<unordered_map>
#include<locale>
using namespace std;

#define empty 0

class Pieces{
    //pieces logic

public:

    unordered_map <int,char> pieces_map={
            {0,'.'},
            {1,'R'},
            {2,'N'},
            {3,'B'},
            {4,'K'},
            {5,'Q'},
            {6,'P'},
            {-1,'r'},
            {-2,'n'},
            {-3,'b'},
            {-4,'k'},
            {-5,'q'},
            {-6,'p'},
        };

};

class Display{
    //show pieces and board
public:
    Pieces pieces;
    unordered_map<int,char> pieces_map=pieces.pieces_map;

    void init(
            vector<vector<int>> &board,
            vector<int> &p1_collec, 
            vector<int> &p2_collec 
        ){

        
        cout<<"==> Player2: ";
        for(int piece:p2_collec){
            cout<<pieces_map[piece]<<" ";
        }
        cout<<endl;

        cout<<endl;
        for(int i=0; i<board.size(); i++){
            cout<<8-i<<"   ";
            for(int j=0; j<board[i].size(); j++){
                cout<<pieces_map[board[i][j]]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<"    ";
        for(int i=97; i<105; i++){
            cout<<char(i)<<" ";
        }
        cout<<endl;
        cout<<endl;

         cout<<"==> Player1: ";
        for(int piece:p1_collec){
            cout<<pieces_map[piece]<<" ";
        }
        cout<<endl;
        cout<<endl;
    }

    void update(
            vector<vector<int>> &board,
            vector<int> &p1_collec, 
            vector<int> &p2_collec 
        ){
        init(board,p1_collec,p2_collec);
    }

};

class Player{
    //player controls and moves
public:
    void swap(int &a, int &b){
        int temp = a;
        a=b;
        b=temp;
    }

    void kill_piece(
            int &start_piece, 
            int &end_piece, 
            vector<vector<int>> &board, 
            vector<int> &p1_collec, 
            vector<int> &p2_collec
        ){
        
        if(start_piece>0 && end_piece<0){
            
            //white p1 kills
            p1_collec.push_back(end_piece);
            end_piece=start_piece;
            start_piece=empty;

        }else if(start_piece<0 && end_piece>0){

            //black p2 kills
            p2_collec.push_back(end_piece);
            end_piece=start_piece;
            start_piece=empty;

        }else{
            // cout<<"*****************"<<endl;
        }
    }

    void make_move(
            vector<vector<int>> &board, 
            vector<vector<int>> &positions,
            vector<int> &p1_collec, 
            vector<int> &p2_collec
        ){
        int x1=positions[0][0], x2=positions[1][0];
        int y1=positions[0][1], y2=positions[1][1];

        int start_piece = board[x1][y1];
        int end_piece = board[x2][y2];

        if(end_piece==empty){
            swap(board[x1][y1],board[x2][y2]);
            return;
        }

        kill_piece(board[x1][y1],board[x2][y2],board,p1_collec,p2_collec);


    }

};

class Game{
    // init, stop, restart, overall game flow
public:
    
    Display display;
    Pieces pieces;

    unordered_map <int,char> pieces_map = pieces.pieces_map;
    
    void init(
        vector<vector<int>> &board,
        vector<int> &p1_collec, 
        vector<int> &p2_collec 
        
    ){      
       
        display.init(board,p1_collec,p2_collec);
       
    }

    vector<vector<int>> update(vector<vector<int>> &board){

    }
    vector<vector<int>> move_decoder(string move){ //2d4d
        string spot_start=string(1,move[0])+string(1,move[1]);//2d
        string spot_end=string(1,move[2])+string(1,move[3]);//4d

        unordered_map <char,int> x_positions_map={
            {'a',0},
            {'b',1},
            {'c',2},
            {'d',3},
            {'e',4},
            {'f',5},
            {'g',6},
            {'h',7}
        };

        char x_start_enc = spot_start[0];
        int x_start_dec = 8-(x_start_enc-'0');

        char y_start_enc = spot_start[1];
        int y_start_dec = x_positions_map[y_start_enc];

        char x_end_enc = spot_end[0];
        int x_end_dec = 8-(x_end_enc-'0');

        char y_end_enc = spot_end[1];
        int y_end_dec = x_positions_map[y_end_enc];


        vector<int> start_pos ={ x_start_dec, y_start_dec };
        vector<int> end_pos ={ x_end_dec, y_end_dec };

        vector<vector<int>> positions_arr = { start_pos, end_pos };

        return positions_arr;
    }

};






int main(){

    bool start = true;
    string move, piece;
    int turns=0;
    Game game;
    Player player;
    Display display;

    vector<vector<int>> board = {
        {-1,-2,-3,-4,-5,-3,-2,-1},
        {-6,-6,-6,-6,-6,-6,-6,-6},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {6,6,6,6,6,6,6,6},
        {1,2,3,4,5,3,2,1},
    };
    
    vector<int> p1_collec={}; 
    vector<int> p2_collec={};
    

    system("cls");
    game.init(board,p1_collec,p2_collec);

    while(start){
        cout<<"Player "<<((turns%2==0)?"1":"2")<<"'s turn: ";
        cin>>move;
        vector<vector<int>> positions = game.move_decoder(move);

        system("cls");

        // cout<<"from: "<<positions[0][0]<<" "<<positions[0][1]<<endl;
        // cout<<"to: "<<positions[1][0]<<" "<<positions[1][1]<<endl;

        player.make_move(board,positions,p1_collec,p2_collec);
        display.update(board,p1_collec,p2_collec);
        

        turns++;
        
    }
    
    system("pause");


    return 0;
}
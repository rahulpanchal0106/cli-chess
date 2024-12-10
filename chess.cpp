#include<iostream>
#include<vector>
#include<cstdlib>
#include<unordered_map>
#include<locale>
#include <fstream> // For file operations
using namespace std;

// void writeBoardToFile(const vector<vector<int>>& board) {
//     ofstream outFile("board_state.txt");
//     if (outFile.is_open()) {
//         outFile << "[";
//         for (size_t i = 0; i < board.size(); ++i) {
//             outFile << "[";
//             for (size_t j = 0; j < board[i].size(); ++j) {
//                 outFile << board[i][j];
//                 if (j != board[i].size() - 1) outFile << ",";
//             }
//             outFile << "]";
//             if (i != board.size() - 1) outFile << ",";
//         }
//         outFile << "]";
//         outFile.close();
//     } else {
//         cerr << "Error: Unable to write board state to file.\n";
//     }
// }

void writeBoardToFile(const std::string& fen, const std::string& filename = "board_state.txt") {
    std::ofstream file(filename);
    if (file.is_open()) {
        cout<<"?????????? "<<fen<<endl;
        file << fen;
        file.close();
        std::cout << "FEN written to file: " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
    }
}

string readAIMoveFromFile() {
    ifstream inFile("ai_move.txt");
    string aiMove;
    if (inFile.is_open()) {
        getline(inFile, aiMove); // Read the move from the file
        inFile.close();
    } else {
        cerr << "Error: Unable to read AI move from file.\n";
    }
    return aiMove;
}



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
        {-6,'p'}
    };

    unordered_map <int,int> pieces_value={
        {0,0},
        {1,4},
        {2,3},
        {3,3},
        {4,200},
        {5,9},
        {6,1},
        {-1,4},
        {-2,3},
        {-3,3},
        {-4,200},
        {-5,9},
        {-6,1}
    };


    bool validate_move(
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
        }

        for(vector<int> position : allowed_pos){ 
            if(positions[1]==position){
                return true;
            }
        }
        return false;
    }
};


class Player{
    //player controls and moves
    Pieces pieces;
    unordered_map<int,int> pieces_value = pieces.pieces_value;

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
            start_piece=0;

        }else if(start_piece<0 && end_piece>0){

            //black p2 kills
            p2_collec.push_back(end_piece);
            end_piece=start_piece;
            start_piece=0;

        }else{
            cout<<"*****************"<<endl;
        }
    }

    int make_move(
            vector<vector<int>> &board, 
            vector<vector<int>> &positions,
            vector<int> &p1_collec, 
            vector<int> &p2_collec,
            bool p1sturn
        ){
        int x1=positions[0][0], x2=positions[1][0];
        int y1=positions[0][1], y2=positions[1][1];

        int start_piece = board[x1][y1];
        int end_piece = board[x2][y2];

        bool allowed = pieces.validate_move(start_piece, end_piece, board, positions,p1sturn);

        if(allowed){

            if(end_piece==0){
                swap(board[x1][y1],board[x2][y2]);
                return 1;
            }

            kill_piece(board[x1][y1],board[x2][y2],board,p1_collec,p2_collec);
            return 1;
        }

        cout<<"~~~~~~~~~~~~~~~~~~~~~"<<endl;
        return 0;
    }

    int score(vector<int> &collec){
        int sum=0;
        for(int piece:collec){
            sum+=pieces_value[piece];
        }
        return sum;
    }

    void print_collec(vector<int> &collec,unordered_map<int,char> map){
        for(int piece:collec){
            cout<<map[piece]<<" ";
        }
        cout<<endl;
    }

};

class Display{
    //show pieces and board
    Player player;
    Pieces pieces;
    unordered_map<int,char> pieces_map=pieces.pieces_map;
    unordered_map<int,int> pieces_value = pieces.pieces_value;

public:

    void init(
            vector<vector<int>> &board,
            vector<int> &p1_collec, 
            vector<int> &p2_collec 
        ){

        cout<<endl;
        
        cout<<"==> Black(p2)'s collection: ";
        player.print_collec(p2_collec,pieces_map);
        cout<<"==> Black(p2)'s score: ";
        cout<<player.score(p2_collec)<<endl;
        
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

        cout<<"==> White(p1)'s collection: ";
        player.print_collec(p1_collec,pieces_map);
        cout<<"==> White(p2)'s score: ";
        cout<<player.score(p1_collec)<<endl;
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

        cout<<"====>> "<<move<<endl;

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
string getAIMove(vector<vector<int>>& gameState) {
    // Open a pipe to the Python script
    FILE* pipe = popen("python chessai.py", "w");
    if (!pipe) return "Error opening pipe";

    // Convert the game state to a JSON-like string
    string gameStateJson = "[";
    for (const auto& row : gameState) {
        gameStateJson += "[";
        for (size_t i = 0; i < row.size(); ++i) {
            gameStateJson += to_string(row[i]);
            if (i != row.size() - 1) gameStateJson += ",";
        }
        gameStateJson += "]";
        if (&row != &gameState.back()) gameStateJson += ",";
    }
    gameStateJson += "]";

    // Send the game state to the Python script
    fputs(gameStateJson.c_str(), pipe);
    fflush(pipe);  // Ensure it's sent immediately
    fclose(pipe);  // Close the pipe for writing

    // Open the pipe again for reading the AI move
    pipe = popen("python chessai.py", "r");
    if (!pipe) return "Error reading from pipe";

    // Read the AI's move from the pipe
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        string aiMove(buffer);  // Get the AI move as a string
        fclose(pipe);
        return aiMove;
    }

    fclose(pipe);
    return "Error: No move generated";
}



std::string arr_to_fen(const std::vector<std::vector<int>>& board) {
    // Map integer piece codes to FEN piece letters
    std::unordered_map<int, char> piece_map = {
        {-1, 'r'}, {-2, 'n'}, {-3, 'b'}, {-4, 'q'}, {-5, 'k'}, {-6, 'p'},
        { 1, 'R'}, { 2, 'N'}, { 3, 'B'}, { 4, 'Q'}, { 5, 'K'}, { 6, 'P'},
        { 0, '.'}
    };

    std::string fen;
    for (const auto& row : board) {
        int empty_count = 0;
        for (int cell : row) {
            if (cell == 0) {
                // Increment empty square counter
                empty_count++;
            } else {
                // Append empty squares count if any
                if (empty_count > 0) {
                    fen += std::to_string(empty_count);
                    empty_count = 0;
                }
                // Append the piece character
                fen += piece_map[cell];
            }
        }
        // Append any trailing empty squares
        if (empty_count > 0) {
            fen += std::to_string(empty_count);
        }
        // Add a '/' for row separation
        fen += '/';
    }

    // Remove the trailing '/'
    if (!fen.empty()) {
        fen.pop_back();
    }

    return fen;
}

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
    

    // system("cls");
    game.init(board,p1_collec,p2_collec);

    while(start){
        bool p1sturn = turns%2==0;
        if (p1sturn) {
            cout << "Player 1's turn: ";
            cin >> move;
        } else {
            cout << "Player 2's turn: ";
            
            // Write the current board state to the file
            string fenboard = arr_to_fen(board) + " b KQkq - 0 1";
            cout<<">>> "<<fenboard<<endl;
            writeBoardToFile(fenboard);
            
            // Call the Python script externally (simulate this by ensuring it runs after the board state is updated)
            system("python chessai.py");
            
            // Read the AI move from the file
            move = readAIMoveFromFile();
            cout << "AI Move: " << move << endl;
        }


        cout<<"&&&&&&&&&&&&&777 "<<move<<endl;
        vector<vector<int>> positions = game.move_decoder(move);

        // system("cls");

        // cout<<"from: "<<positions[0][0]<<" "<<positions[0][1]<<endl;
        // cout<<"to: "<<positions[1][0]<<" "<<positions[1][1]<<endl;

        int move_made = player.make_move(board,positions,p1_collec,p2_collec,p1sturn);
        if(move_made==0){
            turns--;
        }
        
        display.update(board,p1_collec,p2_collec);

        turns++;
        
    }
    
    system("pause");


    return 0;
}
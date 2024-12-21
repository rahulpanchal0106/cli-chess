#include "menu.h"
#include "display.h"
#include "gameflow.h"
#include "m2m.h"
#include<iostream>
#include <cstddef>
using namespace std;

extern Game game;
extern Player player;
extern Display display;
extern Lan lan;

Menu::Menu(){
    int game_mode;
}

int Menu::selector(){
    cout<<"Select your mode of playing:\n "<<endl;
    cout<<"     1 for Pass n Play (Offline 1 on 1)\n     2 for LAN multiplayer\n    Enter 3 for User Manual\n\n---> ";
    cin>>game_mode;
    return game_mode;
}

void Menu::passnplay(
    vector<vector<int>> board,
    vector<int> p1_collec,
    vector<int> p2_collec,
    bool start,
    int turns,
    string move
){
    while(start){
        
        bool p1sturn = turns%2==0;
        cout<<"Total moves: "<<turns<<endl;
        if (p1sturn) {
            cout << "Player 1's turn: ";
            cin >> move;
        } else {
            cout << "Player 2's turn: ";
            
            cin>>move;
        }

        vector<vector<int>> positions = game.move_decoder(move);

        system("cls");

        int move_made = player.make_move(board,positions,p1_collec,p2_collec,p1sturn);
        if(move_made==0){
            cout<<"Invalid Move! Try Again..."<<endl;
            turns--;
        }
        
        display.update(board,p1_collec,p2_collec);

        turns++;
        
    }
}
void Menu::lanmultiplayer(
    vector<vector<int>> board,
    vector<int> p1_collec,
    vector<int> p2_collec,
    bool start,
    int turns,
    string move
){
    lan.initiate(board,turns,move,p1_collec,p2_collec);   
}
void Menu::aiopponent(
    vector<vector<int>> board,
    vector<int> p1_collec,
    vector<int> p2_collec,
    bool start,
    int turns,
    string move
){
   cout<<"Under development"<<endl;
}

void Menu::help(){
    cout << "Welcome to the CLI-Chess Project!\n" << endl;
    cout << "User Manual:\n" << endl;
    cout << "1. Game Modes:\n";
    cout << "   a. Pass and Play: Play against another player on the same device.\n";
    cout << "   b. LAN Multiplayer: Play against another player over a local network.\n";
    cout << "   c. AI Opponent: Play against the computer (Under development).\n" << endl;
    
    cout << "2. How to Play:\n";
    cout << "   a. Enter your move in the format 'e2e4'(without space) to move a piece from e2 to e4.\n";
    cout << "   b. Player 1 (White) moves first, followed by Player 2 (Black).\n";
    cout << "   c. The game alternates turns until a checkmate, stalemate, or draw occurs.\n" << endl;
    
    cout << "3. Controls:\n";
    cout << "   a. Use standard chess notation for moves (e.g., 'e2e4').\n";
    cout << "   b. Enter 'ctrl+c' to quit the game.\n" << endl;
    
    cout << "4. Scoring:\n";
    cout << "   a. Each captured piece has a point value (e.g., Pawn = 1, Knight = 3, etc.).\n";
    cout << "   b. The score is displayed after each move.\n" << endl;
    
    cout << "5. LAN Multiplayer Info:\n";
    cout << "   a. Ensure both players are connected to the same local network.\n";
    cout << "   b. One player should host the game, and the other should join using the host's IP address.\n";
    cout << "   c. Communication between players is handled over the network, so ensure firewalls allow the connection.\n";
    cout << "   d. If connection issues occur, check network settings and try reconnecting.\n" << endl;
    
    cout << "6. Tips:\n";
    cout << "   a. Plan your moves ahead and think strategically.\n";
    cout << "   b. Control the center of the board for better positioning.\n";
    cout << "   c. Protect your King and be mindful of potential threats.\n" ;
    cout << "   d. Don't get confused with lowercase and uppercase charecters.\n" << endl;
    
    cout << "Enjoy the game and have fun!\n" << endl;
}
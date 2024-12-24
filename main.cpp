#include "headers/display.h"
#include "headers/player.h"
#include "headers/gameflow.h"
#include "headers/m2m.h"
#include "headers/pieceslogic.h"
#include "headers/menu.h"
#include "headers/clipalette.h"

#include <iostream>
using namespace std;

Game game;
Player player;
Display display;
Menu menu;
CLIPalette palette;

int main (){
    bool start = true;
    string move, piece;
    int turns=0;

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
    
    int game_mode=menu.select(menu.modes);

    
    cout<<palette.scb(menu.modes[game_mode]+"mode Initializing . . .",{palette.BLINK,palette.CYAN},1)<<endl;
    
    // cout<<endl<<menu.modes[game_mode]<<" initializing . . ."<<endl;

    system("pause");
    
}
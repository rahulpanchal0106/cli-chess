#include "headers/menu.h"
#include "headers/clipalette.h"
#include<iostream>
#include <conio.h>
#include<string>
#include<vector>
using namespace std;

extern CLIPalette palette;

Menu::Menu(){
    modes={
        " Pass n Play ",
        " LAN Multiplayer ",
        " AI Opponent ",
    };
}

void Menu::display(vector<string> &modes,int &mode){
    system("cls");
    
    cout<<endl<<palette.scb(" Select Game Mode ",{palette.BOLD,palette.CYAN},1)<<endl;
    for(int i=0; i<modes.size();i++){
        if(mode==i){
            cout<<palette.scb(" > ",{palette.BOLD,palette.BG_CYAN},0);
        }else{
            cout<<"  ";
        }
        cout << modes[i] << palette.RESET<<endl; 
    }
    cout<<endl;
}

int Menu::select(vector<string> &modes){
    int menu_size=modes.size();
    //traverse through map
    //till menu_size
        //start from mode=0
        int mode=0;
        char key;
        //detect key and increment/decrement accordingly
        Menu::display(modes,mode);
        while(true){
            if(_kbhit()){
                key=_getch();
                if(key==72){ //up
                    mode--;
                    //if mode<0 go back to mode=menu_size
                    if(mode<0){
                        mode=menu_size-1;
                    }

                }else if(key==80){//down
                    mode++;
                    //if mode==menu_size go back to mode=0
                    if(mode==menu_size){
                        mode=0;
                    }
                }else if(key==13){
                    return mode;
                }
                Menu::display(modes,mode);
            }
        }
}


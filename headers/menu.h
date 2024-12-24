#ifndef MENU
#define MENU
#include<vector>
#include<string>
using namespace std;
class Menu{
public:
    vector<string> modes;
    Menu();
    void display(vector<string> &modes,int &mode);
    int select(vector<string> &modes);
    int selected_mode;
};

#endif
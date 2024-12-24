#include "headers/clipalette.h"
#include<iostream>
#include<unordered_map>
using namespace std;

const std::string CLIPalette::RESET = "\033[0m";
const std::string CLIPalette::BOLD = "\033[1m";
const std::string CLIPalette::UNDERLINE = "\033[4m";
const std::string CLIPalette::REVERSED = "\033[7m";
const std::string CLIPalette::ITALIC = "\033[3m";
const std::string CLIPalette::STRIKETHROUGH = "\033[9m";
const std::string CLIPalette::BLINK = "\033[5m";
const std::string CLIPalette::INVISIBLE = "\033[8m";


const std::string CLIPalette::BLACK = "\033[30m";
const std::string CLIPalette::RED = "\033[31m";
const std::string CLIPalette::GREEN = "\033[32m";
const std::string CLIPalette::YELLOW = "\033[33m";
const std::string CLIPalette::BLUE = "\033[34m";
const std::string CLIPalette::MAGENTA = "\033[35m";
const std::string CLIPalette::CYAN = "\033[36m";
const std::string CLIPalette::WHITE = "\033[37m";

const std::string CLIPalette::BG_BLACK = "\033[40m";
const std::string CLIPalette::BG_RED = "\033[41m";
const std::string CLIPalette::BG_GREEN = "\033[42m";
const std::string CLIPalette::BG_YELLOW = "\033[43m";
const std::string CLIPalette::BG_BLUE = "\033[44m";
const std::string CLIPalette::BG_MAGENTA = "\033[45m";
const std::string CLIPalette::BG_CYAN = "\033[46m";
const std::string CLIPalette::BG_WHITE = "\033[47m";


string CLIPalette::color(string text,const string color_name, bool reset_flag ){
    return reset_flag? color_name+text+RESET: color_name+text;
}

string CLIPalette::bg(string text, const string color_name,bool reset_flag){
    return reset_flag?color_name+text+RESET:color_name+text;
}

string CLIPalette::style(string text, const string style_name,bool reset_flag){
    return reset_flag?style_name+text+RESET:style_name+text;
}

string CLIPalette::scb(string text, vector<string> styles,bool reset_flag){
    string styles_string="\033[";
    for(int i=0; i<styles.size(); i++){ // \033[33m
        auto first = styles[i].begin();
        auto last = styles[i].begin()+2;
        styles[i].erase(first,last);// 33m
        styles[i].pop_back();
        styles_string+=styles[i];
        if(i!=styles.size()-1) styles_string+=";";
    }
    styles_string+="m";
    return reset_flag?styles_string+text+RESET:styles_string+text;
}


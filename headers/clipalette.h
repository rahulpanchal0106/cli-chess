#ifndef CLIPALETTE
#define CLIPALETTE
#include <string>
#include <vector>
using namespace std;

class CLIPalette{
public:

    static const std::string RESET;
    static const std::string BOLD;
    static const std::string UNDERLINE;
    static const std::string REVERSED;
    static const std::string ITALIC;
    static const std::string STRIKETHROUGH;
    static const std::string BLINK;
    static const std::string INVISIBLE;


    // Text Colors
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;

    // Background Colors
    static const std::string BG_BLACK;
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    static const std::string BG_MAGENTA;
    static const std::string BG_CYAN;
    static const std::string BG_WHITE;
    

    string color(const string text,const string color_name,bool reset_flag);
    string bg(const string text,const string color_name,bool reset_flag);
    string style(const string text,const string style_name,bool reset_flag);

    string scb(const string text,vector<string> styles,bool reset_flag);
};

#endif
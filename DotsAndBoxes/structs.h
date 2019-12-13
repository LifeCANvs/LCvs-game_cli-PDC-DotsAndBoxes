#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
#include <stdbool.h>
struct player{

    char name[22]; //name can be at most 20 characters + 1 NULL + 1 \n check if pdcurses input puts them automatically
    int score;
    int moves;
    //int color; //see pdcurses interface DOES it have to be int??
};

struct dot{ //holder for coordinates

    int row;
    int column;
    //int emptySlot; //initialised to 4 or 2 or 3
};

struct{

    //grid
    struct player players[2];
    int lines; //lines already connected
    time_t timeElapsed;
    bool player1turn;

}inGameData;

/*struct{

    unsigned int main:3;
    unsigned int beginner:1;
    unsigned int computer:1;
    unsigned int gameToLoad:4;
} menuCoice;*/
#endif // STRUCTS_H_INCLUDED

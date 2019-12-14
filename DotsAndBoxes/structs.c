#include <stdio.h>
#include <stdlib.h>
#include "structs.h" //to be added

struct player{

    char name[22]; //name can be at most 20 characters + 1 NULL + 1 \n check if pdcurses input puts them automatically
    int score;
    int color; //see pdcurses interface DOES it have to be int??
};

struct dot{ //holder for coordinates

    int row;
    int column;
    //int emptySlot; //initialised to 4 or 2 or 3
};

struct line{ //might not need it

    struct dot start;
    struct dot end;
    int color;

};

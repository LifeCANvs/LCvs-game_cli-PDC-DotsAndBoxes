#include <stdio.h>
#include <stdlib.h>
#include "structs.h" //to be added

struct player{

    char name[22]; //name can be at most 20 characters + 1 NULL + 1 \n check if pdcurses input puts them automatically
    int score;
    int color; //see pdcurses interface DOES it have to be int??
};

struct dot{

    unsigned char up;//stores whether the dot is connected to another dot. if yes, stores the index of the line used
    unsigned char down;
    unsigned char left;
    unsigned char right;
    int position; //check pdcurses for precise format
};

struct line{

    struct dot start;
    struct dot end;
    int color;

};

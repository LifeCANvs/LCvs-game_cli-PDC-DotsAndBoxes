#include <stdio.h>
#include <stdlib.h>
#include "grid.h" //put here the grid itself, traversing the grid, etc
#include "structs.h"
#include "globals.h"
#include <stdbool.h>
#define MODE 3 //for test Purposes read dynamic allocation to clean this up

static int grid[MODE*MODE][4]; //MODE should be defined globally and dynamically allocated
int connect(struct dot, struct dot);
int initialiseGrid(int);
bool boxClosed(struct dot);
bool isAvailable(struct dot);


int initialiseGrid(int mode){
    // i = c + r * mode, but as a special case because 0<c<mode c = i%mode
    int size = mode*mode, i= 0, row, column;          //grid has the shape (described in docs
    /*get rid of special cases*/
    for(i = 0; i< size; i++){                           //up    right   down    left
         /* remove exceptions in columns*/              //index index   index   index
         row = i/mode;
         column = i%mode;
        if(column == 0){ //left column
            grid[i][LEFT] = -2; //blocked
            grid[i][RIGHT] = -1;
        }
        else if(column == mode-1){ //rightmost column
            grid[i][RIGHT] = -2; //blocked
            grid[i][LEFT] = -1;
        }
        else{
            grid[i][LEFT] = -1;
            grid[i][RIGHT] = -1;
        }
        /* deal with rows*/
        if(row == 0){ //uppermost row
            grid[i][UP] = -2; //blocked
            grid[i][DOWN] = -1;
        }
        else if (row == mode-1){//lowermost row
            grid[i][DOWN] = -2; //blocked
            grid[i][UP] = -1;
        }
        else{
            grid[i][UP] = -1;
            grid[i][DOWN] = -1;
        }
    }
}


bool isAvailable(struct dot currentDot){
    int i = 0, index = currentDot.column + MODE * currentDot.row;
    for(; i<4; i++){
        if(grid[index][i] == -1){
            return true;
        }
    }
    return false;
}

int connect(struct dot start, struct dot end){ //all dots passed to this function are valid
    int startIndex = start.column + MODE * start.row, endIndex = end.column + end.row * 4;
    int difference = startIndex - endIndex;
    if(difference == 3){
        grid[startIndex][DOWN] = endIndex;
        grid[endIndex][UP] = startIndex;
    }
    else if (difference == -3){
        grid[startIndex][UP] = endIndex;
        grid[endIndex][DOWN] = startIndex;
    }
    else if (difference == 1){
        grid[startIndex][RIGHT] = endIndex;
        grid[endIndex][LEFT] = startIndex;
    }
    else
    {
        grid[startIndex][LEFT] = endIndex;
        grid[endIndex][RIGHT] = startIndex;
    }
}

#include "globals.h"




void initialiseGrid()
{

    // i = c + r * mode, but as a special case because 0<c<mode c = i%mode
    int size = mode*mode, i= 0, row, column;          //grid has the shape (described in docs
    /*get rid of special cases*/
    for(i = 0; i< size; i++)                            //up    right   down    left
    {
        /* remove exceptions in columns*/              //index index   index   index
        row = i/mode;
        column = i%mode;
        if(column == 0)  //left column
        {
            grid[i][LEFT] = -2; //blocked
            grid[i][RIGHT] = -1;
        }
        else if(column == mode-1)  //rightmost column
        {
            grid[i][RIGHT] = -2; //blocked
            grid[i][LEFT] = -1;
        }
        else
        {
            grid[i][LEFT] = -1;
            grid[i][RIGHT] = -1;
        }
        /* deal with rows*/
        if(row == 0)  //uppermost row
        {
            grid[i][UP] = -2; //blocked
            grid[i][DOWN] = -1;
        }
        else if (row == mode-1) //lowermost row
        {
            grid[i][DOWN] = -2; //blocked
            grid[i][UP] = -1;
        }
        else
        {
            grid[i][UP] = -1;
            grid[i][DOWN] = -1;
        }
    }
}


bool isAvailable(struct dot currentDot)
{
    int i = 0, index = currentDot.column + mode * currentDot.row;
    for(; i<4; i++)
    {
        if(grid[index][i] == -1)
        {
            return true;
        }
    }
    return false;
}

bool connectGrid(struct dot start, struct dot end)  //all dots passed to this function are valid, returns whether a box was closed
{
    int startIndex = start.column + mode * start.row, endIndex = end.column + end.row * mode;
    int difference = startIndex - endIndex;
    enum direction dArrival;

    diagonal[0] = start;

    if(difference == -3)
    {
        grid[startIndex][DOWN] = endIndex;
        grid[endIndex][UP] = startIndex;
        dArrival = DOWN;
    }
    else if (difference == 3)
    {
        grid[startIndex][UP] = endIndex;
        grid[endIndex][DOWN] = startIndex;
        dArrival = UP;
    }
    else if (difference == -1)
    {
        grid[startIndex][RIGHT] = endIndex;
        grid[endIndex][LEFT] = startIndex;
        dArrival = RIGHT;
    }
    else
    {
        grid[startIndex][LEFT] = endIndex;
        grid[endIndex][RIGHT] = startIndex;
        dArrival = LEFT;
    }
    return boxClosed(endIndex, dArrival);
}

bool boxClosed(int startIndex, enum direction d)
{

    int i = d, linesJoined = 1, nextIndex = startIndex;
    while(linesJoined < 4)  //check clockwise
    {
        if(linesJoined == 2)
        {
            diagonal[1].row = nextIndex/mode;
            diagonal[1].column = nextIndex%mode;
        }
        i++;
        if(i > 3)
            i = 0;
        nextIndex = grid[nextIndex][i];
        if(nextIndex < 0)
            break;
        else
            linesJoined++;
    }
    if(linesJoined == 4)
        return true;
    else //check counter-clockwise
    {
        i = d, linesJoined = 1, nextIndex = startIndex;
        while(linesJoined < 4)
        {
            if(linesJoined == 2)
            {
                diagonal[1].row = nextIndex/mode;
                diagonal[1].column = nextIndex%mode;
            }
            i--;
            if(i < 0)
                i = 3;
            nextIndex = grid[nextIndex][i];
            if(nextIndex < 0)
                break;
            else
                linesJoined++;
        }
    }
    if(linesJoined == 4)
        return true;
    else
        return false;
}




//#include "computerTurn.h" //to  be added

#include "globals.h"


void initialiseRandom()
{
    srand((unsigned int)time(NULL));
}

void getComputerMove(struct dot chosenDots[2])
{
    int row, column, startX, startY, endX, endY;

    do
    {
        row = getRandomNumber(mode);
        column = getRandomNumber(mode);
    }
    while(!isAvailable((struct dot){.row = row, .column = column}));

    chosenDots[0].row = row, chosenDots[0].column = column;

    startX = 1+column*interdistx, startY = 1+row*interdisty;

    do
    {
        //without getRandomNumber, this generated an error so linearly search vLines and hLines for an empty

        if(chosenDots[0].row == 0)//error restrict more
        {
            row = getRandomNumber(2) + chosenDots[0].row;
        }
        else if(chosenDots[0].row == mode-1)
        {
            row = -(getRandomNumber(2)) + chosenDots[0].row;
        }
        else
        {
            row = (int)pow(-1, rand())*getRandomNumber(2) + chosenDots[0].row;
        }

        if(row != chosenDots[0].row) //column is decided
        {
            column = chosenDots[0].column;
        }
        else
        {
            if(chosenDots[0].column == 0)
            {
                column = chosenDots[0].column + 1;
            }
            else if (chosenDots[0].column == mode-1)
            {
                column = chosenDots[0].column-1;
            }
            else
            {
                column = (int)pow(-1,rand()) + chosenDots[0].column;
            }
        }
        endX = 1 + column*interdistx, endY = 1 + row*interdisty;
    }
    while((startX ==endX && startY == endY) || lineColor(startY, startX, endY, endX));  //same dot or already joined
    chosenDots[1].row = row, chosenDots[1].column = column;
    wattron(gridWindow, COLOR_PAIR(4));
    drawLine(startY,startX,endY, endX);
    wattroff(gridWindow, COLOR_PAIR(4));
    wrefresh(gridWindow);
}

int getRandomNumber(int range){

    int x;
    do
    {
        x = rand();
    }while(x > (RAND_MAX - RAND_MAX % (range-1)));
    return x % range;

}

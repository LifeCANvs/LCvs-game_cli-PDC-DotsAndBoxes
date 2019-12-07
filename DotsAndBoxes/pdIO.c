#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <math.h> //do I need this for abs??
#include <ctype.h>
#include <string.h>
#include "pdIO.h> //to be made
//global (extern) arrays of dots and lines

struct dot * getPlayerMove( int arr[][4] ){

    struct dot chosenDots[2]; //proposed idea: to make an id for each dot (calculated from its index in dot matrix) and pass these only from and to functions
    //input first dot



};

int getMenuChoice(){

    /*print menu and get choice*/

};

void connectDots(/*int chosenDotsID*/){

    //connect chosen dots and unpdate line color

};

//extra functions for screen drawing, refreshing, CTRL+S (in-game menu)

void getPlayerName(struct player * currentPlayerPointer){ //called when a player wins

    struct player currentPlayer = *currentPlayerPointer;
    char name[22];
    /*do something to get name*/
    for(int i = 0; i < 22 && name[i] != '\0'; i++ ){
        name[i] = tolower(name[i]);
    } //what about \n?
    strcpy(currentPlayer.name, name);

};

void displayData(struct player * players, int n ) //n is number of players to display 1, 10
{
  for(int i = 0; i<n;i++){
    /*do something*/
  }
};

#include "globals.h"
//global (extern) arrays of dots and lines



void initialiseUI(){

    int nCols = COLS / 2;
    int nLines = 3*LINES / 2;
    initscr();
    cbreak();
    noecho();
    refresh();

    curs_set(2);

    mainWindow = newwin(nLines, nCols, 0,0);
}

struct dot * getPlayerMove(/*grid is a global variable*/){

    struct dot chosenDots[2]; //proposed idea: to make an id for each dot (calculated from its index in dot matrix) and pass these only from and to functions
    //input first dot



};

/*void getMenuChoice(char * whichMenu){ /*print menu and get choice

    if(!strcmp(whichMenu,"main")){
        struct item mainM [4] = {
            {"start game", subMenu1};
            {"load game", subMenu2};
            {"top 10 players", printTop10()};
        };
    }

};*/

void connectUI(struct dot chosenDots[2]){



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

int doMenu(int y, int x, WINDOW * currentMenu, int n, char * items[n]){

    int maxLength = 0, i, key = '\n', choice = 0, prevChoice = -1;

    for(i = 0; i < n; i++)
        if(strlen(items[i]) > maxLength)
            maxLength = strlen(items[i]); //find out the width of the items

    currentMenu = newwin(n+2, maxLength+4, y,x);
    box(currentMenu, 0, 0);
    keypad(currentMenu, TRUE);
    for(i = 0; i < n; i++){
        mvwprintw(currentMenu,1+i,1,"%s", items[i]);
    }
    wrefresh(currentMenu);

    do{
        if(prevCoice != choice){
            prevCoice == choice;
            wattron(currentMenu, A_REVERSE);
            mvwprintw(currentMenu, 1+choice, 1, "%s", items[choice]);
            wrefresh(currentMenu);
        }
        key = wgetch(currentMenu);
        switch (key){
        case KEY_UP:
            choice = choice == 0? n-1: choice-1; break;
        case KEY_DOWN:
            choice = choice == n-1? 0: choice+1; break;
        }

    }while(key != '\n');
    free(currentMenu);

    return choice;
}



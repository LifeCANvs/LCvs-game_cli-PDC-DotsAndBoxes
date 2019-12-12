#ifndef PDIO_H_INCLUDED
#define PDIO_H_INCLUDED


struct dot * getPlayerMove(/*grid is a global variable*/);

void getMenuChoice( char *);
void connectUI(struct dot chosenDots[2]);
void getPlayerName(struct player * currentPlayerPointer);
void displayData(struct player * players, int n );
int doMenu(int y, int x, WINDOW * currentMenu,int n, char * items[n]);

WINDOW * mainWindow; /*in game windows*/
WINDOW * gridWindow;
WINDOW * dataWindow;
WINDOW * messageWindow;


/*struct item{

    char * name;
    FUNC func;

};*/

#endif // PDIO_H_INCLUDED

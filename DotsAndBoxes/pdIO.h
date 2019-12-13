#ifndef PDIO_H_INCLUDED
#define PDIO_H_INCLUDED


void getPlayerMove(struct dot *);
void drawLine(int, int, int,int);
void getPlayerName(struct player * currentPlayerPointer);
void displayData(struct player * players, int n );
int doMenu(int y, int x, WINDOW * currentMenu,int n, char * items[n]);
void updateDataWindow(int);
int lineColor(int, int, int, int);


WINDOW * helpWindow; /*in game windows*/
WINDOW * gridWindow;
WINDOW * dataWindow;
WINDOW * messageWindow;

int interdistx, interdisty, maxx, maxy; //for grid



/*struct item{

    char * name;
    FUNC func;

};*/

#endif // PDIO_H_INCLUDED

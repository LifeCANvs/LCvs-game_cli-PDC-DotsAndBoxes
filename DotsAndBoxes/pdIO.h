#ifndef PDIO_H_INCLUDED
#define PDIO_H_INCLUDED

void initialiseUI(bool);
void getPlayerMove(struct dot *);
void drawLine(int, int, int,int);
void getPlayerName(int);
void displayData(const char  *, int );
int doMenu(int y, int x, WINDOW * currentMenu,int n, char * items[n]);
void updateDataWindow();
int lineColor(int, int, int, int);
void repaintBox(int);
void reinitialiseUI();


WINDOW * helpWindow; /*in game windows*/
WINDOW * gridWindow;
WINDOW * dataWindow;
WINDOW * messageWindow;

int interdistx, interdisty, maxx, maxy; //for grid


#endif // PDIO_H_INCLUDED

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

int grid[5*5][4]; //temporarily until i know how to do this dynamically
int connectGrid(struct dot, struct dot); //calls boxClosed
void initialiseGrid();
int boxClosed(int, enum direction d);
bool isAvailable(struct dot);

#endif // GRID_H_INCLUDED

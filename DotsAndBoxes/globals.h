#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
enum direction {UP, RIGHT, DOWN, LEFT};
int mode; //linesLeft = (mode-1)*(mode-1)
time_t startTime;
//bool saved = false;///////////
//diameter of connected box

#include "structs.h"
#include "grid.h"
#include "pdIO.h"

struct dot diagonal[2];




#endif // GLOBALS_H_INCLUDED

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
int mode, linesLeft; //linesLeft = (mode-1)*(mode-1)
time_t startTime;

#include "structs.h"
#include "grid.h"
#include "pdIO.h"






#endif // GLOBALS_H_INCLUDED

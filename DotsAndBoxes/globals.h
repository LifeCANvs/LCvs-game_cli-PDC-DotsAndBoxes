#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "structs.h"
#include "pdIO.h"
#include "grid.h"



enum direction {UP, RIGHT, DOWN, LEFT};
int mode, linesLeft; //linesLeft = (mode-1)*(mode-1)

#endif // GLOBALS_H_INCLUDED

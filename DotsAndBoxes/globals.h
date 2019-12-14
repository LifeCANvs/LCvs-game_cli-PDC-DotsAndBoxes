#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
enum direction {UP, RIGHT, DOWN, LEFT};
int mode; //linesLeft = (mode-1)*(mode-1)
time_t time1;
bool saved;
bool repaint;


#include "structs.h"
#include "grid.h"
#include "pdIO.h"

struct dot diagonal[2][2]; //diagonal of connected box




#endif // GLOBALS_H_INCLUDED

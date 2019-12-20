#include "globals.h"
//global (extern) arrays of dots and lines



void initialiseUI()
{

    int remainingLines = LINES - 21;
    int remainingCols = COLS - 41;
    int i, j;
    int max, startX, startY; //maximum number of lines
    interdistx = mode == 3? 19:9;
    interdisty = mode == 3? 9:4;

    initscr();
    clear();
    refresh();
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE, COLOR_BLACK);
    init_pair(3,COLOR_BLACK,COLOR_RED);
    init_pair(4,COLOR_BLACK, COLOR_BLUE);
    init_pair(5,COLOR_BLACK, COLOR_MAGENTA); //selected dot


    curs_set(0);
    keypad(gridWindow, TRUE);

    /*grid window*/
    gridWindow = newwin(21,41,0,0);
    box(gridWindow, 0, 0);
    for(i = 1; i < 20; i += interdisty)
    {
        for(j = 1; j < 40; j += interdistx)
        {
            if(i == 1 && j == 1)
            {
                wattron(gridWindow,A_REVERSE);
                mvwaddch(gridWindow, 1, 1,'O');
                wattroff(gridWindow,A_REVERSE);
            }
            else
            {
                mvwaddch(gridWindow,i,j,'O');
            }
            wnoutrefresh(gridWindow);
        }
    }
    maxx = j-interdistx;
    maxy = i-interdisty;

    if(reload)//only when the game is loaded
    {
        max = mode*(mode-1);
        for(i = 0; i < max; i++)
        {
            int row, column;
            int color = inGameData.vLines[i];
            if(color)
            {
                row = i/mode, column = i%mode;
                startX = 1 +column*interdistx;
                startY = 1 + row*interdisty;
                wattron(gridWindow, COLOR_PAIR(color));
                drawLine(startY, startX, startY+interdisty, startX);
                wattroff(gridWindow, COLOR_PAIR(color));
                //wnoutrefresh(gridWindow);

                wrefresh(gridWindow);
            }
            color = inGameData.hLines[i];
            if(color)
            {
                row = i%mode, column = i/mode;
                startX = 1 + column*interdistx;
                startY = 1 + row*interdisty;
                wattron(gridWindow, COLOR_PAIR(color));
                drawLine(startY, startX, startY, startX+interdistx);
                wattroff(gridWindow, COLOR_PAIR(color));
                wrefresh(gridWindow);

                //wnoutrefresh(gridWindow);
            }
        }
    }


    doupdate();

    /*message window*/
    messageWindow = newwin(remainingLines, 41, 21,0); //print message game saved to 1/2/3
    box(messageWindow,0,0);
    wrefresh(messageWindow);

    /*data window*/
    dataWindow = newwin(21,remainingCols,0,41);//data width = COLS-41 !!
    //call function to initalise data window
    updateDataWindow(-1);

    /*help window*/
    helpWindow = newwin(remainingLines,remainingCols,21,41);
    mvwprintw(helpWindow,1,1,"Choose a dot and press enter\n Press z for undo/redo\n Press s to save");
    box(helpWindow,0,0);

    wrefresh(helpWindow);

}

void getPlayerMove(struct dot chosenDots[2])
{

    struct dot spareDot = {-1, -1}; //for undo and redo
    struct dot currentDot;
    //input first dot
    int x = 1, y = 1, prevX = 1, prevY = 1, i, startX, startY; //grid starting point is 1,1
    int key;
    bool validKey, done;

    cbreak();
    keypad(gridWindow,TRUE);

    wattron(gridWindow, A_REVERSE); /*initially select top left dot*/
    mvwaddch(gridWindow, 1, 1, 'O');
    wattroff(gridWindow, A_REVERSE);
    wrefresh(gridWindow);

    for(i = 0; i < 2; )
    {


        wmove(messageWindow,2,2);
        wclrtoeol(messageWindow);
        done = false;
        if(i == 0)  //logic for first dot
        {
            do
            {
                validKey = false;

                while(!validKey)
                {
                    prevX = x;
                    prevY = y;
                    halfdelay(200);
                    halfdelay(200);
                    halfdelay(200);
                    key = wgetch(gridWindow);
                    switch(key)
                    {
                    case ERR:
                        updateDataWindow();
                        break;
                    case KEY_UP:
                        y = y==1? maxy:y-interdisty;
                        validKey = true;
                        break;
                    case KEY_DOWN:
                        y = y==maxy? 1:y+interdisty;
                        validKey = true;
                        break;
                    case KEY_RIGHT:
                        x = x==maxx? 1:x+interdistx;
                        validKey = true;
                        break;
                    case KEY_LEFT:
                        x = x==1? maxx:x-interdistx;
                        validKey = true;
                        break;
                    case 'z': //redo
                        validKey = true;
                        if(spareDot.row != -1)
                        {
                            x = (1 + spareDot.column*interdistx);
                            y = (1 + spareDot.row * interdisty);
                            done = true;
                        }
                        break;
                    case 's':
                    {
                        char * saveSlots[3] = {"Game 1", "Game 2", "Game 3"};
                        validKey = true;
                        done = true;
                        key = doMenu(2,2,messageWindow, 3, saveSlots);
                        mvwprintw(messageWindow,1,1,"Saving Game..");
                        wrefresh(messageWindow);
                        saveGame(key+1);
                        mvwprintw(messageWindow, 2,1, "Press any key to continue");
                        wrefresh(messageWindow);

                        saved = true;
                    }

                    return;
                    break;
                    case '\n':
                        validKey = true;
                        done = true;
                        break;
                    default:
                        break;

                    }
                }
                //if the previous dot is not magenta, unselect it
                mvwaddch(gridWindow,prevY,prevX,'O');
                wattron(gridWindow,A_REVERSE);
                mvwaddch(gridWindow,y,x,'O');
                wattroff(gridWindow,A_REVERSE);
                wrefresh(gridWindow);
            }
            while(!done);

            if(isAvailable((struct dot)
        {
            y/interdisty,x/interdistx
        }))
            {
                currentDot.row = y/interdisty;
                currentDot.column = x/interdistx;
                wattron(gridWindow,COLOR_PAIR(5));
                mvwaddch(gridWindow,y,x,'O');
                wattroff(gridWindow,COLOR_PAIR(5));
                chosenDots[0] = currentDot;
                i++;
                startX = x;
                startY = y;
            }
            else
            {
                mvwprintw(messageWindow,2,2,"Please select a different dot");
                wrefresh(messageWindow);
            }
        }
        else  //logic for second dot
        {
            do
            {
                validKey = false;

                while(!validKey)
                {
                    prevX = x;
                    prevY = y;
                    key = wgetch(gridWindow);
                    switch(key)
                    {
                    case ERR:
                        updateDataWindow();
                        break;
                    case KEY_UP:
                        if( y == startY && x == startX)  //going up from selected dot
                        {
                            if(y-interdisty > 0)
                                y = y - interdisty;
                        }
                        else if (y - startY == interdisty)  //going up TO selected dot
                        {
                            y = startY;
                        }
                        validKey = true;
                        break;
                    case KEY_DOWN:
                        if( y == startY && x == startX)
                        {
                            if(y+interdisty <= maxy)
                                y = y + interdisty;
                        }
                        else if (startY - y == interdisty)
                        {
                            y = startY;
                        }
                        validKey = true;
                        break;
                    case KEY_RIGHT:
                        if( x == startX && y == startY)
                        {
                            if(x+interdistx <= maxx)
                                x = x + interdistx;
                        }
                        else if (startX - x == interdistx)
                        {
                            x = startX;
                        }
                        validKey = true;
                        break;
                    case KEY_LEFT:
                        if( x == startX && y == startY)
                        {
                            if(x-interdistx > 0)
                                x = x - interdistx;
                        }
                        else if (x - startX == interdistx)
                        {
                            x = startX;
                        }
                        validKey = true;
                        break;
                    case 'z': //undo
                        validKey = true;
                        spareDot = currentDot;
                        i--;
                        x = startX;
                        y = startY;
                        done = true;
                        break;
                    case 's':
                        validKey = true;
                        mvwprintw(messageWindow,2,2,"Please undo first then save");
                        wrefresh(messageWindow);
                        break;
                    case '\n':
                        validKey = true;
                        done = true;
                        break;
                    default:
                        break;

                    }
                }
                if(prevX == startX && prevY == startY)
                {
                    wattron(gridWindow,COLOR_PAIR(5));
                    mvwaddch(gridWindow,prevY,prevX,'O');
                    wattroff(gridWindow, COLOR_PAIR(5));
                }
                else
                {
                    mvwaddch(gridWindow,prevY,prevX,'O');
                }

                wattron(gridWindow,A_REVERSE);
                mvwaddch(gridWindow,y,x,'O');
                wattroff(gridWindow,A_REVERSE);
                wrefresh(gridWindow);
            }
            while(!done);

            if(key == 'z')
                continue;
            if((!(x == startX && y ==startY)) && !lineColor(startY,startX,y,x))
            {

                chosenDots[1].row = y/interdisty;
                chosenDots[1].column = x/interdistx;
                mvwaddch(gridWindow,y,x,'O');

                wattron(gridWindow, inGameData.player1turn?COLOR_PAIR(3):COLOR_PAIR(4));
                drawLine(startY, startX, y, x);
                wattroff(gridWindow, inGameData.player1turn?COLOR_PAIR(3):COLOR_PAIR(4));
                wrefresh(gridWindow);

                i++;
            }
            else
            {
                mvwprintw(messageWindow,2,2,"Please select a different dot");

            }
            wrefresh(messageWindow);

        }


    }

    mvwaddch(gridWindow, startY,startX,'O');
    mvwaddch(gridWindow, y,x, 'O');
}


void drawLine(int startY, int startX, int endY, int endX)
{
    int startRow, startColumn;
    if(startX > endX)
    {
        startX ^= endX;
        endX ^= startX;
        startX ^= endX;
    }
    if(startY > endY)
    {
        startY ^= endY;
        endY ^= startY;
        startY ^= endY;
    }
    startRow = startY/interdisty, startColumn = startX/interdistx;
    if(startX == endX) //vertical line
    {
        mvwvline(gridWindow,startY+1,startX,' ', interdisty-1);
        inGameData.vLines[startColumn + startRow*mode] = inGameData.player1turn?3:4;
    }
    else //horizontal line
    {
        mvwhline(gridWindow,startY,startX+1,' ', interdistx-1);
        inGameData.hLines[startRow + startColumn*mode] = inGameData.player1turn?3:4;
    }

}

//extra functions for screen drawing, refreshing, CTRL+S (in-game menu)

void getPlayerName(int whichPlayer)  //called when a player wins
{
    char name[22];
    int rank;

    wclrtobot(messageWindow);
    box(messageWindow,0,0);
    mvwprintw(messageWindow, 1, 1, "Player %d wins!", whichPlayer);
    mvwprintw(messageWindow, 2, 1, "Please enter your name");
    mvwprintw(messageWindow, 3,1,"(20 characters): ");
    curs_set(1);
    echo();

    wrefresh(messageWindow);
    keypad(messageWindow,TRUE);
    wgetnstr(messageWindow,name, 21);

    for(int i = 0; i < 22 && name[i] != '\0'; i++ )
    {
        name[i] = tolower(name[i]);
    } //what about \n?
    strcpy(inGameData.players[whichPlayer].name, name);
    rank = savePlayer(inGameData.players[whichPlayer]);
    mvwprintw(messageWindow, 6,1,"Your rank is %d", rank+1);
    wrefresh(messageWindow);

}

void displayData(const char *name, int score ) //n is number of players to display 1, 10
{
    static int called = 0;
    if(called == 0)
    {
        mvprintw(LINES/2,COLS/2,"TOP 10 PLAYERS");
    }
    called++;
    mvprintw((LINES/2)+called,COLS/2-22, name);
    mvprintw((LINES/2)+called, COLS/2,"%d",score);
    refresh();
}

int doMenu(int y, int x, WINDOW * currentMenu, int n, char * items[n])
{

    int i, key = '\n', choice = 0, prevChoice = -1;
    unsigned int maxLength = 0;
    for(i = 0; i < n; i++)
        if(strlen(items[i]) > maxLength)
            maxLength = strlen(items[i]); //find out the width of the items

    currentMenu = newwin(n+2, maxLength+4, y,x);
    box(currentMenu, 0, 0);
    keypad(currentMenu, TRUE);
    for(i = 0; i < n; i++)
    {
        mvwprintw(currentMenu,1+i,1,"%s", items[i]);
    }
    wrefresh(currentMenu);

    do
    {
        if(prevChoice != choice)
        {
            if(prevChoice != -1)
            {
                mvwprintw(currentMenu, 1+prevChoice, 1, "%s", items[prevChoice]);
            }
            prevChoice = choice;
            wattron(currentMenu, A_REVERSE);
            mvwprintw(currentMenu, 1+choice, 1, "%s", items[choice]);
            wattroff(currentMenu, A_REVERSE);
            wrefresh(currentMenu);
        }
        key = wgetch(currentMenu);
        switch (key)
        {
        case KEY_UP:
            choice = choice == 0? n-1: choice-1;
            break;
        case KEY_DOWN:
            choice = choice == n-1? 0: choice+1;
            break;
        default:
            break;
        }

    }
    while(key != '\n');
    free(currentMenu);

    return choice;
}

void updateDataWindow()
{
    wclrtobot(dataWindow);
    box(dataWindow,0,0);
    /*turn*/
    if(inGameData.linesLeft <= 0)
    {
        mvwprintw(dataWindow,2,2, "Game Ended       ");
        wnoutrefresh(dataWindow);
    }
    else
    {
        wattron(dataWindow,inGameData.player1turn?COLOR_PAIR(1):COLOR_PAIR(2));
        mvwprintw(dataWindow, 2, 2,"Player %d's turn",inGameData.player1turn?1:2);
        wattroff(dataWindow,inGameData.player1turn?COLOR_PAIR(1):COLOR_PAIR(2));
        wnoutrefresh(dataWindow);
    }


    //doupdate();
    /*remaining lines*/
    mvwprintw(dataWindow, 4,2,"remaining lines = %.2d",inGameData.linesLeft);
    //doupdate();

    /*moves and score*/
    mvwprintw(dataWindow, 7, 2, "moves");
    mvwprintw(dataWindow, 8, 2, "score");
    for(int i = 1; i <= 2; i++)
    {
        wattron(dataWindow, COLOR_PAIR(i));
        mvwprintw(dataWindow, 6, 10*(i),"Player %d", i);
        mvwprintw(dataWindow, 7, 10*(i), "%d",inGameData.players[i-1].moves);
        mvwprintw(dataWindow, 8, 10*(i),"%d",inGameData.players[i-1].score);
        wattroff(dataWindow, COLOR_PAIR(i));
    }
    //doupdate();
    /*time*/
    inGameData.timeElapsed += round(difftime(time(NULL),time1));
    time1 = time(NULL);
    mvwprintw(dataWindow,10,2,"time: %.2d:%.2d", inGameData.timeElapsed/60, inGameData.timeElapsed %60);

    wrefresh(dataWindow);


}

int lineColor(int startY, int startX, int endY, int endX)
{

    chtype middle = mvwinch(gridWindow,abs(startY+endY)/2,abs(startX+endX)/2);
    if( (middle & A_COLOR) == COLOR_PAIR(3))  //player 1 connected this line
    {
        return 3;
    }
    if( (middle & A_COLOR) == COLOR_PAIR(4) )  //player 2 connected this line
    {
        return 4;
    }
    return 0; //not connected

}

void repaintBox(int numberOfBoxes)
{
    int x1, x2, y1, y2;
    for(int i = 0; i < numberOfBoxes; i++)
    {
        x1 = 1 + diagonal[i][0].column * interdistx;
        x2 = 1 + diagonal[i][1].column * interdistx;
        y1 = 1 + diagonal[i][0].row * interdisty;
        y2 = 1 + diagonal[i][1].row * interdisty;
        wattron(gridWindow, inGameData.player1turn?COLOR_PAIR(3):COLOR_PAIR(4));
        drawLine(y1, x1, y1, x2);
        drawLine(y1, x1, y2, x1);
        drawLine(y2, x2, y1, x2);
        drawLine(y2, x2, y2, x1);
        wattroff(gridWindow, inGameData.player1turn?COLOR_PAIR(3):COLOR_PAIR(4));
        wrefresh(gridWindow);
    }


}


#include "globals.h"

//extern int mode;
bool computer;

void playGame();


int main()
{
    int choice, x = 4, y = 4;
    char * mainMenuItems[4]= {"start game","load game","top 10 players","exit"};
    char * subMenu1[4] = {"beginner vs beginner","beginner vs computer","expert vs expert","expert vs computer"};
    char * subMenu2[6] = {"beginner game 1", "beginner game 2", "beginner game 3", "expert game 1", "expert game 2","expert game 3"};
    WINDOW * mainMenuWin = (WINDOW *)0;

    initscr();
    cbreak();
    noecho();
    refresh();
    wprintw(stdscr,"\t\t*** \t ** \t***\t***\n\
             \t*  *\t*  *\t * \t *\n\
             \t*** \t ** \t * \t***\n");
    refresh();

    choice = doMenu(y,x, mainMenuWin,4, mainMenuItems);  //main menu

    switch(choice)
    {

    case 0: /* beginner, vs human*/
        choice = doMenu(y+2,x+10,mainMenuWin,4,subMenu1);
        switch(choice)
        {
        case 0:
            mode = 3, computer = false;
            playGame();
            break;
        case 1:
            mode = 3, computer = true;
            playGame();
            break;
        case 2:
            mode = 5, computer = false;
            playGame();
            break;
        case 3:
            mode = 5, computer = true;
            playGame();
            break;
        }
        break;
    case 1:
        choice = doMenu(y+3,x+10,mainMenuWin, 6,subMenu2);
        switch(choice)
        {
        case 0:
            break;
        default:
            break;

        }
        break;
    case 2:
        //read from file then print
        break;
    default:
        break;
    }

    delwin(gridWindow);
    delwin(dataWindow);
    delwin(messageWindow);
    delwin(helpWindow);
    getch();
    endwin();
    return 0;
}

void playGame()
{
    struct dot chosenDots[2];
    int boxesConnected;
    int currentPlayer;
    repaint = false;
    saved = false;
    for(int i = 0; i<20; i++){
        inGameData.vLines[i] = 0;
        inGameData.hLines[i] = 0;
    }

    inGameData.player1turn = true;
    inGameData.timeElapsed = (time_t)0;
    inGameData.linesLeft = 2*(mode - 1)*(mode);
    time1 = time(NULL);

    initialiseGrid();
    initialiseUI(false);

    for(int i = 0; i < 2; i++)
    {
        inGameData.players[i].score = 0;
        inGameData.players[i].moves = 0;
    }


    while(inGameData.linesLeft > 0) //UNDO is done within getPlayerMove
    {
        currentPlayer = inGameData.player1turn?0:1;
        updateDataWindow();
        if(computer && !inGameData.player1turn)
        {
            //chosenDots = getComputerMove();
        }
        else
        {
            getPlayerMove(chosenDots);
        }

        if(saved)
        {
            return;
        }

        inGameData.linesLeft = inGameData.linesLeft-1;
        inGameData.players[currentPlayer].moves++;
        boxesConnected = connectGrid(*chosenDots, *(chosenDots+1));
        if(boxesConnected) // a box is closed
        {
            inGameData.players[currentPlayer].score+= boxesConnected;
            repaintBox(boxesConnected);
        }
        else
        {
            inGameData.player1turn = !inGameData.player1turn;
        }
    }
    updateDataWindow(-1);
    if(inGameData.players[0].score > inGameData.players[1].score)
    {
        getPlayerName(0); //prints who is winner and prompt name
    }
    else if(inGameData.players[0].score == inGameData.players[1].score)
    {
        mvwprintw(messageWindow, 2,2, "It's a draw!");
        wrefresh(messageWindow);
    }
    else
        getPlayerName(1);

    mvwprintw(helpWindow, 5,1,"Press any key to exit");
    wrefresh(helpWindow);
    //write new data to file

}


#include "globals.h"

//extern int mode;

void playGame();


int main()
{
    int choice, x = 10, y = 6;
    bool ingame = false;
    char * mainMenuItems[4]= {"start game","load game","top 10 players","exit"};
    char * subMenu1[4] = {"beginner vs beginner","beginner vs computer","expert vs expert","expert vs computer"};
    char * subMenu2[6] = {"beginner game 1", "beginner game 2", "beginner game 3", "expert game 1", "expert game 2","expert game 3"};
    WINDOW * mainMenuWin = (WINDOW *)0;

    initscr();
    cbreak();
    noecho();
    refresh();
    initialiseRandom();
    mvprintw(1,3," ____   __  ____  ____     __   __ _  ____    ____   __  _  _  ____  ____");
    mvprintw(2,3,"(    \\ /  \\(_  _)/ ___)   / _\\ (  ( \\(    \\  (  _ \\ /  \\( \\/ )(  __)/ ___)");
    mvprintw(3,3," ) D ((  O ) )(  \\___ \\  /    \\/    / ) D (   ) _ ((  O ))  (  ) _) \\___ \\");
    mvprintw(4,3,"(____/ \\__/ (__) (____/  \\_/\\_/\\_)__)(____/  (____/ \\__/(_/\\_)(____)(____/");
    refresh();

    choice = doMenu(y,x, mainMenuWin,4, mainMenuItems);  //main menu

    switch(choice)
    {

    case 0:
        ingame =true;
        choice = doMenu(y+2,x+10,mainMenuWin,4,subMenu1);
        switch(choice)
        {
        case 0:
            mode = 3, inGameData.computer = false, reload = false;
            playGame();
            break;
        case 1:
            mode = 3, inGameData.computer = true, reload = false;
            playGame();
            break;
        case 2:
            mode = 5, inGameData.computer = false, reload = false;
            playGame();
            break;
        case 3:
            mode = 5, inGameData.computer = true, reload = false;
            playGame();
            break;
        }
        break;
    case 1:
        ingame = true, reload = true;
        choice = doMenu(y+3,x+10,mainMenuWin, 6,subMenu2);
        loadGame(choice);
        playGame(true);
        break;
    case 2:
        clear();
        getTop10();
        break;
    default:
        break;
    }

    getch();

    delwin(mainMenuWin);
    if(ingame){
        delwin(gridWindow);
    delwin(dataWindow);
    delwin(messageWindow);
    delwin(helpWindow);
    }


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
    time1 = time(NULL);

    if(reload)
    {
        initialiseUI(true);
    }
    else //initialise game
    {
        for(int i = 0; i<20; i++)
        {
            inGameData.vLines[i] = 0;
            inGameData.hLines[i] = 0;
        }

        inGameData.player1turn = true;
        inGameData.timeElapsed = (time_t)0;
        inGameData.linesLeft = 2*(mode - 1)*(mode);

        initialiseGrid();
        initialiseUI(false);
        for(int i = 0; i < 2; i++)
        {
            inGameData.players[i].score = 0;
            inGameData.players[i].moves = 0;
        }

    }



    while(inGameData.linesLeft > 0) //UNDO is done within getPlayerMove
    {
        currentPlayer = inGameData.player1turn?0:1;
        updateDataWindow();
        if(inGameData.computer && !inGameData.player1turn)
        {
            getComputerMove(chosenDots);
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
    updateDataWindow();
    if(inGameData.players[0].score > inGameData.players[1].score)
    {
        getPlayerName(1); //prints who is winner and prompt name
    }
    else if(inGameData.players[0].score == inGameData.players[1].score)
    {
        mvwprintw(messageWindow, 2,2, "It's a draw!");
        wrefresh(messageWindow);
    }
    else if (!inGameData.computer)
    {
        getPlayerName(2);
    }
    else
    {
        mvwprintw(messageWindow, 2,2, "The Computer Wins");
        wrefresh(messageWindow);
    }

    mvwprintw(helpWindow, 5,1,"Press any key to exit");
    wrefresh(helpWindow);
    //write new data to file

}


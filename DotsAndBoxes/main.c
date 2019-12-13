#include "globals.h"

extern int mode;
bool computer;

void playGame();


int main()
{
    int choice, x = 4, y = 4;
    char * mainMenuItems[4]= {"start game","load game","top 10 players","exit"};
    char * subMenu1[4] = {"beginner vs beginner","beginner vs computer","expert vs expert","expert vs computer"};
    char * subMenu2[6] = {"beginner game 1", "beginner game 2", "beginner game 3", "expert game 1", "expert game 2","expert game 3"};
    WINDOW * mainMenuWin;

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
        switch(choice){

        case 0: break;

        }
        break;
    case 2:
        //read from file then print
        break;
    default: break;
    }

    getch();
    endwin();
    return 0;
}

void playGame()
{
    struct dot *chosenDots;
    bool incrementScore;
    int currentPlayer;

    inGameData.lines = 0;
    inGameData.player1turn = true;
    inGameData.timeElapsed = 0;
    linesLeft = 2*(mode - 1)*(mode);
    startTime = time(NULL);

    initialiseGrid();
    initialiseUI();

    for(int i = 0; i < 2; i++)
    {
        inGameData.players[i].score = 0;
        inGameData.players[i].moves = 0;
    }

    chosenDots = (struct dot *)calloc(sizeof(struct dot),2);
    if(chosenDots != NULL)
    {
        while(linesLeft > 0) //UNDO is done within getPlayerMove
        {
            currentPlayer = inGameData.player1turn?0:1;
            if(computer)
            {
                chosenDots = getComputerMove();
            }
            else
            {
                getPlayerMove(chosenDots);
            } //assigning a static array pointer to dynamic?
            inGameData.players[currentPlayer].moves++;
            incrementScore = connectGrid(*chosenDots, *(chosenDots+1)); //calls connectUI()
            if(incrementScore)
            {
                inGameData.players[currentPlayer].score++;
            }
            else
            {
                inGameData.player1turn = !inGameData.player1turn;
            }
        }
        if(inGameData.players[0].score > inGameData.players[1].score)
        {
            getPlayerName(&inGameData.players[0]); //prints who is winner and prompt name
        }
        else if(inGameData.players[0].score == inGameData.players[1].score)
        {
            //printDraw();
        }
        else
            getPlayerName(&inGameData.players[1]);
        //write new data to file
    }
    else
    {
        printf("chosenDots not allocated\n"); //debugging purposes
    }
    free(chosenDots);

}


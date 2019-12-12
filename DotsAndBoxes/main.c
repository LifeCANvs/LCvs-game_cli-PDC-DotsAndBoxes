#include "globals.h"
//some functions in main can be called by any other module
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

    choice = doMenu(y,x, mainMenuWin,4, mainMenuItems);  //main menu

    switch(choice)
    {

    case 0: /* beginner, vs human*/
        choice = doMenu(y+2,x+10,mainMenuWin,4,subMenu1);
        switch(choice)
        {
        case 1:
            mode = 3, computer = false;
            playGame();
            break;
        case 2:
            mode = 3, computer = true;
            playGame();
            break;
        case 3:
            mode = 5, computer = false;
            playGame();
            break;
        case 5:
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
    struct inGameData currentGame = {.lines = linesLeft, .player1turn = true, .timeElapsed = 0};
    int currentPlayer;

    for(int i = 0; i < 2; i++)
    {
        currentGame.players[i].score = 0;
        currentGame.players[i].moves = 0;
    }

    chosenDots = (struct dot *)calloc(sizeof(struct dot),2);
    if(chosenDots != NULL)
    {
        while(linesLeft > 0) //UNDO is done within getPlayerMove
        {
            currentPlayer = currentGame.player1turn?0:1;
            if(computer)
            {
                chosenDots = getComputerMove();
            }
            else
            {
                chosenDots = getPlayerMove();
            } //assigning a static array pointer to dynamic?
            currentGame.players[currentPlayer].moves++;
            incrementScore = connectGrid(*chosenDots, *(chosenDots+1)); //calls connectUI()
            if(incrementScore)
            {
                currentGame.players[currentPlayer].score++;
            }
            else
            {
                currentGame.player1turn = !currentGame.player1turn;
            }
        }
        if(currentGame.players[0].score > currentGame.players[1].score)
        {
            getPlayerName(&currentGame.players[0]); //prints who is winner and prompt name
        }
        else if(currentGame.players[0].score == currentGame.players[1].score)
        {
            //printDraw();
        }
        else
            getPlayerName(&currentGame.players[1]);
        //write new data to file
    }
    else
    {
        printf("chosenDots not allocated\n"); //debugging purposes
    }
    free(chosenDots);

}


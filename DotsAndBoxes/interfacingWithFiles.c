#include "globals.h"

void savePlayer(/*args*/)
{

    //write record of player after the game has finished

}

void saveGame(int number)
{

    FILE *S1;
    char  fileName[15];
    sprintf(fileName, "%s%s%d%s", ".\\SAVE", mode == 3? "beginner":"expert",number, ".txt");

    S1=fopen(fileName,"w"); //paths //read and writing
    if(S1==NULL)
    {
        printf("ERROR in opening the file \n");
        exit(1);
    }
    fprintf(S1,"%d,%d,%d,%d,",inGameData.players[0].score,inGameData.players[0].moves,inGameData.players[1].score,inGameData.players[1].moves);
    fprintf(S1,"%d,",inGameData.linesLeft);
    fprintf(S1,"%d,",(int)inGameData.timeElapsed);
    fprintf(S1,"%d,",inGameData.player1turn ? 1:0);
    ///////////////////////////////////////////////*********************
    int i=0;
    for(i=0; i<20; i++)
    {
        fprintf(S1,"%d,",inGameData.vLines[i]);
    }
    for(i=0; i<20; i++)
    {
        fprintf(S1,"%d,",inGameData.hLines[i]);
    }
    ///////////////////////////////////////////////*********************
    //fprintf(S1,"\n");
    int n;
    int m;
    for(n=0; n<5*5; n++)
    {
        for(m=0; m<4; m++)
        {
            fprintf(S1,"%d,",grid[n][m]);
        }
    }
    if(fprintf != 0)
        printf("append successfully !\n");
    else
        printf("error in appending !\n");

    fclose(S1);
}

void loadGame(int number)
{
    char fileName[15]; //should be allocated
    FILE *S1;
    switch(number){
    case 0:
    case 1:
    case 2:
        mode = 3;
        break;
    case 3:
    case 4:
    case 5:
        mode = 5;
        break;
    }
    sprintf(fileName, "%s%s%d%s", ".\\SAVE", mode == 3? "beginner":"expert",(number%3)+1,".txt" );
    S1=fopen(fileName,"r"); //paths //read and writing
    if(S1==NULL)
    {
        printf("ERROR in opening the file \n");
        exit(1);
    }
    char line2[1000];
    int count=0;
    int i=0;
    int n=0;
    int m=0;
    if(S1!=NULL)
    {
        while(!feof(S1))
        {
            char* currentLine = fgets(line2,1000,S1);
            inGameData.players[0].score= atoi(strdup(strtok(line2,",")));
            //printf("%d",players[0].score);
            inGameData.players[0].moves=atoi(strdup (strtok(NULL,",")));
            //printf("%d",players[0].moves);
            inGameData.players[1].score=atoi(strdup(strtok(NULL,",")));
            //printf("%d",players[1].score);
            inGameData.players[1].moves=atoi(strdup(strtok(NULL,",")));
            //printf("%d",players[1].moves);
            //printf("\n");
            inGameData.linesLeft=atoi(strdup(strtok(NULL,",")));
            //printf("%d",inGameData.lines);
            inGameData.timeElapsed=(time_t)atoi(strdup(strtok(NULL,",")));
            //printf("%d",inGameData.timeElapsed);
///////////////////////////////////////////////////////////////
            // printf("\n");
            //if(strcmp("1",strdup(strtok(NULL,",")))==0){inGameData.player1turn=true;}
            //if(strdup(strtok(NULL,","))=="1"){inGameData.player1turn=true;}
            int temp=atoi(strdup(strtok(NULL,",")));
            //  printf("%d",temp);
            if(temp==1)
            {
                inGameData.player1turn=true;
            }
            else
            {
                inGameData.player1turn=false;
            }
            // printf("%s",inGameData.player1turn);
            // printf("\n");
            //   while(inGameData.player1turn){printf("DONE"); break;}
////////////////////////////////////////////************************
            for(i=0; i<20; i++)
            {
                inGameData.vLines[i]=atoi(strdup(strtok(NULL,",")));
            }
            for(i=0; i<20; i++)
            {
                inGameData.hLines[i]=atoi(strdup(strtok(NULL,",")));
            }
///////////////////////////////////////////**************************
            for(n=0; n<5*5; n++)
            {
                for(m=0; m<4; m++)
                {
                    grid[n][m]=atoi(strdup(strtok(NULL,",")));
                }
            }
            /*for(n=0;n<5*5;n++){
                for(m=0;m<4;m++){
                 printf("%d",grid[n][m]);
                }
                }
                //printf("\n");*/
        }
    }

    if(fprintf != 0)
        printf("read successfully !\n");
    else
        printf("error in reading !\n");

    fclose(S1);
}

struct palyer * getTop10(/*args*/)
{
    FILE *F1;
    F1=fopen(".\\Highscores.txt","r"); //paths //read and writing
    if(F1==NULL)
    {
        printf("file not present\n");
        exit(1);
    }
    else
    {
        printf("file opened in read mode\n");
    }
    char line[100];
    char ch;
    int k=0,i=0;
    char *token;
    char *arr[100][2];
    int count=0;

    if(F1!=NULL)
    {
        while(!feof(F1))
        {
            char* currentLine = fgets(line,100,F1);
                arr[i][0] = strdup(strtok(line,","));
                arr[i][1] = strdup(strtok(NULL,","));
                    count+=1;
                    i+=1;
        }
    }
    fclose(F1);
    int a[100];
    for(i=0;i<count;i++){
    a[i]=atoi(arr[i][1]);
    }
    /*
    char b[10];
    for(i=0;i<count;i++){
    strcpy(b[i],arr[i][0]);
    }
    */
    int temp1;
    char temp2[100];

    int j;
    for(i=0;i<count;i++){
        for(j=i+1;j<count;j++){
        if(a[i]<a[j]){
            temp1=a[i];
            a[i]=a[j];
            a[j]=temp1;

            strcpy(temp2,arr[i][0]);
            strcpy(arr[i][0],arr[j][0]);
            strcpy(arr[j][0],temp2);
        }
        }
    }
    for(i=0; i<count; i++)
    {
        displayData(arr[i][0],a[i]);

    }

}



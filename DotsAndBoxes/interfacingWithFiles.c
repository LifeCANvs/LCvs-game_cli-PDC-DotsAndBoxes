#include "globals.h"

int savePlayer(struct player player1)
{

    int testForRank;
    int rank;
    int j;
    int temp1;
    char temp2[100];

    FILE *F1;
    F1=fopen(".\\Highscores.txt","a+"); //paths //read and append
    if(F1==NULL)
    {
        printf("ERROR in opening the file \n");
        exit(1);
    }
    char line[100];
    int k=0,i=0;
    char *arr[100][2];
    int count=0;
    int a[100];
    int test;                     // test =0 if name exists before
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
    for(i=0; i<count; i++)
    {
        a[i]=atoi(arr[i][1]);
    }
    /////////////////////////////////////////////////////////////// read data from fill: done
    for(i=0; i<count; i++)
    {
        test=strcmp(arr[i][0],player1.name);
        if(test==0)
        {
            break;
        }
    }
    /////////////////////////////////////////////////////////////// test if name exists before: done
    if(test==0 && player1.score>a[i])
    {
        //fclose(F1);
        a[i]=player1.score;
        FILE *NewF1;
        NewF1=fopen(".\\temp.txt","a");
        for(k=0; k<count; k++)
        {
            fprintf(NewF1,"%s,%d\n",arr[k][0],a[k]);
        }
        fclose(NewF1);
        for(i=0; i<count; i++)
        {
            for(j=i+1; j<count; j++)
            {
                if(a[i]<a[j])
                {
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
            testForRank=strcmp(arr[i][0],player1.name);
            if(testForRank==0)
            {
                rank=i+1;
                break;
            }
        }
    }
    /////////////////////////////////////////////////////////// case of (test==0 && player1.score>a[i]) : done
    else if(test==0 && player1.score<=a[i])
    {
        for(i=0; i<count; i++)
        {
            for(j=i+1; j<count; j++)
            {
                if(a[i]<a[j])
                {
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
            testForRank=strcmp(arr[i][0],player1.name);
            if(testForRank==0)
            {
                rank=i+1;
                break;
            }
        }
    }
    /////////////////////////////////////////////////////////// case of (test==0 && player1.score<=a[i]) : done
    else if(test!=0)
    {
        fprintf(F1,"%s",player1.name);
        fprintf(F1,",%d",player1.score);
        fprintf(F1,"\n");
        /////////
        count=0;
        i=0;
        F1=fopen(".\\Highscores.txt","a+");
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
        for(i=0; i<count; i++)
        {
            a[i]=atoi(arr[i][1]);
        }
        for(i=0; i<count; i++)
        {
            for(j=i+1; j<count; j++)
            {
                if(a[i]<a[j])
                {
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
            testForRank=strcmp(arr[i][0],player1.name);
            if(testForRank==0)
            {
                rank=i+1;
                break;
            }
        }
    }

    fclose(F1);
    return rank;
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
    fprintf(S1,"%d,",inGameData.computer? 1:0);
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

    fclose(S1);
}

void loadGame(int number)
{
    char fileName[15]; //should be allocated
    FILE *S1;
    switch(number)
    {
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
            temp=atoi(strdup(strtok(NULL,",")));
            //  printf("%d",temp);
            if(temp==1)
            {
                inGameData.computer=true;
            }
            else
            {
                inGameData.computer=false;
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


    fclose(S1);
}

void getTop10()
{
    FILE *F1;
    F1=fopen(".\\Highscores.txt","r"); //paths //read and writing
    if(F1==NULL)
    {
        printf("file not present\n");
        exit(1);
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
    for(i=0; i<count; i++)
    {
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
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(a[i]<a[j])
            {
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



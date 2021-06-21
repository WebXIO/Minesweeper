#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "myconio.h"

COORD coord={0,0}; // this is global variable
//center of axis is set to the top left cornor of the screen
 void gotoxy(int x,int y)
 {
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

 void setColor(int ForgC)
{
     WORD wColor;
                          //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

                           //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                     //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void setColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

void setWindow(int topx, int topy, int bottomx, int bottomy, int forgc, int backc){
    int x,y;
    gotoxy(topx,topy);
    setColorAndBackground(forgc,backc);
    printf("É");
    for(x=topx+1;x<bottomx;x++)
        printf("Í");
    printf("»");
    for(y=topy+1;y<bottomy;y++){
        gotoxy(topx,y);
        printf("º");
        for(x=topx+1;x<bottomx;x++){
            gotoxy(x,y);
            printf(" ");
            //setColor(8);
            //printf("°");
            //setColor(forgc);
        }
        gotoxy(bottomx,y);
        printf("º");
    }
    gotoxy(topx,bottomy);
    printf("È");
    for(x=topx+1;x<bottomx;x++)
        printf("Í");
    printf("¼");
}

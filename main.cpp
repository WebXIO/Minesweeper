#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

#include "Cell.h"
#include "Grid.h"
#include "myconio.h"

using namespace std;

char move(Grid &g){

    char sign;
    sign = getch();

    switch(sign){

    case 'w':
        g.moveCursor(0, -1);
        break;
    case 's':
        g.moveCursor(0, 1);
        break;
    case 'a':
        g.moveCursor(-1, 0);
        break;
    case 'd':
        g.moveCursor(1, 0);
        break;
    case 13:
        g.switchFlag();
        break;
    case 32:
        if(g.checkField()) return 27;
        break;
    }

    return sign;
}
int main() {

    char check;
    Grid g(Beginner);

    while(check != 27 && !g.checkWon()){

        g.render();
        check = move(g);
    }


    system("cls");
    if(g.checkWon())
        g.setLabel("G A M E  O V E R ! W I N");
    else
        g.setLabel("G A M E  O V E R ! L O S E");
    g.render();
    std::cin.get();
}

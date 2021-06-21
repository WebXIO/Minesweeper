#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>

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
    }

    return sign;
}
int main() {
    char check;
    Grid g(Beginner);
    while(check != 27){

        g.render();
        check = move(g);
    }
    g.render();
}

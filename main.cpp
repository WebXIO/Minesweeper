#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "Cell.h"
#include "Grid.h"

using namespace std;

int main()
{

    Cell c(2, false);
    c.setFlag(true);
    std::cout << c.toString();

}

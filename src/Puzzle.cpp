#include "Puzzle.h"

using namespace std;

Puzzle::Puzzle()
{
    x = 0;
    y = 0;
    xPrev = x;
    yPrev = y;
    push = false;
    hasCliff = false;
    isLocked = false;
}

Puzzle::~Puzzle()
{
    free();
}

#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include "LTexture.h"
#include "constant.h"

using namespace std;

class Puzzle: public LTexture
{
public:
    Puzzle();
    ~Puzzle();
    int xPrev, yPrev;

    bool push;
    bool hasCliff;
    bool isLocked;


protected:

private:

};

#endif // PUZZLE_H_INCLUDED

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "LTexture.h"
#include "constant.h"

using namespace std;

class Background: public LTexture
{
public:
    Background();
    ~Background();
    int scrollingOffset;
    void scrollBackground();

protected:

private:

};

#endif // BACKGROUND_H

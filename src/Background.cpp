#include "Background.h"

using namespace std;

Background::Background()
{
    scrollingOffset = 0;
}

Background::~Background()
{
    free();
}

void Background::scrollBackground()
{
    scrollingOffset--;
    if(scrollingOffset < -SCREEN_WIDTH)
    {
        scrollingOffset = 0;
    }
}

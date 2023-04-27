#ifndef NORMAL_H_INCLUDED
#define NORMAL_H_INCLUDED

#include "Level.h"

using namespace std;

class Normal: public Level
{
public:
    Normal();
    ~Normal();

    bool loadMedia(SDL_Renderer *gRenderer);
    void resetNormalMode();
    void setNormalMode(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer);
};

#endif // NORMAL_H_INCLUDED

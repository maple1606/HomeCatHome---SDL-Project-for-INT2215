#ifndef HARD_H_INCLUDED
#define HARD_H_INCLUDED

#include "Level.h"

class Hard: public Level
{
public:
    Hard();
    ~Hard();

    bool loadMedia(SDL_Renderer *gRenderer);
    void resetHardMode();
    void setHardMode(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer);
};

#endif // HARD_H_INCLUDED

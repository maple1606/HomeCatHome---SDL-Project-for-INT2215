#ifndef EASY_H_INCLUDED
#define EASY_H_INCLUDED

#include "Level.h"

using namespace std;

class Easy: public Level
{
public:
    Easy();
    ~Easy();

    bool loadMedia(SDL_Renderer *gRenderer);
    void resetEasyMode();
    void setEasyMode(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer);
};


#endif // LEVEL1_H_INCLUDED

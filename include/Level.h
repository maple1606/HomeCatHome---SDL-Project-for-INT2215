#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <vector>
#include "constant.h"
#include "Character.h"
#include "Puzzle.h"
#include "Item.h"
#include "Button.h"
#include "Background.h"
#include "NotiBoard.h"

class Level
{
public:
    Level();
    ~Level();

    void setup(const int itemNum, const int initMode);
    void handleEvent(const int itemNum, SDL_Event e);
    void render(int &mode, const int itemNum, SDL_Renderer *gRenderer);

protected:
    vector <Puzzle*> puzzle;
    vector <Item*> item;
    Background *background;
    Character *character;
    NotiBoard *board;
    LTexture *lock;
    bool swapOn;
    bool replay;
    int initMode;
};

#endif // LEVEL_H_INCLUDED

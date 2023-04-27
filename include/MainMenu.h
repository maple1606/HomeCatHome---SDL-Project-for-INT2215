#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Background.h"
#include "Button.h"
#include "Character.h"
#include "NotiBoard.h"
#include "Instruction.h"
#include "constant.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    void resetMenu();
    void setMenu(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer);
    bool loadMedia(SDL_Renderer *gRenderer);
    void render(SDL_Renderer *gRenderer);

protected:
    NotiBoard *board;
    Instruction *instruction;
    vector <Button*> button;
    vector <LTexture*> textButton;
    Background *background;
    Character *character;
};

#endif // MAINMENU_H_INCLUDED

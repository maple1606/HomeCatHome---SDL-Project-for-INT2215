#ifndef MAINCONTROL_H_INCLUDED
#define MAINCONTROL_H_INCLUDED

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include "Audio.h"
#include "Easy.h"
#include "Normal.h"
#include "Hard.h"
#include "MainMenu.h"
#include "constant.h"

class MainControl
{
public:
    MainControl();
    ~MainControl();
    bool init();
    void setMode();
    void close();

    bool isQuit() const;

    void reset();

    SDL_Window *getWindow() const;
    SDL_Renderer *getRenderer() const;

private:
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;

    SDL_Event e;
    bool quit;
    int mode;

    Audio *audio;
    MainMenu *menu;
    Easy *easy;
    Normal *normal;
    Hard *hard;
};

#endif // MAINCONTROL_H_INCLUDED

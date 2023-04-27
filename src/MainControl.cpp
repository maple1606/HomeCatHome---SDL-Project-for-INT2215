#include "MainControl.h"

MainControl::MainControl()
{
    gWindow = NULL;
    gRenderer = NULL;
    quit = false;
    mode = MENU;
}

MainControl::~MainControl()
{
    delete menu;
    menu = NULL;
    delete easy;
    easy = NULL;
    delete normal;
    normal= NULL;
    delete hard;
    hard = NULL;
    delete audio;
    audio = NULL;
}

bool MainControl::init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
    {
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if( gRenderer == NULL )
            {
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if(!( IMG_Init(imgFlags) & imgFlags))
                {
                    success = false;
                }
                if( TTF_Init() == -1 )
                {
                    success = false;
                }
                if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
                {
                    success = false;
                }
            }
        }
    }

    menu = new MainMenu();
    easy = new Easy();
    normal = new Normal();
    hard = new Hard();
    audio = new Audio();

    return success;
}

void MainControl::setMode()
{
    audio->playBGM(mode);
    switch (mode)
    {
    case MENU:
    {
        menu->resetMenu();
        menu->setMenu(mode, e, quit, gRenderer);
        break;
    }
    case EASY:
    {
        easy->resetEasyMode();
        easy->setEasyMode(mode, e, quit, gRenderer);
        break;
    }
    case NORMAL:
    {
        normal->resetNormalMode();
        normal->setNormalMode(mode, e, quit, gRenderer);
        break;
    }
    case HARD:
    {
        hard->resetHardMode();
        hard->setHardMode(mode, e, quit, gRenderer);
        break;
    }
    }
}

void MainControl::reset()
{
    mode = MENU;
}

void MainControl::close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

SDL_Window* MainControl::getWindow() const
{
    return gWindow;
}

SDL_Renderer* MainControl::getRenderer() const
{
    return gRenderer;
}

bool MainControl::isQuit() const
{
    return quit;
}

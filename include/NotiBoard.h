#ifndef NOTIBOARD_H_INCLUDED
#define NOTIBOARD_H_INCLUDED

#include <vector>
#include "LTexture.h"
#include "constant.h"

class NotiBoard
{
public:
    NotiBoard();
    ~NotiBoard();

    void setNotiBoard();
    bool loadMedia(SDL_Renderer *gRenderer);
    void popUp(int &mode, SDL_Event e, SDL_Renderer *gRenderer, bool &replay);
    void renderBoard(int &status, SDL_Renderer *gRenderer);
    void renderStatus(int &mode, int &status, SDL_Renderer *gRenderer);

private:
    LTexture *cover;
    LTexture *board;
    LTexture *statusBar;
    vector <LTexture*> statusTxt;
    Uint8 a;
    bool fade;
};

#endif // NOTIBOARD_H_INCLUDED

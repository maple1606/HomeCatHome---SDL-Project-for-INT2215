#include "NotiBoard.h"
#include <fstream>
#include <iostream>

NotiBoard::NotiBoard()
{
    cover = new LTexture();
    board = new LTexture();
    statusBar = new LTexture();
    statusTxt.clear();
    for (int i=WIN; i<=keyPress; i++)
    {
        LTexture *txt = new LTexture();
        statusTxt.push_back(txt);
    }
}

NotiBoard::~NotiBoard()
{
    delete cover;
    cover = NULL;
    delete board;
    board = NULL;
    delete statusBar;
    statusBar = NULL;

    for (LTexture *&txt : statusTxt)
        delete txt;
}

void NotiBoard::setNotiBoard()
{
    a = 255;
    fade = false;
}

bool NotiBoard::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    if (!cover->loadFromFile("asset/image/cover.png", gRenderer))
    {
        success = false;
    }

    if (!board->loadFromFile("asset/image/board.png", gRenderer))
    {
        success = false;
    }

    if (!statusBar->loadFromFile("asset/image/statusBar.png", gRenderer))
    {
        success = false;
    }

    ifstream file("asset/font/statusText.txt");

    for (int i=WIN; i<=keyPress; i++)
    {
        string line;
        getline(file, line);

        int fontSize = 36;
        if (i >= REPLAY)
        {
            fontSize = 24;
        }

        if (i == keyPress)
        {
            if (!statusTxt[i]->loadFromRenderedText(line, gRenderer, 19, "asset/font/Asap.ttf"))
            {
                success = false;

            }
        }

        else if (!statusTxt[i]->loadFromRenderedText(line, gRenderer, fontSize))
        {
            success = false;
        }
    }

    file.close();

    return success;
}

void NotiBoard::popUp(int &mode, SDL_Event e, SDL_Renderer *gRenderer, bool &replay)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        for (int i=REPLAY; i<=BACK; i++)
        {
            if (isInBound(e.button.x, e.button.y, statusTxt.at(i)->x, statusTxt.at(i)->y, statusTxt.at(i)))
            {
                if (i == NEXT_LEVEL)
                {
                    if (mode != HARD)
                        mode++;
                }
                else if (i == BACK)
                {
                    mode = MENU;
                }
                else if (i == REPLAY)
                {
                    replay = true;
                }
            }
        }
    }
}

void NotiBoard::renderBoard(int &status, SDL_Renderer *gRenderer)
{
    cover->setAlpha(150);
    cover->render(0, 0, gRenderer);
    board->render(0, 0, gRenderer);

    int coorX = SCREEN_WIDTH/2 - statusTxt.at(keyPress)->getWidth()/2;
    int coorY = SCREEN_HEIGHT - statusTxt.at(keyPress)->getHeight() - 10;

    if (status != WIN and status != LOSE)
    {
        statusTxt[keyPress]->blink_blink(a, fade);

        statusTxt[keyPress]->setAlpha(a);
        statusTxt[keyPress]->render(coorX, coorY, gRenderer);
    }
}

void NotiBoard::renderStatus(int &mode, int &status, SDL_Renderer *gRenderer)
{
    statusBar->render(0, 0, gRenderer);
    int coorX = SCREEN_WIDTH/2 - statusTxt.at(status)->getWidth()/2;
    int coorY = 95;
    statusTxt.at(status)->render(coorX, coorY, gRenderer);

    if ((mode == EASY or mode == NORMAL) and status == WIN)
    {
        for (int i=REPLAY; i<=BACK; i++)
        {
            coorX = SCREEN_WIDTH/2 - statusTxt.at(i)->getWidth()/2;
            coorY = 175 + 55*(i-3);

            statusTxt.at(i)->x = coorX;
            statusTxt.at(i)->y = coorY;

            int _x, _y;
            SDL_GetMouseState(&_x, &_y);
            Uint8 u = ((isInBound(_x, _y, coorX, coorY, statusTxt.at(i))) ? 0 : 255);
            statusTxt.at(i)->setColor(u, u, u);
            statusTxt.at(i)->render(coorX, coorY, gRenderer);
        }
    }
    else if (mode == HARD or status == LOSE or status == PAUSE)
    {
        for (int i=REPLAY; i<=BACK; i++)
        {
            if (i == NEXT_LEVEL)
                continue;
            coorX = SCREEN_WIDTH/2 - statusTxt.at(i)->getWidth()/2;
            if (i == REPLAY)
                coorY = 190 + 60*(i-3);
            else if (i == BACK)
                coorY = 190 + 60*(i-4);

            statusTxt.at(i)->x = coorX;
            statusTxt.at(i)->y = coorY;

            int _x, _y;
            SDL_GetMouseState(&_x, &_y);
            Uint8 u = ((isInBound(_x, _y, coorX, coorY, statusTxt.at(i))) ? 0 : 255);
            statusTxt.at(i)->setColor(u, u, u);
            statusTxt.at(i)->render(coorX, coorY, gRenderer);
        }
    }
}

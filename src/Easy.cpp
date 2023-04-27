#include "Easy.h"

using namespace std;

Easy::Easy()
{
    setup(EasyItemNum, EASY);
}

Easy::~Easy()
{

}

bool Easy::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<column; j++)
        {
            puzzle[i*column+j]->x = j * frameLength;
            puzzle[i*column+j]->y = i * frameLength;
            string path = "asset/image/grass.png";
            if (!puzzle[i*column+j]->loadFromFile(path, gRenderer))
                success = false;
        }
    }

    if (!character->loadFromFile("asset/image/character.png", gRenderer))
        success = false;

    if (!background->loadFromFile("asset/image/EasyBackground.png", gRenderer))
        success = false;

    if (!puzzle[6]->loadFromFile("asset/image/selectedFrame.png", gRenderer))
        success = false;

    if (!item[EASY_GATE]->loadFromFile("asset/image/gate.png", gRenderer))
        success = false;

    if (!item[EASY_STONE_FI]->loadFromFile("asset/image/stone.png", gRenderer))
        success = false;

    if (!item[EASY_STONE_SE]->loadFromFile("asset/image/stone.png", gRenderer))
        success = false;

    if (!board->loadMedia(gRenderer))
        success = false;

    return success;
}

void Easy::resetEasyMode()
{
    for (int i=0; i<frameNum-1; i++)
    {
        puzzle[i]->x = (i % 3) * frameLength;
        if (i < 3)
            puzzle[i]->y = 0;
        else
            puzzle[i]->y = frameLength;
    }

    character->x = 50;
    character->y = 100;
    character->status = IN_GAME;
    character->freeze = false;
    character->flipType = SDL_FLIP_NONE;

    item[EASY_GATE]->x = 595;
    item[EASY_GATE]->y = 80;
    item[EASY_GATE]->isDestination = true;

    item[EASY_STONE_FI]->x = 165;
    item[EASY_STONE_FI]->y = 100;
    item[EASY_STONE_FI]->isBarrier = true;

    item[EASY_STONE_SE]->x = 330;
    item[EASY_STONE_SE]->y = 350;
    item[EASY_STONE_SE]->isBarrier = true;

    swapOn = false;
    replay = false;
}

void Easy::setEasyMode(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer)
{
    if (loadMedia(gRenderer))
    {
        while(mode == EASY and !quit)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        if (character->status == IN_GAME)
                        {
                            character->freeze = true;
                            character->status = PAUSE;
                        }
                        else if (character->status == PAUSE)
                        {
                            character->freeze = false;
                            character->status = IN_GAME;
                        }
                    }
                }
                else if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                handleEvent(EasyItemNum, e);

                if (character->status != IN_GAME)
                {
                    board->popUp(mode, e, gRenderer, replay);
                }
            }

            for (int i=0; i<EasyItemNum; i++)
            {
                if (character->checkCollision(item[i]))
                {
                    character->handleCollision(item[i]);
                }
            }

            for (int i=0; i<frameNum-1; i++)
            {
                if (((isInBound(character->x+character->getWidth()/4, character->y, puzzle[i]->x, puzzle[i]->y, puzzle[i]) and character->flipType == SDL_FLIP_NONE)
                        or (isInBound(character->x, character->y, puzzle[i]->x, puzzle[i]->y, puzzle[i]) and character->flipType == SDL_FLIP_HORIZONTAL)) and !character->charMove)
                {
                    character->handleMovement(mode, puzzle[i]);
                }
            }

            render(mode, EasyItemNum, gRenderer);

            if (replay) resetEasyMode();
        }
    }
}

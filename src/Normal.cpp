#include "Normal.h"

using namespace std;

Normal::Normal()
{
    setup(NormalItemNum, NORMAL);
}

Normal::~Normal()
{

}

bool Normal::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<column; j++)
        {
            puzzle[i*column+j]->x = j * frameLength;
            puzzle[i*column+j]->y = i * frameLength;
            string path;
            if (i*column+j == 0)
            {
                path = "asset/image/cliff.png";
                puzzle[i*column+j]->hasCliff = true;
            }
            else
                path = "asset/image/grass.png";
            if (!puzzle[i*column+j]->loadFromFile(path, gRenderer))
                success = false;
        }
    }

    if (!character->loadFromFile("asset/image/character.png", gRenderer))
        success = false;

    if (!background->loadFromFile("asset/image/NormalBackground.png", gRenderer))
        success = false;

    if (!puzzle[6]->loadFromFile("asset/image/selectedFrame.png", gRenderer))
        success = false;

    if (!item[NORMAL_GATE]->loadFromFile("asset/image/gate.png", gRenderer))
        success = false;

    if (!item[NORMAL_STONE_FI]->loadFromFile("asset/image/stone.png", gRenderer))
        success = false;

    if (!item[NORMAL_STONE_SE]->loadFromFile("asset/image/stone.png", gRenderer))
        success = false;

    if (!item[NORMAL_CACTUS_FI]->loadFromFile("asset/image/cactus.png", gRenderer))
        success = false;

    if (!item[NORMAL_CACTUS_SE]->loadFromFile("asset/image/cactus.png", gRenderer))
        success = false;

    if (!item[NORMAL_CACTUS_TH]->loadFromFile("asset/image/cactusMini.png", gRenderer))
        success = false;

    if (!board->loadMedia(gRenderer))
        success = false;

    if (!lock->loadFromFile("asset/image/lock.png", gRenderer))
        success = false;


    return success;
}


void Normal::resetNormalMode()
{
    for (int i=0; i<frameNum-1; i++)
    {
        puzzle[i]->x = (i % 3) * frameLength;
        if (i < 3)
            puzzle[i]->y = 0;
        else
            puzzle[i]->y = frameLength;
    }

    puzzle[1]->isLocked = true;
    puzzle[5]->isLocked = true;

    character->x = 50;
    character->y = 350;
    character->freeze = false;
    character->flipType = SDL_FLIP_NONE;
    character->fall = frameLength;
    character->status = IN_GAME;

    item[NORMAL_GATE]->x = 650;
    item[NORMAL_GATE]->y = 330;
    item[NORMAL_GATE]->isDestination = true;

    item[NORMAL_STONE_FI]->x = 168;
    item[NORMAL_STONE_FI]->y = 350;
    item[NORMAL_STONE_FI]->isBarrier = true;

    item[NORMAL_STONE_SE]->x = 320;
    item[NORMAL_STONE_SE]->y = 350;
    item[NORMAL_STONE_SE]->isBarrier = true;

    item[NORMAL_CACTUS_FI]->x = 420;
    item[NORMAL_CACTUS_FI]->y = 345;
    item[NORMAL_CACTUS_FI]->isDangerous = true;

    item[NORMAL_CACTUS_SE]->x = 545;
    item[NORMAL_CACTUS_SE]->y = 95;
    item[NORMAL_CACTUS_SE]->isDangerous = true;

    item[NORMAL_CACTUS_TH]->x = 1;
    item[NORMAL_CACTUS_TH]->y = 95;
    item[NORMAL_CACTUS_TH]->isDangerous = true;

    swapOn = false;
    replay = false;

}

void Normal::setNormalMode(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer)
{
    if (loadMedia(gRenderer))
    {
        while(mode == NORMAL and !quit)
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

                handleEvent(NormalItemNum, e);

                if (character->status != IN_GAME)
                {
                    board->popUp(mode, e, gRenderer, replay);
                }
            }

            render(mode, NormalItemNum, gRenderer);

            for (int i=0; i<NormalItemNum; i++)
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

            if (replay)
                resetNormalMode();
        }
    }
}

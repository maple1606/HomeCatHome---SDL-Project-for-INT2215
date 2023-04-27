//this wasn't a part of my original plan, the code would be somewhat a mess

#include "Hard.h"

using namespace std;

Hard::Hard()
{
    setup(HardItemNum, HARD);
}

Hard::~Hard()
{

}

bool Hard::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<column; j++)
        {
            puzzle[i*column+j]->x = j * frameLength;
            puzzle[i*column+j]->y = i * frameLength;
            string path;
            if (i*column+j == 0 || i*column+j == 1){
                path = "asset/image/cliffAtNight.png";
                puzzle[1]->hasCliff = true;
            }
            else
                path = "asset/image/grassAtNight.png";
            if (!puzzle[i*column+j]->loadFromFile(path, gRenderer))
                success = false;
        }
    }

    if (!character->loadFromFile("asset/image/character.png", gRenderer))
        success = false;

    if (!background->loadFromFile("asset/image/HardBackground.png", gRenderer))
        success = false;

    if (!puzzle[6]->loadFromFile("asset/image/selectedFrame.png", gRenderer))
        success = false;

    if (!item[HARD_TREASURE]->loadFromFile("asset/image/treasure.png", gRenderer))
        success = false;

    if (!item[HARD_STONE]->loadFromFile("asset/image/stone.png", gRenderer))
        success = false;

    if (!item[HIDDEN_PUZZLE]->loadFromFile("asset/image/grassHidden.png", gRenderer))
        success = false;

    if (!item[HARD_KEY]->loadFromFile("asset/image/key.png", gRenderer))
        success = false;

    if (!item[HARD_MAGIC]->loadFromFile("asset/image/magic.png", gRenderer))
        success = false;

    if (!item[HARD_CACTUS_FI]->loadFromFile("asset/image/cactusMini.png", gRenderer))
        success = false;

    if (!item[HARD_CACTUS_TH]->loadFromFile("asset/image/cactusMini.png", gRenderer))
        success = false;

    for (int i=HARD_CACTUS_SE; i<=HARD_CACTUS_FO; i+=2)
        if (!item[i]->loadFromFile("asset/image/cactus.png", gRenderer))
            success = false;

    if (!board->loadMedia(gRenderer))
        success = false;

    if (!lock->loadFromFile("asset/image/lock.png", gRenderer))
        success = false;

    return success;
}


void Hard::resetHardMode()
{
    puzzle[0]->hasCliff = false;
    for (int i=0; i<frameNum-1; i++)
    {
        puzzle[i]->x = (i % 3) * frameLength;
        if (i < 3)
            puzzle[i]->y = 0;
        else
            puzzle[i]->y = frameLength;
    }

    puzzle[1]->isLocked = true;
    puzzle[2]->isLocked = true;

    character->x = 255;
    character->y = 350;
    character->freeze = false;
    character->flipType = SDL_FLIP_NONE;
    character->fall = frameLength;
    character->status = IN_GAME;

    item[HIDDEN_PUZZLE]->x = 62;
    item[HIDDEN_PUZZLE]->y = 170;
    item[HIDDEN_PUZZLE]->fade = false;
    item[HIDDEN_PUZZLE]->a = 255;
    item[HIDDEN_PUZZLE]->setAlpha(255);

    item[HARD_KEY]->x = 550;
    item[HARD_KEY]->y = 270;
    item[HARD_KEY]->isKey = true;
    item[HARD_KEY]->isHidden = false;

    item[HARD_MAGIC]->x = 160;
    item[HARD_MAGIC]->y = 340;
    item[HARD_MAGIC]->isMagic = true;

    item[HARD_TREASURE]->x = 630;
    item[HARD_TREASURE]->y = 55;
    item[HARD_TREASURE]->isDestination = true;

    item[HARD_STONE]->x = 580;
    item[HARD_STONE]->y = 350;
    item[HARD_STONE]->isBarrier = true;

    item[HARD_CACTUS_FI]->x = 1;
    item[HARD_CACTUS_FI]->y = 345;
    item[HARD_CACTUS_FI]->isDangerous = true;

    item[HARD_CACTUS_SE]->x = 415;
    item[HARD_CACTUS_SE]->y = 95;
    item[HARD_CACTUS_SE]->isDangerous = true;

    item[HARD_CACTUS_TH]->x = 1;
    item[HARD_CACTUS_TH]->y = 95;
    item[HARD_CACTUS_TH]->isDangerous = true;

    item[HARD_CACTUS_FO]->x = 670;
    item[HARD_CACTUS_FO]->y = 345;
    item[HARD_CACTUS_FO]->isDangerous = true;

    swapOn = false;
    replay = false;

}

void Hard::setHardMode(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer)
{
    if (loadMedia(gRenderer))
    {
        while(mode == HARD and !quit)
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

                handleEvent(HardItemNum, e);

                if (character->status != IN_GAME)
                {
                    board->popUp(mode, e, gRenderer, replay);
                }
            }

            render(mode, HardItemNum, gRenderer);

            for (int i=0; i<HardItemNum; i++)
            {
                if (character->checkCollision(item[i]))
                {
                    character->handleCollision(item[i]);
                    if (item[i]->isMagic)
                    {
                        item[HIDDEN_PUZZLE]->fading(item[HIDDEN_PUZZLE]->a, item[HIDDEN_PUZZLE]->fade);
                        item[HIDDEN_PUZZLE]->setAlpha(item[HIDDEN_PUZZLE]->a);
                        if (character->flipType == SDL_FLIP_HORIZONTAL and character->x == item[i]->x + item[i]->getWidth())
                        {
                            item[HIDDEN_PUZZLE]->fade = 1-item[HIDDEN_PUZZLE]->fade;
                            puzzle[0]->hasCliff = 1-puzzle[0]->hasCliff;
                        }
                        else if (character->flipType == SDL_FLIP_NONE and character->x + character->getWidth()/4 == item[i]->x)
                        {
                            item[HIDDEN_PUZZLE]->fade = 1-item[HIDDEN_PUZZLE]->fade;
                            puzzle[0]->hasCliff = 1-puzzle[0]->hasCliff;
                        }
                    }
                    else if (item[i]->isKey)
                    {
                        puzzle[1]->isLocked = false;
                        item[i]->isHidden = true;
                    }
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
                resetHardMode();
        }
    }
}

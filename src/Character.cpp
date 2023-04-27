#include "Character.h"

using namespace std;

Character::Character()
{
    SpriteClips[0].x = 0;
    SpriteClips[0].y = 0;
    SpriteClips[0].w = 64;
    SpriteClips[0].h = 91;

    SpriteClips[1].x = 64;
    SpriteClips[1].y = 0;
    SpriteClips[1].w = 64;
    SpriteClips[1].h = 91;

    SpriteClips[2].x = 128;
    SpriteClips[2].y = 0;
    SpriteClips[2].w = 64;
    SpriteClips[2].h = 91;

    SpriteClips[3].x = 192;
    SpriteClips[3].y = 0;
    SpriteClips[3].w = 64;
    SpriteClips[3].h = 91;

    xPrev = x;
    yPrev = y;

    charMove = false;
    fall = frameLength;
    frame = 0;
    velocity = 20;
    audio = new Audio();
}

Character::~Character()
{
    delete audio;
    audio = NULL;
    free();
}

void Character::handleAudio()
{
    switch (status)
    {
    case WIN:
    {
        audio->playLevelUp();
        break;
    }
    case LOSE:
    {
        audio->playOops();
        break;
    }
    }
    if (frame&1 and !velocity)
        audio->playCharAction();
}

void Character::handleAnimation()
{
    if (velocity == 0)
    {
        frame++;
        frame = (frame + animationFrame) % animationFrame;
        velocity = 20;
    }
    else
    {
        velocity--;
    }

    currentClip = &SpriteClips[frame];
}


void Character::handleFall()
{
    if (fall < frameLength)
    {
        fall++;
        y++;
    }
    else
    {
        fall = 0;
    }

    if (y > SCREEN_HEIGHT)
    {
        freeze = true;
        status = LOSE;
        SDL_Delay(700);
    }
    handleAudio();
}

void Character::handleMovement(int &mode, Puzzle *puzzle)
{
    if (fall < frameLength and !freeze)
        handleFall();

    else if (!freeze)
    {
        if (!puzzle->hasCliff)
        {
            if (x < SCREEN_WIDTH-getWidth()/4 and flipType == SDL_FLIP_NONE)
            {
                x++;
            }

            if (x == SCREEN_WIDTH-getWidth()/4 and flipType == SDL_FLIP_NONE)
            {
                flipType = SDL_FLIP_HORIZONTAL;
            }

            if (flipType == SDL_FLIP_HORIZONTAL)
            {
                x--;
            }

            if (x == 0 and flipType == SDL_FLIP_HORIZONTAL)
            {
                flipType = SDL_FLIP_NONE;
            }

            handleAnimation();
        }
        else
        {
            if (mode == HARD)
            {
                if (x < puzzle->x + frameLength/4 and flipType == SDL_FLIP_NONE)
                {
                    x++;
                }
                else if (x + getWidth()/4 > puzzle->x + frameLength/2 and flipType == SDL_FLIP_HORIZONTAL)
                {
                    x--;
                }
                else
                {
                    fall = 0;
                }
            }

            else if (mode == NORMAL)
            {
                if (x < puzzle->x + 3*frameLength/4 and flipType == SDL_FLIP_NONE)
                {
                    x++;
                }
                else if (x + getWidth()/4 > puzzle->x + frameLength/2 and flipType == SDL_FLIP_HORIZONTAL)
                {
                    x--;
                }
                else
                {
                    fall = 0;
                }
            }
            handleAnimation();
        }
        handleAudio();
    }
}

bool Character::checkCollision(Item *item)
{
    bool isCollided = false;
    if (!freeze)
    {
        if (flipType == SDL_FLIP_NONE)
        {
            if (isInBound(x + getWidth()/4, y, item->x, item->y, item))
            {
                isCollided = true;
            }
        }
        else if (flipType == SDL_FLIP_HORIZONTAL)
        {
            if (isInBound(x, y, item->x, item->y, item))
            {
                isCollided = true;
            }
        }
        if (item->isBarrier)
        {
            if (y+getHeight() == item->y+50)
            {
                if (isInBound(x + getWidth()/4, y+getHeight(), item->x, item->y, item))
                    isCollided = true;
                if (isInBound(x, y+getHeight(), item->x, item->y, item))
                    isCollided = true;
            }
        }
        if (item->isKey)
        {
            if (y == item->y)
            {
                if (isInBound(x + getWidth()/4, y+getHeight(), item->x, item->y, item))
                    isCollided = true;
                if (isInBound(x, y+getHeight(), item->x, item->y, item))
                    isCollided = true;
            }
        }
    }

    return isCollided;
}

void Character::handleCollision(Item *item)
{
    if (item->isBarrier)
    {
        if (x == item->x-getWidth()/4 and flipType == SDL_FLIP_NONE)
            flipType = SDL_FLIP_HORIZONTAL;

        if (x == item->x+item->getWidth() and flipType == SDL_FLIP_HORIZONTAL)
            flipType = SDL_FLIP_NONE;

        if (y+getHeight() == item->y+50)
        {
            if (flipType == SDL_FLIP_NONE)
                x = item->x+item->getWidth();
            else if (flipType == SDL_FLIP_HORIZONTAL)
                x = item->x-getWidth()/4;
        }
    }
    if (item->isDestination)
    {
        freeze = true;
        status = WIN;
        SDL_Delay(700);
        handleAudio();
    }
    if (item->isDangerous)
    {
        freeze = true;
        status = LOSE;
        SDL_Delay(700);
        handleAudio();
    }
    if (item->isMagic or item->isKey)
    {
        bool playSFX = false;
        if (x+getWidth()/4 == item->x and flipType == SDL_FLIP_NONE)
            playSFX = true;

        else if (x == item->x+item->getWidth() and flipType == SDL_FLIP_HORIZONTAL)
            playSFX = true;

        else if (y == item->y)
            playSFX = true;

        if (playSFX) audio->playGetItem();
    }
}


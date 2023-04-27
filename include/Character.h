#ifndef CHARACTER_H
#define CHARACTER_H

#include "LTexture.h"
#include "Puzzle.h"
#include "Item.h"
#include "Audio.h"
#include "constant.h"

using namespace std;

class Character: public LTexture
{
public:
    Character();
    ~Character();
    int xPrev, yPrev;
    bool freeze, charMove;
    int fall, frame, status;
    SDL_RendererFlip flipType;
    SDL_Rect SpriteClips[animationFrame];
    SDL_Rect* currentClip;

    void handleMovement(int &mode, Puzzle *puzzle);
    void handleAnimation();
    void handleAudio();
    bool checkCollision(Item *item);
    void handleCollision(Item *item);
    void handleFall();

private:
    int velocity;
    Audio *audio;
};

#endif // CHARACTER_H

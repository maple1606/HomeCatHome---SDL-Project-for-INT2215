#include "Audio.h"
#include "constant.h"

Audio::Audio()
{
    menuBGM = Mix_LoadMUS("asset/audio/menu_bgm.wav");
    easyBGM = Mix_LoadMUS("asset/audio/easy_bgm.wav");
    normalBGM = Mix_LoadMUS("asset/audio/normal_bgm.wav");
    hardBGM = Mix_LoadMUS("asset/audio/hard_bgm.wav");

    charAction = Mix_LoadWAV("asset/audio/walk.wav");
    levelUp = Mix_LoadWAV("asset/audio/clear.wav");
    oops = Mix_LoadWAV("asset/audio/oops.wav");
    getItem = Mix_LoadWAV("asset/audio/get.wav");
}

Audio::~Audio()
{
    Mix_FreeChunk(charAction);
    Mix_FreeChunk(levelUp);
    Mix_FreeChunk(oops);
    Mix_FreeChunk(getItem);

    Mix_FreeMusic(menuBGM);
    Mix_FreeMusic(easyBGM);
    Mix_FreeMusic(normalBGM);
    Mix_FreeMusic(hardBGM);
}

void Audio::playLevelUp()
{
    Mix_PlayChannel(-1, levelUp, 0);
}

void Audio::playOops()
{
    Mix_PlayChannel(-1, oops, 0);
}

void Audio::playCharAction()
{
    Mix_PlayChannel(-1, charAction, 0);
}

void Audio::playGetItem()
{
    Mix_PlayChannel(-1, getItem, 0);
}

void Audio::playBGM(int &mode)
{
    switch (mode)
    {
        case MENU:
        {
            Mix_HaltMusic();
            Mix_PlayMusic(menuBGM, -1);
            break;
        }
        case EASY:
        {
            Mix_HaltMusic();
            Mix_PlayMusic(easyBGM, -1);
            break;
        }
        case NORMAL:
        {
            Mix_HaltMusic();
            Mix_PlayMusic(normalBGM, -1);
            break;
        }
        case HARD:
        {
            Mix_HaltMusic();
            Mix_PlayMusic(hardBGM, -1);
            break;
        }
    }
}

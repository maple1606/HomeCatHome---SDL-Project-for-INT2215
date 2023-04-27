#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <SDL_mixer.h>

class Audio
{
public:
    Audio();
    ~Audio();
    void playBGM(int &mode);
    void playCharAction();
    void playLevelUp();
    void playOops();
    void playGetItem();

private:
    Mix_Music *menuBGM = NULL;
    Mix_Music *easyBGM = NULL;
    Mix_Music *normalBGM = NULL;
    Mix_Music *hardBGM = NULL;

    Mix_Chunk *charAction = NULL;
    Mix_Chunk *levelUp = NULL;
    Mix_Chunk *oops = NULL;
    Mix_Chunk *getItem = NULL;
};

#endif // AUDIO_H_INCLUDED

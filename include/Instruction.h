#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include "LTexture.h"
#include <vector>

class Instruction: public LTexture
{
public:
    Instruction();
    ~Instruction();

    bool loadMedia(SDL_Renderer *gRenderer);
    void reset();
    void render(SDL_Renderer *gRenderer);
    void popUp(SDL_Event e, SDL_Renderer *gRenderer);

private:
    LTexture *board;
    vector <LTexture*> txt;
    bool fade;
    Uint8 a;
};

#endif // INSTRUCTION_H_INCLUDED

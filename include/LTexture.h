#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include "constant.h"

using namespace std;

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(string path, SDL_Renderer* renderer);
    bool loadFromRenderedText(string textureText, SDL_Renderer *gRenderer, int fontSize = 32, string fontType = defaultFont);

    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setAlpha(Uint8 alpha);
    void _resize(SDL_Rect &rct, double porpotion);
    void render(int x, int y,  SDL_Renderer* renderer, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, double porpotion = 1);
    void blink_blink(Uint8 &a, bool &fade);
    void fading(Uint8 &a, bool &fade);

    int getWidth();
    int getHeight();
    int x, y;

protected:
    SDL_Texture* mTexture;
    TTF_Font* font = NULL;

    int mWidth;
    int mHeight;
private:
};

bool isInBound(int x, int y, int ObjectX, int ObjectY, LTexture *LObject);

#endif // LTEXTURE_H_INCLUDED

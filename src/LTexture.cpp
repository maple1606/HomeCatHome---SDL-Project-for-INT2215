#include "LTexture.h"

using namespace std;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(string path, SDL_Renderer* renderer)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface != NULL)
    {
        SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (newTexture != NULL)
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(string textureText, SDL_Renderer *gRenderer, int fontSize, string fontType)
{
    free();
    font = TTF_OpenFont( fontType.c_str(), fontSize );
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if(textSurface != NULL)
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if(mTexture != NULL)
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

    if (font != NULL)
    {
        TTF_CloseFont( font );
        font = NULL;
    }
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::_resize(SDL_Rect &rct, double porpotion)
{
    rct.w *= porpotion;
    rct.h *= porpotion;
}

void LTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, SDL_RendererFlip flip, double porpotion)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h ;

        _resize(renderQuad, porpotion);
    }

    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, 0, NULL, flip);
    //SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::blink_blink(Uint8 &a, bool &fade)
{
    if (a == 255 and !fade)
        fade = true;
    if (a > 135 and fade)
        a -= 2;
    if (a == 135 and fade)
        fade = false;
    if (a < 255 and !fade)
        a += 2;
    a %= 256;
}

void LTexture::fading(Uint8 &a, bool &fade){
    if (fade and a)
        a -= 5;
    else if (!fade and a<255)
        a += 5;

    a %= 256;
}

bool isInBound(int x, int y, int ObjectX, int ObjectY, LTexture *LObject)
{
    bool inside = true;

    if (x < ObjectX)
        inside = false;

    if (x > ObjectX + LObject->getWidth())
        inside = false;

    if (y < ObjectY)
        inside = false;

    if (y > ObjectY + LObject->getHeight())
        inside = false;

    return inside;
}

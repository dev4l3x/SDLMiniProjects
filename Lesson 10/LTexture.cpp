#include "LTexture.h"
#include <SDL_image.h>
#include <stdio.h>

LTexture::LTexture()
{
    texture = nullptr;
    width = 0;
    height = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    free();
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else{
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    texture = newTexture;
    return texture != nullptr;
}

void LTexture::free()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void LTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, width, height};
    if(clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int LTexture::getHeight()
{
    return height;
}

int LTexture::getWidth()
{
    return width;
}
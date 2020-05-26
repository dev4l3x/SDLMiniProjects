
#pragma once 
#ifndef LTexture_H_INCLUDED
#define LTexture_H_INCLUDED

#include <string>
#include <SDL.h>

class LTexture
{
    public:

        LTexture();
        ~LTexture();

        bool loadFromFile(std::string path, SDL_Renderer* renderer);

        void free();

        void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* texture;

        int width;
        int height;
};

#endif
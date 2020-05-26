#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Iniciamos SDL
bool init();

//Cargamos imagen 
bool loadMedia();

//Liberamos todos los recursos
void close();

SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Surface* screenSurface = nullptr;

//Superficie actual cargada
SDL_Surface* currentSurface = nullptr;

SDL_Rect spriteClips[4];
LTexture spriteSheetTexture;

int main(int argc, char* args[])
{
    if(init())
    {
        if(loadMedia())
        {
            bool quit = false;
            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                spriteSheetTexture.render(0, 0, renderer, &spriteClips[0]);

                spriteSheetTexture.render(SCREEN_WIDTH - spriteClips[1].w, 0, renderer, &spriteClips[1]);

                spriteSheetTexture.render(0, SCREEN_HEIGHT - spriteClips[2].h, renderer, &spriteClips[2]);

                spriteSheetTexture.render(SCREEN_WIDTH - spriteClips[3].w, SCREEN_HEIGHT - spriteClips[3].h, renderer, &spriteClips[3]);

                SDL_RenderPresent(renderer);

            }
             
        }
    }

    close();

    return 0;
}

bool init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            printf("Error creating the window ! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == nullptr)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int initImageFlags = IMG_INIT_PNG;
                if((IMG_Init(initImageFlags) != initImageFlags))
                {
                    printf("SDL_image could not initialize! SDL_image ERROR: %s\n", IMG_GetError());
                    success = false;
                }
                else{
                    screenSurface = SDL_GetWindowSurface(window);
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    if(!spriteSheetTexture.loadFromFile("sprites.png", renderer))
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    else{
        spriteClips[0].x = 0;
        spriteClips[0].y = 0;
        spriteClips[0].w = 100;
        spriteClips[0].h = 100;

        
        spriteClips[1].x = 100;
        spriteClips[1].y = 0;
        spriteClips[1].w = 100;
        spriteClips[1].h = 100;

        
        spriteClips[2].x = 0;
        spriteClips[2].y = 100;
        spriteClips[2].w = 100;
        spriteClips[2].h = 100;

        
        spriteClips[3].x = 100;
        spriteClips[3].y = 100;
        spriteClips[3].w = 100;
        spriteClips[3].h = 100;
    }

    
    return success;
}

SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


void close()
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = nullptr;

    SDL_Quit();
    IMG_Quit();
}
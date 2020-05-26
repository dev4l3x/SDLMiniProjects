#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Window* window = nullptr;

SDL_Surface* screenSurface = nullptr;
SDL_Surface* hellowWorld = nullptr;

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
                SDL_BlitSurface(hellowWorld, nullptr, screenSurface, nullptr);
                SDL_UpdateWindowSurface(window);
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
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    hellowWorld = SDL_LoadBMP("nature.bmp");
    if(hellowWorld == nullptr)
    {
        printf("Unable to load image %s! SDL_Error: %s\n", "nature.bpm", SDL_GetError());
        success = true;
    }

    return success;
}

void close()
{
    SDL_FreeSurface(hellowWorld);
    hellowWorld = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}
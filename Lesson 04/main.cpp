#include <SDL.h>
#include <stdio.h>
#include <string>

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

SDL_Window* window = nullptr;


SDL_Surface* screenSurface = nullptr;

//Imagenes a cargar
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Superficie actual cargada
SDL_Surface* currentSurface = nullptr;

int main(int argc, char* args[])
{
    if(init())
    {
        if(loadMedia())
        {
            bool quit = false;
            SDL_Event e;

            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_UP:
                        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;

                    case SDLK_DOWN: 
                        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    
                    case SDLK_LEFT:
                        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;

                    case SDLK_RIGHT:
                        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    
                    default:
                        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                    }
                    
                }
                SDL_BlitSurface(currentSurface, nullptr, screenSurface, nullptr);
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

    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("nature.bmp");
    if(keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
    {
        printf("Unable to load image ! SDL_Error : %s", SDL_GetError());
        success = false;
    }

    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
    if(keyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr)
    {
        printf("Unable to load image ! SDL_Error : %s", SDL_GetError());
        success = false;
    }

    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
    if(keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr)
    {
        printf("Unable to load image ! SDL_Error : %s", SDL_GetError());
        success = false;
    }

    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
    if(keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr)
    {
        printf("Unable to load image ! SDL_Error : %s", SDL_GetError());
        success = false;
    }

    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
    if(keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr)
    {
        printf("Unable to load image ! SDL_Error : %s", SDL_GetError());
        success = false;
    }

    return success;
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == nullptr)
    {
        printf("Error loading image at path %s ! SDL_Error: %s \n", path, SDL_GetError());
    }
    return loadedSurface;
}

void close()
{
    SDL_FreeSurface(currentSurface);
    currentSurface = nullptr;

    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
    {
        SDL_FreeSurface(keyPressSurfaces[i]);
    }

    delete keyPressSurfaces;
    
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}
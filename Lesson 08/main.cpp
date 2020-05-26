#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>

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

SDL_Texture* texture = nullptr;

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

                SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);

                //Render green outlined quad
                SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
                SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );        
                SDL_RenderDrawRect( renderer, &outlineRect );

                //Draw blue horizontal line
                SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );        
                SDL_RenderDrawLine( renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
                //Draw vertical line of yellow dots
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
                for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
                {
                    SDL_RenderDrawPoint( renderer, SCREEN_WIDTH / 2, i );
                }

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

                int initImageFlags = IMG_INIT_JPG;
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
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = nullptr;

    SDL_Quit();
    IMG_Quit();
}
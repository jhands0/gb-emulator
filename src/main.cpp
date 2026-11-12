#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int SDLCALL gb_runapp_callback(int argc, char** argv);

int main(int argc, char** argv) 
{
    return SDL_RunApp(argc, argv, gb_runapp_callback, NULL);
}

int SDLCALL gb_runapp_callback(int argc, char** argv) 
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }
    
    const char* pathname = "";

    if (cart_load(pathname))
    {
        cart_print_info();
    }

    SDL_Quit();

    return 0;
}
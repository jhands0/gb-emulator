#include <iostream>

#define SDL_MAIN_HANDLED
#include "../include/SDL3/SDL.h"
#include "../include/SDL3/SDL_main.h"

#include "../include/emulator_core.h"

int SDLCALL gb_runapp_callback(int argc, char** argv);

int main(int argc, char** argv) 
{
    return SDL_RunApp(argc, argv, gb_runapp_callback, NULL);
}

int SDLCALL gb_runapp_callback(int argc, char** argv) 
{
    int error = core_init();
    if (error != 0)
    {
        return error;
    }

    core_run();

    core_shutdown();

    return 0;
}

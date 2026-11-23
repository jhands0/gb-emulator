#pragma once

#include "SDL3/SDL.h"

struct gfx_context
{
	SDL_Window* 	window;
	SDL_Renderer* 	renderer;
	SDL_Event	event;
	SDL_Texture*	texture;
};

gfx_context* gfx_init(unsigned int width, unsigned int height, const char* title);
void gfx_clear(gfx_context* ctx, SDL_Color color);
void gfx_putpixel(gfx_context* ctx, unsigned int x, unsigned int y, SDL_Color color);
void gfx_update(gfx_context* ctx);
void gfx_destroy(gfx_context* ctx);


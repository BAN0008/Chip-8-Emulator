#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdbool.h>

#include <SDL2/SDL.h>

extern bool graphics[64 * 32];

void clear_display();
void draw_screen(SDL_Renderer *renderer);

#endif //_GRAPHICS_H
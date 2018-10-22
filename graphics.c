#include "graphics.h"

bool graphics[64 * 32];

void clear_display()
{
	for (uint16_t i = 0; i < 64 * 32; i++)
	{
		graphics[i] = false;
	}
}

void draw_screen(SDL_Renderer *renderer)
{
	for (uint16_t i = 0; i < sizeof(graphics) / sizeof(bool); i++)
	{
		SDL_RenderDrawPoint(renderer, i % 64, floor(i / 32));
	}
}
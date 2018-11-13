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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (uint16_t i = 0; i < sizeof(graphics) / sizeof(bool); i++)
	{
		SDL_RenderDrawPoint(renderer, i % 64, floor(i / 32));
	}
	SDL_RenderPresent(renderer);
}
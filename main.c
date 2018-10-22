#include <stddef.h>

#include <SDL2/SDL.h>

#include "global.h"
#include "cpu.h"
#include "graphics.h"

void initialize(char * fname)
{
	program_counter = 0x200;
	opcode = 0x0;
	I_index_register = 0x0;
	stack_pointer = 0x0;

	//Clear Display
	clear_display();

	//Clear Stack
	for (uint8_t i = 0; i < 16; i++)
	{
		stack[i] = 0x0;
	}

	//Clear Registers
	for (uint8_t i = 0; i < 16; i++)
	{
		v_register[i] = 0x0;
	}

	//Clear Memory
	for (uint16_t i = 0; i < 4096; i++)
	{
		memory[i] = 0x0;
	}

	//Load Fontset
	for (uint8_t i = 0; i < 80; i++)
	{
		memory[i + 80] = fontset[i];
	}

	delay_timer = 0;
	sound_timer = 0;

	//Load Program
	FILE *program = fopen(fname, "r");
	fseek(program, 0L, SEEK_END);
	uint16_t program_size = ftell(program);
	rewind(program);
	fread(&memory + 0x200, 1, program_size - 1, program);
	fclose(program);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	//Create Window
	SDL_Renderer *renderer = NULL;
	SDL_Window   *window   = NULL;
	SDL_CreateWindowAndRenderer(64, 32, 0, &window, &renderer);

	initialize(argv[1]);

	while (true)
	{
		emulate_cycle();
		if (true) //Draw Flag
		{
			draw_screen(renderer);
		}
	}
	return 0;
}

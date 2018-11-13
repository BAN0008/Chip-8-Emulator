#include "cpu.h"

#include "global.h"
#include "graphics.h"

void emulate_cycle()
{
	opcode = memory[program_counter] << 8 | memory[program_counter + 1];
	switch (opcode & 0xF000)
	{
		case 0x0000:
			switch (opcode)
			{
				case 0x00E0: //Clear Display
					clear_display();
					break;
				case 0x00EE: //Returns from a subroutine
					program_counter = stack[stack_pointer];
					stack_pointer--;
					break;
				default:
					//NO_OPCODE
					break;
			}
			break;
		case 0x1000: //Goto Address
			program_counter = opcode & 0x0FFF;
			break;
		case 0x2000: //Call subroutine at address
			stack[stack_pointer] = program_counter;
			stack_pointer++;
			program_counter = opcode & 0x0FFF;
			break;
		case 0x3000: //Skips the next instruction if VX equals NN
			if (v_register[opcode & 0x0F00] == opcode & 0x00FF)
			{
				program_counter += 2;
			}
			break;
		case 0x4000: //Skips the next instruction if VX doesn't equal NN
			if (v_register[opcode & 0x0F00] != opcode & 0x00FF)
			{
				program_counter += 2;
			}
			break;
		case 0x5000: 
			if ((opcode & 0xF00F) == 0x5000) //Skips the next instruction if VX equals VY
			{
				if (v_register[opcode & 0x0F00] == v_register[opcode & 0x00F0])
				{
					program_counter += 2;
				}
			}
			else
			{
				//NO_OPCODE
			}
			break;
		case 0x6000: //Sets VX to NN
			v_register[opcode & 0x0F00] = opcode & 0x00FF;
			break;
		case 0x7000: //Adds NN to VX(Carry flag is not changed)
			v_register[opcode & 0x0F00] = v_register[opcode & 0x0F00] & (opcode & 0x00FF);
			break;
		case 0x8000:
			switch (opcode & 0xF00F)
			{
				case 0x8000: //Sets VX to the value of VY
					v_register[opcode & 0x0F00] = v_register[opcode & 0x00F0];
					break;
				case 0x8001: //Sets VX to VX or VY. (Bitwise OR operation)
					v_register[opcode & 0x0F00] = v_register[opcode & 0x0F00] | v_register[opcode & 0x00F0];
					break;
				case 0x8002: //Sets VX to VX and VY. (Bitwise AND operation)
					v_register[opcode & 0x0F00] = v_register[opcode & 0x0F00] & v_register[opcode & 0x00F0];
					break;
				case 0x8003: //Sets VX to VX xor VY.
					v_register[opcode & 0x0F00] = v_register[opcode & 0x0F00] ^ v_register[opcode & 0x00F0];
					break;
				case 0x8004: //Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
					break;
				case 0x8005: //VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
					break;
				case 0x8006: //Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
					break;
				case 0x8007: //Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
					break;
				case 0x800E: //Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
					break;
				default:
					//NO_OPCODE
					break;
			}
			break;
		case 0x9000:
			if ((opcode & 0xF00F) == 0x9000) //Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
			{
				if (v_register[opcode & 0x0F00] != v_register[opcode & 0x00F0])
				{
					program_counter += 2;
				}
			}
			else
			{
				//NO_OPCODE
			}
			break;
		case 0xA000: //Sets I to the address NNN.
			I_index_register = opcode & 0x0FFF;
			break;
		case 0xB000: //Jumps to the address NNN plus V0.
			program_counter = (opcode & 0x0FFF) + v_register[0];
			break;
		case 0xC000: //Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
			 v_register[opcode & 0x0F00] = program_counter; //UNFINISHED
			break;
		case 0xD000: //Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
			for (uint8_t i = I_index_register; i < (opcode & 0x000F) * 8; i++)
			{
				uint16_t temp = (v_register[opcode & 0x00F0] + floor((opcode & 0x000F) / 8)) + v_register[opcode & 0x0F00] + ((i - I_index_register) % 8);
				graphics[temp] = memory[i];
			}
			break;
		case 0xE000: 
			switch (opcode & 0xF0FF)
			{
				case 0xE09E: //Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
					break;
				case 0xE0A1: //Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
					program_counter += 2;
					//NOT_DONE
					break;
				default:
					//NO_OPCODE
					break;
			}
			break;
		case 0xF000:
			switch (opcode & 0xF0FF)
			{
				case 0xF007: //Sets VX to the value of the delay timer.
					v_register[opcode & 0x0F00] = delay_timer;
					break;
				case 0xF00A: //A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
					break;
				case 0xF015: //Sets the delay timer to VX.
					delay_timer = v_register[opcode & 0x0F00];
					break;
				case 0xF018: //Sets the sound timer to VX.
					sound_timer = v_register[opcode & 0x0F00];
					break;
				case 0xF01E: //Adds VX to I.
					I_index_register += v_register[opcode & 0x0F00];
					break;
				case 0xF029: //Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
					I_index_register = (v_register[opcode & 0x0F00] * 5) + 0x50;
					break;
				case 0xF033: //Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
					break;
				case 0xF055: //Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
					break;
				case 0xF065: //Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
					break;
				default:
					//NO_OPCODE
					break;
			}
			break;
		default:
			//NO_OPCODE
			break;
	}
	program_counter += 2;
	if (delay_timer > 0)
	{
		delay_timer--;
	}
	if (sound_timer > 0)
	{
		sound_timer--;
		if (sound_timer == 0)
		{
			//Play Beep
		}
	}
}

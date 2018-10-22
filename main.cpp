uint16_t opcode;
uint8_t  memory[4096];
uint8_t  v_register[16];
uint16_t I_index_register;
uint16_t program_counter;
bool     graphics[64 * 32];
uint8_t  delay_timer;
uint8_t  sound_timer;
uint16_t stack[16];
uint16_t stack_pointer;
bool     keys[16];

void clear_display()
{
	for (unsigned i = 0; i < 64 * 32; i++)
	{
		graphics[i] = false;
	}
}

void initialize()
{
	program_counter = 0x200;
	opcode = 0x0;
	I_index_register = 0x0;
	stack_pointer = 0x0;

	//Clear Display
	clear_display();

	//Clear Stack
	for (unsigned i = 0; i < 16; i++)
	{
		stack[i] = 0x0;
	}

	//Clear Registers

	//Clear Memory
	for (unsigned i = 0; i < 4096; i++)
	{
		memory[i] = 0x0;
	}

	//Load Fontset

	delay_timer = 0;
	sound_timer = 0;

	//Load Program
}

void emulate_cycle()
{
	opcode = memory[program_counter] << 8 | memory[program_counter + 1];
	switch (opcode & 0xF000)
	{
		case 0x0000:
			if (opcode == 0x00E0) //Clear Display
			{
				clear_display();
			}
			if (opcode == 0x00EE) //Returns from a subroutine
			{

			}
			break;
		case 0x1000: //Goto Address
			break;
		case 0x2000: //Call subroutine at address
			break;
		case 0x3000: //Skips the next instruction if VX equals NN
			break;
		case 0x4000: //Skips the next instruction if VX doesn't equal NN
			break;
		case 0x5000: //Skips the next instruction if VX equals VY
			break;
		case 0x6000: //Sets VX to NN
			break;
		case 0x7000: //Adds NN to VX(Carry flag is not changed)
			break;
		case 0x8000: //Sets VX  to the value of VY
			break;
		case 0x8000: //Sets VX to VX or VY. (Bitwise OR operation)
			break;
		case 0x8000: //Sets VX to VX and VY. (Bitwise AND operation)
			break;
		case 0x8000: //Sets VX to VX xor VY.
			break;
		case 0x8000: //Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
			break;
		case 0x8000: //VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
			break;
		case 0x8000: //Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
			break;
		case 0x8000: //Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
			break;
		case 0x8000: //Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
			break;
		case 0x9000: //Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
			break;
		case 0xA000: //Sets I to the address NNN.
			break;
		case 0xB000: //Jumps to the address NNN plus V0.
			break;
		case 0xC000: //Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
			break;
		case 0xD000: //Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
			break;
		case 0xE000: //Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
			break;
		case 0xE000: //Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
			break;
		case 0xF000: //Sets VX to the value of the delay timer.
			break;
		case 0xF000: //A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
			`break;
		case 0xF000: //Sets the delay timer to VX.
			break;
		case 0xF000: //Sets the sound timer to VX.
			break;
		case 0xF000: //Adds VX to I.
			break;
		case 0xF000: //Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
			break;
		case 0xF000: //Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
			break;
		case 0xF000: //Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
			break;
		case 0xF000: //Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
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

int main(int argc, char *argv[])
{
	initialize();

	while (true)
	{
		emulate_cycle();
	}
	return 0;
}

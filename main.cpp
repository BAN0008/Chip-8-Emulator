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

int main(int argcm, char* argv[])
{
	return 0;
}

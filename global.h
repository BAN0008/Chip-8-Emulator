#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdint.h>
#include <stdbool.h>

extern uint16_t opcode;
extern uint8_t  memory[4096];
extern uint8_t  v_register[16];
extern uint16_t I_index_register;
extern uint16_t program_counter;
extern uint8_t  delay_timer;
extern uint8_t  sound_timer;
extern uint16_t stack[16];
extern uint8_t  stack_pointer;
extern bool     keys[16];

extern uint8_t fontset[80];

#endif //_GLOBAL_H
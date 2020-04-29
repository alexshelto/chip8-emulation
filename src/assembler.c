/**
 * @file assembler.c
 * @author Alexander Shelton
 * @brief Carries out instructions for .ch8 files
 * @version 0.1
 * @date 2020-04-29
 * 
 */

#include "stdint.h" //uint8_t,unit16_t


/**
 * @struct Chip8State
 * @brief purpose is to handle the state of
 * 
 * Contained...
 *  * 16, 8-bit registers
 *  * 4k ram, starts at 0x200
 *  * 64x32 Display, 1 bit / pixel
 *  * Display buffer in RAM @ 0xF00
 *  * Memory address register
 *  * Stack instructions: need stack pointer
 *  * 2 Timers: 1 for delay 1 for sound
 */
typedef struct Chip8State {
    uint8_t V[16];   //Register array
    uint16_t I;      //
    uint16_t SP;     //Stack Pointer
    uint16_t PC;     //Program Counter
    uint8_t delay;   //Timer for Delay
    uint8_t sound;   //Timer for Sound
    uint8_t *memory; //'RAM' for state
    uint8_t *screen; //Memory screen Buffer: [0xF00]
 } Chip8State;


/** @brief Allocates chip8state
 *  @return Chip8State* state */
Chip8State* InitChip8(void) {
    Chip8State* state = calloc(sizeof(Chip8State), 1);
    state -> memory = calloc(1024*4, 1);   //4k ram allocation
    state -> screen = &state -> memory[0xf00]; //Placing display buffer in ram @ [0xf00]
    state -> SP = 0xfa0;
    state -> PC = 0x200; //Convention programs start at 0x200 in memory
 
    return state;
}




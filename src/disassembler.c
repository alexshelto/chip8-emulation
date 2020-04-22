/**
 * @author Alexander Shelton
 * @brief shows OpCodes to .ch commands
 * @version 0.1
 * @date 2020-04-22
 * 
 * @copyright Copyright (c) 2020
 * 
**/

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"


void DisassembleChip8(uint8_t *codeBuffer, int programCounter) {
    uint8_t *code = &codeBuffer[programCounter];
    //0x200 because all chip-8 programs start at 0x200 in memory
    //Opcodes are organized by the first upper half of the first half

    uint8_t firstHalf = code[0] >> 4; //taking the upper half of the first byte
    printf("%04x %02x %02x ", programCounter, code[0], code[1]);    
    switch (firstHalf)    
    {   
        case 0x0: 
            switch (code[1]) {
                case 0xe0: printf("%-10s", "CLS"); break;
                case 0xee: printf("%-10s", "RFS"); break;
                default: printf("Unknown 0");  break;

            }
            break;
        /* ---------------------------------- flow ---------------------------------- */
        case 0x1: printf("%-10s $%01x%02x", "JUMP", code[0]&0xf, code[1]); break;
        case 0x2: printf("%-10s $%01x%02x", "CALL", code[0]&0xf, code[1]); break;
        /* ------------------------------ conditionals ------------------------------ */
        case 0x3: printf("%-10s V%01x, #$%02x", "EQ", code[0]&0xf, code[1]); break;
        case 0x4: printf("%-10s V%01x, #$%02x", "NE", code[0]&0xf, code[1]); break;
        case 0x5: printf("%-10s V%01x, V%01x", "SKIP-EQ", code[0]&0xf, code[1] >> 4); break;
        /* ---------------------------------- const --------------------------------- */
        case 0x6: printf("%-10s V%01x, #$%02x", "MVI", code[0]&0xf, code[1]); break;
        case 0x7: printf("%-10s V%01x, #$%02x", "ADD", code[0]&0xf, code[1]); break;

        /* ------------------------------ bitOp / Math ------------------------------ */
        case 0x8: {
            uint8_t lastHalf = code[1] >> 4; //grabbing the last half of the codes
            switch(lastHalf) {
                case 0: printf("%-10s V%01X, V%01X", "MOV.", code[0]&0xf, code[1] >> 4); break;
                case 1: printf("%-10s V%01X, V%01X", "OR.", code[0]&0xf, code[1] >> 4); break;
                case 2: printf("%-10s V%01X, V%01X", "AND.,", code[0]&0xf, code[1] >> 4); break;
                case 3: printf("%-10s V%01X, V%01X", "XOR.", code[0]&0xf, code[1] >> 4); break;
                case 4: printf("%-10s V%01X, V%01X", "ADD.", code[0]&0xf, code[1] >> 4); break;
                case 5: printf("%-10s V%01X,V%01X,V%01X", "SUB.", code[0]&0xf, code[0]&0xf, code[1] >> 4); break;
                case 6: printf("%-10s V%01X,V%01X", "SHR.", code[0]&0xf, code[1] >> 4); break;
                case 7: printf("%-10s V%01X,V%01X,V%01X", "SUB.", code[0]&0xf, code[1] >> 4, code[1] >> 4); break;
                case 0xe: printf("%-10s V%01X,V%01X", "SHL.", code[0]&0xf, code[1] >> 4); break;
                default: printf("UNKNOWN 8"); break;
            }//end switch 
        } //end 0x8 case
        break;
        
        case 0x9: printf("%-10s V%01X, V%01x", "SKIP-NE", code[0]&0xf, code[1] >> 4); break;
		case 0xa: printf("%-10s I,#$%01x%02x", "MVI", code[0]&0xf, code[1]); break;
        case 0xb: printf("%-10s, $%01x%02x + (V0)", "JUMP", code[0]&0xf, code[1]); break;
        case 0xc: printf("%-10s V%01X,#$%02X", "RNDMSK", code[0]&0xf, code[1]); break;
		case 0xd: printf("%-10s V%01X,V%01X,#$%01x", "SPRITE", code[0]&0xf, code[1] >> 4, code[1]&0xf); break;

        /* ------------------------ checking all the e opCode ----------------------- */
        case 0xe: 
			switch(code[1]) {
				case 0x9E: printf("%-10s V%01X", "SKIPKEY.Y", code[0]&0xf); break;
				case 0xA1: printf("%-10s V%01X", "SKIPKEY.N", code[0]&0xf); break;
				default: printf("UNKNOWN E"); break;
			}
        break;
        /* ------------------------ checking all the F opCode ----------------------- */
		case 0xf: 
			switch(code[1]) {
				case 0x07: printf("%-10s V%01X,DELAY", "MOV", code[0]&0xf); break;
				case 0x0a: printf("%-10s V%01X", "KEY", code[0]&0xf); break;
				case 0x15: printf("%-10s DELAY,V%01X", "MOV", code[0]&0xf); break;
				case 0x18: printf("%-10s SOUND,V%01X", "MOV", code[0]&0xf); break;
				case 0x1e: printf("%-10s I,V%01X", "ADI", code[0]&0xf); break;
				case 0x29: printf("%-10s I,V%01X", "SPRITECHAR", code[0]&0xf); break;
				case 0x33: printf("%-10s (I),V%01X", "MOVBCD", code[0]&0xf); break;
				case 0x55: printf("%-10s (I),V0-V%01X", "MOVM", code[0]&0xf); break;
				case 0x65: printf("%-10s V0-V%01X,(I)", "MOVM", code[0]&0xf); break;
				default: printf("UNKNOWN F"); break;
			}
        break;
    }//end switch    
}//end disassembler








   int main (int argc, char**argv)    
   {    
    FILE *f = fopen(argv[1], "rb");    
    if (f==NULL)    
    {    
        printf("error: Couldn't open %s\n", argv[1]);    
        EXIT_FAILURE;    
    }

    //Get the file size    
    fseek(f, 0L, SEEK_END);    
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);    

/* ---------------------------------- debug --------------------------------- */
    printf("Size of file: %x \n", fsize);   
    printf("Allocating a buffer of size: %x \n", fsize + 0x200);    

    //CHIP-8 convention puts programs in memory at 0x200    
    //Starting at 0x200
    // They will all have hardcoded addresses expecting that    

    //Read the file into memory at 0x200 and close it.    
    unsigned char *buffer = malloc(fsize+0x200);
    fread(buffer+0x200, fsize, 1, f); //
    fclose(f);    

    int pc = 0x200;    
    while (pc < (fsize+0x200))    
    {
        DisassembleChip8(buffer, pc);    
        pc += 2; //step 2 in hex eg: (228 += 2 => 22a)
        printf ("\n");    
    }
    EXIT_SUCCESS;    
}    
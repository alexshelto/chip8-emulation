/**
 * @file disassembler.c
 * @brief 
 * @date 2020-04-22
 */

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"


void DisassembleChip8(uint8_t *codeBuffer, int programCounter) {
    uint8_t *code = &codeBuffer[programCounter];
    //0x200 because all chip-8 programs start at 0x200 in memory
    //Opcodes are organized by the first upper half (nibble) of the first byte
    
    uint8_t firstNib = code[0] >> 4;
    printf("%04x %02x %02x ", programCounter, code[0], code[1]);    
    switch (firstNib)    
    {    
        case 0x00: printf("0 not handled yet"); break;    
        case 0x01: printf("1 not handled yet"); break;    
        case 0x02: printf("2 not handled yet"); break;    
        case 0x03: printf("3 not handled yet"); break;    
        case 0x04: printf("4 not handled yet"); break;    
        case 0x05: printf("5 not handled yet"); break;    
        case 0x06:    
            {    
                uint8_t reg = code[0] & 0x0f;    
                printf("%-10s V%01X,#$%02x", "MVI", reg, code[1]);    
            }    
            break;    
        case 0x07: printf("7 not handled yet"); break;    
        case 0x08: printf("8 not handled yet"); break;    
        case 0x09: printf("9 not handled yet"); break;    
        case 0x0a:    
            {   
                uint8_t addresshi = code[0] & 0x0f;    
                printf("%-10s I,#$%01x%02x", "MVI", addresshi, code[1]);    
            }    
            break;    
        case 0x0b: printf("b not handled yet"); break;    
        case 0x0c: printf("c not handled yet"); break;    
        case 0x0d: printf("d not handled yet"); break;    
        case 0x0e: printf("e not handled yet"); break;    
        case 0x0f: printf("f not handled yet"); break;    
    }    
}    

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
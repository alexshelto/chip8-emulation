#










# Instruction Set
https://en.wikipedia.org/wiki/CHIP-8


## Register Placeholders
'x' & 'y' are used in place of register identifiers.
'x' & 'y' are replaced with one of 16 nums inside of 0-F

## Immediate Values
* 'N' is used where the number is interpreted as immediate.  (4-bit)
* 'NN' is used for a byte of data (8-bit)
* 'NNN' is used to signify an address

## 0xxx Opcode
There are 3 ops starting with 0... <br>
the first returns from a sub routine, the seccond clears screen, and the third calls RCA 1802 (wont be neccesary)

## 1xxx, 2xxx Bxxx Opcode
* 1xxx are absolute jumps, the opcode: 14A6 equates to `JUMP $4A6`
* 2NNN jumps to subroutine
* 24A8 would equate to: `CALL $4AB`
    * pushed the address if the next instruction is on the stack
    * setting the PC 'Program Counter' to the address contained in the instruction
* Each subroutine must end with 'OOEE' instruction

## 3xxx, 4xxx, 5xxx, 9xxx Opcode: Conditionals
| Oppcode | Nemonic |
|---------|---------|
|3A00 | EQ  VA, #$00|
|4800 | NE  V8, #$00|
|5A70 | EQ  VA, V7  |
|93B0 | NE  V3. VB  |
where EQ checks for equality and NE checks for not equal

## 9xxx, Register Opcode
* There are 9 instructions in the 8xxx group that use 2 registers
* Vx gets modified by Vy <br>
Some opperations will midify 'VF' based on the result of the math or storing numbers. this is chip 8's condition codes <br>
* For the assembly syntax, a dot '.' after instructions indicates the modification of 'VF' <br>

| Opcode | Nemonic |
|--------|---------|    
|83A0 |  MOV   V3, VA|    
|83A1 |  OR    V3, VA|    
|83A2 |  AND   V3, VA|   
|83A3 |  XOR   V3, VA|   
|83B4 |  ADD.  V3, VB|    
|83B5 |  SUB.  V3, VB|    
|83x6 |  SHR.  V3    |
|83B7 |  SUBB. V3, VB|   
|83xE |  SHL.  V3    |

## The rest of Chip-8 Opcodes...
* The rest of the Opcodes cannot be easilly classified. Most have to do with timers, sprites, and interactions.  
* below is the syntax for them and you can read more in the wiki <br>      
| Opcode | Nemonic |
|--------|---------|    
|DXYN |  SPRITE       VX, VY, #$N |   
|EX9E |  SKIP.KEY     VX          |
|EXA1 |  SKIP.NOKEY   VX          |
|FX07 |  MOV          VX, DELAY   |
|FX0A |  WAITKEY      VX          |
|FX15 |  MOV          DELAY, VX   | 
|FX18 |  MOV          SOUND, VX   | 
|FX1E |  ADD          I, VX       |
|FX29 |  SPRITECHAR   VX          |
|FX33 |  MOVBCD       VX          |
|FX55 |  MOVM         (I), V0-VX  | 
|FX65 |  MOVM         V0-VX, (I)  |







class chip8 {
public:
  chip8();
  ~chip8();

  void emulateCycle();
  void debug();
  void loadApplication(const char * filename);

  bool drawFlag;

  unsigned char gfx[64 * 32];   // total amount of pixels
  unsigned char key[16];          

private:
  unsigned short opcode;        // two byte opcode
  unsigned short pc;            // Program counter values: 0x000 -> 0xFFF
  unsigned short I;             // index register keeps track of pc
  unsigned short sp;            // stack pointer
  
  unsigned char V[16];          // V-registers, 0-F
  unsigned short stack[4096];   // 4K memory

  unsigned char delay_timer;
  unsigned char sound_timer;
  
  void initialize();
};

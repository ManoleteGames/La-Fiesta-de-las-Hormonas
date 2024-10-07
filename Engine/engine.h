/***********************
*  Engine header
************************/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <alloc.h>
#include <mem.h>
#include <math.h>

/////////////////////////////////////////////////////////
// global things
/////////////////////////////////////////////////////////
typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef struct tagPLAYER{
   byte healt;
   byte intell;
   byte charm;
   byte freak;
   byte handsome;

   byte day;
   byte hour;
   byte min;

   byte floor;
   byte event;
   byte hotspot;
   byte move;
   byte oldMove;
   byte act;
   byte state;
   byte oldState;
   byte tile_x;
   byte tile_y;

   word spriteNum;

} PLAYER;


typedef struct tagSPRITEFRAME{			// structure for a sprite frame
	char *compiled_code;
} SPRITEFRAME;

typedef struct tagSPRITE{				// structure for a sprite
	word width;		// Width of full bmp file in px
	word height; 	// Height of full bmp file in px
	word init;		// Initialization flag. 0:= background not saved yet. 1:= background saved
	word animate;
	word speed;
	word anim_counter;
	word anim_speed;
	word baseframe; //first frame
	word aframes;
   byte animation[32];
   byte hide;		// Do not draw back the sprite, just remains hiden
   byte hidden;		// Sprite currently hidden
	byte mode; //FOR AI
	byte stack;	//FOR AI
   byte loaded; // 0:= not loaded / 1:=loaded
	word tile_x;
	word tile_y;
	word pos_x;
	word pos_y;
	word last_x;
	word last_y;
	word last_last_x;
	word last_last_y;
	int mspeed_x;
	int mspeed_y;
	int speed_x;
	int speed_y;
	word fixed_sprite_number;
	word frame;
	word last_frame;
	word nframes;
	word bkg_data;	//restore bkg
	word *ega_size;
	word rows;
	word cols;
	word next_scanline;
	word s_delete;
	word code_size;
	SPRITEFRAME *frames;
} SPRITE;


/* macro to write a word to a port */
#define word_out(port,register,value) \
  outport(port,(((word)value<<8) + register))

#define P_STOP			0;
#define P_UP			1;
#define P_DOWN			2;
#define P_LEFT			3;
#define P_RIGHT		4;
#define P_UPRIGHT		5;
#define P_UPLEFT		6;
#define P_DWNRIGHT	7;
#define P_DWNLEFT		8;


#define K_ESC				0x01
#define K_BKSP				0x0E
#define K_ENTER			0x1C
#define K_O					0x18
#define K_P					0x19
#define K_Q					0x10
#define K_A					0x1E
#define K_S					0x1F
#define K_D					0x20
#define K_UP				0x48
#define K_DOWN				0x50
#define K_LEFT				0x4B
#define K_RIGHT			0x4D
#define K_SPACE			0x39

#define KEYB_IRQ        9

extern byte PlayerAnimation[];

// Engine.c prototypes
extern unsigned char *error1;
extern unsigned char *error2;
extern unsigned char *string;
extern word vram_LogicalWidth; // screen logical with on bytes in vram
extern word vram_Font; // Font address in VRAM
extern word vram_Tiles; // Tiles address in VRAM
extern word vram_SpritesBack; // Sprites background address in VRAM
extern byte palette[256*3];
extern byte *tempdata1; //Temp storage of non tiled data. and also sound samples (1/2)
extern byte *tempdata2; //Temp storage of non tiled data. and also sound samples (2/2)
extern int scroll_x;   // Scroll X
extern int scroll_y;   // Scroll Y
extern int scroll_wy;   // Scroll window Y
extern byte showPanel;
extern byte scrolling_enabled;
extern PLAYER far player;

void InitEngine(void);
void Delay(int count);
void Error(char *error, char *file, char *filename);
void Update(int sprite_follow, int sprite);
void ExitDOS(void);
void MovePlayer(void);
void ResetScroll(void);

// External functions prototypes
extern void (*Fade_out)(void);
extern void (*Fade_in)(void);
extern void (*LoadImage)(char *file,char* dat_string, word page);
extern void (*SetPage)(int page);
extern void (*RotatePalette)(int index1, int index2, int speed);
extern void (*LoadAnimation)(char *file, char *dat_string);
extern void (*LoadFont)(char *file, char *dat_string);
extern void (*LoadTiles)(char *file,char* dat_string);
extern void (*Draw_EmptyBox)(word x, word y, byte w, byte h);
extern void (*SetLoadingInterrupt)(void);
extern void (*ResetLoadingInterrupt)(void);
extern void (*PrintText)(word x, word y, word lineLength, unsigned char *string);
extern void (*Draw_Sprites)(void);
extern void (*SetPalette)(unsigned char *pal);
extern void (*LoadTiles)(char *file,char* dat_string);
extern void (*SetMap)(int x, int y);
extern void (*ScrollMap)(void);
extern void (*UpdatePanel)(void);
extern void (*LoadPanelBackground)(char *file,char* dat_string);

// VIDEO/VGA.c prototypes
extern word vga_page[];

byte VGA_Present(void);
void VGA_Vsync(void);
void VGA_TextMode(void);
void VGA_InitVideoCard(void);
void VGA_Fade_in(void);
void VGA_Fade_out(void);
void VGA_LoadImage(char *file,char* dat_string, word page);
void VGA_HardwareScrolling(void);
void VGA_SetPage(int page);
void VGA_RotatePalette(int index1, int index2, int speed);
void VGA_LoadFont(char *file, char *dat_string);
void VGA_LoadTiles(char *file,char* dat_string);
void VGA_Draw_EmptyBox(word x, word y, byte w, byte h);
void VGA_SetLoadingInterrupt(void);
void VGA_ResetLoadingInterrupt(void);
void VGA_PrintText(word x, word y, word lineLength, unsigned char *string);
void VGA_Draw_Sprites(void);
void VGA_SetPalette(unsigned char *pal);
void VGA_LoadTiles(char *file,char* dat_string);
void VGA_SetMap(int x, int y);
void VGA_ScrollMap(void);
void VGA_Draw_MapBack(void);
void VGA_Set_Window(void);
void VGA_MoveWindow(void);
void VGA_UpdatePanel(void);
void VGA_LoadPanelBackground(char *file,char* dat_string);

// VIDEO/CGA.c prototypes
byte CGA_Present(void);
void CGA_Vsync(void);

// VIDEO/EGA.c prototypes
byte EGA_Present(void);
void EGA_Vsync(void);

// VIDEO/TANDY.c prototypes
void Vsync_TANDY(void);

// SOUND/SBLASTER.c prototypes
byte SB_Present(void);
void SB_SetAddress(unsigned int addr);
void SB_SetLoDMA(unsigned char dma);
void SB_SetHiDMA(unsigned char dma);
void SB_SetIRQ(unsigned char i);
void SB_InitSoundCard(void);

// SOUND/ADLIB.c prototypes
byte ADLIB_Present(void);
void ADLIB_LoadMusic(void);
void ADLIB_UnloadMusic(void);
void ADLIB_PlayMusic(void);
void ADLIB_StopMusic(void);
void ADLIB_InitSoundCard(void);

// SOUND/TANDY_SND.c prototypes
byte TANDY_Present(void);
void TANDY_LoadMusic(void);
void TANDY_UnloadMusic(void);
void TANDY_PlayMusic(void);
void TANDY_StopMusic(void);
void TANDY_InitSoundCard(void);

// SOUND/MUSIC.c prototypes
typedef struct tagIMFsong{				// structure for adlib IMF song, or MOD pattern data
	int size;
	word offset;
	byte filetype; //0 1 - imf0 imf1
	byte *sdata;
} IMFsong;

// KEYB/KEYB.c prototypes
extern int keys[256];
extern int fp_keys[256];
void Set_key_handler(void);
void Reset_key_handler(void);
void Update_FP_Keys(void);

// MAP/MAP.c prototypes
extern word *map_data;
extern byte *map_flip;
extern byte *map_collision;
extern byte *map_hotspot;
extern byte *map_event;
extern word map_width;
extern word map_height;
extern word map_width_px;
extern word map_height_px;
extern int map_offset_x;
extern int map_offset_y;
extern word map_current_x;
extern word map_current_y;
extern word map_last_x;
extern word map_last_y;
extern word map_scrollSide;
void LoadMap(char *file, char* dat_string);

// SPRITE/SPRITE.c prototypes
extern SPRITE far *sprite;
extern byte spriteStackTable[33];
extern byte far *spriteData1;
extern byte far *spriteData2;
extern dword spriteDataOffset;
extern byte spriteStack;
extern SPRITE loadingAnimation;
word CompileBitmap(word logical_width, unsigned char *bitmap, unsigned char *output);
void ResetSpriteStack(void);

void InitSprite(int sprite_number,int x,int y);
void LoadSprite(char *file, char *dat_string, int sprite_number, byte size);
void Unload_sprite(int sprite_number);
void UnloadSprites(void);
void SetSpriteAnimation(int sprite_number, byte firstFrame, byte nframes, byte speed, byte *anim);
void ResetSpriteAnimation(int sprite_number, byte anim);
void ShowSprite(int sprite_number);
void HideSprite(int sprite_number);

// FILE/FILE.c prototypes
void DAT_Seek(FILE *fp,char *dat_string);
void LoadImage_PCX(char* filename, char* dat_string);
void LoadFont_BMP(char* filename, char* dat_string);
void LoadTileset_PCX(char* filename, char* dat_string);
void LoadAnimation_BMP(char* filename, char* dat_string);
void LoadAnimation_PCX(char* filename, char* dat_string);
void LoadText(char* filename, char* dat_string, char* line,unsigned char* str, word *length);
void LoadSprite_PCX(char* filename, char* dat_string, int sprite_number);

// TILE/TILE.c prototypes
extern word tilesetWidth;
extern word tilesetHeight;
extern word tileset_ntiles;
extern byte *tilesetData;


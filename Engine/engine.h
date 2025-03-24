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
   byte intell;
   byte popular;
   byte good;

   byte money;
   byte day;
  
   byte floor;
   byte event;
   byte hotspot;
   byte collision;

   byte ext1_event_mask[33];
	byte ext2_event_mask[33];
	byte floor1_event_mask[33];
	byte floor2_event_mask[33];
	byte gym_event_mask[33];

	byte ext1_hotspot_mask[33];
	byte ext2_hotspot_mask[33];
	byte floor1_hotspot_mask[33];
	byte floor2_hotspot_mask[33];
	byte gym_hotspot_mask[33];

   byte mission_cheat;
   byte mission_party;
   byte mission_doll;
   byte mission_arcade;
   byte mission_bag;
   byte mission_fight;
   byte mission_keys;
   byte mission_band;
   byte mission_chair;

   byte item_exams;
   byte item_chalk;
   byte item_bag;
   byte item_keys;

   byte spriteColl;
   byte move;
   byte oldMove;
   byte facingLeft;
   byte act;
   byte state;
   byte oldState;
   byte tile_x;
   byte tile_y;

   word spriteNum;

   // Scene counters
   byte scn_main;
   byte scn_nerds;
   byte scn_director;
   byte scn_janitor;
   byte scn_thugs;
   byte scn_girls;
   byte scn_jessy;
	byte scn_sensei;

   byte score[5];

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

// SOUND/MUSIC.c prototypes
typedef struct tagIMFsong{				// structure for adlib IMF song, or MOD pattern data
	int size;
	word offset;
	byte filetype; //0 1 - imf0 imf1
	byte *sdata;
} IMFsong;



/* macro to write a word to a port */
#define word_out(port,register,value) \
  outport(port,(((word)value<<8) + register))

// Programable interval timer Command/mode port
#define PTI_MODE 0x43
#define PTI_CH0  0x40
#define PTI_CH1  0x41
#define PTI_CH2  0x42

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


#define TIMER_IRQ       0x1C
#define KEYB_IRQ        9
#define SPEAKER_IRQ     0x1C

extern byte far PlayerAnimation[];

// Engine.c prototypes
extern unsigned char far *error1;
extern unsigned char far *error2;
extern unsigned char far *string;
extern word vram_LogicalWidth; // screen logical with on bytes in vram
extern word vram_Font; // Font address in VRAM
extern word vram_FontS; // Font address in VRAM
extern word vram_Tiles; // Tiles address in VRAM
extern word vram_SpritesBack; // Sprites background address in VRAM
extern byte palette[256*3];
extern byte *tempdata1; //Temp storage of non tiled data. and also sound samples (1/2)
extern byte *tempdata2; //Temp storage of non tiled data. and also sound samples (2/2)
extern int scroll_x;   // Scroll X
extern int scroll_y;   // Scroll Y
extern int scroll_wy;   // Scroll window Y
extern int scroll_x_adjust;
extern int scroll_y_adjust;
extern byte scroll_focus;
extern byte showPanel;
extern byte panelScrolling;
extern byte panelShown;
extern byte panelHiden;
extern byte scrolling_enabled;
extern PLAYER far player;
extern byte speech_active;
extern byte debug;
extern byte video_mode;  //0-undef; 1-vga; 2-ega; 3-cga; 4-tandy
extern byte music_volume; // 0..100
extern byte audio_mode;	//0-undef; 1-Speaker; 2-tandy; 3-adlib; 4-sound blaster
extern byte sound_volume; // 0..100
extern byte language;	//1-spanish; 2-english
extern byte soundPlaying;
extern IMFsong far music;	// One song in ram stored at "music"
extern byte musicPlaying;
extern byte musicNonStopPlaying;
extern byte musicLoaded;

void InitEngine(void);
void SetLoadingInterrupt(void);
void ResetLoadingInterrupt(void);
void SetTimeInterrupt(void);
void ResetTimeInterrupt(void);
void RestartProgram(void);
void Delay(int count);
void Error(char *error, char *file, char *filename);
void Update(int sprite_follow);
void SaveConfig(void);
void ExitDOS(void);
void MovePlayer(void);
void ResetScroll(void);
void Speech(char* facefile, char* face,char* filename, char* dat_string,char * line1, char * line2, char * line3, char * line4);
byte SpeechSelection(int optNum, char* facefile, char* face,char* filename, char* dat_string,char * line1, char * line2, char * line3, char * line4);

// External functions prototypes
extern void (*Fade_out)(void);
extern void (*Fade_in)(void);
extern void (*LoadImage)(char *file,char* dat_string, word page);
extern void (*LoadTransImage)(char *file,char* dat_string);
extern void (*SetPage)(int page);
extern void (*RotatePalette)(int index1, int index2, int speed);
extern void (*RotatePaletteAsync)(int index1, int index2);
extern void (*LoadAnimation)(char *file, char *dat_string);
extern void (*LoadFont)(char *file, char *dat_string);
extern void (*LoadTiles)(char *file,char* dat_string);
extern void (*Draw_EmptyBox)(word x, word y, byte w, byte h);
extern void (*PrintText)(word x, word y, word lineLength, unsigned char *string, byte color);
extern void (*PrintPanelText)(word x, word y, word lineLength, unsigned char *string);
extern void (*PrintLine)(int pos_x, int pos_y, int width_x, int width_y, byte color);
extern void (*Draw_Sprites)(void);
extern void (*Restore_Sprites)(void);
extern void (*DrawSpriteDestructive)(int sprNum);
extern void (*SetPalette)(unsigned char *pal);
extern void (*LoadTiles)(char *file,char* dat_string);
extern void (*SetMap)(void);
extern void (*ScrollMap)(void);
extern void (*PanelRefresh)(void);
extern void (*LoadPanelBackground)(char *file,char* dat_string);
extern void (*DrawMapBack)(void);

extern void (*LoadMusic)(byte song);
extern void (*UnloadMusic)(void);
extern void (*PlayMusic)(void);
extern void (*PlayNonStopMusic)(void);
extern void (*PauseMusic)(void);
extern void (*StopMusic)(void);
extern void (*InitSoundCard)(void);
extern void (*DeInitSoundCard)(void);
extern void (*PlaySound)(byte sound);

// VIDEO/VGA.c prototypes
extern word vga_page[];

byte VGA_Present(void);
void VGA_Vsync(void);
void VGA_TextMode(void);
void VGA_InitVideoCard(void);
void VGA_Fade_in(void);
void VGA_Fade_out(void);
void VGA_LoadImage(char *file,char* dat_string, word page);
void VGA_LoadTransImage(char *file,char* dat_string);
void VGA_HardwareScrolling(void);
void VGA_SetPage(int page);
void VGA_RotatePalette(int index1, int index2, int speed);
void VGA_LoadFont(char *file, char *dat_string);
void VGA_LoadTiles(char *file,char* dat_string);
void VGA_Draw_EmptyBox(word x, word y, byte w, byte h);
void VGA_SetLoadingInterrupt(void);
void VGA_ResetLoadingInterrupt(void);
void VGA_PrintText(word x, word y, word lineLength, unsigned char *string, byte color);
void VGA_PrintPanelText(word x, word y, word lineLength, unsigned char *string);
void VGA_PrintLine(int pos_x, int pos_y, int width_x, int width_y, byte color);
void VGA_Draw_Sprites(void);
void VGA_Restore_Sprites(void);
void VGA_DrawSpriteDestructive(int sprNum);
void VGA_SetPalette(unsigned char *pal);
void VGA_LoadTiles(char *file,char* dat_string);
void VGA_SetMap(void);
void VGA_ScrollMap(void);
void VGA_Draw_MapBack(void);
void VGA_Set_Window(void);
void VGA_MoveWindow(void);
void VGA_PanelRefresh(void);
void VGA_LoadPanelBackground(char *file,char* dat_string);
void VGA_RotatePaletteAsync(int index1, int index2);
void VGA_LoadTransImage(char *file,char* dat_string);

// SOUND/SPEAKER.c prototypes
void SPEAKER_Init(void);
void SPEAKER_Deinit(void);
void SPEAKER_PlaySound(byte sound);
void SPEAKER_PlayMusic(void);
void SPEAKER_PlayNonStopMusic(void);
void SPEAKER_PauseMusic(void);
void SPEAKER_StopMusic(void);
void SPEAKER_LoadMusic(byte song);
void SPEAKER_UnloadMusic(void);

// KEYB/KEYB.c prototypes
extern int keys[256];
extern int fp_keys[256];
void Set_key_handler(void);
void Reset_key_handler(void);
void Update_FP_Keys(void);

// MAP/MAP.c prototypes
extern long maxMapSize;
extern word *map_data;
extern byte *map_flip;
extern byte *map_collision;
extern byte *map_hotspot;
extern byte *map_event;
extern byte *map_sprites;
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
extern byte map_loaded;
void LoadMap(char *file, char* dat_string);
void UnloadMap(void);

// SPRITE/SPRITE.c prototypes
extern SPRITE far *sprite;
extern byte spriteStackTable[33];
extern byte far *spriteData1;
extern byte far *spriteData2;
extern dword spriteDataOffset;
extern byte spriteStack;
extern SPRITE loadingAnimation;
extern int spritesProcessed;
word CompileBitmap(word logical_width, unsigned char *bitmap, unsigned char *output);
void ResetSpriteStack(void);
void UnloadSprite(int sprite_number);

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
void LoadTransImage_PCX(char* filename, char* dat_string);
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

// HORMONA.C prototypes
extern byte PlayerAnimation[];
extern byte PlayerFaceAnimation[];
extern byte JessyAnimation[];
extern byte BirdAnimation[];
extern byte DirectorAnimation[];
extern byte CharacterAnimation2[];
extern byte CharacterAnimation3[];
extern byte EnterAnimation[];
extern byte end_game;
extern byte time_countdown;
extern byte time_minutes;
extern byte time_seconds;

// All day events
void far Events(byte event);
void far Hotspots(byte hotspot);
void far GoToFloor1(int x, int y);
void far GoToFloor2(int x, int y);
void far GoToExt1(int x, int y);
void far GoToExt2(int x, int y);
void far GoToGym(int x, int y);
void far GoToEnd(void);
void far GoToExam(void);
void far InitDay(void);
void far SetNewTime(byte newTime);
void far UpdateGoodness(int value);
void far UpdateInteligence(int value);
void far UpdatePopularity(int value);

// Intro.c
void Intro(void);

// EndGame.c
void far EndGameExtinguisher(void);
void far EndGameRoof(void);

// Janitor.c
void far Janitor(void);

// Director.c
void far Director(void);

// Thugs.c
void far Thugs(void);

// Nerds.c
void far Nerds(void);

// Girls.c
void far Girls(void);

// Sensei.c
void far Sensei(void);

void SetItem(int pos, int spriteNum, char* itemImg);
void ResetItem(int pos, int spriteNum);


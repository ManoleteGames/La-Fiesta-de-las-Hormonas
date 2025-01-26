/***********************
*  Engine functions
************************/

#include "source\engine\engine.h"

unsigned char far *error1;
unsigned char far *error2;
unsigned char far *string;
//byte debug;
//int debug1,debug2,debug3,debug4,debug5;

int scrollCameraFloat = 0;
int scrollCameraArray[135] = {
	0,1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

int scrollCameraSpeed[72] = {
	0,0,0,0,0,0,0,0,
	1,0,0,0,1,0,0,0,
	1,0,1,0,1,0,1,0,
	1,1,1,0,1,1,1,0,
	1,1,1,1,1,1,1,1,
	2,1,1,1,2,1,1,1,
	2,1,2,1,2,1,2,1,
	2,2,2,1,2,2,2,1,
	2,2,2,2,2,2,2,2,
};

byte videoVGA_Present = 0;
byte videoEGA_Present = 0;
byte videoCGA_Present = 0;
byte graphicsModeActive = 0;

byte video_mode = 0;	//0-undef; 1-vga; 2-ega; 3-cga; 4-tandy
byte audio_mode = 0;	//0-undef; 1-Speaker; 2-tandy; 3-adlib; 4-sound blaster
byte sound_volume = 0; // 0..100
byte music_volume = 0; // 0..100
byte language = 0;	//1-spanish; 2-english

byte pcspeakerPresent = 0;
byte soundTandyPresent = 0;
byte adlibPresent = 0;
byte soundBlasterPresent = 0;

byte soundPlaying = 0;
byte musicPlaying = 0;
byte musicNonStopPlaying = 0;
byte musicLoaded = 0;

byte time_countdown = 0;
byte time_done = 0;
byte time_minutes = 0;
byte time_seconds = 0;
int time_counter = 0;

byte *tempdata1; //Temp storage of non tiled data. and also sound samples (1/2)
byte *tempdata2; //Temp storage of non tiled data. and also sound samples (2/2)

// 0..208 >> Image and tile color
// 209..252 >> Sprite colors
// 252..255 >> Font color
byte far palette[256*3];

IMFsong far music;	// One song in ram stored at "music"
PLAYER far player;

// Video memory mapping
word vram_LogicalWidth; // screen logical with on bytes in vram
word vram_Font; // Font address in VRAM
word vram_FontS; // Font address in VRAM
word vram_Tiles; // Tiles address in VRAM
word vram_SpritesBack; // Sprites background address in VRAM

// Scrolling variables
int scroll_x = 0;   // Scroll X
int scroll_y = 0;  // Scroll Y
int scroll_x_adjust = 150;
int scroll_y_adjust = 70;
int scroll_wy = 400;
byte showPanel = 0;
byte panelScrolling = 0;
byte scrolling_enabled = 0; // Scrolling and panning enabled

unsigned char far *data;

byte speech_active = 0;

// Old time handler
void interrupt (*old_time_handler)(void);
void interrupt Time_handler(void){
	asm CLI

   if(time_countdown){
   	time_counter ++;
   	if(time_counter>20){
   		time_counter = 0;

      	if((time_seconds == 0) && (time_minutes > 0)){
            time_minutes--;
            time_seconds = 59;
         }
         else if(time_seconds > 0){
          	time_seconds--;
         }
   	}
   }

   // Acknowledge interrupt
	asm mov al,020h
	//asm mov dx,020h
	asm out 020h, al	//Send 0x20 to 0x20 port (end of interrupt)

	asm STI
}
//Loading transition interrupt
void interrupt (*old_loading_handler)(void);
void interrupt LoadingTransition_handler(void){
	asm CLI

   // Rotate palette colors 243-->249
   RotatePaletteAsync(243, 249);

   // Acknowledge interrupt
	asm mov al,020h
	//asm mov dx,020h
	asm out 020h, al	//Send 0x20 to 0x20 port (end of interrupt)

	asm STI
}



/////////////////////////////////////////////////////////
// Music functions
// - Pointers to the specific sound card functions
/////////////////////////////////////////////////////////
void (*LoadMusic)(byte song);
void (*UnloadMusic)(void);
void (*PlayMusic)(void);
void (*PlayNonStopMusic)(void);
void (*PauseMusic)(void);
void (*StopMusic)(void);
void (*InitSoundCard)(void);
void (*DeInitSoundCard)(void);
void (*PlaySound)(byte sound);

/////////////////////////////////////////////////////////
// Video functions
// - Pointers to the specific video card functions
/////////////////////////////////////////////////////////
void (*Vsync)(void);
void (*InitVideoCard)(void);
void (*TextMode)(void);
void (*Fade_in)(void);
void (*Fade_out)(void);
void (*SetPage)(int page);
void (*LoadImage)(char *file,char* dat_string, word page);
void (*LoadTransImage)(char *file,char* dat_string);
void (*HardwareScrolling)(void);
void (*RotatePalette)(int index1, int index2, int speed);
void (*RotatePaletteAsync)(int index1, int index2);
void (*LoadFont)(char *file, char *dat_string);
void (*LoadTiles)(char *file,char* dat_string);
void (*Draw_EmptyBox)(word x, word y, byte w, byte h);
void (*PrintText)(word x, word y, word lineLength, unsigned char *string,byte color);
void (*Draw_Sprites)(void);
void (*Restore_Sprites)(void);
void (*DrawSpriteDestructive)(int sprNum);
void (*SetPalette)(unsigned char *pal);
void (*LoadTiles)(char *file,char* dat_string);
void (*SetMap)(int x, int y);
void (*ScrollMap)(void);
void (*PanelRefresh)(void);
void (*LoadPanelBackground)(char *file,char* dat_string);
void (*DrawMapBack)(void);
void (*PanelUpdate)(void);

/////////////////////////////////////////////////////////
// Dummy function
/////////////////////////////////////////////////////////
void Dummy(void){
}

/////////////////////////////////////////////////////////
// Reset scroll adjustment function
/////////////////////////////////////////////////////////
void ResetScroll(void){
	scroll_x_adjust = 150;
	scroll_y_adjust = 70;
}

/////////////////////////////////////////////////////////
// Check sound card
//0-undef; 1-Speaker; 2-tandy; 3-Adlib; 4-Sound blaster
/////////////////////////////////////////////////////////
void CheckSoundCard(void){
	printf("***** Checking audio hardware... \n");

   // Check if any card is avaliable
   printf(" - PC Speaker is present. He will never let you out \n");
   pcspeakerPresent = 1;
   if( SB_Present() ){ soundBlasterPresent = 1; }
   //if( false ){ soundTandyPresent = 1; }
   if( ADLIB_Present() ){ adlibPresent = 1; }
}

/////////////////////////////////////////////////////////
// Check graphics card
// 0: No card; 1: VGA; 2: EGA; 3:CGA
/////////////////////////////////////////////////////////
void CheckGraphicsCard(void){
   printf("***** Checking video hardware... \n");

   // Check if any card is avaliable
   if( VGA_Present() ) { videoVGA_Present = 1; }
	//if( EGA_Present() ) { videoEGA_Present = 1; }
   //if( CGA_Present() ) { videoCGA_Present = 1; }

   // No compatible video card detected
   if((videoVGA_Present == 0) && (videoEGA_Present == 0) && (videoCGA_Present == 0)){
   	Error("Unable to detect video card",0,0);
      getch();
      exit(1);
   }
}

/////////////////////////////////////////////////////////
// Initialize keyboard
/////////////////////////////////////////////////////////
void InitKeyboard(void){

	printf("***** Inicializando teclado... \n");

   // Set keyboard interrupt
   Set_key_handler();
   printf(" - Teclado inicializado \n");

}

/////////////////////////////////////////////////////////
// Link audio functions to specific device
// 0-undef; 1-Speaker; 2-tandy; 3-adlib; 4-sound blaster
/////////////////////////////////////////////////////////
void LinkAudio(void){

	printf("***** Inicializando sonido... \n");

	switch(audio_mode){
   	case 0: // audio off. Link all functions to pc speaker but never activate buzzer
         printf(" - Audio is off \n");
         InitSoundCard = &SPEAKER_Init;
         DeInitSoundCard = &SPEAKER_Deinit;
			PlaySound = &SPEAKER_PlaySound;
         LoadMusic = SPEAKER_LoadMusic;
         UnloadMusic = SPEAKER_UnloadMusic;
			PlayMusic = SPEAKER_PlayMusic;
         PlayNonStopMusic = SPEAKER_PlayNonStopMusic;
         PauseMusic = SPEAKER_PauseMusic;
         StopMusic = SPEAKER_StopMusic;
   	case 1: // PC Speaker
      	printf(" - Activating PC Speaker sound mode\n");
      	InitSoundCard = &SPEAKER_Init;
         DeInitSoundCard = &SPEAKER_Deinit;
			PlaySound = &SPEAKER_PlaySound;
         LoadMusic = SPEAKER_LoadMusic;
         UnloadMusic = SPEAKER_UnloadMusic;
			PlayMusic = SPEAKER_PlayMusic;
         PlayNonStopMusic = SPEAKER_PlayNonStopMusic;
         StopMusic = SPEAKER_StopMusic;
      	break;
      case 2: // Tandy sound card
      	printf(" - Activating Tandy sound mode\n");
      	break;
      case 3: // Adlib
      	printf(" - Activating Adlib sound mode\n");
      	InitSoundCard = ADLIB_Init;
         DeInitSoundCard = ADLIB_DeInit;
			PlaySound = ADLIB_PlaySound;
         LoadMusic = ADLIB_LoadMusic;
         UnloadMusic = ADLIB_UnloadMusic;
			PlayMusic = ADLIB_PlayMusic;
         PlayNonStopMusic = ADLIB_PlayNonStopMusic;
         StopMusic = ADLIB_StopMusic;
      	break;
      case 4: // Sound blaster
      	printf(" - Activating Sound Blaster sound mode\n");
        	InitSoundCard = SB_Init;
         DeInitSoundCard = SB_DeInit;
			PlaySound = SB_PlaySound;
         LoadMusic = ADLIB_LoadMusic;
         UnloadMusic = ADLIB_UnloadMusic;
			PlayMusic = ADLIB_PlayMusic;
         PlayNonStopMusic = ADLIB_PlayNonStopMusic;
         StopMusic = ADLIB_StopMusic;
      	break;
      default:
      	printf("No sound mode defined\n");
      	break;
	}
}

/////////////////////////////////////////////////////////
// Link video functions to specific device
// 0: No card; 1: VGA; 2: EGA; 3:CGA; 4-TANDY
/////////////////////////////////////////////////////////
void LinkVideo(void){

   printf("***** Inicializando video... \n");

   switch(video_mode){
   	case 1: // Mode VGA :: 320x200 256 colors, Mode X
      	printf(" - Activating VGA mode\n");
			// Link global functions to VGA custom functions
         Vsync = VGA_Vsync;
         TextMode = VGA_TextMode;
         InitVideoCard = VGA_InitVideoCard;

			Fade_in = VGA_Fade_in;
			Fade_out = VGA_Fade_out;

      	LoadImage = VGA_LoadImage;
         LoadTransImage = VGA_LoadTransImage;
         LoadTiles = VGA_LoadTiles;
         LoadFont = VGA_LoadFont;

         HardwareScrolling = VGA_HardwareScrolling;
         SetPage = VGA_SetPage;
         RotatePalette = VGA_RotatePalette;
         RotatePaletteAsync = VGA_RotatePaletteAsync;

         Draw_EmptyBox = VGA_Draw_EmptyBox;
         PrintText = VGA_PrintText;
         Draw_Sprites = VGA_Draw_Sprites;
         Restore_Sprites = VGA_Restore_Sprites;
         DrawSpriteDestructive = VGA_DrawSpriteDestructive;
         SetPalette = VGA_SetPalette;

         SetMap = VGA_SetMap;
         ScrollMap = VGA_ScrollMap;
         PanelRefresh = VGA_PanelRefresh;
         LoadPanelBackground = VGA_LoadPanelBackground;

         DrawMapBack = VGA_Draw_MapBack;
         PanelUpdate = VGA_PanelUpdate;

      	break;
      case 2:
      	printf(" - Activating EGA mode\n");
			// Link global functions to EGA custom functions
         //Vsync = EGA_Vsync;
      	printf("EGA mode not implemented yet!\n");
         getch();
      	exit(1);
      	break;
      case 3:
      	printf(" - Activating CGA mode\n");
			// Link global functions to CGA custom functions
         //Vsync = CGA_Vsync;
        	printf("CGA mode not implemented yet!\n");
         getch();
      	exit(1);
      	break;
      case 4:
      	printf(" - Activating TANDY mode\n");
			// Link global functions to TANDY custom functions
         //Vsync = Vsync_TANDY;
        	printf("Tandy mode not implemented yet!\n");
         getch();
      	exit(1);
      	break;
      default:
			printf("unknown video mode not implemented yet!\n");
         getch();
      	exit(1);
   }

}

/////////////////////////////////////////////////////////
// Delay
/////////////////////////////////////////////////////////
void Delay(int count){
   int waitcounter = 0;
	while(waitcounter < count)
   {
   	waitcounter++;
      Update(0);
   }
}

/////////////////////////////////////////////////////////
// Save configuration
/////////////////////////////////////////////////////////
void SaveConfig(void){
   FILE *setupfile;
   setupfile = fopen("setup.ini","w");
   if (!setupfile) { Error("Cannot update configuration file SETUP.INI",0,0); }
   fprintf(setupfile,"#SETUP\n------\n[1]VIDEO=%03u\n[2]AUDIO=%03u\n[3]MUSVL=%03u\n[4]SNDVL=%03u\n[5]BLASA=%03x\n[6]BLASI=%03x\n[7]BLSLD=%03x\n[8]BLSHD=%03x\n[9]LANG =%03x",video_mode,audio_mode,music_volume,sound_volume,sbBaseAddress,sbIrq,sbLoDMA,sbHiDMA,language);
	fclose(setupfile);
}

/////////////////////////////////////////////////////////
// Load configuration
/////////////////////////////////////////////////////////
void LoadConfig(void){
	FILE *setupfile;
	byte buffer[256];

	printf("***** Cargando configuracion...\n");
   setupfile = fopen("setup.ini","rb+");
   if (!setupfile) {
		printf(" - setup.ini no encontrado\n - Creando nuevo archivo con la configuracion básica...\n");
		setupfile = fopen("setup.ini","w");
      if (!setupfile) { Error("Cannot create configuration file SETUP.INI",0,0); }
		fprintf(setupfile,"#SETUP\n------\n[1]VIDEO=%03u\n[2]AUDIO=%03u\n[3]MUSVL=050\n[4]SNDVL=050\n[5]BLASA=%03x\n[6]BLASI=%03x\n[7]BLSLD=%03x\n[8]BLSHD=%03x\n[9]LANG =001",1,1,0,0,0,0);
   	//fclose(setupfile);
		//sleep(2);
	}

	fread(buffer,1,256,setupfile);

   // 0: No card; 1: VGA; 2: EGA; 3:CGA
	video_mode 		= (buffer[25]-48)*100 + (buffer[26]-48)*10 + (buffer[27]-48);
   // 0-undef; 1-Speaker; 2-tandy; 3-Adlib; 4-Sound blaster
	audio_mode 		= (buffer[39]-48)*100 + (buffer[40]-48)*10 + (buffer[41]-48);
   music_volume 	= (buffer[53]-48)*100 + (buffer[54]-48)*10 + (buffer[55]-48);
   sound_volume 	= (buffer[67]-48)*100 + (buffer[68]-48)*10 + (buffer[69]-48);
   sbBaseAddress  = (buffer[81]-48)*100 + (buffer[82]-48)*10 + (buffer[83]-48);
   sbIrq				= (buffer[95]-48)*100 + (buffer[96]-48)*10 + (buffer[97]-48);
   sbLoDMA			= (buffer[109]-48)*100 + (buffer[110]-48)*10 + (buffer[111]-48);
   sbHiDMA			= (buffer[123]-48)*100 + (buffer[124]-48)*10 + (buffer[125]-48);
   language 		= (buffer[137]-48)*100 + (buffer[138]-48)*10 + (buffer[139]-48);

   // Check selected video mode is compatible
   // 0: No card; 1: VGA; 2: EGA; 3:CGA
   switch(video_mode){
   	case 1: // VGA
      	printf(" - VGA is selected\n");
      	if( videoVGA_Present == 0){
         	printf(" - ... but not present \n");
         	if( videoEGA_Present ){
         		printf(" - Applying EGA graphics instead \n");
            	video_mode = 2;
            	printf("EGA video mode is not avaliable yet!\n");
            	getch();
      			exit(1);
         	}
        	 	else if( videoCGA_Present ){
         		printf(" - Applying CGA graphics instead \n");
            	video_mode = 3;
            	printf("CGA video mode is not avaliable yet!\n");
            	getch();
      			exit(1);
         	}
            else{
            	printf("No compatible video card found!\n");
            	getch();
            	exit(1);
            }
         }
      	break;
      case 2: // EGA
      	printf(" - EGA is selected \n");
         if( videoEGA_Present == 0){
         	printf(" - ... but not present \n");
         	if( videoVGA_Present ){
         		printf(" - Applying VGA graphics instead \n");
            	video_mode = 1;
         	}
         	else if( videoCGA_Present ){
         		printf(" - Applying CGA graphics instead \n");
            	video_mode = 3;
            	printf("CGA video mode is not avaliable yet!\n");
            	getch();
      			exit(1);
         	}
            else{
            	printf("No compatible video card found!\n");
            	getch();
            	exit(1);
            }
         }
      	break;
      case 3: // CGA
      	printf(" - CGA is selected \n");
         if( videoCGA_Present == 0){
         	printf(" - ... but not present \n");
         	if( videoVGA_Present ){
         		printf(" - Applying VGA graphics instead \n");
            	video_mode = 1;
         	}
         	else if( videoEGA_Present ){
         		printf(" - Applying EGA graphics instead \n");
            	video_mode = 2;
            	printf("EGA video mode is not avaliable yet!\n");
            	getch();
      			exit(1);
         	}
            else{
            	printf("No compatible video card found!\n");
            	getch();
            	exit(1);
            }
         }
      	break;
   }

   // Check selected audio mode is compatible
   // 0-undef; 1-Speaker; 2-tandy; 3-Adlib; 4-Sound blaster
   switch(audio_mode){
   	case 0: // OFF
      	printf(" - Audio OFF is selected\n");
         break;
   	case 1: // Speaker
         printf(" - PC Speaker is selected \n");
      	break;
      case 2: // Tandy
      	printf(" - Tandy audio is selected \n");
         if( soundTandyPresent == 0){
         	printf(" - ... but not present \n");
         	printf(" - Applying PC Speaker audio instead \n");
         	audio_mode = 1;
         }
      	break;
      case 3: // Adlib
      	printf(" - Adlib audio is selected \n");
         if( adlibPresent == 0){
         	printf(" - ...but not present \n");
         	printf(" - Applying PC Speaker audio instead \n");
         	audio_mode = 1;
         }
      	break;
      case 4: // Sound blaster
      	printf(" - Sound blaster audio is selected \n");
         if( soundBlasterPresent == 0){
         	printf(" - ...but not present \n");
         	printf(" - Applying PC Speaker audio instead \n");
         	audio_mode = 1;
         }
      	break;
   }

   printf(" - Configuracion cargada \n");
   fclose(setupfile);
}

/////////////////////////////////////////////////////////
// Exit to dos function
/////////////////////////////////////////////////////////
void ExitDOS(void){

	if(graphicsModeActive){ TextMode(); } // Get back to text mode

	StopMusic();

	outportb(0x43, 0x36);
	outportb(0x40, 0xFF);	//lo-byte
	outportb(0x40, 0xFF);	//hi-byte

   Reset_key_handler();

   // Unload and release music data
	UnloadMusic();

   DeInitSoundCard();
	//UnloadTileset();
	UnloadMap();
   UnloadSprites();

   if(error1){ farfree(error1); }
   if(error2){ farfree(error2); }
   if(string){ farfree(string); }
   if(tempdata1){ farfree(tempdata1); }
   if(tempdata2){ farfree(tempdata2); }
   if(music.sdata){ farfree(music.sdata); }
   if(map_data ){ farfree(map_data); }
   if(map_flip ){ farfree(map_flip); }
   if(map_collision ){ farfree(map_collision); }
   if(map_hotspot ){ farfree(map_hotspot); }
   if(map_event ){ farfree(map_event); }
   if(map_sprites ){ farfree(map_sprites); }
   if(sprite ){ farfree(sprite); }

   printf("bye byte...");
	exit(1);
}

/////////////////////////////////////////////////////////
// Restart program
/////////////////////////////////////////////////////////
void RestartProgram(void){
	if(graphicsModeActive){ TextMode(); } // Get back to text mode

	StopMusic();

	outportb(0x43, 0x36);
	outportb(0x40, 0xFF);	//lo-byte
	outportb(0x40, 0xFF);	//hi-byte

   Reset_key_handler();

   // Unload and release music data
	UnloadMusic();

   DeInitSoundCard();
	//UnloadTileset();
	UnloadMap();
   UnloadSprites();

   if(error1){ farfree(error1); }
   if(error2){ farfree(error2); }
   if(string){ farfree(string); }
   if(tempdata1){ farfree(tempdata1); }
   if(tempdata2){ farfree(tempdata2); }
   if(music.sdata){ farfree(music.sdata); }
   if(map_data ){ farfree(map_data); }
   if(map_flip ){ farfree(map_flip); }
   if(map_collision ){ farfree(map_collision); }
   if(map_hotspot ){ farfree(map_hotspot); }
   if(map_event ){ farfree(map_event); }
   if(map_sprites ){ farfree(map_sprites); }
   if(sprite ){ farfree(sprite); }

   InitEngine();
}

/////////////////////////////////////////////////////////
// Error function
// - This function must be triggered once on graphics mode
/////////////////////////////////////////////////////////
void Error(char *error, char *file, char *filename){
	asm STI; //enable interrupts
   if(graphicsModeActive){
   	TextMode();
      printf("Back to text mode\n");
   } // Get back to text mode
   printf("%s %s >> %s \n",error,file,filename);
	sleep(5);
	ExitDOS();
}

/////////////////////////////////////////////////////////
// Allocating engine memory
//
//  - 64kb Temp Data (Load Tilesets, Load Sprites)
//  - 64kb Music
//  - 64kb Map
//  - 16kb collision map
//  - ?Kb for sprites structures
//  - 64Kb for sprites data
//  - 10kb for sprite table
//  - Asume EXE file around 96KB
//  - Add 16 Kb of used defined data (palette tables...)
//  - Then we need around 400 Kb of Free Ram to run the engine
//
//  ** Sprites, fonts and tiles are allocated on UMA, not on conventional RAM
//  ** See memory distribution for each video mode
/////////////////////////////////////////////////////////
void AllocateEngineMem(void){

	printf("***** Allocating memory ...\n");

   //Allocate error strings
   if ((error1 = farcalloc(30, sizeof(unsigned char))) == NULL) Error("Not enough RAM to allocate 30 bytes of error1 string","error1",0);
 	printf(" error1 allocated onto adddress: %p address \n", error1);
   if ((error2 = farcalloc(30, sizeof(unsigned char))) == NULL) Error("Not enough RAM to allocate 30 bytes of error2 string","error2",0);
   printf(" error2 allocated onto adddress: %p address \n", error2);
   if ((string = farcalloc(40, sizeof(unsigned char))) == NULL) Error("Not enough RAM to allocate 50 bytes of global string","string",0);
   printf(" string allocated onto adddress: %p address \n", string);

   //Allocate 32KB block for temp data
   if ((tempdata1 = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of temp. data","tempdata1",0);
   printf(" tempdata1 allocated onto adddress: %p address \n", tempdata1);
   //Allocate 32 KB of temp data just after the first
   if ((tempdata2 = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of temp. data","tempdata2",0);
   printf(" tempdata2 allocated onto adddress: %p address \n", tempdata2);

	if ((music.sdata = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 64 Kb of music data","music","sdata");
   printf(" music.sdata allocated onto adddress: %p address \n", music.sdata);
   if ((map_data = farcalloc(maxMapSize,sizeof(byte))) == NULL) Error("Not enough RAM to allocate map data","map","data");
   printf(" map_data allocated onto adddress: %p address \n", map_data);
	if ((map_collision = farcalloc(maxMapSize,sizeof(byte))) == NULL) Error("Not enough RAM to allocate collision data","map","collision");
   printf(" map_collision allocated onto adddress: %p address \n", map_collision);
   if ((map_hotspot = farcalloc(maxMapSize,sizeof(byte))) == NULL) Error("Not enough RAM to allocate hotspot data","map","hotspot");
   printf(" map_hotspot allocated onto adddress: %p address \n", map_hotspot);
   if ((map_event = farcalloc(maxMapSize,sizeof(byte))) == NULL) Error("Not enough RAM to allocate event data","map","event");
   printf(" map_event allocated onto adddress: %p address \n", map_event);
   if ((map_sprites = farcalloc(maxMapSize,sizeof(byte))) == NULL) Error("Not enough RAM to allocate event data","map","sprites");
   printf(" map_sprites allocated onto adddress: %p address \n", map_event);
   if ((sprite = farcalloc(20,sizeof(SPRITE))) == NULL) Error("Not enough RAM to allocate 20 predefined sprite structs","sprite",0);
   printf(" sprite allocated onto adddress: %p address \n", sprite);

   printf(" - Memory allocated successfuly \n");
   //getchar();
}

/////////////////////////////////////////////////////////
// Initialize engine
/////////////////////////////////////////////////////////
void InitEngine(void){

	printf("*** Starting engine ****** \n");

   CheckGraphicsCard();
   CheckSoundCard();

   LoadConfig();
   LinkVideo();
   LinkAudio();

   AllocateEngineMem();

   InitKeyboard();

   InitSoundCard();
   InitVideoCard();
   graphicsModeActive = 1;

}

void SetTimeInterrupt(void){

	asm mov al, 0B6h     // Initialize PIT (programable interval timer)
   asm out 43h,al

    //set timer
   asm mov al,0x36  // 0b0011 0110 >> Channel 0, lobyte/hibyte, Mode 3 (square wave), 16bit binary
   asm out PTI_MODE,al
   //unsigned long spd = 1193182/60;= 19886;
   asm mov al,255 //spd lo-byte
   asm out PTI_CH0,al
   asm mov al,255 //spd  hi-byte
   asm out PTI_CH0,al

   // Save old IRQ, usualy the sound interrupt function
   old_time_handler = getvect(TIMER_IRQ); // Save old IRQ

	//set interrupt handler
	setvect(TIMER_IRQ, Time_handler);		//interrupt 1C not available on NEC 9800-series PCs.
}

/////////////////////////////////////////////////////////
// Reset loading transition interrupt (public)
/////////////////////////////////////////////////////////
void ResetTimeInterrupt(void){

	asm CLI

	// do not reset timer
   //outportb(PTI_MODE, 0x36);
  	//outportb(PTI_CH2, 0xFF);	//lo-byte
	//outportb(PTI_CH2, 0xFF);	//hi-byte

    // Restore old handler, normaly the sound interrupt function
	setvect(TIMER_IRQ, old_time_handler);

	asm STI
}


/////////////////////////////////////////////////////////
// Set loading transition interrupt (public)
// - sets an animation on the page 1, meanwhile images
//   can be loaded on other pages.
/////////////////////////////////////////////////////////
void SetLoadingInterrupt(void){
	Fade_out();

   SPEAKER_PauseMusic();
   UnloadSprites();
   UnloadMap();

   LoadTransImage("images.DAT","loading.pcx");
   SetPage(1);
   Fade_in();
   scrolling_enabled = 0;

	Vsync();  //Wait Vsync

	asm CLI

	//set timer on programable internal time interrupt
   // -   Bits         Usage
	//   6 and 7      Select channel :
   //		             0 0 = Channel 0
   //		             0 1 = Channel 1
   //		             1 0 = Channel 2
   //		             1 1 = Read-back command (8254 only)
	//	  4 and 5      Access mode :
   //		             0 0 = Latch count value command
   //		             0 1 = Access mode: lobyte only
   //		             1 0 = Access mode: hibyte only
   //		             1 1 = Access mode: lobyte/hibyte
	//		1 to 3       Operating mode :
   //		             0 0 0 = Mode 0 (interrupt on terminal count)
   //		             0 0 1 = Mode 1 (hardware re-triggerable one-shot)
   //		             0 1 0 = Mode 2 (rate generator)
   //		             0 1 1 = Mode 3 (square wave generator)
   //		             1 0 0 = Mode 4 (software triggered strobe)
   //		             1 0 1 = Mode 5 (hardware triggered strobe)
   //		             1 1 0 = Mode 2 (rate generator, same as 010b)
   //		             1 1 1 = Mode 3 (square wave generator, same as 011b)
	//		0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD

   asm mov al, 0B6h     // Initialize PIT (programable interval timer)
   asm out 43h,al

    //set timer
   asm mov al,0x36  // 0b0011 0110 >> Channel 0, lobyte/hibyte, Mode 3 (square wave), 16bit binary
   asm out PTI_MODE,al
   //unsigned long spd = 1193182/60;= 19886;
   asm mov al,255 //spd lo-byte
   asm out PTI_CH0,al
   asm mov al,255 //spd  hi-byte
   asm out PTI_CH0,al

   // Save old IRQ, usualy the sound interrupt function
   old_loading_handler = getvect(TIMER_IRQ); // Save old IRQ

	//set interrupt handler
	setvect(TIMER_IRQ, LoadingTransition_handler);		//interrupt 1C not available on NEC 9800-series PCs.

	asm STI
}

/////////////////////////////////////////////////////////
// Reset loading transition interrupt (public)
/////////////////////////////////////////////////////////
void ResetLoadingInterrupt(void){

	asm CLI

	// do not reset timer
   //outportb(PTI_MODE, 0x36);
  	//outportb(PTI_CH2, 0xFF);	//lo-byte
	//outportb(PTI_CH2, 0xFF);	//hi-byte

    // Restore old handler, normaly the sound interrupt function
	setvect(TIMER_IRQ, old_loading_handler);

   // Continue playing music from the same point it was
   SPEAKER_PlayNonStopMusic();

	asm STI

	Fade_out();
}

/////////////////////////////////////////////////////////
// Scroll follows a sprite
//  - arg 0: sprite number
/////////////////////////////////////////////////////////
void ScrollFollow(void){
	SPRITE *s = &sprite[player.spriteNum];
	int x;
	int x1;
	int y;
	int y1;
	int speed_x = 0;
	int speed_y = 0;

   //if ((player.move == 0) && (scroll_y_adjust > 70)){ scroll_y_adjust--; }//STANDING
   //if ((player.move == 0) && (scroll_y_adjust < 70)){ scroll_y_adjust++; }//STANDING
   if ((player.move == 1) && (scroll_y_adjust != 90)){ scroll_y_adjust++; }//FACING UP
	if ((player.move == 2) && (scroll_y_adjust != 50)){ scroll_y_adjust--; }//FACING DOWN

	if ((player.move == 3) && (scroll_x_adjust != 190)){ scroll_x_adjust++; }//FACING LEFT
	if ((player.move == 4) && (scroll_x_adjust != 130)){ scroll_x_adjust--; }//FACING RIGHT

   if (player.move == 5){
   	if ((scroll_y_adjust != 90)){ scroll_y_adjust++; }//FACING UP
    	if ((scroll_x_adjust != 130)){ scroll_x_adjust--; }//FACING RIGHT
   }

   if (player.move == 6){
   	if ((scroll_y_adjust != 90)){ scroll_y_adjust++; }//FACING UP
    	if ((scroll_x_adjust != 190)){ scroll_x_adjust++; }//FACING LEFT
   }

   if (player.move == 7){
   	if ((scroll_y_adjust != 50)){ scroll_y_adjust--; }//FACING DOWN
    	if ((scroll_x_adjust != 130)){ scroll_x_adjust--; }//FACING RIGHT
   }

   if (player.move == 8){
   	if ((scroll_y_adjust != 50)){ scroll_y_adjust--; }//FACING DOWN
    	if ((scroll_x_adjust != 190)){ scroll_x_adjust++; }//FACING LEFT
   }



	//Show more screen in the direction the sprite is facing
	x = (s->pos_x-scroll_x) - scroll_x_adjust;
	x1 = abs(x);
   y = (s->pos_y-scroll_y) - scroll_y_adjust;
	y1 = abs(y);

   // If scroll is inside limits
	if ((scroll_x > -1) && ((scroll_x + 319)<map_width_px) && (scroll_y > -1) && ((scroll_y + 209 - vga_page[1])<(map_height_px))){

   	// Reset scroll camera
		if (scrollCameraFloat == 8) scrollCameraFloat = 0;

      // Calculate scroll speed
		speed_x = scrollCameraSpeed[(scrollCameraArray[x1]<<3)+scrollCameraFloat];
		speed_y = scrollCameraSpeed[(scrollCameraArray[y1]<<3)+scrollCameraFloat];

		if (x < 0) scroll_x-=speed_x;
		if (x > 0) scroll_x+=speed_x;
		if (y < 0) scroll_y-=speed_y;
		if (y > 0) scroll_y+=speed_y;

		scrollCameraFloat++;
	}

   // Lock scroll on map limits
	if (scroll_x < 0) scroll_x = 0;
	if ((scroll_x + 320) > map_width_px) scroll_x = map_width_px - 320;
	if (scroll_y < 64) scroll_y = 64;
	if ((scroll_y + 210 - vga_page[1]) > (map_height_px)) scroll_y = map_height_px - 210 + vga_page[1] ;  // it was 201 before
}

/////////////////////////////////////////////////////////
// Update system
/////////////////////////////////////////////////////////
void Update(int player_follow){

	HardwareScrolling();
	if (player_follow) ScrollFollow();
   if (speech_active == 0) Restore_Sprites();
	if (scrolling_enabled) ScrollMap();
   if (speech_active == 0) Draw_Sprites();
   PanelRefresh();
   Update_FP_Keys();
}

/////////////////////////////////////////////////////////
// Move player
// - Move player on the screen
/////////////////////////////////////////////////////////
void MovePlayer(void){
	SPRITE *s = &sprite[player.spriteNum];
	byte half = s->width>>1;

   // Sprite tiles
   //long tile_number = 0;
   int tile_number = 0;

   // Collision flags
   byte left_coll = 0;
   byte right_coll = 0;
   byte up_coll = 0;
   byte down_coll = 0;

  	//GET TILE POS (middle of the sprite)
	s->tile_x = (s->pos_x + half)>>4;
	s->tile_y = (s->pos_y + half - 64)>>4;
   player.tile_x = s->tile_x;
   player.tile_y = s->tile_y;

	// Player state
	player.move = 0;
	player.state = 0;

   // Player movement
  	if( (keys[K_UP] == 1)	&& (keys[K_LEFT] == 0) 	&& (keys[K_RIGHT] == 0)){ player.move = P_UP; }
   if( (keys[K_DOWN] == 1) && (keys[K_LEFT] == 0) 	&& (keys[K_RIGHT] == 0)){ player.move = P_DOWN; }
   if( (keys[K_LEFT] == 1) && (keys[K_UP] == 0) 	&& (keys[K_DOWN] == 0)) { player.move = P_LEFT; }
   if( (keys[K_RIGHT] == 1)&& (keys[K_UP] == 0) 	&& (keys[K_DOWN] == 0)) { player.move = P_RIGHT; }
   if( (keys[K_UP] == 1) 	&& (keys[K_RIGHT] == 1) && (keys[K_LEFT] == 0)) { player.move = P_UPRIGHT; }
   if( (keys[K_UP] == 1) 	&& (keys[K_RIGHT] == 0) && (keys[K_LEFT] == 1)) { player.move = P_UPLEFT; }
   if( (keys[K_DOWN] == 1) && (keys[K_RIGHT] == 1) && (keys[K_LEFT] == 0)) { player.move = P_DWNRIGHT; }
   if( (keys[K_DOWN] == 1) && (keys[K_RIGHT] == 0) && (keys[K_LEFT] == 1)) { player.move = P_DWNLEFT; }


   // Reset collision flags
   left_coll = 0;
   right_coll = 0;
   up_coll = 0;
   down_coll = 0;
   player.event = 0;
   player.hotspot = 0;
   player.collision = 0;

    // Up colision
   if( (s->tile_y) <= 0){ up_coll = 1; player.collision = 99; }
   // Left colision
	if( (s->tile_x) <= 0){ left_coll = 1; player.collision = 99;  }
	// Right colision
	if( (s->tile_x) >= map_width ){ right_coll = 1; player.collision = 99;  }
   // Down colision
	if( (s->tile_y) >= map_height ){ down_coll = 1; player.collision = 99;  }

   // Check map collisions
   //if( (player.move == P_DWNLEFT) || (player.move == P_UPLEFT) || (player.move == P_LEFT) ){
   if( (player.move == 8) || (player.move == 6) || (player.move == 3) ){
  	   tile_number = ( ((s->pos_y + 4 - 64)>>4)* map_width ) +  s->tile_x - 1;
   	if(map_collision[tile_number]  != 0) {  left_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  left_coll = 1; player.collision = map_sprites[tile_number]+10;  }
      tile_number = ( ((s->pos_y + s->height - 4 - 64)>>4)* map_width) +  s->tile_x - 1;
     	if(map_collision[tile_number]  != 0) {  left_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  left_coll = 1; player.collision = map_sprites[tile_number]+10; }
   }
   //if( (player.move == P_UPRIGHT) || (player.move == P_UPLEFT) || (layer.move == P_UP) ){
   if( (player.move == 5) || (player.move == 6) || (player.move == 1) ){
      tile_number = ((s->tile_y-1) * map_width ) +  ((s->pos_x + 4)>>4);
   	if(map_collision[tile_number]  != 0) {  up_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  up_coll = 1; player.collision = map_sprites[tile_number]+10; }
      tile_number = ((s->tile_y-1) * map_width ) +  ((s->pos_x + s->width - 4)>>4);
     	if(map_collision[tile_number]  != 0) {  up_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  up_coll = 1; player.collision = map_sprites[tile_number]+10; }
   }
   //if( (player.move == P_UPRIGHT) || (player.move == P_DWNRIGHT) || (player.move == P_RIGHT) ){
   if( (player.move == 5) || (player.move == 7) || (player.move == 4) ){
      tile_number = ( ((s->pos_y + 4 - 64)>>4)* map_width ) +  s->tile_x + 1;
   	if(map_collision[tile_number]  != 0) {  right_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  right_coll = 1; player.collision = map_sprites[tile_number]+10; }
      tile_number = ( ((s->pos_y + s->height - 4 - 64)>>4)* map_width) +  s->tile_x + 1;
     	if(map_collision[tile_number]  != 0) {  right_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  right_coll = 1; player.collision = map_sprites[tile_number]+10; }
   }
   //if( (player.move == P_DWNLEFT) || (player.move == P_DWNRIGHT) || (player.move == P_DOWN) ){
   if( (player.move == 8) || (player.move == 7) || (player.move == 2) ){
      tile_number = ((s->tile_y+1) * map_width ) +  ((s->pos_x + 4)>>4);
   	if(map_collision[tile_number]  != 0) {  down_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  down_coll = 1; player.collision = map_sprites[tile_number]+10; }
      tile_number = ((s->tile_y+1) * map_width ) +  ((s->pos_x + s->width - 4)>>4);
     	if(map_collision[tile_number]  != 0) {  down_coll = 1; player.collision = map_collision[tile_number]; }
      if(map_sprites[tile_number]  != 0) {  down_coll = 1; player.collision = map_sprites[tile_number]+10; }
   }

   // Player movement
  	//if( (player.move == P_UP) || (player.move == P_UPRIGHT) || (player.move == P_UPLEFT) ){
   if( (player.move == 1) || (player.move == 5) || (player.move == 6) ){
   	if(up_coll == 0) s->pos_y--;
   }
   //if( (player.move == P_DOWN) || (player.move == P_DWNRIGHT) || (player.move == P_DWNLEFT) ) {
   if( (player.move == 2) || (player.move == 7) || (player.move == 8) ) {
    	if(down_coll == 0) s->pos_y++;
   }
   //if( (player.move == P_LEFT) || (player.move == P_UPLEFT) || (player.move == P_DWNLEFT) ) {
   if( (player.move == 3) || (player.move == 6) || (player.move == 8) ) {
    	if(left_coll == 0) s->pos_x--;
   }
   //if( (player.move == P_RIGHT) || (player.move == P_UPRIGHT) || (player.move == P_DWNRIGHT) ) {
   if( (player.move == 4) || (player.move == 5) || (player.move == 7) ) {
    	if(right_coll == 0) s->pos_x++;
   }

	// Check map events and hotspots
   tile_number = ( ((s->pos_y + 16 - 64)>>4)* map_width ) +  ((s->pos_x + 16)>>4); // Check the middle of the sprite
	player.event = map_event[tile_number];
   player.hotspot = map_hotspot[tile_number];
   player.spriteColl = map_sprites[tile_number];

	//Fixed animations
   if((player.oldMove !=  player.move)&& (s->animate == 1)){
   	switch (player.move){
      	case 1:
         	// Check if it was facing left
            if(player.facingLeft == 1){
            	SetSpriteAnimation(player.spriteNum,21,4,12,PlayerAnimation);  // up left
            }
            else{
               SetSpriteAnimation(player.spriteNum,25,4,12,PlayerAnimation);  // up right
            }
         	break;
         case 2:
         	// Check if it was facing left
            if(player.facingLeft == 1){
         		SetSpriteAnimation(player.spriteNum,13,4,12,PlayerAnimation); // down left
            }
            else{
               SetSpriteAnimation(player.spriteNum,17,4,12,PlayerAnimation); // down right
            }
         	break;
	  		case 3:
            player.facingLeft = 1;
         	SetSpriteAnimation(player.spriteNum,13,4,12,PlayerAnimation);  // left

         	break;
			case 4:
         	player.facingLeft = 0;
         	SetSpriteAnimation(player.spriteNum,17,4,12,PlayerAnimation);  // right
         	break;
         case 5:
         	player.facingLeft = 0;
         	SetSpriteAnimation(player.spriteNum,25,4,12,PlayerAnimation);  // up + right
         	break;
         case 6:
         	player.facingLeft = 1;
         	SetSpriteAnimation(player.spriteNum,21,4,12,PlayerAnimation);  // up + left
         	break;
         case 7:
         	player.facingLeft = 0;
         	SetSpriteAnimation(player.spriteNum,17,4,12,PlayerAnimation);  // down + right
         	break;
         case 8:
         	player.facingLeft = 1;
         	SetSpriteAnimation(player.spriteNum,13,4,12,PlayerAnimation);  // down + left
         	break;
      	default: // Static motion
     	   	s->aframes = 1;
		   	s->anim_counter = 0;
				break;
   	}
   }
   player.oldMove =  player.move;
}

/////////////////////////////////////////////////////////
// Question
// - Exam question function
/////////////////////////////////////////////////////////
int Question(char* filename, char* dat_string, int numQ){
   word length;
   unsigned char line[3];
   byte currentQ = 0;
   byte question[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   byte index = 0;
   byte end = 0;
   byte next = 0;
   byte found = 0;
   byte q1,q2,q3,q4;
   byte r1,r2,r3,r4;
   byte r_ok = 0;
   byte good_option = 0;
   byte option;
   byte second_chance = 0;
   int good_count = 0;

   player.mission_cheat = 100;
   if(player.mission_party == 0){time_minutes = 1;}
   else{time_minutes = 2;}
   time_seconds = 0;
   time_countdown = 1;

   SetTimeInterrupt();

   while((currentQ < numQ)&&((time_minutes > 0)||(time_seconds > 0))){

      option = 1;

      srand(time(NULL));

   	while(!found){
   		index = rand() % 20;
      	if( question[index] == 0 ){
         	found = 1;
            question[index] = 1;
            index = index*10 + 20;  // apply offset
      		q1 = index;
      		q2 = index + 1;
      		q3 = index + 2;
      		q4 = index + 3;
      		r1 = index + 4;
      		r2 = index + 5;
         	r3 = index + 6;
      		r4 = index + 7;
      		r_ok = index + 8;
         }
   	}

      Draw_EmptyBox(0,0,38,8);

      // Question line 1
      sprintf(line, "%03d", q1);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,1,length,string,0);

      // Question line 2
      sprintf(line, "%03d", q2);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,2,length,string,0);

      // Question line 3
      sprintf(line, "%03d", q3);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,3,length,string,0);

      // Question line 4
      sprintf(line, "%03d", q4);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,4,length,string,0);

      // Response a
      sprintf(line, "%03d", r1);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,5,length,string,1);

      // Response b
      sprintf(line, "%03d", r2);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,6,length,string,0);

      // Response c
      sprintf(line, "%03d", r3);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,7,length,string,0);

      // Response d
      sprintf(line, "%03d", r4);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,8,length,string,0);

      // Response OK
      sprintf(line, "%03d", r_ok);
      LoadText(filename,dat_string,&line,string,&length);
      good_option = string[1]-48; // convert to value

      while(( keys[K_ENTER] != 1)&&((time_minutes > 0)||(time_seconds > 0))) {
			//select response
      	if(fp_keys[K_UP]){
   			switch(option){
         		case 1: // Do nothing
            		break;
            	case 2: // Rewrite old and new option
               	sprintf(line, "%03d", r2);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,6,length,string,0);
	            	option--; // Change option
                  sprintf(line, "%03d", r1);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,5,length,string,1);
				  		break;
            	case 3: // Rewrite old and new option
               	sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,7,length,string,0);
	            	option--; // Change option
                  sprintf(line, "%03d", r2);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,6,length,string,1);
				  		break;
            	case 4: // Rewrite old and new option
               	sprintf(line, "%03d", r4);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,8,length,string,0);
	            	option--; // Change option
                  sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,7,length,string,1);
				  		break;
         	}
      	}

      	if(fp_keys[K_DOWN]){
      		switch(option){
         		case 1: // Rewrite old and new option
            		sprintf(line, "%03d", r1);
            		LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,5,length,string,0);
      	      	option++;
               	sprintf(line, "%03d", r2);
         	   	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,6,length,string,1);
               	break;
            	case 2: // Rewrite old and new option
            		sprintf(line, "%03d", r2);
	            	LoadText(filename,dat_string,line,string,&length);
            		PrintText(1,6,length,string,0);
               	option++;
               	sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
               	PrintText(1,7,length,string,1);
               	break;
            	case 3: // Rewrite old and new option
                  sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
               	PrintText(1,7,length,string,0);
               	option++;
               	sprintf(line, "%03d", r4);
               	LoadText(filename,dat_string,line,string,&length);
               	PrintText(1,8,length,string,1);
                  break;
            	case 4: // Do nothing
				  		break;
         	}
      	}
      	if(option < 1){option = 1;}
         if(option > 4){option = 4;}

         // Print remaining time
         sprintf(string, "%02d", time_minutes);
         PrintText(34,22,2,string,1);
         PrintText(36,22,1,":",1);
         sprintf(string, "%02d", time_seconds);
         PrintText(37,22,2,string,1);

      	Update(0);
   	}

      if((time_minutes > 0)||(time_seconds > 0)) {
      	if(option == good_option){
        		currentQ++;
         	good_count++;
     			found = 0;
        		second_chance = 0;
      	} else {
      		// if cheater
      		if(player.mission_cheat > 99) {
      			if((option != good_option) && (second_chance == 0)) {

            		second_chance = 1;

         			// Clear screen
         			Draw_EmptyBox(0,0,38,8);

            		sprintf(line, "%03d", 10);
           			LoadText(filename,dat_string,&line,string,&length);
   					PrintText(1,1,length,string,0);

            		sprintf(line, "%03d", 11);
            		LoadText(filename,dat_string,&line,string,&length);
   					PrintText(1,3,length,string,0);

               	sprintf(line, "%03d", 12);
            		LoadText(filename,dat_string,&line,string,&length);
   					PrintText(1,4,length,string,0);

            		sprintf(line, "%03d", 13);
            		LoadText(filename,dat_string,&line,string,&length);
   					PrintText(1,5,length,string,0);

               	sprintf(line, "%03d", 14);
            		LoadText(filename,dat_string,&line,string,&length);
   					PrintText(1,6,length,string,0);

                  while( keys[K_ENTER] != 1) {
							// Print remaining time
         				sprintf(string, "%02d", time_minutes);
         				PrintText(34,22,2,string,1);
         				PrintText(36,22,1,":",1);
         				sprintf(string, "%02d", time_seconds);
         				PrintText(37,22,2,string,1);

      					Update(0);
   					}
            		while( keys[K_ENTER] == 1) {
							//wait
   					}

            		// Clear screen
         			Draw_EmptyBox(0,0,38,8);

         		}
        	 		else{
         			currentQ++;
     					found = 0;
        				second_chance = 0;
         		}
      		}
      		else
      		{
       			currentQ++;
         		found = 0;
      		}
      	}
      }

   	while( keys[K_ENTER] == 1) {
			//wait

   	}
   }

   ResetTimeInterrupt();

   return good_count;
}

/////////////////////////////////////////////////////////
// Speech
// - Speaking function
/////////////////////////////////////////////////////////
void Speech(char* facefile, char* face,char* filename, char* dat_string,char * line1, char * line2, char * line3, char * line4){
   word length;
   int newscroll_x;
   int newscroll_y;

   LoadSprite("SPRMISC.DAT","enter.pcx",18,16); //Load sprites to one of the fixed structs
   LoadSprite(facefile,face,19, 48); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);
   SetSpriteAnimation(19,0,1,48,PlayerFaceAnimation);

   speech_active = 1;

  	// Recalculate scroll to fit screen on absolute values
  	newscroll_x = (scroll_x>>4)<<4;
  	newscroll_y = (scroll_y>>4)<<4;

   while( (newscroll_x != scroll_x) || (newscroll_y != scroll_y) ){
      if(scroll_x < newscroll_x){scroll_x++;}
      if(scroll_x > newscroll_x){scroll_x--;}
		if(scroll_y < newscroll_y){scroll_y++;}
      if(scroll_y > newscroll_y){scroll_y--;}

   	Update(0);
   }

	Draw_EmptyBox(0,0,5,5);
   Draw_EmptyBox(7,0,31,5);

   sprite[19].pos_x = scroll_x + 4;
   sprite[19].pos_y = scroll_y + 4;
   Update(0);

   ShowSprite(19);
   DrawSpriteDestructive(19);

   if(line1 != 0){
   	LoadText(filename,dat_string,line1,string,&length);
   	PrintText(8,1,length,string,0);
   	Delay(20);
   }
   if(line2 != 0){
	   LoadText(filename,dat_string,line2,string,&length);
 		PrintText(8,2,length,string,0);
   	Delay(20);
	}
   if(line3 != 0){
		LoadText(filename,dat_string,line3,string,&length);
   	PrintText(8,3,length,string,0);
	   Delay(20);
   }
   if(line4 != 0){
		LoadText(filename,dat_string,line4,string,&length);
   	PrintText(8,4,length,string,0);
	   Delay(20);
   }

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 34;
   ShowSprite(18);

	while( keys[K_ENTER] != 1) {
  		Update(0);
      DrawSpriteDestructive(18);
   }
   while( keys[K_ENTER] == 1) {
		//wait
      HideSprite(19);
      HideSprite(18);
   }

   UnloadSprite(18);
   UnloadSprite(19);

   speech_active = 0;
   if(map_loaded){ DrawMapBack(); }
}

/////////////////////////////////////////////////////////
// Speech selection
// - Speaking function
/////////////////////////////////////////////////////////
byte SpeechSelection(int optNum, char* facefile, char* face,char* filename, char* dat_string,char * line1, char * line2, char * line3, char * line4){
   word length;
   byte option = 1;
   int newscroll_x;
   int newscroll_y;

   LoadSprite("SPRMISC.DAT","enter.pcx",18,16); //Load sprites to one of the fixed structs
   LoadSprite(facefile,face,19, 48); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);
   SetSpriteAnimation(19,0,1,48,PlayerFaceAnimation);

   speech_active = 1;

     	// Recalculate scroll to fit screen on absolute values
  	newscroll_x = (scroll_x>>4)<<4;
  	newscroll_y = (scroll_y>>4)<<4;

   while( (newscroll_x != scroll_x) || (newscroll_y != scroll_y) ){
      if(scroll_x < newscroll_x){scroll_x++;}
      if(scroll_x > newscroll_x){scroll_x--;}
		if(scroll_y < newscroll_y){scroll_y++;}
      if(scroll_y > newscroll_y){scroll_y--;}

   	Update(0);
   }

	Draw_EmptyBox(0,0,5,5);
   Draw_EmptyBox(7,0,31,5);

   sprite[19].pos_x = scroll_x + 4;
   sprite[19].pos_y = scroll_y + 4;
   Update(0);

   ShowSprite(19);
   DrawSpriteDestructive(19);

   if(line1 != 0){
   	LoadText(filename,dat_string,line1,string,&length);
   	PrintText(8,1,length,string,1);
   }
   if(line2 != 0){
	   LoadText(filename,dat_string,line2,string,&length);
 		PrintText(8,2,length,string,0);
	}
   if(line3 != 0){
		LoadText(filename,dat_string,line3,string,&length);
   	PrintText(8,3,length,string,0);
   }
   if(line4 != 0){
		LoadText(filename,dat_string,line4,string,&length);
   	PrintText(8,4,length,string,0);
   }

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 34;
   ShowSprite(18);

	while( keys[K_ENTER] != 1) {
		//selectopm
      if(fp_keys[K_UP]){
   		switch(option){
         	case 1: // Do nothing
            	break;
            case 2: // Rewrite old and new option
               LoadText(filename,dat_string,line2,string,&length);
   				PrintText(8,2,length,string,0);
	            option--; // Change option
               LoadText(filename,dat_string,line1,string,&length);
   				PrintText(8,1,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
               LoadText(filename,dat_string,line3,string,&length);
   				PrintText(8,3,length,string,0);
	            option--; // Change option
               LoadText(filename,dat_string,line2,string,&length);
   				PrintText(8,2,length,string,1);
				  	break;
            case 4: // Rewrite old and new option
               LoadText(filename,dat_string,line4,string,&length);
   				PrintText(8,4,length,string,0);
	            option--; // Change option
               LoadText(filename,dat_string,line3,string,&length);
   				PrintText(8,3,length,string,1);
				  	break;
         }
      }

      if(fp_keys[K_DOWN]){
      	switch(option){
         	case 1: // Rewrite old and new option
            	if(optNum > 1){
		            LoadText(filename,dat_string,line1,string,&length);
   					PrintText(8,1,length,string,0);
      	         option++;
         	      LoadText(filename,dat_string,line2,string,&length);
   					PrintText(8,2,length,string,1);
               }
               break;
            case 2: // Rewrite old and new option
	            if(optNum > 2){
						LoadText(filename,dat_string,line2,string,&length);
   					PrintText(8,2,length,string,0);
      	         option++;
         	      LoadText(filename,dat_string,line3,string,&length);
   					PrintText(8,3,length,string,1);
               }
               break;
            case 3: // Rewrite old and new option
               if(optNum > 3){
						LoadText(filename,dat_string,line3,string,&length);
   					PrintText(8,3,length,string,0);
      	         option++;
         	      LoadText(filename,dat_string,line4,string,&length);
   					PrintText(8,4,length,string,1);
               }
				  	break;
            case 4: // Do nothing
				  	break;
         }
      }
      if(option < 1){option = 1;}
      if(option > optNum){option = optNum;}

      DrawSpriteDestructive(18);
      Update(0);
   }
   while( keys[K_ENTER] == 1) {
		//wait
      HideSprite(19);
      HideSprite(18);
   }

   vram_SpritesBack -= (sprite[18].width*sprite[18].width)>>1;
   vram_SpritesBack -= (sprite[19].width*sprite[19].width)>>1;
   UnloadSprite(18);
   UnloadSprite(19);


   speech_active = 0;
   if(map_loaded){ DrawMapBack(); }

   return option;
}

/////////////////////////////////////////////////////////
//  Set item
// - Sets item on panel position
/////////////////////////////////////////////////////////
void SetItem(int pos, int spriteNum, char* itemImg){
	// Update panel item
	LoadSprite("SPRMISC.DAT",itemImg,16, 32); //Load sprites to one of the fixed structs
   switch(pos){
   	case 1:
   		sprite[spriteNum].pos_x = 221;
      	break;
      case 2:
      	sprite[spriteNum].pos_x = 247;
      	break;
   }
   sprite[spriteNum].pos_y = 0;
   DrawSpriteDestructive(spriteNum);
   UnloadSprite(spriteNum);
}

/////////////////////////////////////////////////////////
//  Reset item
// - Sets item on panel position
/////////////////////////////////////////////////////////
void ResetItem(int pos, int spriteNum){
  // Update panel item
	LoadSprite("SPRMISC.DAT","eitem.pcx",16, 32); //Load sprites to one of the fixed structs
   switch(pos){
   	case 1:
   		sprite[spriteNum].pos_x = 221;
      	break;
      case 2:
      	sprite[spriteNum].pos_x = 247;
      	break;
   }
   sprite[spriteNum].pos_y = 0;
   DrawSpriteDestructive(spriteNum);
   UnloadSprite(spriteNum);
}




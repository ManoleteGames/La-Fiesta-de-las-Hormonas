/***********************
*  Engine functions
************************/

#include "source\engine\engine.h"

unsigned char *error1;
unsigned char *error2;
unsigned char *string;

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

byte videoCard_detected;  // 0: No card; 1: VGA; 2: EGA; 3:CGA                                              
byte soundCard_detected;  // 0-undef; 1-Speaker; 2-tandy; 3-adlib; 4-sound blaster
byte graphicsModeActive = 0;
                                                                                                 
byte video_mode = 0;	//0-undef; 1-vga; 2-ega; 3-cga; 4-tandy
byte music_mode = 0;	//0-undef; 1-Speaker; 2-tandy; 3-FM Chip (Adlib & Sound blaster)
byte music_volume = 0; // 0..100
byte sfx_mode = 0;	//0-undef; 1-Speaker; 2-tandy; 3-adlib; 4-sound blaster
byte sfx_volume = 0; // 0..100
byte language = 0;	//1-spanish; 2-english

byte *tempdata1; //Temp storage of non tiled data. and also sound samples (1/2)
byte *tempdata2; //Temp storage of non tiled data. and also sound samples (2/2)

// 0..208 >> Image and tile color
// 209..252 >> Sprite colors
// 252..255 >> Font color
byte palette[256*3];

IMFsong music;	// One song in ram stored at "music"
PLAYER far player;

// Video memory mapping
word vram_LogicalWidth; // screen logical with on bytes in vram
word vram_Font; // Font address in VRAM
word vram_Tiles; // Tiles address in VRAM
word vram_SpritesBack; // Sprites background address in VRAM

// Scrolling variables
int scroll_x = 0;   // Scroll X
int scroll_y = 0;  // Scroll Y
int scroll_x_adjust = 150;
int scroll_y_adjust = 70;
int scroll_wy = 400;
byte showPanel = 0;
byte scrolling_enabled = 0; // Scrolling and panning enabled

unsigned char far *data;

// Old time handler
void interrupt (*old_time_handler)(void);

/////////////////////////////////////////////////////////
// Music functions
// - Pointers to the specific sound card functions
/////////////////////////////////////////////////////////
void (*LoadMusic)(void);
void (*UnloadMusic)(void);
void (*PlayMusic)(void);
void (*StopMusic)(void);
void (*InitSoundCard)(void);

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
void (*HardwareScrolling)(void);
void (*RotatePalette)(int index1, int index2, int speed);
void (*LoadFont)(char *file, char *dat_string);
void (*LoadTiles)(char *file,char* dat_string);
void (*Draw_EmptyBox)(word x, word y, byte w, byte h);
void (*SetLoadingInterrupt)(void);
void (*ResetLoadingInterrupt)(void);
void (*PrintText)(word x, word y, word lineLength, unsigned char *string);
void (*Draw_Sprites)(void);
void (*SetPalette)(unsigned char *pal);
void (*LoadTiles)(char *file,char* dat_string);
void (*SetMap)(int x, int y);
void (*ScrollMap)(void);
void (*UpdatePanel)(void);
void (*LoadPanelBackground)(char *file,char* dat_string);

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

	soundCard_detected = 0;

   printf("***** Checking audio hardware... \n");

   // Check if any card is avaliable
   if(soundCard_detected == 0){ if( SB_Present() ) { soundCard_detected = 4; }}
   if(soundCard_detected == 0){ if( ADLIB_Present() ) { soundCard_detected = 3; }}
   if(soundCard_detected == 0){ if( TANDY_Present() ) { soundCard_detected = 2; }}
   if(soundCard_detected == 0){
   	printf(" - No sound card detected \n");
      printf(" -- only PC Speaker avaliable \n");
   	soundCard_detected = 1;
   }  // Only speaker avaliable
}

/////////////////////////////////////////////////////////
// Check graphics card
// 0: No card; 1: VGA; 2: EGA; 3:CGA
/////////////////////////////////////////////////////////
void CheckGraphicsCard(void){

   videoCard_detected = 0;

   printf("***** Checking video hardware... \n");

   // Check if any card is avaliable
   if(videoCard_detected == 0){ if( VGA_Present() ) { videoCard_detected = 1; }}
   if(videoCard_detected == 0){ if( EGA_Present() ) { videoCard_detected = 2; }}
   if(videoCard_detected == 0){ if( CGA_Present() ) { videoCard_detected = 3; }}

   videoCard_detected = 1;

   // Set Vsync pointer for the detected video card
   switch( videoCard_detected ){
   	case 1:
      	Vsync = VGA_Vsync;
      	break;
      case 2:
      	Vsync = EGA_Vsync;
      	break;
      case 3:
      	Vsync = CGA_Vsync;
      	break;
      default:
      	Vsync = Dummy;
      	break;
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
// Link sound functions to specific device
// 0-undef; 1-Speaker; 2-tandy; 3-adlib; 4-sound blaster
/////////////////////////////////////////////////////////
void LinkSound(void){

	printf("***** Inicializando sonido... \n");

	switch(sfx_mode){
   	case 1: // PC Speaker
      	printf(" - Activating PC Speaker sound mode\n");
      	InitSoundCard = Dummy;
         //DeInitSoundCard = &Dummy_VoidFunction;
			//PlaySFX = &Speaker_PlaySFX;
      	break;
      case 2: // Tandy sound card
      	printf(" - Activating Tandy sound mode\n");
      	InitSoundCard = TANDY_InitSoundCard;
         //DeInitSoundCard = &Dummy_VoidFunction;
      	break;
      case 3: // Adlib
      	printf(" - Activating Adlib sound mode\n");
      	InitSoundCard = ADLIB_InitSoundCard;
         //DeInitSoundCard = &Dummy_VoidFunction;
			//PlaySFX = &FM_PlaySFX;
      	break;
      case 4: // Sound blaster
      	printf(" - Activating Sound Blaster sound mode\n");
        	InitSoundCard = SB_InitSoundCard;
         //DeInitSoundCard = &SBlaster_DeInit;
			//PlaySFX = &SBlaster_PlaySFX;
      	break;
      default:
      	printf("No sound mode defined\n");
      	break;
	}
}


/////////////////////////////////////////////////////////
// Link music functions to specific device
// 0-undef; 1-Speaker; 2-tandy; 3-adlib
/////////////////////////////////////////////////////////
void LinkMusic(void){

	printf("***** Inicializando musica... \n");

	switch(music_mode){
   	case 1: // PC Speaker
      	printf(" - Activating PC speaker music mode\n");
      	break;
      case 2: // Tandy sound card
      	printf(" - Activating Tandy music mode\n");
      	LoadMusic = TANDY_LoadMusic;
         UnloadMusic = TANDY_UnloadMusic;
			PlayMusic = TANDY_PlayMusic;
         StopMusic = TANDY_StopMusic;
      	break;
      case 3: // Adlib or sound blaster
      	printf(" - Activating FM music mode\n");
        	LoadMusic = ADLIB_LoadMusic;
         UnloadMusic = ADLIB_UnloadMusic;
			PlayMusic = ADLIB_PlayMusic;
         StopMusic = ADLIB_StopMusic;
      	break;
      default:
			printf(" - No music mode defined\n");
      	exit(1);
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
         LoadTiles = VGA_LoadTiles;
         LoadFont = VGA_LoadFont;

         HardwareScrolling = VGA_HardwareScrolling;
         SetPage = VGA_SetPage;
         RotatePalette = VGA_RotatePalette;

         Draw_EmptyBox = VGA_Draw_EmptyBox;
         SetLoadingInterrupt = VGA_SetLoadingInterrupt;
         ResetLoadingInterrupt = VGA_ResetLoadingInterrupt;
         PrintText = VGA_PrintText;
         Draw_Sprites = VGA_Draw_Sprites;
         SetPalette = VGA_SetPalette;

         SetMap = VGA_SetMap;
         ScrollMap = VGA_ScrollMap;
         UpdatePanel = VGA_UpdatePanel;
         LoadPanelBackground = VGA_LoadPanelBackground;

      	break;
      case 2:
      	printf(" - Activating EGA mode\n");
			// Link global functions to EGA custom functions
         Vsync = EGA_Vsync;
      	printf("EGA mode not implemented yet!\n");
         getch();
      	exit(1);
      	break;
      case 3:
      	printf(" - Activating CGA mode\n");
			// Link global functions to CGA custom functions
         Vsync = CGA_Vsync;
        	printf("CGA mode not implemented yet!\n");
         getch();
      	exit(1);
      	break;
      case 4:
      	printf(" - Activating TANDY mode\n");
			// Link global functions to TANDY custom functions
         Vsync = Vsync_TANDY;
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
      Update(0,0);
   }
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
		printf(" - setup.ini no encontrado\n - Creando nuevo archivo con la configuracion detectada...\n");
		setupfile = fopen("setup.ini","w");
		fprintf(setupfile,"#SETUP\n------\n[1]VIDEO=%03u\n[2]MUSIC=%03u\n[3]MUSVOL=050\n[4]SFX=%03u\n[5]SFXVOL=050\n[6]BLASA=%03x\n[7]BLASI=%03x\n[8]BLASLD=%03x\n[9]BLASHD=%03x\n[10]LANG=001",1,1,1,0,0,0,0);
		fclose(setupfile);
		sleep(2);
	}

	fread(buffer,1,256,setupfile);

	video_mode = (buffer[25]-48)*100 + (buffer[26]-48)*10 + (buffer[27]-48);
	music_mode = (buffer[39]-48)*100 + (buffer[40]-48)*10 + (buffer[41]-48);
   music_volume = (buffer[54]-48)*100 + (buffer[55]-48)*10 + (buffer[56]-48);
   sfx_mode = (buffer[66]-48)*100 + (buffer[67]-48)*10 + (buffer[68]-48);
   sfx_volume = (buffer[81]-48)*100 + (buffer[82]-48)*10 + (buffer[83]-48);
   SB_SetAddress((buffer[95]-48)*100 + (buffer[96]-48)*10 + (buffer[97]-48));
   SB_SetIRQ((buffer[109]-48)*100 + (buffer[110]-48)*10 + (buffer[111]-48));
   SB_SetLoDMA((buffer[124]-48)*100 + (buffer[125]-48)*10 + (buffer[126]-48));
   SB_SetHiDMA((buffer[139]-48)*100 + (buffer[140]-48)*10 + (buffer[141]-48));
   language = (buffer[153]-48)*100 + (buffer[154]-48)*10 + (buffer[155]-48);

   video_mode = 1;
   music_mode = 1;
   sfx_mode = 1;

   printf(" - Configuracion cargada \n");

   fclose(setupfile);
}

/////////////////////////////////////////////////////////
// Exit to dos function
/////////////////////////////////////////////////////////
void ExitDOS(void){

	if(graphicsModeActive){ TextMode(); } // Get back to text mode

	//StopMusic();

	outportb(0x43, 0x36);
	outportb(0x40, 0xFF);	//lo-byte
	outportb(0x40, 0xFF);	//hi-byte

   Reset_key_handler();

   // Unload and release music data
	//UnloadMusic();

   //DeInitSoundCard();
	//UnloadTileset();
	//UnloadMap();
   UnloadSprites();

   if(error1){ farfree(error1); }
   if(error2){ farfree(error2); }
   if(string){ farfree(string); }

   if(music.sdata){ farfree(music.sdata); }
   //if(player){ farfree(player); }
   if(sprite){ farfree(sprite); }

   if(map_data ){ farfree(map_data); }
   if(map_flip ){ farfree(map_flip); }
   if(map_collision ){ farfree(map_collision); }
   if(map_hotspot ){ farfree(map_hotspot); }
   if(map_event ){ farfree(map_event); }

   printf("bye byte...");
	exit(1);
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
	unsigned char *dummy;

	printf("***** Allocating memory ...\n");

   //Allocate first 32kb just to keep a space before allocating data
   //if ((dummy = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of dummy data after exe","dummy",0);

   //Allocate error strings
   if ((error1 = farcalloc(30, sizeof(unsigned char))) == NULL) Error("Not enough RAM to allocate 30 bytes of error1 string","error1",0);
 	printf(" error1 allocated onto adddress: %p address \n", error1);
   if ((error2 = farcalloc(30, sizeof(unsigned char))) == NULL) Error("Not enough RAM to allocate 30 bytes of error2 string","error2",0);
   printf(" error2 allocated onto adddress: %p address \n", error2);
   if ((string = farcalloc(40, sizeof(unsigned char))) == NULL) Error("Not enough RAM to allocate 30 bytes of global string","string",0);
   printf(" string allocated onto adddress: %p address \n", string);

   //Allocate 32KB block for temp data
   //if ((tempdata1 = farcalloc(32768L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of temp. data","tempdata1",0);
   if ((tempdata1 = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of temp. data","tempdata1",0);
   printf(" tempdata1 allocated onto adddress: %p address \n", tempdata1);
   //Allocate 32 KB of temp data just after the first
	//if ((tempdata2 = farcalloc(32768L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of temp. data","tempdata2",0);
   if ((tempdata2 = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 32 Kb of temp. data","tempdata2",0);
   printf(" tempdata2 allocated onto adddress: %p address \n", tempdata2);

	//if ((music.sdata = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate 64 Kb of music data","music","sdata");
   //printf(" music.sdata allocated onto adddress: %p address \n", music.sdata);
	//if ((map_data = farcalloc(65535L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate map data","map","data");
   if ((map_data = farcalloc(32768L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate map data","map","data");
   printf(" map_data allocated onto adddress: %p address \n", map_data);
	if ((map_collision = farcalloc(8192L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate collision data","map","collision");
   printf(" map_collision allocated onto adddress: %p address \n", map_collision);
   if ((map_hotspot = farcalloc(8192L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate hotspot data","map","hotspot");
   printf(" map_hotspot allocated onto adddress: %p address \n", map_hotspot);
   if ((map_event = farcalloc(8192L,sizeof(byte))) == NULL) Error("Not enough RAM to allocate event data","map","event");
   printf(" map_event allocated onto adddress: %p address \n", map_event);
//   if ((player = farcalloc(1,sizeof(PLAYER))) == NULL) Error("Not enough RAM to allocate player predefined sprite struct","player",0);
//   printf(" player allocated onto adddress: %p address \n", player);
   if ((sprite = farcalloc(20,sizeof(SPRITE))) == NULL) Error("Not enough RAM to allocate 22 predefined sprite structs","sprite",0);
   printf(" sprite allocated onto adddress: %p address \n", sprite);

   //if(dummy ){ farfree(dummy); }

   printf(" - Memory allocated successfuly \n");
   getchar();
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
   LinkMusic();
   LinkSound();

   AllocateEngineMem();

   InitKeyboard();

   InitSoundCard();
   InitVideoCard();
   graphicsModeActive = 1;
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
void Update(int player_follow, int sprite){
	HardwareScrolling();
	if (player_follow) ScrollFollow();
	if (scrolling_enabled) ScrollMap();
   Draw_Sprites();                           
   UpdatePanel();
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
   long tile_number = 0;
   word nextTile = 0;

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

    // Up colision
   if( (s->tile_y) <= 0){ up_coll = 1; }
   // Left colision
	if( (s->tile_x) <= 0){ left_coll = 1; }
	// Right colision
	if( (s->tile_x) >= map_width ){ right_coll = 1; }
   // Down colision
	if( (s->tile_y) >= map_height ){ down_coll = 1; }

   // Check map collisions
   //if( (player.move == P_DWNLEFT) || (player.move == P_UPLEFT) || (player.move == P_LEFT) ){
   if( (player.move == 8) || (player.move == 6) || (player.move == 3) ){
  	   tile_number = ( ((s->pos_y + 4 - 64)>>4)* map_width ) +  s->tile_x - 1;
   	if(map_collision[tile_number]  != 0) {  left_coll = 1; }
      tile_number = ( ((s->pos_y + s->height - 4 - 64)>>4)* map_width) +  s->tile_x - 1;
     	if(map_collision[tile_number]  != 0) {  left_coll = 1; }
   }
   //if( (player.move == P_UPRIGHT) || (player.move == P_UPLEFT) || (layer.move == P_UP) ){
   if( (player.move == 5) || (player.move == 6) || (player.move == 1) ){
      tile_number = ((s->tile_y-1) * map_width ) +  ((s->pos_x + 4)>>4);
   	if(map_collision[tile_number]  != 0) {  up_coll = 1; }
      tile_number = ((s->tile_y-1) * map_width ) +  ((s->pos_x + s->width - 4)>>4);
     	if(map_collision[tile_number]  != 0) {  up_coll = 1; }
   }
   //if( (player.move == P_UPRIGHT) || (player.move == P_DWNRIGHT) || (player.move == P_RIGHT) ){
   if( (player.move == 5) || (player.move == 7) || (player.move == 4) ){
      tile_number = ( ((s->pos_y + 4 - 64)>>4)* map_width ) +  s->tile_x + 1;
   	if(map_collision[tile_number]  != 0) {  right_coll = 1; }
      tile_number = ( ((s->pos_y + s->height - 4 - 64)>>4)* map_width) +  s->tile_x + 1;
     	if(map_collision[tile_number]  != 0) {  right_coll = 1; }
   }
   //if( (player.move == P_DWNLEFT) || (player.move == P_DWNRIGHT) || (player.move == P_DOWN) ){
   if( (player.move == 8) || (player.move == 7) || (player.move == 2) ){
      tile_number = ((s->tile_y+1) * map_width ) +  ((s->pos_x + 4)>>4);
   	if(map_collision[tile_number]  != 0) {  down_coll = 1; }
      tile_number = ((s->tile_y+1) * map_width ) +  ((s->pos_x + s->width - 4)>>4);
     	if(map_collision[tile_number]  != 0) {  down_coll = 1; }
   }

   // Event finder
   player.event = map_event[tile_number];

   // Hotspot finder
   player.hotspot = map_hotspot[tile_number];

   // Player movement
  	//if( (player.move == P_UP) || (player.move == P_UPRIGHT) || (player.move == P_UPLEFT) ){
   if( (player.move == 1) || (player.move == 5) || (player.move == 6) ){
   	if(up_coll == 0) s->pos_y--;
      //s->pos_y--;
   }
   //if( (player.move == P_DOWN) || (player.move == P_DWNRIGHT) || (player.move == P_DWNLEFT) ) {
   if( (player.move == 2) || (player.move == 7) || (player.move == 8) ) {
    	if(down_coll == 0) s->pos_y++;
      //s->pos_y++;
   }
   //if( (player.move == P_LEFT) || (player.move == P_UPLEFT) || (player.move == P_DWNLEFT) ) {
   if( (player.move == 3) || (player.move == 6) || (player.move == 8) ) {
    	if(left_coll == 0) s->pos_x--;
      //s->pos_x--;
   }
   //if( (player.move == P_RIGHT) || (player.move == P_UPRIGHT) || (player.move == P_DWNRIGHT) ) {
   if( (player.move == 4) || (player.move == 5) || (player.move == 7) ) {
    	if(right_coll == 0) s->pos_x++;
      //s->pos_x++;
   }


	//Fixed animations
   if((player.oldMove !=  player.move)&& (s->animate == 1)){
   	switch (player.move){
      	case 1:
            SetSpriteAnimation(player.spriteNum,25,4,12,PlayerAnimation);  // up
         	break;
         case 2:
         	SetSpriteAnimation(player.spriteNum,13,4,12,PlayerAnimation); // down
         	break;
	  		case 3:
         	SetSpriteAnimation(player.spriteNum,17,4,12,PlayerAnimation);  // left
         	break;
			case 4:
         	SetSpriteAnimation(player.spriteNum,13,4,12,PlayerAnimation);  // right
         	break;
         case 5:
         	SetSpriteAnimation(player.spriteNum,25,4,12,PlayerAnimation);  // up + right
         	break;
         case 6:
         	SetSpriteAnimation(player.spriteNum,21,4,12,PlayerAnimation);  // up + left
         	break;
         case 7:
         	SetSpriteAnimation(player.spriteNum,13,4,12,PlayerAnimation);  // down + right
         	break;
         case 8:
         	SetSpriteAnimation(player.spriteNum,17,4,12,PlayerAnimation);  // down + left
         	break;
			case 0:
         	SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);  // stand
         	break;
      	default:
         	SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);  // stand
				break;
   	}
      //SetSpriteAnimation(player.spriteNum,s->baseframe,s->aframes,s->speed,PlayerAnimation);
   }

   player.oldMove =  player.move;
}




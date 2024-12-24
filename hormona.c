/***********************
*  LA FIESTA DE LAS HORMONAS
*  - Autor: jmartin
*  - Agradecimientos especiales a mills32 por su proyecto Little Game Engine, el cual ha servido de base para este programa
************************/

#include "source\engine\engine.h"
#include "source\engine\keyb\keyb.h"

byte option = 1;
byte PlayerAnimation[] = {0,0,0,0,0,0,0,1,2,1,0,2,1,3,4,3,5,6,7,6,8,9,10,9,11,12,13,12,14};
byte PlayerFaceAnimation[] = {0,1,2};
byte JessyAnimation[] = {0,0,0,0,0,0,0,1,2,1,0,2,1,3,4,3,5,6,7,6,8,9,10,9,11,12,13,12,14};
byte EnterAnimation[] = {0,0,0,1};
byte BirdAnimation[] = {0,1,2,3,4,3,4,3,2,1,0,0,0,0,0};
byte DirectorAnimation[] = {0,1,0,1,0,0,2,2,3,3,4,0,0,0,1};
byte CharacterAnimation2[] = {0,0,0,1,0,0,0};
byte CharacterAnimation3[] = {0,0,0,1,2,0,0};

/////////////////////////////////////////////////////////
// Logo function
// - Little sequence with logos and stuff
/////////////////////////////////////////////////////////
void Logo(void){
	// Dos contest logo
	Fade_out();
   LoadImage("LOGO.DAT","LCONTEST.pcx",1);
   SetPage(1);
   Fade_in();

   // MS-DOS club logo
   LoadImage("LOGO.DAT","LDOSCLUB.pcx",2);
   Fade_out();
   SetPage(2);
   Fade_in();
   RotatePalette(48,83,98);

   LoadImage("LOGO.DAT","LMANOL.pcx",1);
   Fade_out();
   SetPage(1);
   Fade_in();

   Delay(120);

   Fade_out();
}

/////////////////////////////////////////////////////////
// Main menu
// - Shows a menu with 4 options
//	-- New game
// -- Continue game
// -- Options
// -- Quit game
/////////////////////////////////////////////////////////
void Menu(void)
{
   word length;
   int menu_pos[5] = {92,100,108,116,124};
   byte MenuCursorAnimation[8] = {0,1,2,3,3,3,3,3};

   // Load animation
	SetLoadingInterrupt();   // Start loading animation
   // Load resources
   LoadImage("IMAGES.DAT","MENU.pcx",2); // Load menu background image to non visible page
   LoadFont("FONTS.DAT","FONT.bmp"); //Load font
   LoadSprite("SPRMISC.DAT","cursor.pcx",1,16); //Load sprites to one of the fixed structs
   InitSprite(1,110,menu_pos[option] + vga_page[2]);
   SetSpriteAnimation(1,0,7,6,MenuCursorAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);

   // Draw menu options
   Draw_EmptyBox(13,12,14,4);
   LoadText("GLB_STR.DAT","global.txt","001",string,&length);
   PrintText(15,13,length,string,1);
   LoadText("GLB_STR.DAT","global.txt","002",string,&length);
   PrintText(15,14,length,string,0);
   LoadText("GLB_STR.DAT","global.txt","003",string,&length);
   PrintText(15,15,length,string,0);
   LoadText("GLB_STR.DAT","global.txt","004",string,&length);
   PrintText(15,16,length,string,0);

   Fade_in();

   while( keys[K_ENTER] != 1 )
   {
      sprite[1].pos_y = menu_pos[option] + vga_page[2];

      if( fp_keys[K_UP] == 1) {

      	switch(option){
         	case 1: // Do nothing
            	break;
            case 2: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","002",string,&length);
				   PrintText(15,14,length,string,0);
	            option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","001",string,&length);
				   PrintText(15,13,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,0);
               option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","002",string,&length);
				   PrintText(15,14,length,string,1);
				  	break;
            case 4: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","004",string,&length);
				   PrintText(15,16,length,string,0);
               option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,1);
				  	break;
         }
      }
      if( fp_keys[K_DOWN] == 1){
      	switch(option){
         	case 1: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","001",string,&length);
				   PrintText(15,13,length,string,0);
               option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","002",string,&length);
				   PrintText(15,14,length,string,1);
            	break;
            case 2: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","002",string,&length);
				   PrintText(15,14,length,string,0);
	            option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,0);
               option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","004",string,&length);
				   PrintText(15,16,length,string,1);
				  	break;
            case 4: // Do nothing
				  	break;
         }
      }

     	if(option < 1){ option = 1;}
      if(option > 4){ option = 4;}

      // Main loop
      Update(0);
   }

   Fade_out();
}


/////////////////////////////////////////////////////////
// New game
// - Starts the party...
/////////////////////////////////////////////////////////
void NewGame(void) {

	// Initialize player status
 	player.spriteNum = 1;
   player.floor = 1;
   player.day = 10;
   player.hour = 8;
   player.min = 45;

   // Starting player status
   player.intell = 10;
   player.popular = 10;
   player.good = 10;
   player.money = 0;

   // Initialize events masks
   player.ext1_event_mask[1] = 1;
   player.ext1_event_mask[2] = 1;
	player.ext1_event_mask[3] = 1;
	player.ext1_event_mask[4] = 0;
   player.ext1_event_mask[5] = 0;
   player.ext1_event_mask[6] = 0;
   player.ext1_event_mask[7] = 0;
   player.ext1_event_mask[8] = 0;
   player.ext1_event_mask[9] = 0;
   player.ext1_event_mask[10] = 0;
   player.ext1_event_mask[11] = 0;
   player.ext1_event_mask[12] = 0;
   player.ext1_event_mask[13] = 0;
   player.ext1_event_mask[14] = 0;
   player.ext1_event_mask[15] = 0;

   player.ext2_event_mask[1] = 1;
   player.ext2_event_mask[2] = 1;
	player.ext2_event_mask[3] = 1;
	player.ext2_event_mask[4] = 0;
   player.ext2_event_mask[5] = 0;
   player.ext2_event_mask[6] = 0;
   player.ext2_event_mask[7] = 0;
   player.ext2_event_mask[8] = 0;
   player.ext2_event_mask[9] = 0;
   player.ext2_event_mask[10] = 0;
   player.ext2_event_mask[11] = 0;
   player.ext2_event_mask[12] = 0;
   player.ext2_event_mask[13] = 0;
   player.ext2_event_mask[14] = 0;
   player.ext2_event_mask[15] = 0;

   player.floor1_event_mask[1] = 1;
   player.floor1_event_mask[2] = 1;
	player.floor1_event_mask[3] = 1;
	player.floor1_event_mask[4] = 1;
   player.floor1_event_mask[5] = 0;
   player.floor1_event_mask[6] = 0;
   player.floor1_event_mask[7] = 0;
   player.floor1_event_mask[8] = 0;
   player.floor1_event_mask[9] = 0;
   player.floor1_event_mask[10] = 0;
   player.floor1_event_mask[11] = 0;
   player.floor1_event_mask[12] = 0;
   player.floor1_event_mask[13] = 0;
   player.floor1_event_mask[14] = 0;
   player.floor1_event_mask[15] = 0;

   player.floor2_event_mask[1] = 1;
   player.floor2_event_mask[2] = 1;
	player.floor2_event_mask[3] = 0;
	player.floor2_event_mask[4] = 0;
   player.floor2_event_mask[5] = 0;
   player.floor2_event_mask[6] = 0;
   player.floor2_event_mask[7] = 0;
   player.floor2_event_mask[8] = 0;
   player.floor2_event_mask[9] = 0;
   player.floor2_event_mask[10] = 0;
   player.floor2_event_mask[11] = 0;
   player.floor2_event_mask[12] = 0;
   player.floor2_event_mask[13] = 0;
   player.floor2_event_mask[14] = 0;
   player.floor2_event_mask[15] = 0;

   player.gym_event_mask[1] = 1;
   player.gym_event_mask[2] = 0;
	player.gym_event_mask[3] = 0;
	player.gym_event_mask[4] = 0;
   player.gym_event_mask[5] = 0;
   player.gym_event_mask[6] = 0;
   player.gym_event_mask[7] = 0;
   player.gym_event_mask[8] = 0;
   player.gym_event_mask[9] = 0;
   player.gym_event_mask[10] = 0;
   player.gym_event_mask[11] = 0;
   player.gym_event_mask[12] = 0;
   player.gym_event_mask[13] = 0;
   player.gym_event_mask[14] = 0;
   player.gym_event_mask[15] = 0;

   // Initialize hotspot masks
   player.ext1_hotspot_mask[1] = 0;
   player.ext1_hotspot_mask[2] = 0;
	player.ext1_hotspot_mask[3] = 0;
	player.ext1_hotspot_mask[4] = 0;
   player.ext1_hotspot_mask[5] = 0;
   player.ext1_hotspot_mask[6] = 0;
   player.ext1_hotspot_mask[7] = 0;
   player.ext1_hotspot_mask[8] = 0;
   player.ext1_hotspot_mask[9] = 0;
   player.ext1_hotspot_mask[10] = 0;
   player.ext1_hotspot_mask[11] = 0;
   player.ext1_hotspot_mask[12] = 0;
   player.ext1_hotspot_mask[13] = 0;
   player.ext1_hotspot_mask[14] = 0;
   player.ext1_hotspot_mask[15] = 0;

   player.ext2_hotspot_mask[1] = 0;
   player.ext2_hotspot_mask[2] = 0;
	player.ext2_hotspot_mask[3] = 0;
	player.ext2_hotspot_mask[4] = 0;
   player.ext2_hotspot_mask[5] = 0;
   player.ext2_hotspot_mask[6] = 0;
   player.ext2_hotspot_mask[7] = 0;
   player.ext2_hotspot_mask[8] = 0;
   player.ext2_hotspot_mask[9] = 0;
   player.ext2_hotspot_mask[10] = 0;
   player.ext2_hotspot_mask[11] = 0;
   player.ext2_hotspot_mask[12] = 0;
   player.ext2_hotspot_mask[13] = 0;
   player.ext2_hotspot_mask[14] = 0;
   player.ext2_hotspot_mask[15] = 0;

   player.floor1_hotspot_mask[1] = 1;
   player.floor1_hotspot_mask[2] = 1;
	player.floor1_hotspot_mask[3] = 1;
	player.floor1_hotspot_mask[4] = 0;
   player.floor1_hotspot_mask[5] = 1;
   player.floor1_hotspot_mask[6] = 0;
   player.floor1_hotspot_mask[7] = 1;
   player.floor1_hotspot_mask[8] = 1;
   player.floor1_hotspot_mask[9] = 0;
   player.floor1_hotspot_mask[10] = 1;
   player.floor1_hotspot_mask[11] = 1;
   player.floor1_hotspot_mask[12] = 1;
   player.floor1_hotspot_mask[13] = 1;
   player.floor1_hotspot_mask[14] = 0;
   player.floor1_hotspot_mask[15] = 0;

   player.floor2_hotspot_mask[1] = 1;
   player.floor2_hotspot_mask[2] = 0;
	player.floor2_hotspot_mask[3] = 1;
	player.floor2_hotspot_mask[4] = 0;
   player.floor2_hotspot_mask[5] = 0;
   player.floor2_hotspot_mask[6] = 1;
   player.floor2_hotspot_mask[7] = 1;
   player.floor2_hotspot_mask[8] = 1;
   player.floor2_hotspot_mask[9] = 0;
   player.floor2_hotspot_mask[10] = 1;
   player.floor2_hotspot_mask[11] = 1;
   player.floor2_hotspot_mask[12] = 0;
   player.floor2_hotspot_mask[13] = 0;
   player.floor2_hotspot_mask[14] = 0;
   player.floor2_hotspot_mask[15] = 0;

   player.gym_hotspot_mask[1] = 0;
   player.gym_hotspot_mask[2] = 0;
	player.gym_hotspot_mask[3] = 0;
	player.gym_hotspot_mask[4] = 0;
   player.gym_hotspot_mask[5] = 0;
   player.gym_hotspot_mask[6] = 0;
   player.gym_hotspot_mask[7] = 0;
   player.gym_hotspot_mask[8] = 0;
   player.gym_hotspot_mask[9] = 0;
   player.gym_hotspot_mask[10] = 0;
   player.gym_hotspot_mask[11] = 0;
   player.gym_hotspot_mask[12] = 0;
   player.gym_hotspot_mask[13] = 0;
   player.gym_hotspot_mask[14] = 0;
   player.gym_hotspot_mask[15] = 0;

   player.mission_cheat = 0;
   player.mission_doll = 0;

   player.item_chalk = 0;

   player.rel_freaks = 0;
   player.rel_thugs = 0;
   player.rel_jessy = 0;

   LoadFont("FONTS.DAT","FONT.bmp"); //Load text font
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   VGA_PanelUpdate();

   D10_GoToFloor1(100, 185);

   while( keys[K_ESC] != 1 )
   {
   	switch(player.day){
      	case 10: // 1st day
         	D10_Events(player.event);
            if(keys[K_ENTER] == 1){ D10_Hotspots(player.hotspot); }
            break;
         case 9: // 2nd day
         	D9_Events(player.event);
            if(keys[K_ENTER] == 1){ D9_Hotspots(player.hotspot); }
            break;
         case 8: // 3rd day
         	D8_Events(player.event);
            if(keys[K_ENTER] == 1){ D8_Hotspots(player.hotspot); }
            break;
      	case 7: // 4th day
         	D7_Events(player.event);
            if(keys[K_ENTER] == 1){ D7_Hotspots(player.hotspot); }
            break;
         case 6: // 5th day
         	D6_Events(player.event);
            if(keys[K_ENTER] == 1){ D6_Hotspots(player.hotspot); }
            break;
         case 5: // 6th day
         	D5_Events(player.event);
            if(keys[K_ENTER] == 1){ D5_Hotspots(player.hotspot); }
            break;
      	case 4: // 7th day
         	D4_Events(player.event);
            if(keys[K_ENTER] == 1){ D4_Hotspots(player.hotspot); }
            break;
         case 3: // 8th day
         	D3_Events(player.event);
            if(keys[K_ENTER] == 1){ D3_Hotspots(player.hotspot); }
            break;
         case 2: // 9th day
         	D2_Events(player.event);
            if(keys[K_ENTER] == 1){ D2_Hotspots(player.hotspot); }
            break;
      	case 1: // 10 day. Last one
           	D1_Events(player.event);
            if(keys[K_ENTER] == 1){ D1_Hotspots(player.hotspot); }
            break;
         case 0: // End game
				D0_Events(player.event);
            if(keys[K_ENTER] == 1){ D0_Hotspots(player.hotspot); }
            break;
			default:
				Error("Undefined day number",0,0);
				break;
      }

      //debug
      if(fp_keys[K_D]){
      	if(debug == 1){debug=0;}
         else{debug=1;}
      }


      // Main loop
      MovePlayer();
      Update(1);
   }
}

/////////////////////////////////////////////////////////
// Main function
// - Main entry function of the program
/////////////////////////////////////////////////////////
void main(){

	system("cls");
   printf("\n************************************************\n");
   printf("*********** LA FIESTA DE LAS HORMONAS **********\n");
   printf("************************************************\n");
   printf("\n");

   InitEngine(); // Initialize system

   //Logo(); // Show logos and stuff before start the party

   while( keys[K_ESC] != 1 )
   {
		//Menu(); // Show game main menu
      option = 1;

      switch(option)
      {
      	case 1: // New game
            Intro();
         	NewGame();
      		break;
         case 2: // Continue

         	break;
         case 3: // Options

         	break;
         case 4: // Exit
         	ExitDOS();
         	break;
         default:
         	ExitDOS();
         	break;
      }
   }
   ExitDOS();
}


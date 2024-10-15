/***********************
*  LA FIESTA DE LAS HORMONAS
*  - Autor: jmartin
*  - Agradecimientos especiales a mills32 por su proyecto Little Game Engine, el cual ha servido de base para este programa
************************/

#include "source\engine\engine.h"
#include "source\engine\keyb\keyb.h"

byte option = 1;
byte PlayerAnimation[] = {0,0,0,0,0,0,0,1,2,1,0,2,1,8,9,8,9,3,4,3,4,5,6,7,6,5,6,7,6};
byte PlayerFaceAnimation[] = {0,1,2};
byte JessyAnimation[] = {0,0,0,0,0,0,0,1,2,1,0,2,1,8,9,8,9,3,4,3,4,5,6,7,6,5,6,7,6};
byte EnterAnimation[] = {0,0,0,1};
byte BirdAnimation[] = {0,1,2,3,4,3,4,3,2,1,0,0,0,0,0};
byte DirectorAnimation[] = {0,1,0,1,0,0,2,2,3,3,4,0,0,0,1};
byte CharacterAnimation2[] = {0,0,0,1,0,0,0};
byte CharacterAnimation3[] = {0,0,0,1,2,0,0};

byte ext1_event_mask[] = {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte ext2_event_mask[] = {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte floor1_event_mask[] = {0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0};
byte floor2_event_mask[] = {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte gym_event_mask[] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

byte ext1_hotspot_mask[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte ext2_hotspot_mask[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte floor1_hotspot_mask[] = {0,1,1,1,0,1,0,1,1,0,1,1,1,0,0,0,0};
byte floor2_hotspot_mask[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte gym_hotspot_mask[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


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
   LoadText("SGLB_STR.DAT","global.txt","001",string,&length);
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
      Update(0,0);
   }

   Fade_out();
}


/////////////////////////////////////////////////////////
// New game
// - Starts the party...
/////////////////////////////////////////////////////////
void NewGame(void) {
	SetLoadingInterrupt();   // Start loading animation

   LoadFont("FONTS.DAT","FONT.bmp"); //Load text font
	LoadMap("MAPS.DAT","floor1.tmx"); // Load floor 1 map
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRCHR.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","david.pcx",3, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","xavi.pcx",4, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","alain.pcx",5, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","antonio.pcx",6, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRMISC.DAT","enter.pcx",7,16); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","playerf.pcx",8, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRMISC.DAT","smoke.pcx",9, 64); //Load sprites to one of the fixed structs

   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
 	player.spriteNum = 1;
   player.floor = 1;
   player.day = 10;
   player.hour = 8;
   player.min = 45;
   player.money = 0;

   // Player status
   player.healt = 50;
   player.intell = 50;
   player.charm = 50;
   player.freak = 50;
   player.handsome = 50;
   player.badass = 50;

   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   SetSpriteAnimation(6,0,6,19,CharacterAnimation2);
   SetSpriteAnimation(7,0,4,8,EnterAnimation);
   SetSpriteAnimation(8,0,1,48,PlayerFaceAnimation);
   SetSpriteAnimation(9,0,1,64,PlayerFaceAnimation);

   ResetLoadingInterrupt(); // Stop loading animation
   // Allow scroll
   scrolling_enabled = 1;
   // Draw map
   SetMap(0,4);
   Update(0,0);

   InitSprite(2,512,402);

   InitSprite(3,396,102);
   InitSprite(4,408,122);
   InitSprite(5,434,142);
   InitSprite(6,396,142);
   InitSprite(7,0,0);
   InitSprite(8,0,0);
   InitSprite(9,0,0);

   InitSprite(1,100,185);

   HideSprite(7);
   HideSprite(8);
   HideSprite(9);

   Fade_in();

   panelScrolling = 1;
   showPanel = 1;

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

      // Main loop
      MovePlayer();
      Update(1,0);

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
            //Intro();
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


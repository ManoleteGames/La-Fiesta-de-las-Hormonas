/***********************
*  LA FIESTA DE LAS HORMONAS
*  - Autor: jmartin
*  - Agradecimientos especiales a mills32 por su proyecto Little Game Engine, el cual ha servido de base para este programa
************************/

#include "source\engine\engine.h"
#include "source\engine\keyb\keyb.h"

byte option = 1;
byte PlayerAnimation[] = {0,0,0,1,0,0,0,1,2,1,0,2,1,3,4,5,4,6,7,8,7,9,10,11,10,12,13,14,13};
byte PlayerFaceAnimation[] = {0,1,2};
byte JessyAnimation[] = {0,0,0,1,0,0,0,1,2,1,0,2,1,3,4,5,4,6,7,8,7,9,10,11,10,12,13,14,13};
byte ArrowAnimation[] = {0,1,2,3,3,3,3,3};
byte BirdAnimation[] = {0,1,2,3,4,3,4,3,2,1,0,0,0,0,0};
byte DirectorAnimation[] = {0,1,0,1,0,0,2,2,3,3,4,0,0,0,1};

/////////////////////////////////////////////////////////
// Logo function
// - Little sequence with logos and stuff
/////////////////////////////////////////////////////////
void Logo(void){
	// Dos contest logo
	Fade_out();
   LoadImage("IMAGES.DAT","LCONTEST.pcx",1);
   SetPage(1);
   Fade_in();

   // MS-DOS club logo
   LoadImage("IMAGES.DAT","LDOSCLUB.pcx",2);
   //Delay(120);

	Fade_out();
   SetPage(2);
   Fade_in();

   Delay(50);
   RotatePalette(48,83,98);
   Delay(120);

   Fade_out();
}

/////////////////////////////////////////////////////////
// New game intro
// - Sets a little intro at the very begining of the game
// - Can be skipped by pushing ESC
/////////////////////////////////////////////////////////
void Intro(void){
   word length;
	byte endIntro = 0;
   byte step = 0; // Current intro step

  	SetLoadingInterrupt();   // Start loading animation

   LoadFont("FONTS.DAT","FONT.bmp"); //Load a font
   // Load map and tilesets
   LoadMap("MAPS.DAT","ext1.tmx");
   LoadTiles("TILESETS.DAT","ext1.pcx");
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");

   LoadSprite("SPRITES.DAT","enter.pcx",1, 16); //Load sprites to one of the fixed structs
   LoadSprite("SPRITES.DAT","player.pcx",2, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRITES.DAT","playerf.pcx",3, 64); //Load sprites to one of the fixed structs
   LoadSprite("SPRITES.DAT","bird.pcx",4, 32); //Load sprites to one of the fixed structs

   ResetLoadingInterrupt(); // Stop loading animation

   scrolling_enabled = 1;

   // Draw loaded map
   SetMap(0,0);

   Update(0,0);

   Fade_in();

   // Intro loop
   while( (keys[K_ESC] != 1) && (endIntro != 1) )
   {
   	// Animation
      switch(step){
      	case 0:  // Init bird sprite
		      InitSprite(4,102,96);
            SetSpriteAnimation(4,0,14,8,BirdAnimation);
            step = 1;
	         break;
         case 1:	// Wait end of sequence
         	Delay(100);
            step = 2;
            HideSprite(4);
            break;
         case 2:	// Move scroll down
            if( scroll_y < 256 ){
            	scroll_y++;
            }
            else{
            	step = 3;
            }
         	break;
         case 3:	// Draw player sprite out of the screen limits
			  	InitSprite(2,0,360);
            SetSpriteAnimation(2,13,4,8,PlayerAnimation); // Set animation >> right

            step = 4;
         	break;
         case 4:  // Move player sprite inside screen
         	if( sprite[2].pos_x < 64 ){
            	sprite[2].pos_x ++;
            }
            else{
            	// Set animation >> static
            	SetSpriteAnimation(2,0,6,8,PlayerAnimation);   // Stand up
               step = 5;
            }
         	break;
          case 5: // Show spech
  	         Draw_EmptyBox(0,0,6,6);
            Draw_EmptyBox(8,0,30,6);
            Update(0,0);

			  	InitSprite(3,scroll_x,scroll_y);
            SetSpriteAnimation(3,0,1,64,PlayerFaceAnimation);

            LoadText("STRINGS.DAT","global.txt","010",string,&length);
   			PrintText(9,1,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","011",string,&length);
   			PrintText(9,3,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","012",string,&length);
   			PrintText(9,4,length,string);
            Delay(20);

            InitSprite(1,scroll_x + 298,scroll_y + 42);
            SetSpriteAnimation(1,0,7,8,ArrowAnimation);

            step = 6;
   			break;
          case 6: // Wait ENTER key
         	if( keys[K_ENTER] == 1) {
	            step = 7;
            }
   			break;
         case 7: // Show spech

         	HideSprite(1);

            Draw_EmptyBox(8,0,30,6);
            Delay(10);

            LoadText("STRINGS.DAT","global.txt","014",string,&length);
   			PrintText(9,1,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","015",string,&length);
   			PrintText(9,2,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","016",string,&length);
   			PrintText(9,3,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","017",string,&length);
   			PrintText(9,3,length,string);
            Delay(20);

            ShowSprite(1);

            step = 8;
          	break;
         case 8:  // Wait ENTER key
				if( keys[K_ENTER] == 1) {
               HideSprite(1);
              	HideSprite(3);
  	            VGA_Draw_MapBack();

            	SetSpriteAnimation(2,13,4,12,PlayerAnimation); // Set animation >> right
	            step = 9;
            }
            break;
         case 9: // Move player sprite inside screen
         	if( sprite[2].pos_x < 140 ){
            	sprite[2].pos_x ++;
            }
            else{
               step = 10;
            }
         	break;
         // **** END OF FIRST PART OF THE INTRO ****
         case 10: // Load interior floor 1 map

	        	SetLoadingInterrupt();   // Start loading animation

            // Load floor 1 map
			   LoadMap("MAPS.DAT","floor1.tmx");
			   LoadTiles("TILESETS.DAT","floor1.pcx");
            LoadSprite("SPRITES.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","player.pcx",2,32); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","playerf.pcx",3,64); //Load sprites to one of the fixed structs

            ResetLoadingInterrupt(); // Stop loading animation

			   // Allow scroll
			   scrolling_enabled = 1;
            // Draw map
			   SetMap(0,12);

            Update(0,0);

            InitSprite(2,0,400);
            SetSpriteAnimation(2,13,4,8,PlayerAnimation); // Set animation >> right

			   Fade_in();

            step = 11;
            break;
         case 11: // Move player sprite inside screen
         	if( sprite[2].pos_x < 96 ){
            	sprite[2].pos_x ++;
            }
            else{
               // Set animation walking up
               SetSpriteAnimation(2,25,4,8,PlayerAnimation); // Set animation >> up
               step = 12;
            }
         	break;
         case 12: // Move player and scroll up (inside building)
            	if( sprite[2].pos_x < 116 ){
            	sprite[2].pos_x ++;
               sprite[2].pos_y --;
               scroll_y--;
            }
            else{
               step = 13;
            }
         	break;
         case 13: // Move player and scroll up (inside building)
            if( sprite[2].pos_y > 200 ){
               sprite[2].pos_y --;
               scroll_y--;
            }
            else{
               SetSpriteAnimation(2,26,1,64,PlayerAnimation);  // Set animation >> static
               step = 14;
            }
         	break;
         case 14: // Move player and scroll up (inside building)
         	step = 15;
         	break;
         case 15: // Show spech
            Draw_EmptyBox(0,0,6,6);
            Draw_EmptyBox(8,0,30,6);
            Update(0,0);

            InitSprite(3,scroll_x,scroll_y);
            SetSpriteAnimation(3,0,1,64,PlayerFaceAnimation);

            LoadText("STRINGS.DAT","global.txt","020",string,&length);
   			PrintText(9,1,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","022",string,&length);
   			PrintText(9,3,length,string);

            Delay(50);

            InitSprite(1,scroll_x + 298,scroll_y + 42);
            SetSpriteAnimation(1,0,7,8,ArrowAnimation);

            step = 16;
            break;
         case 16: // Wait ENTER key
				if( keys[K_ENTER] == 1) {
               HideSprite(1);
               HideSprite(3);
               VGA_Draw_MapBack();

               SetSpriteAnimation(2,25,4,8,PlayerAnimation); // Set animation >> walking up
	            step = 17;
            }
            break;
         case 17: // Show spech
            // Move player sprite inside screen
         	if( sprite[2].pos_y > 180 ){
               sprite[2].pos_y --;
            }
            else{
               step = 18;
            }
            break;
         case 18: // Show board
         	SetLoadingInterrupt();   // Start loading animation

         	LoadImage("IMAGES.DAT","cartel.pcx",2); // Load menu background image to non visible page
            LoadSprite("SPRITES.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","playerf.pcx",3, 64); //Load sprites to one of the fixed structs
            
            ResetLoadingInterrupt();   // Stop loading animation

            SetPage(2);

            Fade_in();

            InitSprite(1,scroll_x + 298,scroll_y + 180);
            SetSpriteAnimation(1,0,7,8,ArrowAnimation);

            step = 19;

         case 19: // Wait for ENTER key
            if( keys[K_ENTER] == 1) {
					HideSprite(1);
	            step = 20;
            }
         	break;
         case 20: // Show speech

         	Draw_EmptyBox(0,0,6,6);
            Draw_EmptyBox(8,0,30,6);
            Update(0,0);

            InitSprite(3,scroll_x,scroll_y);
            SetSpriteAnimation(3,0,1,64,PlayerFaceAnimation);

            LoadText("STRINGS.DAT","global.txt","024",string,&length);
   			PrintText(9,1,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","025",string,&length);
   			PrintText(9,2,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","026",string,&length);
   			PrintText(9,3,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","027",string,&length);
   			PrintText(9,4,length,string);
            Delay(20);

            sprite[1].pos_x = scroll_x + 298;
            sprite[1].pos_y = scroll_y + 42;
            ShowSprite(1);

            step = 21;
            break;
			case 21:
            if( keys[K_ENTER] == 1) {
	            step = 22;
            }
            break;
         case 22:  // Show back map (page 0)

           	SetLoadingInterrupt();   // Start loading animation

			   LoadMap("MAPS.DAT","floor1.tmx");   // Load floor 1 map
			   LoadTiles("TILESETS.DAT","floor1.pcx");
            LoadSprite("SPRITES.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","player.pcx",2, 32); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","jessy.pcx",3, 32); //Load sprites to one of the fixed structs

            InitSprite(2,100,185);
            SetSpriteAnimation(2,0,6,12,PlayerAnimation); // Set static

            ResetLoadingInterrupt(); // Stop loading animation

			   // Allow scroll
			   scrolling_enabled = 1;
            // Draw map
			   SetMap(0,0);

            Update(0,0);

 	   		Fade_in();

            step = 23;
         	break;
         case 23: // Scroll down to see the door
          	if( scroll_y < 164 ){
               scroll_y++;
            }
            else{
               step = 24;
            }
         	break;
         case 24: // Load girl sprite

            InitSprite(3,120,364);
            SetSpriteAnimation(3,25,4,8,JessyAnimation);
            step = 25;
         	break;
         case 25: // Move girl
            if(sprite[3].pos_y > 254){
               sprite[3].pos_y --;
            }
            else{
            	step = 26;
            }
         	break;
         case 26: // Move girl
            if(sprite[3].pos_y > 234){
               sprite[3].pos_y --;
               sprite[3].pos_x ++;
            }
            else{
            	step = 27;
            }
         	break;
         case 27: // Show girl
         	SetLoadingInterrupt();   // Start loading animation

         	LoadImage("IMAGES.DAT","jessy.pcx",2); // Load menu background image to non visible page
            LoadSprite("SPRITES.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","playerf.pcx",2, 64); //Load sprites to one of the fixed structs

            ResetLoadingInterrupt();   // Stop loading animation

            SetPage(2);

            Fade_in();

      	   step = 28;
            break;
         case 28: // Show text box

            Draw_EmptyBox(0,0,6,6);
            Draw_EmptyBox(8,0,30,6);
            Update(0,0);

            InitSprite(2,scroll_x,scroll_y);
            SetSpriteAnimation(2,0,1,64,PlayerFaceAnimation);

            LoadText("STRINGS.DAT","global.txt","028",string,&length);
   			PrintText(9,1,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","029",string,&length);
   			PrintText(9,2,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","030",string,&length);
   			PrintText(9,3,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","031",string,&length);
   			PrintText(9,4,length,string);
            Delay(20);

            InitSprite(1,scroll_x + 298,scroll_y + 42);
            SetSpriteAnimation(1,0,7,8,ArrowAnimation);

            step = 29;

   			break;
         case 29: // Wait ENTER key
            if( keys[K_ENTER] == 1) {
            	HideSprite(1);
	            step = 30;
            }
         	break;
         case 30: // Show text box
            Draw_EmptyBox(8,0,30,6);

            Delay(10);

            LoadText("STRINGS.DAT","global.txt","032",string,&length);
   			PrintText(9,1,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","033",string,&length);
   			PrintText(9,2,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","034",string,&length);
   			PrintText(9,3,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","035",string,&length);
   			PrintText(9,4,length,string);
            Delay(20);

            ShowSprite(1);

            step = 31;
   			break;
         case 31: // Wait ENTER key
            if( keys[K_ENTER] == 1) {
            	HideSprite(1);
	            step = 32;
            }
         	break;
         case 32: // Show text box
            Draw_EmptyBox(8,0,30,6);

            Delay(10);

            LoadText("STRINGS.DAT","global.txt","036",string,&length);
   			PrintText(9,1,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","037",string,&length);
   			PrintText(9,2,length,string);
            Delay(20);
            LoadText("STRINGS.DAT","global.txt","038",string,&length);
   			PrintText(9,3,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","039",string,&length);
   			PrintText(9,4,length,string);
            Delay(20);

            ShowSprite(1);

            step = 33;
   			break;
         case 33: // Wait ENTER key
            if( keys[K_ENTER] == 1) {
	            step = 34;
            }
         	break;
         case 34: // Show back map

         	SetLoadingInterrupt();   // Start loading animation

             // Load floor 1 map
			   LoadMap("MAPS.DAT","floor1.tmx");
			   LoadTiles("TILESETS.DAT","floor1.pcx");
            LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","jessy.pcx",2, 32); //Load sprites to one of the fixed structs

            SetSpriteAnimation(1,0,6,12,PlayerAnimation);
            SetSpriteAnimation(2,13,4,8,JessyAnimation);
            InitSprite(1,100,180);
            InitSprite(2,140,225);

            ResetLoadingInterrupt(); // Stop loading animation

			   SetPage(1);

			   // Allow scroll
			   scrolling_enabled = 1;

            // Draw map
			   SetMap(0,6);

            Fade_in();
            step = 35;
         	break;

         case 35: // Move girl
            if(sprite[2].pos_x < 300){
               sprite[2].pos_x ++;
            }
            else{
            	// Move sprite 17 out of the screen and clear it
               HideSprite(2);
            	step = 36;
            }
         	break;
         case 36: // Scroll up back
         	if( scroll_y > 124 ){
               scroll_y--;
            }
            else{
               step = 37;

               Delay(20);
            }
         	break;
         case 37: // Show spech
         	SetLoadingInterrupt();   // Start loading animation

            LoadImage("IMAGES.DAT","player.pcx",2); // Load menu background image to non visible page
            LoadSprite("SPRITES.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRITES.DAT","playerf.pcx",2, 64); //Load sprites to one of the fixed structs

            ResetLoadingInterrupt();   // Stop loading animation

            SetPage(2);
            Fade_in();

            Draw_EmptyBox(0,0,6,6);
            Draw_EmptyBox(8,0,30,6);
            Update(0,0);

            InitSprite(2,scroll_x,scroll_y);
            SetSpriteAnimation(2,0,1,64,PlayerFaceAnimation);

            LoadText("STRINGS.DAT","global.txt","040",string,&length);
   			PrintText(9,1,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","041",string,&length);
   			PrintText(9,2,length,string);
            Delay(80);
            LoadText("STRINGS.DAT","global.txt","042",string,&length);
   			PrintText(9,3,length,string);
            Delay(50);
            LoadText("STRINGS.DAT","global.txt","043",string,&length);
   			PrintText(9,4,length,string);
            Delay(20);

            InitSprite(1,scroll_x + 296,scroll_y + 42);
            SetSpriteAnimation(1,0,7,8,ArrowAnimation);

            step = 38;
            break;
			case 38: // Wait ENTER key
            if( keys[K_ENTER] == 1) {
               endIntro = 1;
            }
            break;
         default:
            endIntro = 1;
            break;
      }
      Update(0,0);  // sprite follow inactive for sprite 16
   }
   // End of intro
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
   LoadFont("FONTS.DAT","FONT.bmp"); //Load a font
   LoadSprite("SPRITES.DAT","cursor.pcx",1,16); //Load sprites to one of the fixed structs
   InitSprite(1,110,menu_pos[option] + vga_page[2]);
   SetSpriteAnimation(1,0,7,6,MenuCursorAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);

   // Draw menu options
   Draw_EmptyBox(13,12,14,4);
   LoadText("STRINGS.DAT","global.txt","001",string,&length);
   PrintText(15,13,length,string);
   LoadText("STRINGS.DAT","global.txt","002",string,&length);
   PrintText(15,14,length,string);
   LoadText("STRINGS.DAT","global.txt","003",string,&length);
   PrintText(15,15,length,string);
   LoadText("STRINGS.DAT","global.txt","004",string,&length);
   PrintText(15,16,length,string);

   Fade_in();

   while( keys[K_ENTER] != 1 )
   {
      sprite[1].pos_y = menu_pos[option] + vga_page[2];

      if( fp_keys[K_UP] == 1) {option--; }
      if( fp_keys[K_DOWN] == 1) {option++;}

     	if(option < 1){ option = 1;}
      if(option > 4){ option = 4;}

      // Main loop
      Update(0,0);
   }

   Fade_out();
}

/////////////////////////////////////////////////////////
// Go to floor 2 from floor 1 left stairs
/////////////////////////////////////////////////////////
void GoToFloor2_Left(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 2 map
	LoadMap("MAPS.DAT","floor2.tmx");
	LoadTiles("TILESETS.DAT","floor2.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,48,185);
  	player.floor = 2;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
	SetMap(0,3);
	Update(0,0);
	Fade_in();
}

/////////////////////////////////////////////////////////
// Go to floor 2 from floor 1 right stairs
/////////////////////////////////////////////////////////
void GoToFloor2_Right(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 2 map
	LoadMap("MAPS.DAT","floor2.tmx");
	LoadTiles("TILESETS.DAT","floor2.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,496,295);
  	player.floor = 2;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
	SetMap(16,10);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to exterior 1 from floor 1 main door
/////////////////////////////////////////////////////////
void GoToExt1_Door(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load ext 1 map
	LoadMap("MAPS.DAT","ext1.tmx");
	LoadTiles("TILESETS.DAT","ext1.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,128,365);
   player.floor = 3;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
	SetMap(0,12);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to exterior 2 from floor 1 backdoor
/////////////////////////////////////////////////////////
void GoToExt2_BackDoor(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load ext 2 map
	LoadMap("MAPS.DAT","ext2.tmx");
	LoadTiles("TILESETS.DAT","ext2.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,484,384);
  	player.floor = 4;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
	SetMap(21,13);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to floor 1 from floor 2 left
/////////////////////////////////////////////////////////
void GoToFloor1_Left(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   player.floor = 1;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,48,175);
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
   SetMap(0,3);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to floor 1 from floor 2 right
/////////////////////////////////////////////////////////
void GoToFloor1_Right(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
 	player.spriteNum = 1;
   player.floor = 1;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,502,295);
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
   SetMap(16,10);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to next day
/////////////////////////////////////////////////////////
void GoToNextDay(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load ext 1 map
	LoadMap("MAPS.DAT","ext1.tmx");
	LoadTiles("TILESETS.DAT","ext1.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,32,365);
   player.floor = 3;
   player.day --;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
   SetMap(0,18);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to floor 1 from entry
/////////////////////////////////////////////////////////
void GoToFloor1_Entry(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   player.floor = 1;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,32,395);
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
   SetMap(0,18);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to exterior 1 from exterior 2
/////////////////////////////////////////////////////////
void GoToExt1_Right(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load ext 1 map
	LoadMap("MAPS.DAT","ext1.tmx");
	LoadTiles("TILESETS.DAT","ext1.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   player.floor = 3;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,868,64);
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
   SetMap(40,0);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to floor 1 Back door
/////////////////////////////////////////////////////////
void GoToFloor1_BackDoor(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   player.floor = 1;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,248,96);
 	ResetLoadingInterrupt(); // Stop loading animation
	scrolling_enabled = 1;
	SetMap(7,0);
   Update(0,0);
	Fade_in();
}

/////////////////////////////////////////////////////////
// Go to gym
/////////////////////////////////////////////////////////
void GoToGym(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load gym map
	LoadMap("MAPS.DAT","gym.tmx");
	LoadTiles("TILESETS.DAT","gym.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   player.floor = 5;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,200,96);
	ResetLoadingInterrupt(); // Stop loading animation
	SetMap(15,0);
   Update(0,0);
	Fade_in();
}

/////////////////////////////////////////////////////////
// Go to exterior 2 from gym
/////////////////////////////////////////////////////////
void GoToExt2_Gym(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load ext 2 map
	LoadMap("MAPS.DAT","ext2.tmx");
	LoadTiles("TILESETS.DAT","ext2.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   player.floor = 4;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,200,95);
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
   SetMap(15,10);
   Update(0,0);
   Fade_in();
}

/////////////////////////////////////////////////////////
// Go to exterior 2 from ext1 right
/////////////////////////////////////////////////////////
void GoToExt2_Right(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load ext 2 map
	LoadMap("MAPS.DAT","ext2.tmx");
	LoadTiles("TILESETS.DAT","ext2.pcx");
  	LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,784,456);
  	player.floor = 4;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
	SetMap(40,12);
   Update(0,0);
   Fade_in();
}


/////////////////////////////////////////////////////////
// New game
// - Starts the party...
/////////////////////////////////////////////////////////
void NewGame(void) {
	SetLoadingInterrupt();   // Start loading animation

   LoadFont("FONTS.DAT","FONT.bmp"); //Load a font
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRITES.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRITES.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
 	player.spriteNum = 1;
   player.floor = 1;
   player.day = 10;
   player.hour = 9;
   player.min = 0;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   InitSprite(1,100,185);
   InitSprite(2,512,402);

   ResetLoadingInterrupt(); // Stop loading animation
   // Allow scroll
   scrolling_enabled = 1;
   // Draw map
   SetMap(0,4);
   Update(0,0);

   Fade_in();

	/*scrolling_enabled = 0;
   while( keys[K_ESC] != 1 )
   {
   	if( keys[K_UP] == 1 ){scroll_y --;}
   	if( keys[K_DOWN] == 1 ){scroll_y ++;}

      Update(0,0);
   } */


   while( keys[K_ESC] != 1 )
   {
   	switch(player.floor){
      	case 1: // floor 1
         	if(player.event == 1){ GoToFloor2_Left();}
         	if(player.event == 2){ GoToFloor2_Right();}
            if(player.event == 3){ GoToExt1_Door();}
            if(player.event == 4){ GoToExt2_BackDoor();}
         	break;
         case 2: // floor 2
            if(player.event == 1){ GoToFloor1_Left();}
         	if(player.event == 2){ GoToFloor1_Right();}
         	break;
         case 3: // exterior 1
            if(player.event == 1){ GoToNextDay();}
         	if(player.event == 2){ GoToFloor1_Entry();}
           	if(player.event == 3){ GoToExt2_Right();}
         	break;
         case 4: // exterior 2
            if(player.event == 1){ GoToExt1_Right();}
         	if(player.event == 2){ GoToGym();}
         	if(player.event == 3){ GoToFloor1_BackDoor();}
         	break;
         case 5: // gym
            if(player.event == 1){ GoToExt2_Gym();}
         	break;
         default:
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


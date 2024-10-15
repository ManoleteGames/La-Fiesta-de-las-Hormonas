/***********************
*  INTRO
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// New game intro
// - Sets a little intro at the very begining of the game
// - Can be skipped by pushing ESC
/////////////////////////////////////////////////////////
void Intro(void){
	byte endIntro = 0; // End intro flag
   byte step = 0; // Current intro step

  	SetLoadingInterrupt();   // Start loading animation

   LoadFont("FONTS.DAT","FONT.bmp"); //Load a font
   // Load map and tilesets
   LoadMap("MAPS.DAT","ext1.tmx");
   LoadTiles("TILESETS.DAT","ext1.pcx");
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");

   LoadSprite("SPRMISC.DAT","enter.pcx",1, 16); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","player.pcx",2, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","playerf.pcx",3, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRMISC.DAT","bird.pcx",4, 32); //Load sprites to one of the fixed structs

   ResetLoadingInterrupt(); // Stop loading animation

   scrolling_enabled = 1;
   SetMap(0,0);    // Draw loaded map

   InitSprite(1,0,0);
  	InitSprite(2,0,360);
  	InitSprite(3,0,0);
   InitSprite(4,102,96);
   SetSpriteAnimation(1,0,4,8,EnterAnimation);
   SetSpriteAnimation(2,13,4,8,PlayerAnimation); // Set animation >> right
   SetSpriteAnimation(3,0,1,48,PlayerFaceAnimation);
   SetSpriteAnimation(4,0,14,8,BirdAnimation);

   HideSprite(1);
   HideSprite(2);
   HideSprite(3);
   HideSprite(4);

   Fade_in();

   // Intro loop
   while( (keys[K_ESC] != 1) && (endIntro != 1) )
   {
   	// Animation
      switch(step){
      	case 0:  // Init bird sprite
         	ShowSprite(4);
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
				ShowSprite(2);
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
            Speech(3,1,"GLB_STR.DAT","intro.txt","010","011","012",0);
            Speech(3,1,"GLB_STR.DAT","intro.txt","014","015","017",0);
            step = 8;
            break;
         case 8:  // Wait ENTER key
            HideSprite(1);
           	HideSprite(3);
            DrawMapBack();
           	SetSpriteAnimation(2,13,4,12,PlayerAnimation); // Set animation >> right
            step = 9;
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

         // **** SECOND INTRO SCENE *******
         case 10: // Load interior floor 1 map

	        	SetLoadingInterrupt();   // Start loading animation

            // Load floor 1 map
			   LoadMap("MAPS.DAT","floor1.tmx");
			   LoadTiles("TILESETS.DAT","floor1.pcx");
            LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRCHR.DAT","player.pcx",2,32); //Load sprites to one of the fixed structs
            LoadSprite("SPRFACE.DAT","playerf.pcx",3,48); //Load sprites to one of the fixed structs

            ResetLoadingInterrupt(); // Stop loading animation

			   // Allow scroll
			   scrolling_enabled = 1;
            // Draw map
			   SetMap(0,12);

            InitSprite(1,0,0);
  				InitSprite(2,0,400);
  				InitSprite(3,0,0);

   			SetSpriteAnimation(1,0,4,8,EnterAnimation);
   			SetSpriteAnimation(2,13,4,8,PlayerAnimation); // Set animation >> right
   			SetSpriteAnimation(3,0,1,48,PlayerFaceAnimation);

  				HideSprite(1);
   			HideSprite(3);

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
               if(scroll_y > vga_page[1]){scroll_y--;}
            }
            else{
               step = 13;
            }
         	break;
         case 13: // Move player and scroll up (inside building)
            if( sprite[2].pos_y > 200 ){
               sprite[2].pos_y --;
               if(scroll_y > vga_page[1]){ scroll_y--; }
            }
            else{
               SetSpriteAnimation(2,26,1,48,PlayerAnimation);  // Set animation >> static
               step = 14;
            }
         	break;
         case 14: // empty
         	step = 15;
         	break;
         case 15: // Show spech
         	Speech(3,1,"GLB_STR.DAT","intro.txt","020","022",0,0);
            step = 16;
            break;
         case 16: // Wait ENTER key
				DrawMapBack();
            SetSpriteAnimation(2,25,4,8,PlayerAnimation); // Set animation >> walking up
	         step = 17;
            break;
         case 17: // Move player up
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
            LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRFACE.DAT","playerf.pcx",3, 48); //Load sprites to one of the fixed structs

            InitSprite(1,0,0);
  				InitSprite(3,0,0);

   			SetSpriteAnimation(1,0,4,8,EnterAnimation);
   			SetSpriteAnimation(3,0,1,48,PlayerFaceAnimation);

   			HideSprite(3);

            ResetLoadingInterrupt();   // Stop loading animation

            SetPage(2);

            sprite[1].pos_x =  scroll_x + 298;
            sprite[1].pos_y = scroll_y + 180;

            Fade_in();

            step = 19;

         case 19: // Wait for ENTER key
            if( keys[K_ENTER] != 1) {
            	Update(0,0);
            }
            else {
					HideSprite(1);
	            step = 20;
            }
         	break;
         case 20: // Show speech
           	Speech(3,1,"GLB_STR.DAT","intro.txt","024","025","026","027");
            step = 22;
            break;
         case 22:  // Show back map (page 0)
           	SetLoadingInterrupt();   // Start loading animation

			   LoadMap("MAPS.DAT","floor1.tmx");   // Load floor 1 map
			   LoadTiles("TILESETS.DAT","floor1.pcx");
            LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRCHR.DAT","player.pcx",2, 32); //Load sprites to one of the fixed structs
            LoadSprite("SPRCHR.DAT","jessy.pcx",3, 32); //Load sprites to one of the fixed structs

            InitSprite(2,100,185);
            SetSpriteAnimation(2,0,6,12,PlayerAnimation); // Set static

            ResetLoadingInterrupt(); // Stop loading animation

			   // Allow scroll
			   scrolling_enabled = 1;
            // Draw map
			   SetMap(0,0);

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
            LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRFACE.DAT","playerf.pcx",3, 48); //Load sprites to one of the fixed structs

            ResetLoadingInterrupt();   // Stop loading animation

            SetPage(2);

         	LoadImage("IMAGES.DAT","jessy2.pcx",1); // Load menu background image to non visible page

	         InitSprite(1,scroll_x + 298,scroll_y + 42);
  				InitSprite(3,scroll_x,scroll_y);

   			SetSpriteAnimation(1,0,4,8,EnterAnimation);
   			SetSpriteAnimation(3,0,1,48,PlayerFaceAnimation);

            HideSprite(1);
            HideSprite(3);

            Fade_in();

      	   step = 28;
            break;
         case 28: // Show text box
           	Speech(3,1,"GLB_STR.DAT","intro.txt","028","029","030","031");
            step = 30;
   			break;
         case 30: // Show text box
            SetPage(1);
				Speech(3,1,"GLB_STR.DAT","intro.txt","032","033","034","035");
            step = 37;
   			break;
         case 37: // Show spech
         	SetLoadingInterrupt();   // Start loading animation

            LoadImage("IMAGES.DAT","player.pcx",2); // Load menu background image to non visible page
            LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
            LoadSprite("SPRFACE.DAT","playerf.pcx",3, 48); //Load sprites to one of the fixed structs

            ResetLoadingInterrupt();   // Stop loading animation

            SetPage(2);

            InitSprite(1,scroll_x + 296,scroll_y + 42);
            InitSprite(3,scroll_x,scroll_y);
            SetSpriteAnimation(1,0,4,8,EnterAnimation);
            SetSpriteAnimation(3,0,1,48,PlayerFaceAnimation);

            HideSprite(1);
            HideSprite(3);

            Fade_in();

            Speech(3,1,"GLB_STR.DAT","intro.txt","036","037","038","039");
            Speech(3,1,"GLB_STR.DAT","intro.txt","040","041","042","043");
            step = 38;
            break;
			case 38: // Wait ENTER key
            endIntro = 1;
            break;
         default:
            endIntro = 1;
            break;
      }
      Update(0,0);  // sprite follow inactive for sprite 16
   }
   // End of intro
}

/***********************
*  exterior 1
************************/

#include "source\engine\engine.h"


/////////////////////////////////////////////////////////
// Go to exterior 1
/////////////////////////////////////////////////////////
void far GoToExt1(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

	LoadMap("MAPS.DAT","ext1.tmx");
	LoadTiles("TILESETS.DAT","ext1.pcx");

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);

   switch(player.day){
   	case 4:
         break;
      case 3:
      	break;
      case 2:
   		if(player.mission_bag < 3){
         	LoadSprite("SPRMISC.DAT","bag.pcx",4, 32); //Load sprites to one of the fixed structs
	         SetSpriteAnimation(4,0,1,12,CharacterAnimation2);
      	   InitSprite(4,222,346);
         }
      	break;
      case 1:
      	break;
   }

   player.floor = 3;

   InitSprite(player.spriteNum,x,y);

   ResetLoadingInterrupt(); // Stop loading animation
   
   // Allow scroll
   scrolling_enabled = 1;

   // Draw map
   SetMap();
  
	Fade_in();

   panelScrolling = 1;
   showPanel = 1;
}


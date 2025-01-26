/***********************
*  exterior 2
************************/

#include "source\engine\engine.h"


/////////////////////////////////////////////////////////
// Go to exterior 2
/////////////////////////////////////////////////////////
void far GoToExt2(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

	LoadMap("MAPS.DAT","ext2.tmx");
	LoadTiles("TILESETS.DAT","ext2.pcx");

   // Disable hotspots by default
   player.ext2_hotspot_mask[1] = 0;
   player.ext2_hotspot_mask[2] = 0;

   switch(player.day){
   	case 10:
         // Load thugs sprites
   		if( player.scn_thugs == 1){
   			LoadSprite("SPRCHR1.DAT","toni.pcx",7, 32); //Load sprites to one of the fixed structs
   			LoadSprite("SPRCHR1.DAT","jon.pcx",8, 32); //Load sprites to one of the fixed structs
   			LoadSprite("SPRCHR1.DAT","erik.pcx",9, 32); //Load sprites to one of the fixed structs

      		SetSpriteAnimation(7,0,6,30,CharacterAnimation3);
   			SetSpriteAnimation(8,0,6,23,CharacterAnimation2);
   			SetSpriteAnimation(9,0,6,19,CharacterAnimation2);

      		InitSprite(7,808,362);
   			InitSprite(8,844,362);
   			InitSprite(9,776,362);

   		}
      	break;
      case 9:
         // Load nerd sprites
         LoadSprite("SPRCHR1.DAT","david.pcx",3, 32); //Load sprites to one of the fixed structs
         LoadSprite("SPRCHR1.DAT","xavi.pcx",4, 32); //Load sprites to one of the fixed structs
         LoadSprite("SPRCHR1.DAT","alain.pcx",5, 32); //Load sprites to one of the fixed structs
         LoadSprite("SPRCHR1.DAT","antonio.pcx",6, 32); //Load sprites to one of the fixed structs
         SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
         SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
         SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
         SetSpriteAnimation(6,0,6,19,CharacterAnimation2);
         InitSprite(3,296,302);
         InitSprite(4,328,302);
         InitSprite(5,354,322);
         InitSprite(6,276,322);
      	break;
      default:
      	break;
   }

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);
   InitSprite(player.spriteNum,x,y);

   player.floor = 4;

   ResetLoadingInterrupt(); // Stop loading animation

   // Allow scroll
   scrolling_enabled = 1;
   // Draw map
   // - calculate map position
   mapx = (x>>4)-10;
   if(mapx < 0){ mapx = 0;}
   if((mapx + 21) > map_width){ mapx = map_width - 21;}
   mapy = (y>>4)-6;
   if(mapy < 0){ mapy = 0;}
   SetMap(mapx,mapy);

   Update(0);

	Fade_in();

   panelScrolling = 1;
   showPanel = 1;
}


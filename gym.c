  /***********************
*  gym
************************/

#include "source\engine\engine.h"



/////////////////////////////////////////////////////////
// Go to gym
/////////////////////////////////////////////////////////
void far GoToGym(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

   // Load gym map
   switch(player.day){
   	case 4:   //////////////////////////// day 4 ///////////////////////////
			LoadMap("MAPS.DAT","gym_4.tmx");
      	break;
      case 3:   //////////////////////////// day 3 ///////////////////////////
			LoadMap("MAPS.DAT","gym_3.tmx");
      	break;
      case 2:   //////////////////////////// day 2 ///////////////////////////
         if(player.mission_chair){ LoadMap("MAPS.DAT","gym_1.tmx"); }
			else{ LoadMap("MAPS.DAT","gym_2.tmx"); }
      	break;
      case 1:   //////////////////////////// day 1 ///////////////////////////
			LoadMap("MAPS.DAT","gym_1.tmx");
      	break;
   }

	LoadTiles("TILESETS.DAT","gym.pcx");

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
	SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);

   LoadSprite("SPRCHR2.DAT","sensei.pcx",2, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(2,0,6,30,CharacterAnimation3);
   InitSprite(2,208,162);

   switch(player.day){
   	case 4:
      	break;
   	case 3: //////////////////////////// day 3 ///////////////////////////
         LoadSprite("SPRCHR1.DAT","jessy.pcx",3, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","vane.pcx",4, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","fany.pcx",5, 32); //Load sprites to one of the fixed structs
   		SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   		SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   		SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   		InitSprite(3,138,190);
   		InitSprite(4,112,202);
   		InitSprite(5,168,202);
      	break;
      case 2: //////////////////////////// day 2 ///////////////////////////
      	if((player.mission_bag > 3)|(player.scn_girls == 99)){
         	LoadSprite("SPRCHR1.DAT","jessy.pcx",3, 32); //Load sprites to one of the fixed structs
            SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
            InitSprite(3,138,190);
         }

         LoadSprite("SPRCHR1.DAT","vane.pcx",4, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","fany.pcx",5, 32); //Load sprites to one of the fixed structs
   		SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   		SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   		InitSprite(4,112,202);
   		InitSprite(5,168,202);
      	break;
      case 1: //////////////////////////// day 1 ///////////////////////////
      	LoadSprite("SPRCHR1.DAT","jessy.pcx",3, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","vane.pcx",4, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","fany.pcx",5, 32); //Load sprites to one of the fixed structs
   		SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   		SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   		SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   		InitSprite(3,138,190);
   		InitSprite(4,112,202);
   		InitSprite(5,168,202);
      	break;
   }

   InitSprite(player.spriteNum,x,y);

   player.floor = 5;

   ResetLoadingInterrupt(); // Stop loading animation

   // Allow scroll
   scrolling_enabled = 1;

   // Draw map
   SetMap();
   
	Fade_in();

   panelScrolling = 1;
   showPanel = 1;
}


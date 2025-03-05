/***********************
*  FLOOR 1
************************/

#include "source\engine\engine.h"

void far GoToFloor1(int x, int y){
	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

  	LoadMap("MAPS.DAT","floor1.tmx"); // Load floor 1 map
  	LoadTiles("TILESETS.DAT","floor1.pcx");

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);

   switch(player.day){
   	case 4:  ////////////////////// day 4 //////////////////////////
      	// Load nerd sprites
         LoadSprite("SPRCHR1.DAT","david.pcx",4, 32); //Load sprites to one of the fixed structs
         LoadSprite("SPRCHR1.DAT","xavi.pcx",5, 32); //Load sprites to one of the fixed structs
         LoadSprite("SPRCHR1.DAT","alain.pcx",6, 32); //Load sprites to one of the fixed structs
         LoadSprite("SPRCHR1.DAT","antonio.pcx",7, 32); //Load sprites to one of the fixed structs
         SetSpriteAnimation(4,0,6,8,CharacterAnimation2);
         SetSpriteAnimation(5,0,6,30,CharacterAnimation3);
         SetSpriteAnimation(6,0,6,23,CharacterAnimation3);
         SetSpriteAnimation(7,0,6,19,CharacterAnimation2);
         InitSprite(4,396,102);
         InitSprite(5,408,122);
         InitSprite(6,434,142);
         InitSprite(7,396,142);

         if((player.scn_janitor == 99)|(player.mission_cheat < 3)){
         	LoadSprite("SPRCHR2.DAT","conser.pcx",3, 32); //Load sprites to one of the fixed structs
      		SetSpriteAnimation(3,0,6,12,CharacterAnimation2);
      		InitSprite(3,64,128);
         } else {
         	LoadSprite("SPRCHR2.DAT","conser.pcx",3, 32); //Load sprites to one of the fixed structs
            SetSpriteAnimation(3,0,6,12,CharacterAnimation2);
            InitSprite(3,446,412);
         }


         if(player.scn_director == 99){
         	LoadSprite("SPRCHR2.DAT","dsleep.pcx",2, 32); //Load sprites to one of the fixed structs
   			SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   			InitSprite(2,512,402);
         } else {
            LoadSprite("SPRCHR2.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
   			SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   			InitSprite(2,512,402);
         }
         break;
      case 3:  ////////////////////// day 3 //////////////////////////
      	LoadSprite("SPRCHR1.DAT","toni.pcx",8, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","jon.pcx",9, 32); //Load sprites to one of the fixed structs
   		LoadSprite("SPRCHR1.DAT","erik.pcx",10, 32); //Load sprites to one of the fixed structs

      	SetSpriteAnimation(8,0,6,30,CharacterAnimation3);
   		SetSpriteAnimation(9,0,6,23,CharacterAnimation2);
   		SetSpriteAnimation(10,0,6,19,CharacterAnimation2);

   		InitSprite(9,398,102);
         InitSprite(8,414,122);
         InitSprite(10,398,142);

         LoadSprite("SPRCHR2.DAT","conser.pcx",3, 32); //Load sprites to one of the fixed structs
         SetSpriteAnimation(3,0,6,12,CharacterAnimation2);
         InitSprite(3,64,128);

         if((player.scn_main == 0)&&(player.item_keys == 0)){
         	LoadSprite("SPRMISC.DAT","keys.pcx",4, 32); //Load sprites to one of the fixed structs
	         SetSpriteAnimation(4,0,1,12,CharacterAnimation2);
      	   InitSprite(4,522,346);
         }

         LoadSprite("SPRCHR2.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
         SetSpriteAnimation(2,0,15,12,DirectorAnimation);
         InitSprite(2,512,402);

      	break;
      case 2:  ////////////////////// day 2 //////////////////////////
      	if((player.mission_bag <= 3)&&(player.scn_girls != 99)){
         	LoadSprite("SPRCHR1.DAT","jessy.pcx",4, 32); //Load sprites to one of the fixed structs
      		SetSpriteAnimation(4,0,6,8,CharacterAnimation2);
         	InitSprite(4,246,190);
         }

      	LoadSprite("SPRCHR2.DAT","conser.pcx",3, 32); //Load sprites to one of the fixed structs
         SetSpriteAnimation(3,0,6,12,CharacterAnimation2);
         InitSprite(3,64,128);

         if(player.scn_director == 99){
         	LoadSprite("SPRCHR2.DAT","dsleep.pcx",2, 32); //Load sprites to one of the fixed structs
   			SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   			InitSprite(2,512,402);
         } else {
            LoadSprite("SPRCHR2.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
   			SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   			InitSprite(2,512,402);
         }

      	break;
      case 1:  ////////////////////// day 1 //////////////////////////
      	if((player.mission_fight <= 1)&&(player.scn_main != 2)){
         	LoadSprite("SPRCHR1.DAT","jon.pcx",3, 32); //Load sprites to one of the fixed structs
         	SetSpriteAnimation(3,0,6,23,CharacterAnimation2);
         	InitSprite(3,286,182);

         	LoadSprite("SPRCHR1.DAT","antonio.pcx",4, 32); //Load sprites to one of the fixed structs
         	SetSpriteAnimation(4,0,6,19,CharacterAnimation2);
         	InitSprite(4,246,182);
         }
         if((player.mission_fight > 1)&&(player.scn_main != 2)){
            LoadSprite("SPRCHR2.DAT","conser.pcx",3, 32); //Load sprites to one of the fixed structs
         	SetSpriteAnimation(3,0,6,12,CharacterAnimation2);
         	InitSprite(3,64,128);

            LoadSprite("SPRCHR1.DAT","toni.pcx",8, 32); //Load sprites to one of the fixed structs
            SetSpriteAnimation(8,0,6,30,CharacterAnimation3);
   			InitSprite(8,452,400);

         	LoadSprite("SPRCHR1.DAT","xavi.pcx",5, 32); //Load sprites to one of the fixed structs
         	SetSpriteAnimation(5,0,6,30,CharacterAnimation3);
         	InitSprite(5,452,416);
         }
         if(player.scn_janitor == 99){
            LoadSprite("SPRCHR2.DAT","conser.pcx",3, 32); //Load sprites to one of the fixed structs
         	SetSpriteAnimation(3,0,6,12,CharacterAnimation2);
         	InitSprite(3,64,128);
         }
         LoadSprite("SPRCHR2.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
         SetSpriteAnimation(2,0,15,12,DirectorAnimation);
         InitSprite(2,512,402);

      	break;
   }

  	InitSprite(player.spriteNum,x,y);
   player.floor = 1;

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

   Update(1);

   Fade_in();

   panelScrolling = 1;
   showPanel = 1;
}


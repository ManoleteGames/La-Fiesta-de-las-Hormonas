/***********************
*  ALL DAY EVENTS
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Go to floor 2 from floor 1 left stairs
/////////////////////////////////////////////////////////
void GoToFloor2_Left(void){
	SetLoadingInterrupt();   // Start loading animation
   // Load floor 2 map
	LoadMap("MAPS.DAT","floor2.tmx");
	LoadTiles("TILESETS.DAT","floor2.pcx");
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
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
  	LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   InitSprite(1,784,456);
  	player.floor = 4;
   ResetLoadingInterrupt(); // Stop loading animation
   scrolling_enabled = 1;
	SetMap(40,12);
   Update(0,0);
   Fade_in();
}

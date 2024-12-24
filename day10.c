/***********************
*  DAY 10
************************/

#include "source\engine\engine.h"

// Existing scenes
// 0. Freaks appear on the arcade machine.
//    Thugs assault after speak with freaks
//    Jessy and her friends are on the second floor speaking
// 1. Freaks move to the backschool and play a chalk painted heroquest on the floor.
//		Thugs smoke on the backschool and paint with chalk on the wall
//		Jessy and her friends are on the second floor speaking
// 2. All are on the second floor waiting for the maths exam.
// 3. Freaks are on the second floor speaking
//		Thugs assault you after go down to the first floor.
//    Jessy and her frieds are on the caffe shop

byte scene = 1;
byte freaks = 0;
byte director = 0;

void D10_GoToFloor1(int x, int y){
	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

  	LoadMap("MAPS.DAT","floor1.tmx"); // Load floor 1 map
  	LoadTiles("TILESETS.DAT","floor1.pcx");

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);

   LoadSprite("SPRCHR2.DAT","conser.pcx",7, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(7,0,6,12,CharacterAnimation2);
	InitSprite(7,64,128);

   LoadSprite("SPRCHR2.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs  /// MEMORY LEAK!!!!////
   SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   InitSprite(2,512,402);

   // Load nerd sprites
   if( scene == 0){

   	LoadSprite("SPRCHR1.DAT","david.pcx",3, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","xavi.pcx",4, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","alain.pcx",5, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","antonio.pcx",6, 32); //Load sprites to one of the fixed structs
   	SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   	SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   	SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   	SetSpriteAnimation(6,0,6,19,CharacterAnimation2);
      InitSprite(3,396,102);
   	InitSprite(4,408,122);
   	InitSprite(5,434,142);
   	InitSprite(6,396,142);
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

   Update(0);

   Fade_in();

   panelScrolling = 1;
   showPanel = 1;
}

/////////////////////////////////////////////////////////
// Go to floor 2
/////////////////////////////////////////////////////////
void D10_GoToFloor2(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

	LoadMap("MAPS.DAT","floor2.tmx");
	LoadTiles("TILESETS.DAT","floor2.pcx");

   // Load jessy and friends sprites
   if(( scene == 0)||(scene == 1)){

   	LoadSprite("SPRCHR1.DAT","jessy.pcx",3, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","vane.pcx",4, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","fany.pcx",5, 32); //Load sprites to one of the fixed structs
   	SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   	SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   	SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   	InitSprite(3,158,170);
   	InitSprite(4,132,182);
   	InitSprite(5,188,182);
   }

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);
   InitSprite(player.spriteNum,x,y);


   player.floor = 2;

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

/////////////////////////////////////////////////////////
// Go to exterior 1
/////////////////////////////////////////////////////////
void D10_GoToExt1(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

	LoadMap("MAPS.DAT","ext1.tmx");
	LoadTiles("TILESETS.DAT","ext1.pcx");
   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);
   InitSprite(player.spriteNum,x,y);

   player.floor = 3;

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

/////////////////////////////////////////////////////////
// Go to exterior 2
/////////////////////////////////////////////////////////
void D10_GoToExt2(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

	LoadMap("MAPS.DAT","ext2.tmx");
	LoadTiles("TILESETS.DAT","ext2.pcx");

   // Load nerd and thugs sprites
   if( scene == 1){

   	LoadSprite("SPRCHR1.DAT","david.pcx",3, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","xavi.pcx",4, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","alain.pcx",5, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR1.DAT","antonio.pcx",6, 32); //Load sprites to one of the fixed structs

      SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   	SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   	SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   	SetSpriteAnimation(6,0,6,19,CharacterAnimation2);

      InitSprite(3,286,302);
   	InitSprite(4,328,302);
   	InitSprite(5,354,322);
   	InitSprite(6,256,322);


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

/////////////////////////////////////////////////////////
// Go to gym
/////////////////////////////////////////////////////////
void D10_GoToGym(int x, int y){

	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

   // Load gym map
	LoadMap("MAPS.DAT","gym.tmx");
	LoadTiles("TILESETS.DAT","gym.pcx");
   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
	SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);
   InitSprite(player.spriteNum,x,y);

   player.floor = 5;

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

/////////////////////////////////////////////////////////
// Go to next day
/////////////////////////////////////////////////////////
void D10_GoToNextDay(int x, int y){

   player.day --;

	D10_GoToExt1(x, y);
}

/////////////////////////////////////////////////////////
// Go to encounter with nerds
/////////////////////////////////////////////////////////
void D10_GoToNerds(void){
	byte option;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES.DAT","frikis.pcx",2); // Load menu background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("antof.pcx","D10_STR.DAT","D10NERD.TXT","001","002","003",0);
   Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","005","006","007","008");
   Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","010","011","012","013");
   Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","017","018","019","020");
   option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10NERD.TXT","022","023","024","025");

   switch(option){
   	case 1: // VAYA PANDA DE FRIKIS ESTAIS HECHOS
         Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","027","028",0,0);
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","029","030",0,0);
         Speech("antof.pcx","D10_STR.DAT","D10NERD.TXT","031","032","033",0);
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
         player.rel_freaks ++;
      	break;
     	case 2: // OS HABEIS ENTERADO QUE HAY UN BAILE?
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","035","036","037","038");
         Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","039","040","041",0);
         Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","043","044","045",0);
         Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","051","052","053","054");
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
      case 3: // SILVER AXE ES LO MEJOR!
         Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","055","056","057",0);
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","058","059","060","061");
         Speech("antof.pcx","D10_STR.DAT","D10NERD.TXT","062","063",0,0);
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
         player.rel_freaks ++;
         player.rel_freaks ++;
      	break;
      case 4: // DONDE ESTE UN JUEGO DE NAVES...
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","065","066","067",0);
         Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","068","069",0,0);
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","071","072",0,0);
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
         player.rel_freaks ++;
      	break;
   }
}

/////////////////////////////////////////////////////////
// Go to encounter with toni at lobby
/////////////////////////////////////////////////////////
void D10_GoToMacarras(void){
 	byte option;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

   SetSpriteAnimation(1,0,6,12,PlayerAnimation);

   LoadSprite("SPRCHR1.DAT","jon.pcx",10, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR1.DAT","toni.pcx",11, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR1.DAT","erik.pcx",12, 32); //Load sprites to one of the fixed structs

   SetSpriteAnimation(10,0,6,30,CharacterAnimation2);
   SetSpriteAnimation(11,0,6,23,CharacterAnimation3);
   SetSpriteAnimation(12,0,6,19,CharacterAnimation3);

   sprite[10].pos_x = sprite[player.spriteNum].pos_x;
   sprite[10].pos_y = sprite[player.spriteNum].pos_y - 32;
   sprite[11].pos_x = sprite[player.spriteNum].pos_x;
   sprite[11].pos_y = sprite[player.spriteNum].pos_y + 32;
   sprite[12].pos_x = sprite[player.spriteNum].pos_x - 32;
   sprite[12].pos_y = sprite[player.spriteNum].pos_y;

	DrawSpriteDestructive(10);
   Delay(40);
   DrawSpriteDestructive(11);
   Delay(40);
	DrawSpriteDestructive(12);
   Delay(40);

	SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES.DAT","macarras.pcx",2); // Load menu background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","001","002","003",0);
   Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","005",0,0,0);
   Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","009",0,0,0);
   Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","013",0,0,0);
   Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","017","018","019","020");
   option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10MACA.TXT","023","024","025","026");
   switch(option){
   	case 1: //A FUMARME UN PITI AL RECRE
         player.rel_thugs ++;
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","029","030","031",0);
         break;
      case 2: //SOLO PASABA POR AQUI
        	Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","035","036","037",0);
         Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","039",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
      case 3: //A CLASE, COMO ES DEBIDO
         player.rel_thugs --;
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","047","048","049","050");
         Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","051",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
      case 4: //APARTATE MATON, O ME CHIVO
	      player.rel_thugs --;
         player.rel_thugs --;
         Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","043","044",0,0);
         Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","045",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","046",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","035","036","037",0);
         Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","039",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
   }
}

/////////////////////////////////////////////////////////
// Day 10. Events
/////////////////////////////////////////////////////////
void D10_Events(byte event){
	switch(player.floor){
   	case 1: // Floor 1
			if(player.floor1_event_mask[event] == 1){
        		if(player.event == 1){ D10_GoToFloor2(50,185);}
	        	if(player.event == 2){ D10_GoToFloor2(496,275);}
	         if(player.event == 3){ D10_GoToExt1(128,365);}
            if(player.event == 4){ D10_GoToExt2(484,384);}
            if(player.event == 9){
					director = 1;
               scene = 1;
               D10_GoToMacarras();
   				// Update player status
   				player.day = 10;
   				player.hour = 8;
   				player.min = 55;
               player.floor1_event_mask[9] = 0; // Disable event
               player.floor1_hotspot_mask[4] = 1;  // Enable hotspot arcade
   				player.floor1_hotspot_mask[11] = 0;  // Disable hotspot nerds
               D10_GoToFloor1(232, 155);
   				Speech("playerf.pcx","D10_STR.DAT","D10MACA.TXT","052","053","054","055");
            }
		   }
      	break;
      case 2: // Floor 2
      	if(player.floor2_event_mask[event] == 1){
	         if(player.event == 1){ D10_GoToFloor1(50,175);}
         	if(player.event == 2){ D10_GoToFloor1(502,295);}
		   }
      	break;
     	case 3: // Ext 1
      	if(player.ext1_event_mask[event] == 1){
         	if(player.event == 1){ D10_GoToNextDay(32,365);}
         	if(player.event == 2){ D10_GoToFloor1(32,395);}
           	if(player.event == 3){ D10_GoToExt2(784,456);}
		   }
      	break;
      case 4: // Ext 2
      	if(player.ext2_event_mask[event] == 1){
         	if(player.event == 1){ D10_GoToExt1(868,64);}
         	if(player.event == 2){ D10_GoToGym(56,296);}
         	if(player.event == 3){ D10_GoToFloor1(248,96);}
		   }
      	break;
      case 5: // Gym
      	if(player.gym_event_mask[event] == 1){
            if(player.event == 1){ D10_GoToExt2(648,256); }
		   }
      	break;
   }
}

void D10_Hotspots(byte hotspot){
	byte option;
	switch(player.floor){
   	case 1: // Floor 1
			if(player.floor1_hotspot_mask[hotspot] == 1){
            if(player.hotspot == 1){ // NEWS BOARD
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","001","002",0,0);
            }

            if(player.hotspot == 2){ // EXTINGUISHER
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","005","006","007",0);
   				option = SpeechSelection(2,"playerf.pcx","D10_STR.DAT","D10GLB.TXT","010","011",0,0);

   				switch(option){
				   	case 1: // ABRIR EXTINTOR
                 	   LoadSprite("SPRMISC.DAT","smoke.pcx",9, 64); //Load sprites to one of the fixed structs
						   SetSpriteAnimation(9,0,1,64,PlayerFaceAnimation);
			      		player.good = 0;
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_x;
							HideSprite(1);
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x + 10;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y + 8;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 8;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 10;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x + 13;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 2;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 17;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y + 12;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 25;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 23;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);

                     SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up
                     ShowSprite(1);
                     Update(0);
			        		Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","013",0,0,0);

                     EndGameExtinguisher();

			      		break;
     					case 2: // NO ABRIR EXTINTOR
         				Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","015",0,0,0);
      					break;
               }
            }

            if(player.hotspot == 3){ // GIRLS BATHROOM
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","041","042",0,0);
            }

            if(player.hotspot == 4){ // ARCADE
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","078","079",0,0);
            }

            if(player.hotspot == 5){ // BAR
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","003","004",0,0);
            }

            if(player.hotspot == 6){ // EXAMENES
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","081","082",0,0);
   				option = SpeechSelection(2,"playerf.pcx","D10_STR.DAT","D10GLB.TXT","085","086",0,0);

   				switch(option){
				   	case 1: // COGER LOS EXAMENES
                  	player.good--;
                     player.mission_cheat = 1;
                     player.floor2_hotspot_mask[3] = 0;
                     SetSpriteAnimation(1,0,6,12,PlayerAnimation);
                     Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","088","089",0,0);
                     director = 3;
			      		break;
     					case 2: // NO COGER EXAMENES
      					player.good++;
                     player.mission_cheat = 0;
         				Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","091","092",0,0);
      					break;
               }
            }

            if(player.hotspot == 7){ // HACK COMPUTER
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","020","021","022","023");
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","025",0,0,0);
               Speech("pcf.pcx","D10_STR.DAT","D10GLB.TXT","028",0,0,0);
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","029",0,0,0);
            }

            if(player.hotspot == 8){ // WC
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","031","032","033","034");
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","035","036",0,0);
            }

            if(player.hotspot == 10){ // TAQUILLAS
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","038","039","040",0);
            }

            if(player.hotspot == 11){ // NERDS

					if(freaks == 1){
            		Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
               }
               else{

            		D10_GoToNerds();
   					// Update player status
   					player.day = 10;
   					player.hour = 8;
   					player.min = 45;

   					player.floor1_event_mask[9] = 1; // Enable event
   					D10_GoToFloor1(355, 155);
                  freaks = 1;

               }
            }

            if(player.hotspot == 12){ // DIRECTOR
               Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","001",0,0,0);
               if(director == 0){ option = SpeechSelection(2,"playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006",0,0);}
               if(director == 1){ option = SpeechSelection(3,"playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007",0);}
               if(director == 2){ option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007","009");}
               if(director == 3){ option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007","008");}
   				switch(option){
				   	case 1: // NADA, SOLO  A SALUDAR
                     Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","010","011","012","013");
			      		break;
     					case 2: // ESO QUE SUENA ES UN JUEGO?
         				Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","015","016","017",0);
           				Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","011","012","013",0);
      					break;
                  case 3: // QUIERO DENUNCIAR ACOSO ESCOLAR
							Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","019","020","021","022");
							Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","024","025","026","027");
                     Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","029","030","031","032");
                     Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","034","011","012","013");
                     Speech("playerf.pcx","D10_STR.DAT","D10DIR.TXT","036","037",0,0);
      					break;
                  case 4: // DAR TIZAS O EXAMENES ROBADOS
                     if(director == 3){
              	   		player.mission_cheat = 0;
                     	player.good ++;
                  		Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","040","041","042","043");
                  		Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","045","046","047",0);
                     	Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","049","011","012","013");
                        director = 1;
                     }
                     if(director == 4){
                     	Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","051","052","053","054");
                  		Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","045","046","047",0);
                     	Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","049","011","012","013");
                        player.item_chalk = 0;
                        player.mission_cheat = 4;
                        director = 1;
                     }
                     break;
               }
            }
            if(player.hotspot == 13){ // CONSERJE
               switch(player.mission_cheat){
               	case 0:
                  	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","001","002",0,0);
               		Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","005","006",0,0);
                  	option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10CNS.TXT","010","011","012","013");
               		switch(option){
				   			case 1: // FOTOCOPIAS
                     		Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","018","019","020","021");
			      				break;
     							case 2: // UNA RATA?
         						Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","025","026","027",0);
           						Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","029","030","031",0);
                     		Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","033",0,0,0);
      							break;
                  		case 3: // NECESITO TIZAS
									Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","035","036","037",0);
									Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","039","040",0,0);
                     		Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","043","044","045",0);
                     		Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","047","048","049","050");
                        	if(player.mission_cheat == 0){player.mission_cheat = 1;}
      							break;
                  		case 4: // SALUDAR
                  			Speech("conserf.pcx","D10_STR.DAT","D10DIR.TXT","055",0,0,0);
                     		break;
               		}
                     break;
                  case 1: // Acusación sin pruebas
                     Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","059","060","061",0);
                		option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10CNS.TXT","066","067","068","069");
               		switch(option){
				   			case 1: // TONI Y SUS SECUACES
                     		Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","075","076","077","078");
                           Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","047","048","049","050");
			      				break;
     							case 2: // LOS FRIKIS
         						Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","080","081","082",0);
           						Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","084","085","086","087");
                           Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","047","048","049","050");
      							break;
                  		case 3: // DIRECTOR
                        	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","090","091","092","093");
									Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","095","096",0,0);
      							break;
                  		case 4: // NO LO SE
                        	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","047","048","049","050");
                     		break;
               		}
                  	break;
                  case 2:  // Acusación con pruebas a Tony y sus secuaces
                  	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","059","060","061",0);
                     Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","100","101","102","103");
                     Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","105","106","107",0);
                     player.floor1_hotspot_mask[13] = 0;
                     sprite[7].hide = 1;
                     player.mission_cheat = 5;
                     break;
		            case 3:  // Acusación a los frikis
                  	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","059","060","061",0);
                     Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","109","110","111","112");
                     Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","113","114","115","116");
                     player.floor1_hotspot_mask[13] = 0;
                     sprite[7].hide = 1;
                     player.mission_cheat = 5;
                  	break;
                  case 4:  // Acusación al director
                  	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","059","060","061",0);
                     Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","121","122","123",0);
                     Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","125","126","127","128");
                     player.floor1_hotspot_mask[13] = 0;
                     sprite[7].hide = 1;
                     player.mission_cheat = 5;
                  	break;
                  case 5:  //
                  	Speech("conserf.pcx","D10_STR.DAT","D10CNS.TXT","001","002",0,0);
                     Speech("playerf.pcx","D10_STR.DAT","D10CNS.TXT","013",0,0,0);
                     Speech("conserf.pcx","D10_STR.DAT","D10DIR.TXT","055",0,0,0);
                  	break;
                  default:
                  	break;
               }
            }
		   }
      	break;
      case 2: // Floor 2
      	if(player.floor2_hotspot_mask[hotspot] == 1){

            if(player.hotspot == 1){ // COMPUTER
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","020","021","022","023");
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","025","026","027","028");
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","029",0,0,0);
            }

            if(player.hotspot == 6){ // EXTINGUISHER
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","005","006","007",0);
   				option = SpeechSelection(2,"playerf.pcx","D10_STR.DAT","D10GLB.TXT","010","011",0,0);

   				switch(option){
				   	case 1: // ABRIR EXTINTOR
                 	   LoadSprite("SPRMISC.DAT","smoke.pcx",9, 64); //Load sprites to one of the fixed structs
						   SetSpriteAnimation(9,0,1,64,PlayerFaceAnimation);
			      		player.good = 0;
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_x;
							HideSprite(1);
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x + 10;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y + 8;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 8;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 10;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x + 13;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 2;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 17;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y + 12;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 25;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 23;
                     DrawSpriteDestructive(9);
                     Update(0);
                     Delay(20);

                     SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up
                     ShowSprite(1);
                     Update(0);
			        		Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","013",0,0,0);

                     EndGameExtinguisher();

			      		break;
     					case 2: // NO ABRIR EXTINTOR
         				Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","015",0,0,0);
      					break;
               }
            }

            if(player.hotspot == 7){ // boys bathroom
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","078","079",0,0);
            }

            if(player.hotspot == 8){ // GIRLS BATHROOM
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","041","042",0,0);
            }

            if(player.hotspot == 10){ // WINDOW
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","095","096",0,0);
            }
            if(player.hotspot == 11){ // BOARD
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","045","046",0,0);
               option = SpeechSelection(2,"playerf.pcx","D10_STR.DAT","D10GLB.TXT","049","050",0,0);
               switch(option){
				   	case 1: // Pintar cipote
                     Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","052","053",0,0);
                  	break;
                  case 2:
                  	Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","054","055",0,0);
                     player.item_chalk = 1;
                     director = 2;
                     player.floor2_hotspot_mask[11] = 0;
                     break;
               }
            }
		   }
      	break;
     	case 3: // Ext 1
      	if(player.ext1_hotspot_mask[hotspot] == 1){

		   }
      	break;
      case 4: // Ext 2
      	if(player.ext2_hotspot_mask[hotspot] == 1){

		   }
      	break;
      case 5: // Gym
      	if(player.gym_hotspot_mask[hotspot] == 1){
		   }
      	break;
   }
}



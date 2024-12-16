/***********************
*  DAY 10
************************/

#include "source\engine\engine.h"

void D10_GoToFloor1(int x, int y){
	int mapx,mapy;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

  	LoadMap("MAPS.DAT","floor1.tmx"); // Load floor 1 map
  	LoadTiles("TILESETS.DAT","floor1.pcx");

   LoadSprite("SPRCHR.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(player.spriteNum,0,6,12,PlayerAnimation);

   LoadSprite("SPRCHR.DAT","conser.pcx",7, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(7,0,6,12,CharacterAnimation2);
	InitSprite(7,64,128);

   LoadSprite("SPRCHR.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs  /// MEMORY LEAK!!!!////
   SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   InitSprite(2,512,402);

   // Load nerd sprites if event has not been triggered yet
   if( (floor1_event_mask[9] == 1) || (floor1_event_mask[10] == 1)){

   	LoadSprite("SPRCHR.DAT","david.pcx",3, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR.DAT","xavi.pcx",4, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR.DAT","alain.pcx",5, 32); //Load sprites to one of the fixed structs
   	LoadSprite("SPRCHR.DAT","antonio.pcx",6, 32); //Load sprites to one of the fixed structs
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

   LoadSprite("SPRCHR.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
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
   LoadSprite("SPRCHR.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
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
      	player.popular ++;
         Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","027","028",0,0);
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","029","030",0,0);
         Speech("antof.pcx","D10_STR.DAT","D10NERD.TXT","031","032","033",0);
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
     	case 2: // OS HABEIS ENTERADO QUE HAY UN BAILE?
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","035","036","037","038");
         Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","039","040","041",0);
         Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","043","044","045",0);
         Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","051","052","053","054");
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
      case 3: // SILVER AXE ES LO MEJOR!
      	player.popular --;
         Speech("davidf.pcx","D10_STR.DAT","D10NERD.TXT","055","056","057",0);
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","058","059","060","061");
         Speech("antof.pcx","D10_STR.DAT","D10NERD.TXT","062","063",0,0);
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
      case 4: // DONDE ESTE UN JUEGO DE NAVES...
      	player.popular --;
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","065","066","067",0);
         Speech("xavif.pcx","D10_STR.DAT","D10NERD.TXT","068","069",0,0);
         Speech("alainf.pcx","D10_STR.DAT","D10NERD.TXT","071","072",0,0);
         Speech("playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049",0);
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

   LoadSprite("SPRCHR.DAT","jon.pcx",10, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","toni.pcx",11, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","erik.pcx",12, 32); //Load sprites to one of the fixed structs

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
        	player.popular ++;
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","029","030","031",0);
         break;
      case 2: //SOLO PASABA POR AQUI
        	Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","035","036","037",0);
         Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","039",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
      case 3: //A CLASE, COMO ES DEBIDO
         player.popular --;
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","047","048","049","050");
         Speech("jonf.pcx","D10_STR.DAT","D10MACA.TXT","051",0,0,0);
         Speech("tonif.pcx","D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech("erikf.pcx","D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
      case 4: //APARTATE MATON, O ME CHIVO
	      player.popular --;
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
			if(floor1_event_mask[event] == 1){
        		if(player.event == 1){ D10_GoToFloor2(50,185);}
	        	if(player.event == 2){ D10_GoToFloor2(496,275);}
	         if(player.event == 3){ D10_GoToExt1(128,365);}
            if(player.event == 4){ D10_GoToExt2(484,384);}
            if(player.event == 9){
               D10_GoToMacarras();
   				// Update player status
   				player.day = 10;
   				player.hour = 8;
   				player.min = 55;
               floor1_event_mask[9] = 0; // Disable event
               floor1_hotspot_mask[4] = 1;  // Enable hotspot arcade
   				floor1_hotspot_mask[11] = 0;  // Disable hotspot nerds
               D10_GoToFloor1(232, 155);
   				Speech("playerf.pcx","D10_STR.DAT","D10MACA.TXT","052","053","054","055");
            }
            if(player.event == 10){

					floor1_event_mask[10] = 0; // Disable event

            	D10_GoToNerds();
   				// Update player status
   				player.day = 10;
   				player.hour = 8;
   				player.min = 45;

   				floor1_event_mask[9] = 1; // Enable event

   				D10_GoToFloor1(355, 155);
            }
		   }
      	break;
      case 2: // Floor 2
      	if(floor2_event_mask[event] == 1){
	         if(player.event == 1){ D10_GoToFloor1(50,175);}
         	if(player.event == 2){ D10_GoToFloor1(502,295);}
		   }
      	break;
     	case 3: // Ext 1
      	if(ext1_event_mask[event] == 1){
         	if(player.event == 1){ D10_GoToNextDay(32,365);}
         	if(player.event == 2){ D10_GoToFloor1(32,395);}
           	if(player.event == 3){ D10_GoToExt2(784,456);}
		   }
      	break;
      case 4: // Ext 2
      	if(ext2_event_mask[event] == 1){
         	if(player.event == 1){ D10_GoToExt1(868,64);}
         	if(player.event == 2){ GoToGym();}
         	if(player.event == 3){ D10_GoToFloor1(248,96);}
		   }
      	break;
      case 5: // Gym
      	if(gym_event_mask[event] == 1){
		   }
      	break;
   }
}

void D10_Hotspots(byte hotspot){
	byte option;
	switch(player.floor){
   	case 1: // Floor 1
			if(floor1_hotspot_mask[hotspot] == 1){
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
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
            }

            if(player.hotspot == 12){ // DIRECTOR
               Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","001",0,0,0);
               if(player.cheats == 0){ option = SpeechSelection(3,"playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007",0);}
               else{ option = SpeechSelection(4,"playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007","008");}
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
                  case 4: // DAR EXAMENES ROBADOS
                  	player.cheats = 0;
                     player.good ++;
                  	Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","040","041","042","043");
                  	Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","045","046","047",0);
                     Speech("directf.pcx","D10_STR.DAT","D10DIR.TXT","049","011","012","013");
                     break;
               }
            }
		   }
      	break;
      case 2: // Floor 2
      	if(floor2_hotspot_mask[hotspot] == 1){

            if(player.hotspot == 1){ // COMPUTER
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","020","021","022","023");
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","025","026","027","028");
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","029",0,0,0);
            }

            if(player.hotspot == 3){ // EXAMENES
               Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","081","082",0,0);
   				option = SpeechSelection(2,"playerf.pcx","D10_STR.DAT","D10GLB.TXT","085","086",0,0);

   				switch(option){
				   	case 1: // COGER LOS EXAMENES
                  	player.good--;
                     player.cheats = 1;
                     floor2_hotspot_mask[3] = 0;
                     SetSpriteAnimation(1,0,6,12,PlayerAnimation);
                     Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","088","089",0,0);
			      		break;
     					case 2: // NO COGER EXAMENES
      					player.good++;
                     player.cheats = 0;
         				Speech("playerf.pcx","D10_STR.DAT","D10GLB.TXT","091","092",0,0);
      					break;
               }
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
		   }
      	break;
     	case 3: // Ext 1
      	if(ext1_hotspot_mask[hotspot] == 1){

		   }
      	break;
      case 4: // Ext 2
      	if(ext2_hotspot_mask[hotspot] == 1){

		   }
      	break;
      case 5: // Gym
      	if(gym_hotspot_mask[hotspot] == 1){
		   }
      	break;
   }
}



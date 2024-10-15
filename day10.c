/***********************
*  DAY 10
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Go to encounter with nerds
/////////////////////////////////////////////////////////
void GoToNerds(void){
	word length;
 	byte option;

   panelScrolling = 0;
   showPanel = 0;
   Update(0,0);

	SetLoadingInterrupt();   // Start loading animation

   // Reset event
   // - Event will be never raised again
   floor1_event_mask[10] = 0;

   LoadImage("IMAGES.DAT","frikis.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","playerf.pcx",2, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","antof.pcx",3, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","davidf.pcx",4, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","alainf.pcx",5, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","xavif.pcx",6, 48); //Load sprites to one of the fixed structt

   SetSpriteAnimation(1,0,4,8,EnterAnimation);
   SetSpriteAnimation(2,0,1,48,PlayerFaceAnimation);
   SetSpriteAnimation(3,0,1,48,PlayerFaceAnimation);
   SetSpriteAnimation(4,0,1,48,PlayerFaceAnimation);
   SetSpriteAnimation(5,0,1,48,PlayerFaceAnimation);
   SetSpriteAnimation(6,0,1,48,PlayerFaceAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0,0);

   InitSprite(1,scroll_x + 298,scroll_y + 42);
   InitSprite(2,scroll_x,scroll_y);
   InitSprite(3,scroll_x,scroll_y);
   InitSprite(4,scroll_x,scroll_y);
   InitSprite(5,scroll_x,scroll_y);
   InitSprite(6,scroll_x,scroll_y);

   HideSprite(1);
   HideSprite(2);
   HideSprite(3);
   HideSprite(4);
   HideSprite(5);
   HideSprite(6);

   Fade_in();

   Speech(3,1,"D10_STR.DAT","D10NERD.TXT","001","002","003",0);
   Speech(6,1,"D10_STR.DAT","D10NERD.TXT","005","006","007","008");
   Speech(5,1,"D10_STR.DAT","D10NERD.TXT","010","011","012","013");
   Speech(4,1,"D10_STR.DAT","D10NERD.TXT","017","018","019","020");
   option = SpeechSelection(4,2,1,"D10_STR.DAT","D10NERD.TXT","022","023","024","025");

   switch(option){
   	case 1: // VAYA PANDA DE FRIKIS ESTAIS HECHOS
      	player.freak --;
         Speech(6,1,"D10_STR.DAT","D10NERD.TXT","027","028",0,0);
         Speech(5,1,"D10_STR.DAT","D10NERD.TXT","029","030",0,0);
         Speech(3,1,"D10_STR.DAT","D10NERD.TXT","031","032","033",0);
         Speech(2,1,"D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
     	case 2: // OS HABEIS ENTERADO QUE HAY UN BAILE?
      	player.freak --;
         Speech(5,1,"D10_STR.DAT","D10NERD.TXT","035","036","037","038");
         Speech(4,1,"D10_STR.DAT","D10NERD.TXT","039","040","041",0);
         Speech(6,1,"D10_STR.DAT","D10NERD.TXT","043","044","045",0);
         Speech(4,1,"D10_STR.DAT","D10NERD.TXT","051","052","053","054");
         Speech(2,1,"D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
      case 3: // SILVER AXE ES LO MEJOR!
      	player.freak ++;
         Speech(4,1,"D10_STR.DAT","D10NERD.TXT","055","056","057",0);
         Speech(5,1,"D10_STR.DAT","D10NERD.TXT","058","059","060","061");
         Speech(3,1,"D10_STR.DAT","D10NERD.TXT","062","063",0,0);
         Speech(2,1,"D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
      case 4: // DONDE ESTE UN JUEGO DE NAVES...
      	player.freak ++;
         Speech(5,1,"D10_STR.DAT","D10NERD.TXT","065","066","067",0);
         Speech(6,1,"D10_STR.DAT","D10NERD.TXT","068","069",0,0);
         Speech(5,1,"D10_STR.DAT","D10NERD.TXT","071","072",0,0);
         Speech(2,1,"D10_STR.DAT","D10NERD.TXT","047","048","049",0);
      	break;
   }

   // Back to floor 1
   SetLoadingInterrupt();   // Start loading animation
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRCHR.DAT","david.pcx",3, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","xavi.pcx",4, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","alain.pcx",5, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","antonio.pcx",6, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRMISC.DAT","enter.pcx",7,16); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","playerf.pcx",8, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs

   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
 	player.spriteNum = 1;
   player.floor = 1;
   player.day = 10;
   player.hour = 8;
   player.min = 45;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   SetSpriteAnimation(3,0,6,8,CharacterAnimation2);
   SetSpriteAnimation(4,0,6,30,CharacterAnimation3);
   SetSpriteAnimation(5,0,6,23,CharacterAnimation3);
   SetSpriteAnimation(6,0,6,19,CharacterAnimation2);
   SetSpriteAnimation(7,0,4,8,EnterAnimation);
   SetSpriteAnimation(8,0,1,48,PlayerFaceAnimation);

   ResetLoadingInterrupt(); // Stop loading animation
   // Allow scroll
   scrolling_enabled = 1;
   // Draw map
   SetMap(12,1);
   Update(0,0);

   InitSprite(2,512,402);

   InitSprite(3,396,102);
   InitSprite(4,408,122);
   InitSprite(5,434,142);
   InitSprite(6,396,142);
   InitSprite(7,0,0);
   InitSprite(8,0,0);

   InitSprite(1,356,155);

   HideSprite(7);
   HideSprite(8);

   Fade_in();

   panelScrolling = 1;
   showPanel = 1;

   // Enable event
   // - Event will be active again
   floor1_event_mask[9] = 1;

}

/////////////////////////////////////////////////////////
// Go to encounter with toni at lobby
/////////////////////////////////////////////////////////
void GoToMacarras(void){
	word length;
 	byte option;
   byte thread;

   SetSpriteAnimation(1,0,6,12,PlayerAnimation);

   LoadSprite("SPRCHR.DAT","jon.pcx",10, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","toni.pcx",11, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","erik.pcx",12, 32); //Load sprites to one of the fixed structs

   SetSpriteAnimation(10,0,6,30,CharacterAnimation2);
   SetSpriteAnimation(11,0,6,23,CharacterAnimation3);
   SetSpriteAnimation(12,0,6,19,CharacterAnimation3);

   InitSprite(10,sprite[player.spriteNum].pos_x,sprite[player.spriteNum].pos_y - 32);
   Delay(40);
   InitSprite(11,sprite[player.spriteNum].pos_x,sprite[player.spriteNum].pos_y + 32);
   Delay(40);
   InitSprite(12,sprite[player.spriteNum].pos_x - 32,sprite[player.spriteNum].pos_y);
   Delay(40);

   panelScrolling = 0;
   showPanel = 0;
   Update(0,0);

	SetLoadingInterrupt();   // Start loading animation

   // Reset event
   // - Event will be never raised again
   floor1_event_mask[9] = 0;

   // Enable hotspot
   floor1_hotspot_mask[4] = 1;

   // Disable hotspot
   floor1_hotspot_mask[11] = 0;


   LoadImage("IMAGES.DAT","macarras.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",1,16); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","playerf.pcx",2, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","tonif.pcx",3, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","jonf.pcx",4, 48); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","erikf.pcx",5, 48); //Load sprites to one of the fixed structs

   SetSpriteAnimation(1,0,4,8,EnterAnimation);
   SetSpriteAnimation(2,0,1,64,PlayerFaceAnimation);
   SetSpriteAnimation(3,0,1,64,PlayerFaceAnimation);
   SetSpriteAnimation(4,0,1,64,PlayerFaceAnimation);
   SetSpriteAnimation(5,0,1,64,PlayerFaceAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0,0);

   InitSprite(1,scroll_x + 298,scroll_y + 42);
   InitSprite(2,scroll_x,scroll_y);
   InitSprite(3,scroll_x,scroll_y);
   InitSprite(4,scroll_x,scroll_y);
   InitSprite(5,scroll_x,scroll_y);

   HideSprite(1);
   HideSprite(2);
   HideSprite(3);
   HideSprite(4);
   HideSprite(5);

   Fade_in();

   Speech(3,1,"D10_STR.DAT","D10MACA.TXT","001","002","003",0);
   Speech(4,1,"D10_STR.DAT","D10MACA.TXT","005",0,0,0);
   Speech(3,1,"D10_STR.DAT","D10MACA.TXT","009",0,0,0);
   Speech(5,1,"D10_STR.DAT","D10MACA.TXT","013",0,0,0);
   Speech(3,1,"D10_STR.DAT","D10MACA.TXT","017","018","019","020");
   option = SpeechSelection(4,2,1,"D10_STR.DAT","D10MACA.TXT","023","024","025","026");
   switch(option){
   	case 1: //A FUMARME UN PITI AL RECRE
        	player.badass ++;
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","029","030","031",0);
         break;
      case 2: //SOLO PASABA POR AQUI
        	Speech(3,1,"D10_STR.DAT","D10MACA.TXT","035","036","037",0);
         Speech(4,1,"D10_STR.DAT","D10MACA.TXT","039",0,0,0);
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech(5,1,"D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
      case 3: //A CLASE, COMO ES DEBIDO
         player.freak ++;
         player.badass --;
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","047","048","049","050");
         Speech(4,1,"D10_STR.DAT","D10MACA.TXT","051",0,0,0);
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech(5,1,"D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
      case 4: //APARTATE MATON, O ME CHIVO
	      player.freak ++;
         player.badass --;
         Speech(4,1,"D10_STR.DAT","D10MACA.TXT","043","044",0,0);
         Speech(5,1,"D10_STR.DAT","D10MACA.TXT","045",0,0,0);
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","046",0,0,0);
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","035","036","037",0);
         Speech(4,1,"D10_STR.DAT","D10MACA.TXT","039",0,0,0);
         Speech(3,1,"D10_STR.DAT","D10MACA.TXT","040",0,0,0);
         Speech(5,1,"D10_STR.DAT","D10MACA.TXT","041",0,0,0);
         break;
   }

   // Back to floor 1
   SetLoadingInterrupt();   // Start loading animation
   // Load floor 1 map
	LoadMap("MAPS.DAT","floor1.tmx");
	LoadTiles("TILESETS.DAT","floor1.pcx");
   LoadSprite("SPRCHR.DAT","player.pcx",1, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR.DAT","director.pcx",2, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRMISC.DAT","enter.pcx",7,16); //Load sprites to one of the fixed structs
   LoadSprite("SPRFACE.DAT","playerf.pcx",8, 48); //Load sprites to one of the fixed structs

   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
 	player.spriteNum = 1;
   player.floor = 1;
   player.day = 10;
   player.hour = 8;
   player.min = 45;
   SetSpriteAnimation(1,0,6,12,PlayerAnimation);
   SetSpriteAnimation(2,0,15,12,DirectorAnimation);
   SetSpriteAnimation(7,0,4,8,EnterAnimation);
   SetSpriteAnimation(8,0,1,48,PlayerFaceAnimation);

   ResetLoadingInterrupt(); // Stop loading animation
   // Allow scroll
   scrolling_enabled = 1;
   // Draw map
   SetMap(7,1);
   Update(0,0);

   InitSprite(1,232,155);
  	InitSprite(2,512,402);
   InitSprite(7,0,0);
   InitSprite(8,0,0);

   HideSprite(7);
   HideSprite(8);

   Fade_in();

   panelScrolling = 1;
   showPanel = 1;

   Speech(8,7,"D10_STR.DAT","D10MACA.TXT","052","053","054","055");
}

/////////////////////////////////////////////////////////
// Day 10. Events
/////////////////////////////////////////////////////////
void D10_Events(byte event){
	switch(player.floor){
   	case 1: // Floor 1
			if(floor1_event_mask[event] == 1){
        		if(player.event == 1){ GoToFloor2_Left();}
	        	if(player.event == 2){ GoToFloor2_Right();}
	         if(player.event == 3){ GoToExt1_Door();}
            if(player.event == 4){ GoToExt2_BackDoor();}
            if(player.event == 9){ GoToMacarras();}
            if(player.event == 10){ GoToNerds();}
		   }
      	break;
      case 2: // Floor 2
      	if(floor2_event_mask[event] == 1){
	         if(player.event == 1){ GoToFloor1_Left();}
         	if(player.event == 2){ GoToFloor1_Right();}
		   }
      	break;
     	case 3: // Ext 1
      	if(ext1_event_mask[event] == 1){
         	if(player.event == 1){ GoToNextDay();}
         	if(player.event == 2){ GoToFloor1_Entry();}
           	if(player.event == 3){ GoToExt2_Right();}
		   }
      	break;
      case 4: // Ext 2
      	if(ext2_event_mask[event] == 1){
         	if(player.event == 1){ GoToExt1_Right();}
         	if(player.event == 2){ GoToGym();}
         	if(player.event == 3){ GoToFloor1_BackDoor();}
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
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","001","002",0,0);
            }

            if(player.hotspot == 2){ // EXTINGUISHER
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","005","006","007",0);
   				option = SpeechSelection(2,8,7,"D10_STR.DAT","D10GLB.TXT","010","011",0,0);

   				switch(option){
				   	case 1: // ABRIR EXTINTOR
			      		player.badass = player.badass + 20;
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_x;
							HideSprite(1);
                     DrawSpriteDestructive(9);
                     Update(0,0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x + 10;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y + 8;
                     DrawSpriteDestructive(9);
                     Update(0,0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 8;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 10;
                     DrawSpriteDestructive(9);
                     Update(0,0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x + 13;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 2;
                     DrawSpriteDestructive(9);
                     Update(0,0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 17;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y + 12;
                     DrawSpriteDestructive(9);
                     Update(0,0);
                     Delay(20);
                     sprite[9].pos_x = sprite[player.spriteNum].pos_x - 25;
                     sprite[9].pos_y = sprite[player.spriteNum].pos_y - 23;
                     DrawSpriteDestructive(9);
                     Update(0,0);
                     Delay(20);

                     SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up
                     ShowSprite(1);
                     Update(0,0);
			        		Speech(8,7,"D10_STR.DAT","D10GLB.TXT","013",0,0,0);

                     EndGameExtinguisher();

			      		break;
     					case 2: // NO ABRIR EXTINTOR
      					player.freak --;
         				Speech(8,7,"D10_STR.DAT","D10GLB.TXT","015",0,0,0);
      					break;
               }
            }

            if(player.hotspot == 3){ // GIRLS BATHROOM
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","041","042",0,0);
            }

            if(player.hotspot == 4){ // ARCADE
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","078","079",0,0);
            }

            if(player.hotspot == 5){ // BAR
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","003","004",0,0);
            }

            if(player.hotspot == 7){ // HACK COMPUTER
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","020","021","022","023");
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","025","026","027","028");
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","029",0,0,0);
            }

            if(player.hotspot == 8){ // WC
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","031","032","033","034");
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","035","036",0,0);
            }

            if(player.hotspot == 10){ // TAQUILLAS
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","038","039","040",0);
            }

            if(player.hotspot == 11){ // NERDS
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","017","018","019",0);
            }

            if(player.hotspot == 12){ // DIRECTOR
               Speech(8,7,"D10_STR.DAT","D10GLB.TXT","044",0,0,0);
               option = SpeechSelection(3,8,7,"D10_STR.DAT","D10GLB.TXT","046","047","048",0);
   				switch(option){
				   	case 1: // NADA, SOLO PASABA A SALUDAR
                     Speech(8,7,"D10_STR.DAT","D10GLB.TXT","050","051","052","053");
			      		break;
     					case 2: // ESO QUE SUENA ES UN JUEGO?
         				Speech(8,7,"D10_STR.DAT","D10GLB.TXT","055","056","057",0);
           				Speech(8,7,"D10_STR.DAT","D10GLB.TXT","051","052","053",0);
      					break;
                  case 3: // QUIERO DENUNCIAR ACOSO ESCOLAR
							Speech(8,7,"D10_STR.DAT","D10GLB.TXT","059","060","061","062");
							Speech(8,7,"D10_STR.DAT","D10GLB.TXT","064","065","066","067");
                     Speech(8,7,"D10_STR.DAT","D10GLB.TXT","069","070","071","072");
                     Speech(8,7,"D10_STR.DAT","D10GLB.TXT","074","051","052","053");
                     Speech(8,7,"D10_STR.DAT","D10GLB.TXT","076","077",0,0);
      					break;
               }

            }
		   }
      	break;
      case 2: // Floor 2
      	if(floor2_hotspot_mask[hotspot] == 1){

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



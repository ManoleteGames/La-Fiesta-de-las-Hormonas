/***********************
*  ALL DAY HOTSPOTS
************************/

#include "source\engine\engine.h"

void far Hotspots(byte hotspot){
	byte option;
   byte end_conversation = 0;

   // Hotspots 1..7 are common hotspots for all the floors
   if(player.hotspot == 1){ // WINDOW
 		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","095","096",0,0);
   }
   if(player.hotspot == 2){ // EXTINGUISHER
   	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","005","006","007",0);
   	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","010","011",0,0);
   	switch(option){
			case 1: // OPEN
            LoadSprite("SPRMISC.DAT","smoke.pcx",9, 64); //Load sprites to one of the fixed structs
			   SetSpriteAnimation(9,0,1,64,PlayerFaceAnimation);
            sprite[9].pos_x = sprite[player.spriteNum].pos_x + 32;
            sprite[9].pos_y = sprite[player.spriteNum].pos_y + 0;
            DrawSpriteDestructive(9);
            Update(0);
            Delay(20);
            sprite[9].pos_x = sprite[player.spriteNum].pos_x + 32;
            sprite[9].pos_y = sprite[player.spriteNum].pos_y + 32;
            DrawSpriteDestructive(9);
            Update(0);
            Delay(20);
            sprite[9].pos_x = sprite[player.spriteNum].pos_x + 16;
            sprite[9].pos_y = sprite[player.spriteNum].pos_y + 32;
            DrawSpriteDestructive(9);
            Update(0);
            Delay(20);
            sprite[9].pos_x = sprite[player.spriteNum].pos_x + 0;
            sprite[9].pos_y = sprite[player.spriteNum].pos_y + 32;
            DrawSpriteDestructive(9);
            Update(0);
            Delay(20);
            sprite[9].pos_x = sprite[player.spriteNum].pos_x - 32;
            sprite[9].pos_y = sprite[player.spriteNum].pos_y + 32;
            DrawSpriteDestructive(9);
            Update(0);
            Delay(20);
            sprite[9].pos_x = sprite[player.spriteNum].pos_x - 64;
            sprite[9].pos_y = sprite[player.spriteNum].pos_y + 32;
            DrawSpriteDestructive(9);
            Update(0);
   			Delay(20);
            SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up
            Update(0);
            Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","013",0,0,0);

            EndGameExtinguisher();

            break;
         case 2: // DO NOT OPEN
      		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","015",0,0,0);
            break;
      }
	}
   if(player.hotspot == 3){ // GIRLS BATHROOM
   	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","041","042",0,0);
   }
   if(player.hotspot == 4){ // boys bathroom
   	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","073","074",0,0);
      Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","075","076",0,0);
   }
   if(player.hotspot == 5){ // Jon sign
   	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","031","032","033","034");
      Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","035","036",0,0);
   }
   if(player.hotspot == 6){ // Spare
   }
   if(player.hotspot == 7){ // Spare
   }



   // ********************************************************
   // CUSTOM FLOOR HOTSPOTS
   // ********************************************************
	switch(player.floor){

   	// FLOOR 1
      // *****************************************
   	case 1: // Floor 1
			if(player.floor1_hotspot_mask[hotspot] == 1){
         	// NEWS BOARD
            // *****************************************
            if(player.hotspot == 8){
               switch(player.day){
               	case 10:
               		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","001","002",0,0);
                     break;
                  case 9:
                     Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","001","002",0,0);
                     break;
                  case 8:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8GLB.TXT","001","002",0,0);
                     break;
                  case 7:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7GLB.TXT","001","002",0,0);
                     break;
                  case 6:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6GLB.TXT","001","002",0,0);
                     break;
                  case 5:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D5_STR.DAT","D5GLB.TXT","001","002",0,0);
                     break;
                  case 4:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","001","002",0,0);
                     break;
                  case 3:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","001","002",0,0);
                     break;
                  case 2:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","001","002",0,0);
                     break;
                  case 1:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GLB.TXT","001","002",0,0);
                     break;
               }
            }
            // ARCADE MACHINE
            // *****************************************
            if(player.hotspot == 9){
               if(player.mission_arcade==0){
               	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","001","002",0,0);
               	if(player.money >= 25){
               		Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","003","004",0,0);
                  	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","006","007",0,0);
                  	switch(option){
				   			case 1: // ECHAR 5 DUROS
                     		player.mission_arcade = 1;
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","010",0,0,0);
                        	player.money = player.money - 25;
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","011",0,0,0);
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","013",0,0,0);
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","013",0,0,0);
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","015","016",0,0);
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","020","021","022",0);
                        	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","025",0,0,0);
                        	break;
                     	case 2:
                     		Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","012",0,0,0);
                     		break;
                  	}
                  }
               }

               if(player.mission_arcade==1){
                	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","030","031",0,0);
               }
            }
            // BAR
            // *****************************************
            if(player.hotspot == 10){ // BAR
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","040","041",0,0);
            }
            // EXAMS ITEM
            // - Only available during day 10
            // *****************************************
            if(player.hotspot == 11){ // EXAMENES
            	if(player.mission_cheat<5){

               	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","081","082",0,0);
   					option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","085","086",0,0);

                  if(player.scn_main == 0){ player.scn_main = 1; } // Set scene 1

   					switch(option){
				   		case 1: // TAKE EXAMS
                     	player.mission_cheat = 5;
                     	player.item_exams = 1;
                     	SetItem(2,16,"exams.pcx");
                     	SetSpriteAnimation(1,0,6,12,PlayerAnimation);
                     	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","088","089",0,0);
                     	player.scn_director = 3;
                        player.good = 9;
			      			break;
     						case 2: // DO NOT TAKE EXAMS
         					Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","091","092",0,0);
                        player.good = 11;
      						break;
               	}
               } else {
            			Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","105","106","107",0);
            	}
            }
            // COMPUTER
            // *****************************************
            if(player.hotspot == 12){
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","050","051","052","053");
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","055",0,0,0);
               Speech("SPRFACE2.DAT","pcf.pcx","GLB_STR.DAT","MISC.TXT","058",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","059",0,0,0);
            }
            // LOCKERS
            // *****************************************
            if(player.hotspot == 13){
            	switch(player.day){
                  case 9:
                  	if(player.mission_doll > 0){
                      	Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","052","053",0,0);
                     }
                     if((player.mission_doll == 0)&&(player.item_keys == 1)){
                     	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","022","023",0,0);
                  		switch(option){
				   				case 1: // OPEN LOCKERS
                     			player.mission_doll = 2;
                              Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","110",0,0,0);
                              Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","111",0,0,0);
                              Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","112",0,0,0);
                              Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","113",0,0,0);
                              Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","114","115",0,0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","026",0,0,0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","027","028","029","030");
                        		SetSpriteAnimation(1,0,6,12,PlayerAnimation);
                           	Update(0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","033","034","035","036");
                              Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","037","038","039",0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","040",0,0,0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","043","044","045",0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","047","048","049","050");
                     			break;
     								case 2: // DO NOT OPEN
         							Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","055","056","057",0);
      								break;
               			}
                     }
                     if((player.mission_doll == 0)&&(player.item_keys == 0)){
                     	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","044","045","046",0);
                     }
                     break;
                  case 10,8,7,6,5,4,3,2,1:
                  	if(player.mission_doll >= 2){
                      	Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","052","053",0,0);
                     }
                     else{
                     	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","044","045","046",0);
                     }
                  	break;
               }
            }

            // NERDS / THUGS
            // *****************************************
            if(player.hotspot == 14){ // NERDS / THUGS
               switch(player.day){
               	case 10: // nerds near arcade
            			Nerds();
                     break;
                  case 9:  // DAY 9: thugs near arcade machine
                     Thugs();
                     break;
                  case 8:  // DAY 8: ,...
                  	break;
                  default:
                  	break;
               }
            }

            if(player.hotspot == 15){ // Director
               Director();
            }
            if(player.hotspot == 16){ // JANITOR
             	Janitor();
            }
            if(player.hotspot == 17){ // NERDS ON THE MIDDLE
               //Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","001","002",0,0);
            }
            if(player.hotspot == 18){ // PRINTER
               //Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","001","002",0,0);
            }
            // ITEM KEYS
            // *****************************************
            if(player.hotspot == 19){
               Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","005","006","007","008");
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","010","011",0,0);
               	switch(option){
                  	case 1: // TAKE KEYS
                     	SetItem(2,16,"keys.pcx");
                    		player.item_keys = 1;
                        HideSprite(4);
                        player.floor1_hotspot_mask[19] = 0;
                     	break;
                     case 2: // DO NOT TAKE
                     	Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GLB.TXT","013","014","015","016");
                        break;
               }
            }
		   }
      	break;


      case 2: // Floor 2
      	if(player.floor2_hotspot_mask[hotspot] == 1){

            if(player.hotspot == 11){ // CHALK BOARD
               Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","045","046",0,0);
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","049","050",0,0);
               switch(option){
				   	case 1: // Draw
                     Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","052","053",0,0);
                  	break;
                  case 2: // take chalk
                  	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","054","055",0,0);

                     player.item_chalk = 1;
                     SetItem(2,16,"chalk.pcx");

                     player.scn_director = 2;  // Enable new director scene
                     player.floor2_hotspot_mask[11] = 0;  // Reset chalk hotspot
                     break;
               }
            }
            if(player.hotspot == 12){ // GIRLS
               Girls();
            }
		   }
      	break;
     	case 3: // Ext 1
      	if(player.ext1_hotspot_mask[hotspot] == 1){
         	if(player.hotspot == 2){ // Three bottom

            }
            if(player.hotspot == 3){ // Thugs

            }
		   }
      	break;
      case 4: // Ext 2
      	if(player.ext2_hotspot_mask[hotspot] == 1){
            if(player.hotspot == 8){ // near gym wall
               Thugs();
            }
            if(player.hotspot == 9){ // near heroquest map
					Nerds();
            }
		   }
      	break;
      case 5: // Gym
      	if(player.gym_hotspot_mask[hotspot] == 1){
			  if(player.hotspot == 8){ // sensei
           		switch(player.day){
               	case 10:
               		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GYM.TXT","001",0,0,0);
               		Speech("SPRFACE2.DAT","senseif.pcx","D10_STR.DAT","D10GYM.TXT","002",0,0,0);

                     end_conversation = 0;
               		while(!end_conversation){
   							option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GYM.TXT","005","006","007",0);
   							switch(option){
				   				case 1: // are you from japan?
                  				Speech("SPRFACE2.DAT","senseif.pcx","D10_STR.DAT","D10GYM.TXT","010","011","012","013");
                     			Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GYM.TXT","015",0,0,0);
                 	   			break;
     								case 2: // ask about party
                     			Speech("SPRFACE2.DAT","senseif.pcx","D10_STR.DAT","D10GYM.TXT","018","019","020",0);
      								break;
                  			case 3: // byte
                     			Speech("SPRFACE2.DAT","senseif.pcx","D10_STR.DAT","D10GYM.TXT","022",0,0,0);
                              end_conversation = 1;
      								break;
               			}
               		}
               		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GYM.TXT","025","026","027",0);
            			break;
                  case 9:
                     Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GYM.TXT","001",0,0,0);
                     Speech("SPRFACE2.DAT","senseif.pcx","D9_STR.DAT","D9GYM.TXT","002",0,0,0);
                  	break;
               }
            }

            if(player.hotspot == 9){ // girls
            	Girls();
            }
		   }
      	break;
   }
}



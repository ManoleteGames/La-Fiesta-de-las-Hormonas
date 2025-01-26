/***********************
*  ALL DAY EVENTS
************************/

#include "source\engine\engine.h"

void far Events(byte event){
	byte option;
	switch(player.floor){
   	case 1: // Floor 1
			if(player.floor1_event_mask[event] == 1){
        		if(player.event == 1){ GoToFloor2(50,185);}
	        	if(player.event == 2){ GoToFloor2(496,275);}
	         if(player.event == 3){ GoToExt1(128,365);}
            if(player.event == 4){ GoToExt2(484,384);}
            if(player.event == 5){ /// Director's room entry
            	if(player.day == 10){
            		switch(player.scn_janitor){
               		case 2:
                  		Speech("SPRFACE2.DAT","conserf.pcx","D10_STR.DAT","D10CNS.TXT","135","136",0,0);
                     	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","050","051","052",0);
                     	player.scn_janitor = 3;
                  		break;
                  	case 3:
                  		Speech("SPRFACE2.DAT","conserf.pcx","D10_STR.DAT","D10CNS.TXT","138","139","140",0);
                     	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","055",0,0,0);
                     	player.scn_janitor = 4;
                  		break;
                  	default:
                  		break;
               	}
               	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10CNS.TXT","141","142","143",0);
               	sprite[player.spriteNum].pos_y = sprite[player.spriteNum].pos_y - 16;
            	}
            }
            if(player.event == 9){ // Going out of the bar
               if(player.day == 10){
						player.scn_director = 1; // Enable talk about bullying with the director
               	player.floor1_event_mask[9] = 0; // Disable thugs assault event
               	Thugs();
               	GoToFloor1(232, 155);
   					Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10THUG.TXT","052","053","054","055");
            	}
            }
		   }
      	break;
      case 2: // Floor 2
      	if(player.floor2_event_mask[event] == 1){
	         if(player.event == 1){ GoToFloor1(50,175);}
         	if(player.event == 2){ GoToFloor1(502,295);}
            if(player.event == 3){ // Go to exam
            	if( player.scn_main < 1 ){ // mission not done yet
                	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","098","099",0,0);
               } else {
                  Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","100","101",0,0);
               }
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","102","103",0,0);
               if(option == 1){
               	GoToExam();
                  player.scn_main = 2;
               	switch(player.day){
                  	case 10:
                  		// Update scn_thugs
   							player.scn_thugs = 2;
   							player.ext1_hotspot_mask[8] = 1;  // Enable hotspot 8 of ext1. Thugs
                  		player.ext2_hotspot_mask[8] = 0;  // Disble hotspot 8 of ext2. Thugs

							   // Update scn_nerds
   							player.scn_nerds = 6;
   							player.floor1_hotspot_mask[9] = 1; // Enable arcade hotspot
   							player.floor1_hotspot_mask[17] = 1;  // Enable nerds hotspot at the lobby
   							player.floor1_hotspot_mask[14] = 0;  // Disable nerds hotspot at the arcade
   							player.floor2_event_mask[3] = 0;     // Disable exam event

                        break;
                     case 9:
                     	break;
                  	default:
                     	break;
                  }
               } else {
               	sprite[player.spriteNum].pos_y = sprite[player.spriteNum].pos_y + 16;
               }
            }
		   }
      	break;
     	case 3: // Ext 1
      	if(player.ext1_event_mask[event] == 1){
         	if(player.event == 1){ // Go to next day
            	if(player.scn_main < 2){ // exam not done yet
               	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","058","059",0,0);
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","066","067",0,0);
                  switch(option){
                  	case 1: // PASS CLASSES
                     	if(player.intell > 0){player.intell--;}
                        if(player.good > 0){player.good--;}
                        if(player.popular > 0){player.popular--;}
                        if(player.day > 0){player.day --;}
                        InitDay();
                        break;
                     default: // GO BACK
                        break;
                  }
               } else {
               	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","062",0,0,0);
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","065","067",0,0);
                  switch(option){
                  	case 1: // GO HOME
                     	if(player.day > 0){player.day --;}
                        InitDay();
                        break;
                     default: // GO BACK
                        break;
                  }
               }

               if(player.day > 0){GoToExt1(32, 365);}
               else { GoToEnd(); }

            }
         	if(player.event == 2){ GoToFloor1(32,395);}
           	if(player.event == 3){ GoToExt2(784,456);}
		   }
      	break;
      case 4: // Ext 2
      	if(player.ext2_event_mask[event] == 1){
         	if(player.event == 1){ GoToExt1(868,64);}
         	if(player.event == 2){ GoToGym(56,296);}
         	if(player.event == 3){ GoToFloor1(248,96);}
		   }
      	break;
      case 5: // Gym
      	if(player.gym_event_mask[event] == 1){
            if(player.event == 1){ GoToExt2(648,256); }
		   }
      	break;
   }
}



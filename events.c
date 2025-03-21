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
	        	if(player.event == 2){ GoToFloor2(496,270);}
	         if(player.event == 3){ GoToExt1(128,365);}
            if(player.event == 4){ GoToExt2(484,384);}
            if(player.event == 5){ /// Director's room entry
               switch(player.day){
               	case 4:
                  	Janitor();
                     break;
                  case 1:
                     switch(player.scn_director){
               			case 0:
                        	Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","065","066",0,0);
                           Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1DIR.TXT","068","069",0,0);
                           Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","071","072","073","074");
                           player.scn_director++;
                  			break;
                  		case 1:
                        	Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","077","078","079",0);
                           Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","082","083",0,0);
                           Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","085","086",0,0);
                           break;
                  		default:
                  			break;
               		}
                     Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","088","089","090","091");
                     break;
            	}
               sprite[player.spriteNum].pos_y = sprite[player.spriteNum].pos_y - 16;
            }
            if(player.event == 9){ // Going out of the bar, thugs assault
               if(player.day == 4){
               	player.floor1_event_mask[9] = 0; // Disable thugs assault event
               	Thugs();
                  player.ext2_hotspot_mask[8] = 1; // Enable hotspot thugs on ext2
               	GoToFloor1(232, 155);
   					Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4THUG.TXT","052","053","054","055");
            	}
            }
            if(player.event == 10){ // jon and anto out of the fight
            	if(player.day == 1){
                  player.floor1_event_mask[10] = 0; // Disable thugs assault event
               	Nerds();
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
                	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","101","102",0,0);
               } else {
                  Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","103","104",0,0);
               }
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","105","106",0,0);
               if(option == 1){
               	player.floor2_event_mask[3] = 0;
               	GoToExam();
                  player.scn_main = 2;

                  // disable all the npc scenes
  						player.scn_nerds = 99;
   					player.scn_thugs = 99;
   					player.scn_girls = 99;
   					player.scn_janitor = 99;
   					player.scn_director = 99;
   					player.scn_sensei = 99;

   					// End of exam
   					GoToFloor2(446,270);
   					LoadMusic(1);
   					PlayNonStopMusic();

   					if(player.score[player.day]<3){
   						Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","125","126",0,0);
      					if(player.intell>2){UpdateInteligence(-1); }
      					if(player.intell>2){UpdateInteligence(-1); }
   					}
   					else if((player.score[player.day]>=3)&&(player.score[player.day]<5)){
   						Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","125","126",0,0);
      					if(player.intell>2){UpdateInteligence(-1); }
   					}
   					else if((player.score[player.day]>=5) && (player.score[player.day]<=7)){
      					Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","127","128",0,0);
      					if(player.intell<18){UpdateInteligence(1);}
   					}
   					else{
      					Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","129","130",0,0);
      					if(player.intell<18){UpdateInteligence(1);}
      					if(player.intell<18){UpdateInteligence(1);}
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
               	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","108","109",0,0);
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","116","117",0,0);
                  switch(option){
                  	case 1: // PASS CLASSES
                     	Fade_out();
                        UnloadMusic();
                     	if(player.intell > 2){player.intell--;}
                        if(player.intell > 2){player.intell--;}
                        if(player.good > 2){player.good--;}
                        if(player.good > 2){player.good--;}
                        if(player.popular > 2){player.popular--;}
                        if(player.popular > 2){player.popular--;}
                        if(player.day > 0){player.day --;}
                        if(player.day > 0){
                        	InitDay();
                        	LoadMusic(1);
                        	GoToExt1(32, 365);
                        }
               			else { GoToEnd(); }
                        break;
                     default: // GO BACK
                        sprite[player.spriteNum].pos_x = sprite[player.spriteNum].pos_x + 16;
                        break;
                  }
               } else {
               	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","112",0,0,0);
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","115","117",0,0);
                  switch(option){
                  	case 1: // GO HOME
                        Fade_out();
                        UnloadMusic();
                     	if(player.day > 0){player.day --;}
                        if(player.day > 0){
                           InitDay();
                           LoadMusic(1);
                        	GoToExt1(32, 365);
                        }
                        else { GoToEnd(); }
                        break;
                     default: // GO BACK
                     	sprite[player.spriteNum].pos_x = sprite[player.spriteNum].pos_x + 16;
                        break;
                  }
               }
            }
         	if(player.event == 2){ GoToFloor1(32,395);}
           	if(player.event == 3){ GoToExt2(784,420);}
            if(player.event == 4){ EndGameRoof(); }
            if(player.event == 5){ EndGameRoof(); }
            if(player.event == 6){ EndGameRoof(); }
            if(player.event == 7){ EndGameRoof(); }
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



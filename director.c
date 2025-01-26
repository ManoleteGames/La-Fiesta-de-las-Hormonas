/***********************
*  DIRECTOR CONVERSATIONS
************************/

#include "source\engine\engine.h"

void far Director(void){
	byte option = 1;
	byte end_conversation = 0;
	switch(player.day){
   	case 10:
      	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","001",0,0,0);
         while(end_conversation == 0){
           	if(player.scn_director == 0){ option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006",0,0);}
           	if(player.scn_director == 1){ option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007",0);}
           	if(player.scn_director == 2){ option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007","008");}
           	if(player.scn_director == 3){ option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10DIR.TXT","005","006","007",0);}
           	switch(option){
         	   case 1: // Nothing
               	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","010","011","012","013");
                  end_conversation = 1;
                  break;
               case 2: // Is it a game?
               	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","015","016","017",0);
               	break;
               case 3: // Bullying
               	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","019","020","021","022");
                  Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","024","025","026","027");
                  Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","029","030","031","032");
                  Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10DIR.TXT","036","037",0,0);
                  break;
               case 4: // Give chalk
               	Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","040","041","042","043");
                  Speech("SPRFACE2.DAT","directf.pcx","D10_STR.DAT","D10DIR.TXT","044","045","046","048");
                  player.item_chalk = 0;
                  ResetItem(2,16);

                  player.mission_cheat = 3;
                  player.scn_director = 3;
                  break;
            }
         }
      	break;
      case 9:
      	Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","001",0,0,0);
         while(end_conversation == 0){
           	option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9DIR.TXT","005","006","007",0);
           	switch(option){
         	   case 1: // MUSIC?
               	Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","010","011","012","013");
                  Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9DIR.TXT","015","016",0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","019",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9DIR.TXT","021",0,0,0);
                  break;
               case 2: // JANITOR?
               	Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","024",0,0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","026","027","028",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9DIR.TXT","030",0,0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","034","035","036",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9DIR.TXT","038",0,0,0);
               	break;
               case 3: // BYE
               	Speech("SPRFACE2.DAT","directf.pcx","D9_STR.DAT","D9DIR.TXT","040","041","042",0);
                  end_conversation = 1;
                  break;
            }
         }
      	break;
      case 8:
      	Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","001","002",0,0);
         while(end_conversation == 0){
           	option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","005","006","007",0);
           	switch(option){
         	   case 1: // PARTY?
               	Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","010","011",0,0);
               	Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","015","016","017",0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","019","020",0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","024","025","026",0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","029","030","031",0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","034","035","036","037");
                  Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","040",0,0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","044",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","048","049",0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","051","052",0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","055",0,0,0);
                  break;
               case 2: // MONKEY?
               	Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","060","061","062","063");
               	Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","065","066","067",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","070","071","072",0);
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","075","076","077","078");
                  Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","080","081","082",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8DIR.TXT","085",0,0,0);
               	break;
               case 3: // BYE
               	Speech("SPRFACE2.DAT","directf.pcx","D8_STR.DAT","D8DIR.TXT","088","089",0,0);
                  end_conversation = 1;
                  break;
            }
         }
      	break;
      case 7:
         Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","001",0,0,0);
         while(end_conversation == 0){
           	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","005","006",0,0);
           	switch(option){
         	   case 1: // GAME?
               	Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","010","011",0,0);
               	Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","015","016","017",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","020","021",0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","025","026","027",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","029",0,0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","032","033","034","035");
                  Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","037","038","039",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","040","041","042","043");
                  Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","045","046","047","048");
                  Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","055",0,0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","050","051","052",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7DIR.TXT","057",0,0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","058",0,0,0);
                  break;
               case 2: // BYE
               	Speech("SPRFACE2.DAT","directf.pcx","D7_STR.DAT","D7DIR.TXT","060",0,0,0);
                  end_conversation = 1;
                  break;
            }
         }
      	break;
      case 6:
      	Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","004",0,0,0);
         while(end_conversation == 0){
         	if((player.scn_janitor == 0)||(player.scn_director == 1)){ option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005","006",0,0); }
         	else{ option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005","006","007",0); }
           	switch(option){
         	   case 1: // day?
               	Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","010",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","012","013",0,0);
                  break;
               case 2: // bye
               	Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","015","016",0,0);
                  end_conversation = 1;
                  break;
               case 3: // return game
               	Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","020","021",0,0);
               	Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","024","025",0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","028","029","030",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","032","033","034",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","036","037",0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","040","041","042",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","043","044",0,0);
                  Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","047","048","049","050");
                  Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","052","053","054",0);
                  Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","058","059","060","061");
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","065","066",0,0);
                  switch(option){
         	   		case 1: // yes
               			Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","069",0,0,0);
                        Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","070",0,0,0);
                        // SetItem(3,32)  game
                        player.item_game = 1;
                  		break;
               		case 2: // no
               			Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","072","073","074",0);
                 			break;
                  }
                  player.scn_director = 1;
                  break;
            }
         }
      	break;
      case 5:
         Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005",0,0,0);
      	break;
      case 4:
         Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005",0,0,0);
      	break;
      case 3:
         Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005",0,0,0);
      	break;
      case 2:
         Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005",0,0,0);
      	break;
      case 1:
         Speech("SPRFACE2.DAT","directf.pcx","D6_STR.DAT","D6DIR.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6DIR.TXT","005",0,0,0);
      	break;
   }
}
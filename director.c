/***********************
*  DIRECTOR CONVERSATIONS
************************/

#include "source\engine\engine.h"

void far Director(void){
	byte option = 1;
	byte end_conversation = 0;
	switch(player.day){
   	case 4:  //////////////////////// day 4 ////////////////////////
      	switch(player.scn_director){
         	case 0:
      			Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","001",0,0,0);
         		while(end_conversation == 0){
               	if(player.item_chalk == 1){ option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4DIR.TXT","005","006","007","008"); }
            		else { option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4DIR.TXT","005","006","007",0);}
           			switch(option){
               		case 1: // Is it a game?
               			Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","015","016","017",0);
               			break;
               		case 2: // Bullying
               			Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","019","020","021","022");
                  		Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","024","025","026","027");
                  		Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","029","030","031","032");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4DIR.TXT","036","037",0,0);
                  		break;
               		case 3: // Nothing
               			Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","010","011","012","013");
                  		end_conversation = 1;
                  		break;
               		case 4: // Give chalk
               			Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","040","041","042","043");
                  		Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","044","045","046","047");
                  		player.item_chalk = 0;
                  		ResetItem(2,16);
								player.mission_cheat = 2;
                  		break;
            		}
         		}
      			break;
            case 99:
               Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","060",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4DIR.TXT","065","066","067","068");
            	break;
         }
         break;
      case 3:  //////////////////////// day 3 ////////////////////////
      	switch(player.scn_director){
         	case 0:
      			Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","001",0,0,0);
         		while(end_conversation == 0){
           			option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","005","006","007",0);
           			switch(option){
         	   		case 1: // MUSIC?
               			Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","010","011","012","013");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","015","016",0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","019",0,0,0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","021",0,0,0);
                  		break;
               		case 2: // JANITOR?
               			Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","024",0,0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","026","027","028",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","030",0,0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","034","035","036",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","038",0,0,0);
               			break;
               		case 3: // BYE
               			Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","040","041","042",0);
                  		end_conversation = 1;
                  		break;
            		}
         		}
      			break;
            case 99:
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","050",0,0,0);
               Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","055","056","057","058");
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","060","061",0,0);
               Speech("SPRFACE2.DAT","directf.pcx","D3_STR.DAT","D3DIR.TXT","063",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3DIR.TXT","065","066","067",0);
            	break;
         }
         break;
      case 2:  //////////////////////// day 2 ////////////////////////
         switch(player.scn_director){
         	case 0:
      			Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","001","002",0,0);
         		while(end_conversation == 0){
           			option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","005","006","007",0);
           			switch(option){
         	   		case 1: // PARTY?
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","010","011",0,0);
               			Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","015","016","017",0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","019","020",0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","024","025","026",0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","029","030","031",0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","034","035","036","037");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","040",0,0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","044",0,0,0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","048","049",0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","051","052",0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","055",0,0,0);
                  		break;
               		case 2: // MONKEY?
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","060","061","062","063");
               			Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","065","066","067",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","070","071","072",0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","075","076","077","078");
                  		Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","080","081","082",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","085",0,0,0);
               			break;
               		case 3: // BYE
               			Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","088","089",0,0);
                  		end_conversation = 1;
                  		break;
            		}
         		}
      			break;
            case 99:
               Speech("SPRFACE2.DAT","directf.pcx","D2_STR.DAT","D2DIR.TXT","095",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2DIR.TXT","100","101",0,0);
            	break;
      	}
         break;
      case 1:   //////////////////////// day 1 ////////////////////////
      	switch(player.scn_director){
         	case 0:
         		Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","001",0,0,0);
         		while(end_conversation == 0){
               	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","005","006",0,0);
           			switch(option){
         	   		case 1: // GAME?
               			Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","010","011",0,0);
               			Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","015","016","017",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","020","021",0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","025","026","027",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","029",0,0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","032","033","034","035");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","037","038","039",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","040","041","042","043");
                  		Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","045","046","047","048");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","055",0,0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","050","051","052",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1DIR.TXT","057",0,0,0);
                  		Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","058",0,0,0);
                  		break;
               		case 2: // BYE
               			Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","060",0,0,0);
                  		end_conversation = 1;
                  		break;
            		}
         		}
      			break;
            case 99:
            	Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","095","096","097","098");
               Speech("SPRFACE2.DAT","directf.pcx","D1_STR.DAT","D1DIR.TXT","100","101",0,0);
            	break;
         }
         break;
   }
}
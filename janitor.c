/***********************
*  JANITOR CONVERSATIONS
************************/

#include "source\engine\engine.h"

void far Janitor(void){
	byte option = 1;
	byte end_conversation = 0;

	switch(player.day){
   	case 4: /////////////////////// day 4 ///////////////////
         switch(player.scn_janitor){ ///////////////////// janitor ////////////////////////////////
         	case 0:  ////////////////  scene 0 ///////////////////
            	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","001","002",0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","005","006",0,0);
               while(end_conversation == 0){
               	option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","010","011","012","013");
                  switch(option){
                  	case 1: // copies
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","018","019","020","021");
                        break;
                     case 2: // a rat?
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","025","026","027",0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","029","030","031",0);
                        Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","033",0,0,0);
                        break;
                     case 3: // need chalk
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","035","036","037",0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","039","040",0,0);
                        Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","043","044","045",0);
                        Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","047","048","049","050");
                        player.scn_janitor++;
                        end_conversation = 1;
                     	break;
                     case 4: // SALUDAR
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","055",0,0,0);
                        end_conversation = 1;
                        break;
                  }
               }
               break;
            case 1: //////////////// scene 1 accusation ///////////
            	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","059","060","061",0);
               while(end_conversation == 0){
               	option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","066","067","068","069");
                  switch(option){
                  	case 1: // thugs
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","075","076","077","078");
                        break;
                     case 2: // nerds
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","080","081","082",0);
                        Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","084","085","086","087");
                        break;
                     case 3: // director
                     	if(player.mission_cheat == 2){  // if director has chalk
                        	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","121","122","123",0);
                           Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","125","126","127","128");
                           player.floor1_hotspot_mask[16] = 0;  // Disable janitor hotspot
                           player.floor1_event_mask[5] = 1;  // Enable event after enter directors room
                           HideSprite(3);
                           sprite[3].pos_x = 446;
                           sprite[3].pos_y = 412;
                           Update(0);
                           ShowSprite(3);
                           player.mission_cheat = 3;  // Update mission cheat status
                           player.scn_janitor++;
                           end_conversation = 1;
                        } else {  // if director has no chalk yet
                        	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","090",0,0,0);
                           Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","091","092","093","094");
                           Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","095","096",0,0);
                  		}
                        break;
                     case 4: // I do not know
                     	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","047","048","049","050");
                        end_conversation = 1;
                        break;
                  }
               }
            	break;
            case 2:  /// triggered by event after enter directors room
            	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","135","136",0,0);
               Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","050","051","052",0);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","141","142","143",0);
               player.scn_janitor++;
               break;
            case 3:
            	Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","138","139","140",0);
               Speech("SPRFACE2.DAT","directf.pcx","D4_STR.DAT","D4DIR.TXT","055",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","141","142","143",0);
               player.scn_janitor++;
               break;
            case 99:
               Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","100","101","102","103");
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","105",0,0,0);
               Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","107",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","109",0,0,0);
               Speech("SPRFACE2.DAT","conserf.pcx","D4_STR.DAT","D4CNS.TXT","112","113","114","115");
            	break;
            default:
            	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4CNS.TXT","141","142","143",0);
         		break;
         }
      	break;
      case 3: /////////////////////// day 3 /////////////////////
         switch(player.scn_janitor){ ///////////////////// janitor ////////////////////////////////
         	case 0:  ////////////////  scene 0 ///////////////////
         		Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","001","002",0,0);
         		while(end_conversation == 0){
         			option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3CNS.TXT","010","011","012","013");
            		switch(option){
            			case 1: // COPY
               			Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","018","019","020","021");
                  		break;
               		case 2: // A RAT?
               			Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","025","026","027",0);
                  		break;
               		case 3: // ABOUT DIRECTOR
               			Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","029","030","031",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3CNS.TXT","033","034",0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","037","038","039","040");
                  		Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","043","044","045",0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","047","048","049",0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","051",0,0,0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3CNS.TXT","055","056",0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","059",0,0,0);
                  		break;
               		case 4: // SALUDAR
               			Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","066",0,0,0);
                  		end_conversation = 1;
                  		break;
            		}
         		}
      			break;
            case 99:
               Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","070","071",0,"073");
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3CNS.TXT","075",0,0,0);
               Speech("SPRFACE2.DAT","conserf.pcx","D3_STR.DAT","D3CNS.TXT","077",0,0,0);
            	break;
         }
         break;
      case 2: /////////////////////// day 2 /////////////////////
      	switch(player.scn_janitor){ ///////////////////// janitor ////////////////////////////////
         	case 0:  ////////////////  scene 0 ///////////////////
         		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","001","002",0,0);
         		while(end_conversation == 0){
         			if(player.mission_bag == 1){ option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","010","011","012","013"); }
         			else{ option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","010","011","012",0); }
            		switch(option){
            			case 1: // live here?
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","018","019","020",0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","022","023",0,0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","025",0,0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","028","029","030","031");
                  		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","033","034","035","036");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","040",0,0,0);
                  		break;
               		case 2: // party?
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","044","045",0,0);
               			Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","049","050",0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","052","053","054","055");
                  		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","059","060","061",0);
                  		break;
               		case 3: // hi
               			Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","065",0,0,0);
                  		end_conversation = 1;
                  		break;
               		case 4: // bag?
               			Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","070","071",0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","072","073","074","075");
                        Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","077",0,0,0);
                        end_conversation = 1;
                  		break;
            		}
         		}
      			break;
            case 99:
            	Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","080","081",0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2CNS.TXT","085","086",0,0);
               Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2CNS.TXT","088","089",0,0);
            	break;
      	}
         break;
      case 1: /////////////////////// day 1 /////////////////////
         switch(player.scn_janitor){ ///////////////////// janitor ////////////////////////////////
         	case 0:  ////////////////  scene 0 ///////////////////
      			Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","001",0,0,0);
         		Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","005","006",0,0);
         		end_conversation = 0;
					while(end_conversation == 0){
         			option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","010","011","012",0);
         			switch(option){
            			case 1: // why do not stop it?
               			Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","019","020","021","022");
               			Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","024","025","026",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","029","030","031","032");
                  		Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","034","035","036","037");
                  		break;
               		case 2: // do something
               			Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","040","041","042","043");
               			Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","045","046","047","048");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","050","051",0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","055","056","057",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","060",0,0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","063",0,0,0);
                  		break;
               		case 3: // my way
               			Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","070","071","072",0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","074","075",0,0);
                  		Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","080","081","082",0);
               			end_conversation = 1;
               			break;
            		}
         		}
      			break;
            case 1:
            	Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","103","104","105","106");
               Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","108","109","110",0);
               Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","113","114","115","116");
               break;
            case 99:
               Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","090","091","092",0);
               Speech("SPRFACE2.DAT","conserf.pcx","D1_STR.DAT","D1CNS.TXT","094","095","096",0);
               Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1CNS.TXT","099",0,0,0);
            	break;
         }
         break;
   }
}
 /***********************
*  DAY 10 THE EXAM THEFT
************************/

#include "source\engine\engine.h"
/////////////////////////////////////////////////////////
// Go to encounter with nerds
/////////////////////////////////////////////////////////
void near GoToNerds(void){
	byte option;
   byte end_conversation = 0;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES.DAT","frikis.pcx",2); // Load menu background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("SPRFACE1.DAT","antof.pcx","D10_STR.DAT","D10NERD.TXT","001","002","003",0);
   Speech("SPRFACE1.DAT","xavif.pcx","D10_STR.DAT","D10NERD.TXT","005","006","007","008");
   Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","010","011","012","013");
   Speech("SPRFACE1.DAT","davidf.pcx","D10_STR.DAT","D10NERD.TXT","017","018","019","020");

   while(end_conversation == 0){
   	option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10NERD.TXT","022","023","024","025");
   	switch(option){
     		case 1: // party?
         	Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","035","036","037","038");
         	Speech("SPRFACE1.DAT","davidf.pcx","D10_STR.DAT","D10NERD.TXT","039","040","041",0);
         	Speech("SPRFACE1.DAT","xavif.pcx","D10_STR.DAT","D10NERD.TXT","043","044","045",0);
         	Speech("SPRFACE1.DAT","davidf.pcx","D10_STR.DAT","D10NERD.TXT","051","052","053","054");
      		break;
      	case 2: // like silver axe
         	Speech("SPRFACE1.DAT","davidf.pcx","D10_STR.DAT","D10NERD.TXT","055","056","057",0);
         	Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","058","059","060","061");
         	Speech("SPRFACE1.DAT","antof.pcx","D10_STR.DAT","D10NERD.TXT","062","063",0,0);
      		break;
      	case 3: // shooter game
         	Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","065","066","067",0);
         	Speech("SPRFACE1.DAT","xavif.pcx","D10_STR.DAT","D10NERD.TXT","068","069",0,0);
         	Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","071","072",0,0);
         	player.rel_nerds ++;
      		break;
         case 4: // bye bye
         	Speech("SPRFACE1.DAT","xavif.pcx","D10_STR.DAT","D10NERD.TXT","027",0,0,0);
         	Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","029",0,0,0);
         	Speech("SPRFACE1.DAT","antof.pcx","D10_STR.DAT","D10NERD.TXT","031",0,0,0);
            end_conversation = 1;
      		break;
      }
   }
}

/////////////////////////////////////////////////////////
// Nerds
/////////////////////////////////////////////////////////
void far Nerds(void){
	byte option = 1;
   byte end_conversation = 0;
	switch(player.day){
   	case 10:
      	switch(player.scn_nerds){
         	case 0: //first time speak
            	GoToNerds();
   				player.floor1_event_mask[9] = 1; // Enable event. thugs assault
   				GoToFloor1(355, 155);
               player.scn_nerds = 1;
               Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10NERD.TXT","047","048","049","050");
               break;
            case 1: // second time speak
            	Speech("SPRFACE1.DAT","xavif.pcx","D10_STR.DAT","D10NERD.TXT","075","076","077",0);
               Speech("SPRFACE1.DAT","davidf.pcx","D10_STR.DAT","D10NERD.TXT","080","081",0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
               player.scn_nerds = 2;
               break;
            case 2:
         		Speech("SPRFACE1.DAT","davidf.pcx","D10_STR.DAT","D10NERD.TXT","082","083","084",0);
               Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
               player.scn_nerds = 3;
               break;
            case 3:
            	Speech("SPRFACE1.DAT","antof.pcx","D10_STR.DAT","D10NERD.TXT","086","087","088","089");
               Speech("SPRFACE1.DAT","xavif.pcx","D10_STR.DAT","D10NERD.TXT","091","092",0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D10_STR.DAT","D10NERD.TXT","094","095",0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
               player.scn_nerds = 4;
               break;
            case 4:
            	Speech("SPRFACE1.DAT","alainf.pcx","D10_STR.DAT","D10NERD.TXT","097","098","099","100");
               Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
               player.scn_nerds = 5;
               break;
            default:
         		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GLB.TXT","017","018","019",0);
               break;
         }
      	break;
      case 9:
      	switch(player.scn_nerds){
         	case 0:
            	Speech("SPRFACE1.DAT","davidf.pcx","D9_STR.DAT","D9NERD.TXT","005","006",0,0);
               end_conversation = 0;
               while(!end_conversation){
               	if( player.mission_doll==0){option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9NERD.TXT","010","011","012",0);}
                  else{ option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9NERD.TXT","010","011","012","013"); }
                  switch(option){
                  	case 1: // like
                     	Speech("SPRFACE1.DAT","xavif.pcx","D9_STR.DAT","D9NERD.TXT","015","016",0,0);
                        Speech("SPRFACE1.DAT","davidf.pcx","D9_STR.DAT","D9NERD.TXT","018","019","020",0);
                        Speech("SPRFACE1.DAT","antof.pcx","D9_STR.DAT","D9NERD.TXT","022","023","024",0);
                        Speech("SPRFACE1.DAT","davidf.pcx","D9_STR.DAT","D9NERD.TXT","026","027","028",0);
                        Speech("SPRFACE1.DAT","antof.pcx","D9_STR.DAT","D9NERD.TXT","030","031",0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9NERD.TXT","035","036",0,0);
                        break;
                     case 2: // can i?
                     	Speech("SPRFACE1.DAT","xavif.pcx","D9_STR.DAT","D9NERD.TXT","045","046","047",0);
                        break;
                     case 3: // bye
                     	Speech("SPRFACE1.DAT","davidf.pcx","D9_STR.DAT","D9NERD.TXT","050","051","052",0);
                        Speech("SPRFACE1.DAT","alainf.pcx","D9_STR.DAT","D9NERD.TXT","055","056","057",0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9NERD.TXT","060","061",0,0);
                        end_conversation = 1;
                        break;
                     case 4: // doll mission
                     	Speech("SPRFACE1.DAT","xavif.pcx","D9_STR.DAT","D9NERD.TXT","080","081","082",0);
                        Speech("SPRFACE1.DAT","antof.pcx","D9_STR.DAT","D9NERD.TXT","085","086","087",0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9NERD.TXT","090","091","092","093");
                        Speech("SPRFACE1.DAT","alainf.pcx","D9_STR.DAT","D9NERD.TXT","095",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9NERD.TXT","097","098",0,0);
                        Speech("SPRFACE1.DAT","xavif.pcx","D9_STR.DAT","D9NERD.TXT","100",0,0,0);
                        Speech("SPRFACE1.DAT","davidf.pcx","D9_STR.DAT","D9NERD.TXT","101",0,0,0);
                        end_conversation = 1;
                        player.scn_nerds++;
                  }
               }
               break;
            case 1:
            	Speech("SPRFACE1.DAT","xavif.pcx","D9_STR.DAT","D9NERD.TXT","070",0,0,0);
               player.scn_nerds++;
               break;
            case 2:
            	Speech("SPRFACE1.DAT","davidf.pcx","D9_STR.DAT","D9NERD.TXT","075","076",0,0);
               player.scn_nerds++;
               break;
            default:
            	Speech("SPRFACE1.DAT","antof.pcx","D9_STR.DAT","D9NERD.TXT","065","066","067",0);
               break;
         }
      	break;
      case 8:
      	Speech("SPRFACE1.DAT","playerf.pcx","D8_STR.DAT","D8NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D8_STR.DAT","D8NERD.TXT","002",0,0,0);
      	break;
      case 7:
      	Speech("SPRFACE1.DAT","playerf.pcx","D7_STR.DAT","D7NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D7_STR.DAT","D7NERD.TXT","002",0,0,0);
      	break;
      case 6:
      	Speech("SPRFACE1.DAT","playerf.pcx","D6_STR.DAT","D6NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D6_STR.DAT","D6NERD.TXT","002",0,0,0);
      	break;
      case 5:
      	Speech("SPRFACE1.DAT","playerf.pcx","D5_STR.DAT","D5NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D5_STR.DAT","D5NERD.TXT","002",0,0,0);
      	break;
      case 4:
      	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","002",0,0,0);
      	break;
      case 3:
      	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","002",0,0,0);
      	break;
      case 2:
      	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D2_STR.DAT","D2NERD.TXT","002",0,0,0);
      	break;
      case 1:
      	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","001",0,0,0);
         Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1NERD.TXT","002",0,0,0);
      	break;
   }
}



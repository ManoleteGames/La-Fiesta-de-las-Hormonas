/***********************
*  GIRLS
************************/

#include "source\engine\engine.h"


/////////////////////////////////////////////////////////
// Go to encounter with girls on second floor
/////////////////////////////////////////////////////////
void near GoToGirls(void){
 	byte option;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES.DAT","girls.pcx",2); // Load menu background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","001","002",0,0);
   Speech("SPRFACE1.DAT","jessyf.pcx","D10_STR.DAT","D10GIRL.TXT","004",0,0,0);
   Speech("SPRFACE1.DAT","fanyf.pcx","D10_STR.DAT","D10GIRL.TXT","005",0,0,0);
   Speech("SPRFACE1.DAT","vanef.pcx","D10_STR.DAT","D10GIRL.TXT","006",0,0,0);

   if(player.scn_girls == 0){
   	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","010","011",0,0);
   	switch(option){
   		case 1: //DO YOU KNOW ABOUT PARTY?
         	Speech("SPRFACE1.DAT","jessyf.pcx","D10_STR.DAT","D10GIRL.TXT","015","016","017","018");
         	Speech("SPRFACE1.DAT","vanef.pcx","D10_STR.DAT","D10GIRL.TXT","020",0,0,0);
         	Speech("SPRFACE1.DAT","fanyf.pcx","D10_STR.DAT","D10GIRL.TXT","022","023",0,0);
         	player.scn_girls = 1;
         	break;
      	case 2: //NOTHING
        		Speech("SPRFACE1.DAT","jessyf.pcx","D10_STR.DAT","D10GIRL.TXT","013",0,0,0);
        	 	break;
   	}
   }

   if(player.scn_girls == 1){
   	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","025","026",0,0);
   	switch(option){
   		case 1: //NO
         	Speech("SPRFACE1.DAT","fanyf.pcx","D10_STR.DAT","D10GIRL.TXT","028","029","030",0);
         	Speech("SPRFACE1.DAT","vanef.pcx","D10_STR.DAT","D10GIRL.TXT","032","033","034",0);
         	player.scn_girls = 2;
            player.popular--;
         	break;
      	case 2: //YES
        		Speech("SPRFACE1.DAT","fanyf.pcx","D10_STR.DAT","D10GIRL.TXT","036",0,0,0);
            Speech("SPRFACE1.DAT","jessyf.pcx","D10_STR.DAT","D10GIRL.TXT","037",0,0,0);
         	Speech("SPRFACE1.DAT","vanef.pcx","D10_STR.DAT","D10GIRL.TXT","038",0,0,0);
            Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","060","061","062","063");
            player.popular ++;
            player.scn_girls = 2;
            player.mission_party = 1;
         	break;
   	}
   }
}

/////////////////////////////////////////////////////////
// Girls
/////////////////////////////////////////////////////////
void far Girls(void){
	byte option = 1;
   byte end_conversation = 0;
	switch(player.day){
   	case 10:
      	switch(player.scn_girls){
         	case 0: //first time speak
            	GoToGirls();
            	GoToFloor2(155, 200);
            	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","048","049",0,0);
            	if(player.mission_party){
            		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","051","052","053","054");
            	} else {
            		Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","056","057","058",0);
            	}
            	break;
         	default: // second time speak
            	if(player.mission_party == 1){
               	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","040",0,0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D10_STR.DAT","D10GIRL.TXT","041",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D10_STR.DAT","D10GIRL.TXT","042",0,0,0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D10_STR.DAT","D10GIRL.TXT","043",0,0,0);

               } else {
               	Speech("SPRFACE1.DAT","playerf.pcx","D10_STR.DAT","D10GIRL.TXT","040",0,0,0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D10_STR.DAT","D10GIRL.TXT","044",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D10_STR.DAT","D10GIRL.TXT","045",0,0,0);
               }
               break;
         }
      	break;
      case 9:
			if(player.mission_party > 0){
         	switch(player.scn_girls){
            	case 0:
               	Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","001",0,0,0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","003",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","003",0,0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","040","041","042",0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","045",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","048","049","050",0);
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","052","053",0,0);
                  switch(option){
                  	case 1: //HELP
                  		Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","055",0,0,0);
                        Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","057","058",0,0);
                        player.mission_party = 1;
                        break;
                     case 2: //DO NOT HELP
                     	Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","025",0,0,0);
                        Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","026",0,0,0);
                        player.mission_party = 0;
                        break;
                  }
                  player.scn_girls = 1;
                  break;
               case 1:
               	if(player.mission_doll > 0){
                  	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","065","066",0,0);
                                 switch(option){
                        				case 1: //JON?
                           				Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","070","071",0,0);
                                       Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","078","081","082",0);
                                       Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","080","081","082",0);
                           				Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","085","086","087","088");
                                       Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","078","081","082",0);
                              			break;
                           			case 2: //BYE
                              			break;
                        			}
                              }
                        		Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","055",0,0,0);
                           	Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","057","058",0,0);
                           	Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","060",0,0,0);
                        		break;
                        }
                     }
                     else{
                     	switch(player.scn_girls){
                        	case 0:
                     		 	Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","001",0,0,0);
                     			Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","003",0,0,0);
                     			Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","004","005",0,0);
                           	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","010","011",0,0);
   									switch(option){
   										case 1: //GREAT
         									Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","015","016","017","018");
         									Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","020","021",0,0);
         									break;
      									case 2: //UNLIKE
                                 	Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","025",0,0,0);
        										Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","026",0,0,0);
            								break;
   									}
                           	player.scn_girls = 1;
                              break;
                        	case 1:
                           	if(player.mission_doll > 0){
                               	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","065","066",0,0);
                                 switch(option){
                        				case 1: //JON?
                           				Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","070","071",0,0);
                                       Speech("SPRFACE1.DAT","playerf.pcx","D9_STR.DAT","D9GIRL.TXT","075","076",0,0);
                                       Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","080","081","082",0);
                           				Speech("SPRFACE1.DAT","jessyf.pcx","D9_STR.DAT","D9GIRL.TXT","085","086","087","088");
                                       player.scn_girls = 2;
                              			break;
                           			case 2: //BYE
                                    	Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","090",0,0,0);
                              			break;
                        			}
                              }
                           case 2:
                           	Speech("SPRFACE1.DAT","fanyf.pcx","D9_STR.DAT","D9GIRL.TXT","030","031",0,0);
                          		Speech("SPRFACE1.DAT","vanef.pcx","D9_STR.DAT","D9GIRL.TXT","033","034","035",0);
                           	break;
                        }
                     }
                  	break;
      case 8:
      	break;
      case 7:
      	break;
      case 6:
      	break;
      case 5:
      	break;
      case 4:
      	break;
      case 3:
      	break;
      case 2:
      	break;
      case 1:
      	break;
   }
}


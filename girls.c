/***********************
*  GIRLS
************************/

#include "source\engine\engine.h"


/////////////////////////////////////////////////////////
// Go to encounter with girls on second floor
/////////////////////////////////////////////////////////
void near GoToGirls_D4(void){
 	byte option;

	SetLoadingInterrupt();   // Start loading animation
   LoadImage("IMAGES.DAT","girls.pcx",2); // Load menu background image to non visible page
   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","001","002",0,0);
   Speech("SPRFACE1.DAT","jessyf.pcx","D4_STR.DAT","D4GIRL.TXT","004",0,0,0);
   Speech("SPRFACE1.DAT","fanyf.pcx","D4_STR.DAT","D4GIRL.TXT","005",0,0,0);
   Speech("SPRFACE1.DAT","vanef.pcx","D4_STR.DAT","D4GIRL.TXT","006",0,0,0);
   option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","010","011",0,0);
   switch(option){
   	case 1: //DO YOU KNOW ABOUT PARTY?
      	Speech("SPRFACE1.DAT","jessyf.pcx","D4_STR.DAT","D4GIRL.TXT","015","016","017","018");
         Speech("SPRFACE1.DAT","vanef.pcx","D4_STR.DAT","D4GIRL.TXT","020",0,0,0);
         Speech("SPRFACE1.DAT","fanyf.pcx","D4_STR.DAT","D4GIRL.TXT","022","023","024",0);
         Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","060","061","062","063");
         option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","025","026",0,0);
         switch(option){
      			case 1: // help
        				Speech("SPRFACE1.DAT","fanyf.pcx","D4_STR.DAT","D4GIRL.TXT","036","037","038",0);
            		Speech("SPRFACE1.DAT","jessyf.pcx","D4_STR.DAT","D4GIRL.TXT","070","071",0,0);
                  Fade_out();
                  LoadImage("IMAGES2.DAT","later.pcx",1); // Load menu background image to non visible page
                  SetPage(1);
         			Fade_in();
                  if(player.popular<18){UpdatePopularity(1);}
                  SetNewTime(time_seconds-30);
            		player.mission_party = 1;
         			Delay(100);
         			Fade_out();
         			SetPage(2);
         			Fade_in();

                  Speech("SPRFACE1.DAT","vanef.pcx","D4_STR.DAT","D4GIRL.TXT","080","081","082","083");
                  Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","085",0,0,0);
                  break;
               case 2: // do not help
         			Speech("SPRFACE1.DAT","fanyf.pcx","D4_STR.DAT","D4GIRL.TXT","028","029","030",0);
         			Speech("SPRFACE1.DAT","vanef.pcx","D4_STR.DAT","D4GIRL.TXT","032","033","034",0);
                  player.mission_party = 9;
         			break;
   			}
         	player.scn_girls = 1;
         	break;
      	case 2: // nothing
        		Speech("SPRFACE1.DAT","jessyf.pcx","D4_STR.DAT","D4GIRL.TXT","013",0,0,0);
        	 	break;
   }
}

/////////////////////////////////////////////////////////
// Girls
/////////////////////////////////////////////////////////
void far Girls(void){
	byte option = 1;
   byte end_conversation = 0;
	switch(player.day){

   	case 4:  /////////////////////////// day 4 //////////////////////
      	switch(player.scn_girls){
         	case 0: //first time speak
            	GoToGirls_D4();
            	GoToFloor2(155, 200);

               SetSpriteAnimation(player.spriteNum,0,6,8,PlayerAnimation);   // Stand up player
               Update(0);

            	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","048","049",0,0);
               if(player.mission_party == 1){
               	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","051","052","053","054");
                  Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","065","066",0,0);
               }
               if(player.mission_party == 9){
               	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GIRL.TXT","056","057","058",0);
               }
            	break;
         	case 1: // scene 1 : second time speak
               Speech("SPRFACE1.DAT","fanyf.pcx","D4_STR.DAT","D4GIRL.TXT","040","041","042","043");
               Speech("SPRFACE1.DAT","jessyf.pcx","D4_STR.DAT","D4GIRL.TXT","044",0,0,0);
               Speech("SPRFACE1.DAT","vanef.pcx","D4_STR.DAT","D4GIRL.TXT","045","046",0,0);
               break;
            case 99:
               Speech("SPRFACE1.DAT","fanyf.pcx","D4_STR.DAT","D4GIRL.TXT","090","091","092","093");
               Speech("SPRFACE1.DAT","vanef.pcx","D4_STR.DAT","D4GIRL.TXT","095","096","097",0);
            	break;
         }
      	break;
      case 3:  /////////////////////////// day 3 //////////////////////
      	switch(player.scn_girls){
         	case 0:
            	SetLoadingInterrupt();   // Start loading animation
   				LoadImage("IMAGES2.DAT","girls2.pcx",2); // Load menu background image to non visible page
   				ResetLoadingInterrupt();   // Stop loading animation

   				SetPage(2);
   				Update(0);

               Fade_in();
            	if(player.mission_party > 0){
               	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GIRL.TXT","001",0,0,0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","003",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","003",0,0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","040","041","042","043");
                  Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","015","016","017","018");
               } else {
               	Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","004","005","006",0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","015","016","017","018");
                  Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","020","021",0,0);
               }

               Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","010","011","012","013");
               Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","045",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GIRL.TXT","048","049","050",0);
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GIRL.TXT","052","053",0,0);
               switch(option){
               	case 1: //HELP

                  	Fade_out();
                     LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
         				Fade_in();

                     if(player.popular<20){UpdatePopularity(1);}
                     SetNewTime(time_seconds-30);

         				Delay(100);
         				Fade_out();
         				LoadImage("IMAGES.DAT","girls.pcx",2); // Load menu background image to non visible page
        	 				Fade_in();

                  	Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","055",0,0,0);
                     Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","057","058",0,0);
                     player.mission_party = 1;
                     player.scn_girls = 1;
                     break;
                  case 2: //DO NOT HELP
                  	if(player.popular>0){UpdatePopularity(-1);}
                     Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","025",0,0,0);
                     Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","026",0,0,0);
                     player.mission_party = 0;
                     player.scn_girls = 2;
                     break;
               }
               GoToGym(126,226);
               break;
            case 1:
            	Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","055",0,0,0);
               Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","057","058",0,0);
               Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","060",0,0,0);
               player.scn_girls = 2;
               break;
            case 99:
               Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","095","096",0,0);
               Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","100",0,0,0);
               Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","103","104","105",0);
            	break;
            default:
            	Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","030","031",0,0);
               Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","033","034","035",0);
               break;
         }

         if((player.mission_doll > 0)&&(player.scn_girls < 10)){
         	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GIRL.TXT","065","066",0,0);
            switch(option){
            	case 1: //JON?
               	if(player.popular>0){UpdatePopularity(-1);}
                  if(player.good>0){UpdateGoodness(-1);}
                  Speech("SPRFACE1.DAT","vanef.pcx","D3_STR.DAT","D3GIRL.TXT","070","071",0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GIRL.TXT","075","076",0,0);
                  Speech("SPRFACE1.DAT","fanyf.pcx","D3_STR.DAT","D3GIRL.TXT","080","081","082",0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D3_STR.DAT","D3GIRL.TXT","085","086","087","088");
                  break;
               case 2: //BYE
               	break;
            }
            player.scn_girls = 10;
         }
         break;

      case 2:  /////////////////////////// day 2 //////////////////////
      	if(player.floor == 1) { // speak with jessy
         	switch(player.mission_bag){
            	case 0:  //////////////////////////////// scene 0 : first time speak ////////////////////////////////////
               	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","001",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","005",0,0,0);
                  while(end_conversation == 0){
                  	option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","007","008","009",0);
                     switch(option){
                     	case 1: //what happens?
                        	Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","015","016","017",0);
                           Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","020","021","022",0);
                           Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","024","025","026",0);
                           option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","028","029",0,0);
                           switch(option){ // ask about bag
                           	case 1: //help
                              	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","032","033",0,0);
                                 Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","039","040","041",0);

                                 player.mission_bag = 1;
                                 end_conversation = 1;
                                 break;
                              case 2: // not help
                              	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","035","036",0,0);
                                 Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","037",0,0,0);
                                 end_conversation = 1;
                                	if(player.popular>2){UpdatePopularity(-1);}
                                 player.mission_bag = 9;
                                 player.scn_girls = 1;
                                 break;
                           }
                           break;
                        case 2: //girls?
                        	Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","042","043","044",0);
                           break;
                        case 3: // bye
                        	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","002",0,0,0);
                           Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","037",0,0,0);
                           end_conversation = 1;
                           break;
                     }
                  }
                  break;
               case 1:  //////////////////////////////// scene 1 : do not have bag yet ////////////////////////////////////
               	Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","048",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","050","051","052",0);
                  break;
               case 2: ///////////////////////////////// scene 2 : do not take it /////////////////////////
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","048",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","085","086","087",0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","096","097","098",0);
               	break;
               case 3:
               	Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","048",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","059","060",0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","062","063","064",0);
                  option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","055","056",0,0);
                  switch(option){
                  	case 1: // accuse toni
                     	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","067","068",0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","090","091",0,0);
                        Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","093","094",0,0);
                        if(player.popular<18){UpdatePopularity(1);}
                        if(player.good>2){UpdateGoodness(-1);}
                        player.item_bag = 0;
                        HideSprite(4);
                        break;
                     case 2: // do not accusse toni
                     	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","067","068","069",0);
                        Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","071","072","073",0);
                        if(player.popular<18){UpdatePopularity(1);}
                        if(player.good<18){UpdateGoodness(1);}
                        player.item_bag = 0;
                        HideSprite(4);
                        break;
                  }
                  ResetItem(1,16);

                  player.floor1_hotspot_mask[17] = 0;
                  player.mission_bag = 4;
                  player.scn_main = 1;
                  player.scn_girls = 1;
               	break;
               case 9:  //////////////////////////////// scene 9 : do not help ////////////////////////////////////
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","001",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","005",0,0,0);
                  if(player.popular>2){UpdatePopularity(-1);}
                  while(end_conversation == 0){
                  	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","008","009",0,0);
                     switch(option){
                        case 1: //girls?
                        	Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","042","043","044",0);
                           break;
                        case 2: // bye
                        	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","002",0,0,0);
                           Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","037",0,0,0);
                           end_conversation = 1;
                           break;
                     }
                  }
               	break;
            }
         }
         if(player.floor == 5) { // speak with girls at gym
         	switch (player.scn_girls){
               case 0:
                  end_conversation = 0;
            		while(end_conversation == 0){
            			if(player.mission_bag == 1){ option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","104","105","106","107"); }
				   		else{	option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","104","105","106",0); }
               		switch(option){
               			case 1: // how r u doing?
                  			Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","110","111",0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","114",0,0,0);
                     		Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","116",0,0,0);
                     		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","119","120",0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","122",0,0,0);
                     		break;
                  		case 2:   // need something?
                  			Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","075","076","077",0);
                        	Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","080","081","082",0);
                     		break;
                  		case 3: /// bye
                  			Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","154",0,0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","156",0,0,0);
                     		end_conversation = 1;
                     		break;
                  		case 4: // bag?
                  			Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","160","161",0,0);
                     		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","163","164",0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","166","167",0,0);
                     		Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","170","171","172",0);
                     		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","177","178",0,0);
                     		end_conversation = 1;
                     		break;
               		}
            		}
               	break;
            	case 1:
               	SetLoadingInterrupt();   // Start loading animation
  						LoadImage("IMAGES2.DAT","girls2.pcx",2); // Load menu background image to non visible page
            		ResetLoadingInterrupt();   // Stop loading animation
            		SetPage(2);
            		Update(0);

                  Fade_in();
         			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","100",0,0,0);
            		Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","101",0,0,0);
            		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","102",0,0,0);
            		end_conversation = 0;
            		while(end_conversation == 0){
                  	option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","104","105","106",0);
               		switch(option){
               			case 1: // how r u doing?
                  			Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","110","111",0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","114",0,0,0);
                     		Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","116",0,0,0);
                     		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","119","120",0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","122",0,0,0);
                     		break;
                  		case 2:   // need something?
                      		Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","124","125","126",0);
                     		if (player.mission_bag == 1){Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","129","130","131","132"); }
                     		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","134","135","136","137");
                        	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","139","140",0,0);
                        	if(option == 1){  // help
                        		Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","143","144",0,0);
                              Fade_out();
                    				LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
         							Fade_in();

                     			if(player.popular<18){UpdatePopularity(1);}
                              SetNewTime(time_seconds-30);

                              player.mission_chair = 1;

         							Delay(100);
                              Fade_out();
         							LoadImage("IMAGES2.DAT","girls2.pcx",2); // Load menu background image to non visible page
        	 							Fade_in();
                              Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","146",0,0,0);
                           } else { // do not help
                           	if(player.popular>2){UpdatePopularity(-1);}
                              Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","150","151",0,0);
                           }
                           player.scn_girls++;
                           end_conversation = 1;
                           break;
                        case 3: /// bye
                  			Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","154",0,0,0);
                     		Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","156",0,0,0);
                     		end_conversation = 1;
                     		break;
                     }
                  }
                  GoToGym(126,226);
                  break;
            	case 2: // scn girls
                  Speech("SPRFACE1.DAT","fanyf.pcx","D2_STR.DAT","D2GIRL.TXT","174",0,0,0);
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","175",0,0,0);
               	break;
               case 99:
                  Speech("SPRFACE1.DAT","jessyf.pcx","D2_STR.DAT","D2GIRL.TXT","190","191","192",0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","194","195","196","197");
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","199","200",0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","202",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GIRL.TXT","204",0,0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D2_STR.DAT","D2GIRL.TXT","206",0,0,0);
               	break;
            }
         }
      	break;
      case 1:  /////////////////////////// day 1 //////////////////////
         switch (player.scn_girls){
         	case 0:
               Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","001",0,0,0);
            	Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","005",0,0,0);
               Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","006",0,0,0);
               Speech("SPRFACE1.DAT","fanyf.pcx","D1_STR.DAT","D1GIRL.TXT","007","008",0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","010","011",0,0);
               Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","015","016",0,0);
               Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","018","019","020","021");
               Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","025","026","027",0);
               Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","030","031",0,0);
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","034","035",0,0);
               switch(option){
               	case 1:  // help
                  	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","038",0,0,0);
                     Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","042","043",0,0);
                     SetSpriteAnimation(player.spriteNum,25,1,8,PlayerAnimation); // Set animation >> up
               		Update(0);
                     Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","047","048",0,0);
                     player.scn_girls = 1;
                     player.mission_band = 1;
                     SetNewTime(time_seconds-30);
                  	break;
                  case 2:  // do not help
                  	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","039",0,0,0);
                     Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","045",0,0,0);
                     if(player.popular>2){UpdatePopularity(-1);}
                     player.scn_girls = 2;
                  	break;
               }
               break;
            case 1:
            	Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","055","056",0,0);
            	if((player.scn_nerds == 2)&&(player.scn_thugs == 2)){
               	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","059","060",0,0);
               	switch(option){
               		case 1:  // pulmon negro
                     	Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","063",0,0,0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","065","066",0,0);
                        Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","069",0,0,0);
                     	player.scn_girls = 2;
                     	player.mission_band = 2;
                  		break;
                 		case 2:  // la oreja
                     	Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","072",0,0,0);
                  		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","074",0,0,0);
                     	Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","076","077",0,0);
                        if(player.good<18){UpdateGoodness(1);}
                        if(player.popular<18){UpdatePopularity(1);}
                     	player.scn_girls = 3;
                        player.mission_band = 3;
                  		break;
               	}
               } else if ((player.scn_nerds == 2)&&(player.scn_thugs != 2)){
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","060",0,0,0);
               	Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","072",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","074",0,0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","076","077",0,0);
                  if(player.good<18){UpdateGoodness(1);}
                  if(player.popular<18){UpdatePopularity(1);}
                  player.scn_girls = 3;
                  player.mission_band = 3;
               } else if ((player.scn_nerds != 2)&&(player.scn_thugs == 2)){
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","059",0,0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","063",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","065","066",0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","069",0,0,0);
               	player.scn_girls = 2;
               	player.mission_band = 2;
               }else{
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1GIRL.TXT","083","084",0,0);
                  Speech("SPRFACE1.DAT","vanef.pcx","D1_STR.DAT","D1GIRL.TXT","086","087",0,0);
               }
            	break;
            case 2:  // pulmon negro
               Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","095","096","097",0);
               Speech("SPRFACE1.DAT","fanyf.pcx","D1_STR.DAT","D1GIRL.TXT","100","101",0,0);
            	break;
            case 3:  // la oreja
            	Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","090","091",0,0);
            	break;
            case 99:
               Speech("SPRFACE1.DAT","jessyf.pcx","D1_STR.DAT","D1GIRL.TXT","105","106",0,0);
            	break;
         }
      	break;
   }
}


/***********************
*  ALL DAY HOTSPOTS
************************/

#include "source\engine\engine.h"

void far Hotspots(byte hotspot){
	byte option;
   byte end_conversation = 0;

   // Hotspots 1..7 are common hotspots for all the floors
   if(player.hotspot == 1){ ///////////////////////// window /////////////////////////
 		Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","065","066",0,0);
   }
   if(player.hotspot == 2){ ////////////////////// extinguisher ////////////////////
   	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","070","071","072",0);
   	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","027","028",0,0);
   	switch(option){
			case 1: // OPEN
            EndGameExtinguisher();
            break;
         case 2: // DO NOT OPEN
            break;
      }
	}
   if(player.hotspot == 3){ ////////////// girls bathroom ////////////////////////////
   	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","061","062",0,0);
   }
   if(player.hotspot == 4){ ///////////////////// boys bathroom ////////////////////
   	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","073","074",0,0);
      Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","075","076",0,0);
   }
   if(player.hotspot == 5){ //////////////////// Jon sign /////////////////////////
   	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","080","081","082",0);
      Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","084","085",0,0);
   }
   if(player.hotspot == 6){ /////////////////// Spare ///////////////////////////////
   }
   if(player.hotspot == 7){ //////////////////// Spare //////////////////////////////
   }


   // ********************************************************
   // CUSTOM FLOOR HOTSPOTS
   // ********************************************************
	switch(player.floor){
   	case 1: ////////////////////////////// Floor 1 ////////////////////////////////
			if(player.floor1_hotspot_mask[hotspot] == 1){
         	if(player.hotspot == 8){ //////////////////// News board ///////////////////////
               switch(player.day){
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
            if(player.hotspot == 9){ ///////////////////////// arcade machine //////////////////////////
               if(player.mission_arcade==0){
               	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","001","002",0,0);
               	if(player.money >= 25){
               		Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","003","004","034","035");
                     Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","036","037","038",0);
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
            if(player.hotspot == 10){ /////////////////////////// bar ////////////////////////////////
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","040","041",0,0);
            }
            // *****************************************
            if(player.hotspot == 11){ ////////////////////////// item exams /////////////////////////
               if(player.day == 4){ // exams only available on day 4
            		switch(player.mission_cheat){
            			case 3:
               			Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","081","082",0,0);
                     	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","078","079","080",0);
   							option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","085","086",0,0);
                  		if(player.scn_main == 0){ player.scn_main = 1; } // Set scene 1
   							switch(option){
				   				case 1: // TAKE EXAMS
                     			player.mission_cheat = 4;
                     			player.item_exams = 1;
                     			SetItem(2,16,"exams.pcx");
                     			SetSpriteAnimation(1,0,6,12,PlayerAnimation);
                     			Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","088","089",0,0);
                     			player.scn_director = 3;
                        		if(player.good>0){UpdateGoodness(-1);}
			      					break;
     								case 2: // DO NOT TAKE EXAMS
                     			player.mission_cheat = 5;
         							Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","091","092",0,0);
                        		if(player.good<18){UpdateGoodness(1);}
      								break;
               			}
                     	break;
                  	case 4:
                  		Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","105","106","107",0);
                  		break;
                  	case 5:
                  		Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","110","111","112","113");
                  		break;
               	}
               } else { // rest of the days, just papers
                	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","105","106","107",0);
               }
            }
            if(player.hotspot == 12){  ////////////////////////// computer ///////////////////////////////
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","050","051","052","053");
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","055",0,0,0);
               Speech("SPRFACE2.DAT","pcf.pcx","GLB_STR.DAT","MISC.TXT","058",0,0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","059",0,0,0);
            }
           if(player.hotspot == 13){ /////////////////////// Lockers /////////////////////////////////
           		if((player.mission_doll == 0)&&(player.item_keys == 0)){
               	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","044","045","046",0);
               } else if((player.mission_doll == 0)&&(player.item_keys == 1)){
               	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","022","023",0,0);
                  switch(option){
                  	case 1: // Open lookers
                     	if(player.good>0){UpdateGoodness(-1);}
                        player.mission_doll = 1;
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","110",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","111",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","112",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","113",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","114","115",0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","026",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","027","028","029","030");
                        SetSpriteAnimation(1,0,6,12,PlayerAnimation);
                        Update(0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","033","034","035","036");
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","037","038","039",0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","040",0,0,0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","043","044","045",0);
                        Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","047","048","049","050");
                        break;
                     case 2: // Do not open lookers
                     	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","055","056","057",0);
                        break;
                  }
               } else if(player.mission_doll > 0){
               	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","052","053",0,0);
               }
            }
            if(player.hotspot == 14){ //////////////// near arcede machine (nerds / thugs ) /////////////////
               switch(player.day){
               	case 4: // nerds near arcade
            			Nerds();
                     break;
                  case 3:  // thugs near arcade machine
                     Thugs();
                     break;
                  default:
                  	break;
               }
            }

            if(player.hotspot == 15){ ///////////////////////////////// Director ////////////////////////
               Director();
            }
            if(player.hotspot == 16){ //////////////////////////////// Janitor //////////////////////////
             	Janitor();
            }
            if(player.hotspot == 17){ ///////////////////////// Middle on the hall //////////////////////
               if(player.day == 2){ // jessy
                  Girls();
               }
               if(player.day == 1){ // jon and anto
               	Nerds();
               }
            }
            if(player.hotspot == 18){ /////////////////////////// printer //////////////////////////////
               Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","090","091","092","093");
            }
            if(player.hotspot == 19){ ///////////////////////// item keys //////////////////////////////
            	switch(player.mission_keys){
               	case 0:
               		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","005","006","007","008");
               		option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","010","011",0,0);
               		switch(option){
                  		case 1: // TAKE KEYS
                     		SetItem(1,16,"kitem.pcx");
                    			player.item_keys = 1;
                        	HideSprite(4);
                        	player.floor1_hotspot_mask[19] = 0;
                           player.mission_keys = 1;
                     		break;
                     	case 2: // DO NOT TAKE
                     		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","013","014","015","016");
                           player.mission_keys = 2;
                        	break;
               		}
                  case 1:
                  	// keys already taken
                  	break;
                  case 2:
                  	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3GLB.TXT","013","014","015","016");
                  	break;
            	}
            }
		   }
      	break;
      case 2: ////////////////////////////////////// Floor 2 ///////////////////////////////
      	if(player.floor2_hotspot_mask[hotspot] == 1){
            if(player.hotspot == 11){ /////////////// Chalk board ///////////////
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","045","046",0,0);
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","049","050",0,0);
               switch(option){
				   	case 1: // Draw a dick
                     Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","052","053",0,0);
                  	break;
                  case 2: // Take chalk
                  	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4GLB.TXT","054","055",0,0);
                     player.item_chalk = 1;
                     SetItem(2,16,"chalk.pcx");
                     player.mission_cheat = 1;  // Mission cheat started
                     player.floor2_hotspot_mask[11] = 0;  // Reset chalk hotspot
                     break;
               }
            }
            if(player.hotspot == 12){ //////////////// Corridor (girls and nerds) /////////////
               if(player.day == 4){ Girls(); }
               if(player.day == 2){ Nerds(); }
            }
            if(player.hotspot == 13){ //////////////// first window /////////////////
               if(player.day == 2){
               	switch(player.mission_bag){
                  	case 0:
                     	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","110","111","112","113");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","115","116","117","118");
                     	break;
                     case 1:
                        Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","110","111","112","113");
                  		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","082","083","084",0);
                  		option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","085","086",0,0);
                  		switch(option){
                  			case 1:
                     			GoToExt1(240,185);
                     			break;
                     		case 2:
                     			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","088","089","090",0);
                              player.mission_bag = 2;
                     			break;
                  		}
                     	break;
                     case 2:
                        Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2GLB.TXT","005","006","007",0);
                     	break;
                     default:
                     	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","065","066",0,0);
                     	break;
                  }
               } else {
               	Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","065","066",0,0);
               }
   			}
		   }
      	break;
     	case 3: // Ext 1
      	if(player.ext1_hotspot_mask[hotspot] == 1){
         	if(player.hotspot == 2){ // Three bottom

            }
            if(player.hotspot == 3){ // Thugs

            }

            if(player.hotspot == 13){ // Window
            	GoToFloor2(80,195);
               Speech("SPRFACE1.DAT","xavif.pcx","D2_STR.DAT","D2NERD.TXT","145","146",0,0);
               Speech("SPRFACE1.DAT","alainf.pcx","D2_STR.DAT","D2NERD.TXT","148",0,0,0);
               Speech("SPRFACE1.DAT","davidf.pcx","D2_STR.DAT","D2NERD.TXT","150",0,0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","152",0,0,0);
            }

            if(player.hotspot == 14){ // bag
            	player.ext1_hotspot_mask[14] = 0;
             	player.item_bag = 1;
               HideSprite(4);
               SetItem(1,16,"bitem.pcx");
               player.mission_bag = 3;
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
            if(player.hotspot == 10){ // near heroquest map
					Janitor();
            }
            if(player.hotspot == 11){ // fight
               Thugs();
            }
		   }
      	break;
      case 5: // Gym
      	if(player.gym_hotspot_mask[hotspot] == 1){
			  if(player.hotspot == 8){ // sensei
           		Sensei();
            }

            if(player.hotspot == 9){ // girls
            	Girls();
            }
		   }
      	break;
   }
}



/***********************
*  THUGS
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Go to encounter with thugs at lobby
/////////////////////////////////////////////////////////
void near GoToThugs_D4(void){
 	byte option;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

   SetSpriteAnimation(1,0,6,12,PlayerAnimation);

   LoadSprite("SPRCHR1.DAT","jon.pcx",10, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR1.DAT","toni.pcx",11, 32); //Load sprites to one of the fixed structs
   LoadSprite("SPRCHR1.DAT","erik.pcx",12, 32); //Load sprites to one of the fixed structs

   SetSpriteAnimation(10,0,6,30,CharacterAnimation2);
   SetSpriteAnimation(11,0,6,23,CharacterAnimation3);
   SetSpriteAnimation(12,0,6,19,CharacterAnimation3);

   sprite[10].pos_x = sprite[player.spriteNum].pos_x;
   sprite[10].pos_y = sprite[player.spriteNum].pos_y - 32;
   sprite[11].pos_x = sprite[player.spriteNum].pos_x;
   sprite[11].pos_y = sprite[player.spriteNum].pos_y + 32;
   sprite[12].pos_x = sprite[player.spriteNum].pos_x - 32;
   sprite[12].pos_y = sprite[player.spriteNum].pos_y;

	DrawSpriteDestructive(10);
   Delay(40);
   DrawSpriteDestructive(11);
   Delay(40);
	DrawSpriteDestructive(12);
   Delay(40);

	SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES.DAT","thugs.pcx",2); // Load menu background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","001","002","003",0);
   Speech("SPRFACE1.DAT","jonf.pcx","D4_STR.DAT","D4THUG.TXT","005","006",0,0);
   Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","009","010",0,0);
   Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","013","014",0,0);
   Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","017","018","019","020");
   option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4THUG.TXT","023","024",0,0);
   switch(option){
   	case 1: //A FUMARME UN PITI AL RECRE
         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","029","030",0,0);
         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","031","032","033",0);
         if(player.popular<18){UpdatePopularity(1);}
         player.scn_thugs = 2;
         break;
      case 2: //APARTATE MATON, O ME CHIVO
         Speech("SPRFACE1.DAT","jonf.pcx","D4_STR.DAT","D4THUG.TXT","043","044",0,0);
         Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","045",0,0,0);
         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","046",0,0,0);
         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","036","037","038",0);
         Speech("SPRFACE1.DAT","jonf.pcx","D4_STR.DAT","D4THUG.TXT","039",0,0,0);
         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","040",0,0,0);
         Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","041",0,0,0);
         if(player.popular>2){UpdatePopularity(-1);}
         if(player.good<18){UpdateGoodness(1);}
         player.scn_thugs = 1;
         break;
   }
}

/////////////////////////////////////////////////////////
// Go to encounter with thugs at ext2
/////////////////////////////////////////////////////////
void near GoToThugs_Ext2(void){
	byte option;
	SetLoadingInterrupt();   // Start loading animation
   LoadImage("IMAGES2.DAT","thugs2.pcx",2); // Load menu background image to non visible page
   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","058","059","060",0);
   option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4THUG.TXT","062","063",0,0);
   switch(option){
   	case 1: // just walking
      	Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","066","067",0,0);
         Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","068",0,0,0);
         Speech("SPRFACE1.DAT","jonf.pcx","D4_STR.DAT","D4THUG.TXT","069","070",0,0);
         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","071",0,0,0);
         Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","072",0,0,0);
         if(player.good<18){UpdateGoodness(1);}
         break;
      case 2: // To smoke
      	Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","074","075","076","077");
         Fade_out();
         LoadImage("IMAGES2.DAT","later.pcx",1); // Load menu background image to non visible page
         SetPage(1);
         Fade_in();
         if(player.popular<18){UpdatePopularity(1);}
         if(player.good>2){UpdateGoodness(-1);}
         SetNewTime(time_seconds-30);
         Delay(100);
         Fade_out();
         SetPage(2);
         Fade_in();

         Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","078","079","080","081");
         Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4THUG.TXT","085","086","087",0);
         break;
   }
}

/////////////////////////////////////////////////////////
// Go to encounter with thugs and nerds fight
/////////////////////////////////////////////////////////
void near GoToFight(void){
 	byte option;
   byte end_conversation;
   player.mission_fight = 3;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES3.DAT","fight_3.pcx",2); // Load fight image 1

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   end_conversation = 0;
   while(end_conversation == 0){
   	switch(player.scn_thugs){
   		case 0: // scene 0 thugs
      		Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","005","006","007",0);
         	Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","001","002","003",0);
         	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","010","011",0,0);
         	Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","013","014","015",0);
         	Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","017","018","019",0);
         	Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","021","022","023",0);
				option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","032","033",0,0);
         	switch(option){
         		case 1:  // draw
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","040","041","042","043");
               	Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","045","046","047",0);
               	Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","050","051",0,0);
                  player.mission_fight++;
            		break;
            	case 2:  // fying toys
            		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","055","056","057","058");
         			Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","060",0,0,0);
               	Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","062","063","064",0);
                  player.mission_fight--;
              		break;
            }
         	player.scn_thugs++;
      		break;
      	case 1:  // scene 1 thugs
            option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","067","068",0,0);
         	switch(option){
         		case 1:  // do not fight
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","071","072","073",0);
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","075","076","077",0);
               	Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","080","081","082",0);
                  player.mission_fight++;
            		break;
            	case 2:  // tatoo
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","085","086","087","088");
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","090",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","092","093","094",0);
                  player.mission_fight--;
              		break;

            }
         	player.scn_thugs++;
      		break;
      	case 2:
         	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","097","098",0,0);
         	switch(option){
         		case 1:  // do not fight
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","100","101","102",0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","105","106",0,0);
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","110","111","112",0);
                  player.mission_fight++;
            		break;
            	case 2:  // u do not know how to even fight
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","115","116","117",0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","120","121",0,0);
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","125","126","127",0);
                  player.mission_fight--;
              		break;
            }
         	player.scn_thugs++;
      		break;
         case 3:
				option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","130","131",0,0);
         	switch(option){
         		case 1:  // leave it now
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","135","136","137","138");
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","140","141",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","143","144",0,0);
                  player.mission_fight++;
            		break;
            	case 2:  // fight like cows
               	Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","146","147","148","149");
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1THUG.TXT","151","152",0,0);
                  player.mission_fight--;
              		break;
            }
         	player.scn_thugs++;
      		break;
         case 4:
         	player.mission_fight = 5;
         	end_conversation = 1;
            break;

      }

      switch(player.mission_fight){
      	case 1: // they hit you
            Fade_out();
            LoadImage("IMAGES3.DAT","fight_1.pcx",2); // Load fight image 1
            Update(0);
            Fade_in();
            Delay(100);
            player.mission_fight = 2;
            end_conversation = 1;
         	break;
         case 2: // end of fight bad
            Fade_out();
            LoadImage("IMAGES3.DAT","fight_2.pcx",2); // Load fight image 2
            Update(0);
            Fade_in();
         	break;
         case 3: // ...
         	Fade_out();
            LoadImage("IMAGES3.DAT","fight_3.pcx",2); // Load fight image 3
            Update(0);
            Fade_in();
         	break;
         case 4: // ....
         	Fade_out();
            LoadImage("IMAGES3.DAT","fight_4.pcx",2); // Load fight image 4
            Update(0);
            Fade_in();
         	break;
         case 5: // end of fight good
         	Fade_out();
            LoadImage("IMAGES3.DAT","fight_5.pcx",2); // Load fight image 5
            Update(0);
            Fade_in();

            Delay(100);

            player.mission_fight = 3;
      		end_conversation = 1;

         	break;
         default:
         	break;
      }
   }
}

/////////////////////////////////////////////////////////
// Thugs
/////////////////////////////////////////////////////////
void far Thugs(void){
	byte option = 1;
   byte end_conversation = 0;
	switch(player.day){
   	case 4:    //////////////////////////// day 4 //////////////////////////////
         switch(player.scn_thugs){
         	case 0:  // assault on floor 1
               GoToThugs_D4();
				 	player.ext2_hotspot_mask[2] = 1; // Enable hotspot of thugs on ext2
            	break;
            case 1:  // sneak
            	Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","058","059","060",0);
               Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","048",0,0,0);
               Speech("SPRFACE1.DAT","jonf.pcx","D4_STR.DAT","D4THUG.TXT","049",0,0,0);
               break;
            case 2:  // to smoke
               GoToThugs_Ext2();
               player.scn_thugs++;
               GoToExt2(824, 396);
               break;
            case 3:
            	Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","095","096","097",0);
               Speech("SPRFACE1.DAT","erikf.pcx","D4_STR.DAT","D4THUG.TXT","100",0,0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","102","103","104","105");
               player.scn_thugs++;
               break;
            case 4:
             	Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","110","111","112",0);
               player.scn_thugs++;
               break;
         	case 99:
             	Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","120","121","122",0);
               Speech("SPRFACE1.DAT","jonf.pcx","D4_STR.DAT","D4THUG.TXT","125",0,0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D4_STR.DAT","D4THUG.TXT","127","128","129","130");
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4THUG.TXT","134","135",0,0);
               break;
            default:
            	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4THUG.TXT","115","116",0,0);
               break;
         }
      	break;
      case 3:   //////////////////////////// day 3 //////////////////////////////
      	switch(player.scn_thugs){
         	case 0: //first time speak
            	panelScrolling = 0;
               showPanel = 0;
               Update(0);

               // Load image
               SetLoadingInterrupt();   // Start loading animation

               LoadImage("IMAGES2.DAT","thugs3.pcx",2); // Load menu background image to non visible page

               ResetLoadingInterrupt();   // Stop loading animation

               SetPage(2);
               Update(0);

               Fade_in();

            	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","001",0,0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","005","006",0,0);
               Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","007",0,0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","009",0,0,0);
               end_conversation == 0;
               while(end_conversation == 0){
               	if((player.mission_doll == 0)&&(player.item_keys == 0)){option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","012","013","014",0); }
               	else if((player.mission_doll == 0)&&(player.item_keys == 1)){option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","012","013","014","015"); }
               	else if((player.mission_doll == 1)&&(player.item_keys == 1)){option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","012","013","014","016"); }
               	else{option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","012","013","014",0); }
               	switch(option){
               		case 1: // what are you doing?
                  		Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","017","018","019",0);
                     	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","021","022",0,0);
                     	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","025","026",0,0);
                     	switch(option){
                     	case 1: // no, even if i have
                        	Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","028",0,0,0);
                           Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","029",0,0,0);
                           break;
                        case 2: // no money
                        	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","031","032",0,0);
                           Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","033","034",0,0);
                           Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","036","037",0,0);
                           break;
                     }
                     break;
                  case 2: // what are you hiddin?
               		Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","040","041","042","043");
                     Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","045",0,0,0);
                     Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","047","048","049",0);
                     Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","050","051","052","053");
                     Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","125","126","127",0);
                     option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","090","091","092",0);
                     switch(option){
                     	case 1: // LET ME TRY

                           Fade_out();
         						LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
         						Fade_in();
                        	SetNewTime(time_seconds-30);
                           if(player.popular<18){UpdatePopularity(1);}
                           if(player.good>2){UpdateGoodness(-1);}
         						Delay(100);
         						Fade_out();
         						LoadImage("IMAGES2.DAT","thugs3.pcx",2); // Load menu background image to non visible page
        	 						Fade_in();

                        	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","055",0,0,0);
                           Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","056",0,0,0);
                           Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","057","058","059",0);
                           Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","060","061",0,0);
                           Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","064","065",0,0);
                           Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","067","068","069","070");
                           end_conversation = 1;
                           player.scn_thugs = 1;
                           break;
                        case 2: // go away
                        	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","130","131",0,0);
                           Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","135","136",0,0);
                           Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","138",0,0,0);
                           Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","140","141","142","143");
                           if(player.good<18){UpdateGoodness(1);}
                           end_conversation = 1;
                           player.scn_thugs = 3;
                           break;
                        case 3: // GONNA TELL
                        	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","075","076","077","078");
                           Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","080",0,0,0);
                           Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","083","084",0,0);
                           if(player.popular>0){UpdatePopularity(-1);}
                           if(player.good<20){UpdateGoodness(1);}
                           end_conversation = 1;
                           player.scn_thugs = 2;
                           break;
                     }
                     break;
                  case 3: // just walking
                  	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","086",0,0,0);
                     Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","087","088",0,0);
                     end_conversation = 1;
                     break;
                  case 4: // keys
                  	if(player.good<20){UpdateGoodness(1);}
                  	Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
                     Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","113","114",0,0);
                     Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","116",0,0,0);
                     Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","118",0,0,0);
                     ResetItem(1,16);
                     player.item_keys = 0;
                     player.scn_main = 1;
                     // ask about keys
                     if(player.mission_doll == 1){
                     	player.mission_doll = 2;
                     }
                     break;
               	}
           	 	}
            	GoToFloor1(355, 155);
         		break;
         	case 1: // second time speak if help thugs
         		if((player.mission_doll == 0)&&(player.item_keys == 1)){
            		if(player.good<20){UpdateGoodness(1);}
            		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","015",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
               	ResetItem(1,16);
               	player.item_keys = 0;
               	player.scn_main = 1;
            	}
         		if(player.mission_doll == 1){
            		if(player.good<20){UpdateGoodness(1);}
            		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","016",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
               	ResetItem(1,16);
               	player.item_keys = 0;
               	player.mission_doll = 2;
               	player.scn_main = 1;
            	}
            	Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","095",0,0,0);
            	Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","096",0,0,0);
            	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","097","098","099",0);
            	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","067","068","069","070");
            	break;
         	case 2: // second time speak if do not help thugs
         		if((player.mission_doll == 0)&&(player.item_keys == 1)){
            		if(player.good<20){UpdateGoodness(1);}
            		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","015",0,0,0);
            		Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
               	ResetItem(1,16);
               	player.item_keys = 0;
               	player.scn_main = 1;
            	}
            	if(player.mission_doll == 1){
            		if(player.good<20){UpdateGoodness(1);}
            		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","016",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
               	ResetItem(1,16);
               	player.item_keys = 0;
               	player.mission_doll = 2;
               	player.scn_main = 1;
            	}
            	Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","105","106",0,0);
            	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","108",0,0,0);
            	break;
         	case 3: // second time speak if do not help thugs
         		if((player.mission_doll == 0)&&(player.item_keys == 1)){
            		if(player.good<20){UpdateGoodness(1);}
            		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","015",0,0,0);
            		Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
               	ResetItem(1,16);
               	player.item_keys = 0;
               	player.scn_main = 1;
            	}
            	if(player.mission_doll == 1){
            		if(player.good<20){UpdateGoodness(1);}
            		Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","016",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","110","111",0,0);
               	ResetItem(1,16);
               	player.item_keys = 0;
               	player.mission_doll = 2;
               	player.scn_main = 1;
            	}
            	Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","105","107",0,0);
            	Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","109",0,0,0);
            	break;
         	case 99:
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","150","151","152","153");
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","155","156","157",0);
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3THUG.TXT","160","161","162",0);
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","165","166","167",0);
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","169","170","171",0);
               Speech("SPRFACE1.DAT","erikf.pcx","D3_STR.DAT","D3THUG.TXT","174",0,0,0);
               Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","176",0,0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","178","179","180",0);
               Speech("SPRFACE1.DAT","jonf.pcx","D3_STR.DAT","D3THUG.TXT","182","183","184",0);
               Speech("SPRFACE1.DAT","tonif.pcx","D3_STR.DAT","D3THUG.TXT","186",0,0,0);
            	break;
            default:
            	break;
        	}
     	 	break;
      case 2: //////////////////////////// day 2 //////////////////////////////
         switch(player.scn_thugs){
        		case 0: //////////////// scene 0 :  first time speak ////////////////
      			panelScrolling = 0;
         		showPanel = 0;
         		Update(0);

         		// Load image
         		SetLoadingInterrupt();   // Start loading animation
        		 	LoadImage("IMAGES2.DAT","thugs2.pcx",2); // Load menu background image to non visible page
         		ResetLoadingInterrupt();   // Stop loading animation

         		SetPage(2);
         		Update(0);

         		Fade_in();

         		Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","001","002",0,0);
               end_conversation = 0;
               while(!end_conversation){
         			if(player.mission_bag == 1){option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","005","006","007","008"); }
         			else{option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","005","006","007",0); }
         			switch(option){
         				case 1: // just walk
            				Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","010","011",0,0);
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","014",0,0,0);
               			Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","017","018","019",0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","022","023","024",0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","026","027","028",0);
            				break;
            			case 2: // your mother
            				Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","017","018","019",0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","022","023","024",0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","026","027","028",0);
            				break;
            			case 3: // grafiti
                     	Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","030","031","032","033");
                  		option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","035","036","037",0);
                  		switch(option){
                  			case 1:  // paint with them
                           	Fade_out();
         							LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
         							Fade_in();

                             	if(player.popular<20){UpdatePopularity(1);}
                              if(player.popular<20){UpdatePopularity(1);}
		                        if(player.good>0){UpdateGoodness(-1);}

                        		SetNewTime(time_seconds-30);

                        		Delay(100);
         							Fade_out();
         							LoadImage("IMAGES2.DAT","thugs2.pcx",2); // Load menu background image to non visible page
        	 							Fade_in();

                     			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","085",0,0,0);
                        		Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","088","089","090",0);

                              GoToExt2(844, 396);

                        		// janitor appears
                        		LoadSprite("SPRCHR2.DAT","conser.pcx",15, 32); //Load sprites to one of the fixed structs
      								SetSpriteAnimation(15,0,6,12,CharacterAnimation2);
      								InitSprite(15,708,382);
                        		Update(0);

                        		Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2THUG.TXT","130","131","132",0);
                        		Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","135",0,0,0);
                              Speech("SPRFACE2.DAT","conserf.pcx","D2_STR.DAT","D2THUG.TXT","138","139","140",0);
                        		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","142",0,0,0);

                        		HideSprite(15);

                              player.scn_thugs = 1;
                              end_conversation = 1;
                     			break;
                     		case 2:   // do not paint
                     			Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","100","101",0,0);
                        		Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","105",0,0,0);
                        		if(player.good<18){UpdateGoodness(1);}
                        		end_conversation = 1;
                              player.scn_thugs = 2;
                              GoToExt2(844, 396);
                     			break;
                     		case 3: //tell
                        		Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","125","126",0,0);
                        		if(player.popular>0){UpdatePopularity(-1);}
                        		if(player.good<18){UpdateGoodness(1);}
                        		player.scn_thugs = 3;
                              end_conversation = 1;
                              GoToExt2(844, 396);
                     			break;
                  		}
                        break;
                     case 4: // bag?
                     	Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","040","041",0,0);
               			Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","043",0,0,0);
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","045","046","047",0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","050","051","052",0);
               			Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","054",0,0,0);
               			Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","056",0,0,0);
               			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","060","061",0,0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","064","065",0,0);
               			Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","067",0,0,0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","069","070",0,0);
               			Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","073","074",0,0);
               			Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","075",0,0,0);
            				break;
                  }
               }
               break;
            case 1:
               Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","110","111",0,0);
               if(player.mission_bag == 1){
               	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","008",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","040","041",0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","043",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","045","046","047",0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","050","051","052",0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","054",0,0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","056",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","060","061",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","064","065",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","067",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","069","070",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","073","074",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","075",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","077","078",0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","080",0,0,0);
                  SetSpriteAnimation(player.spriteNum,0,6,8,PlayerAnimation);   // Stand up player
                  Update(0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","082","083",0,0);
         		}
               break;
            case 2:
            	Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","115","116",0,0);
               Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","118","119",0,0);
               Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","122",0,0,0);
               if(player.mission_bag == 1){
               	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","008",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","040","041",0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","043",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","045","046","047",0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","050","051","052",0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","054",0,0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","056",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","060","061",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","064","065",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","067",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","069","070",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","073","074",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","075",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","077","078",0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","080",0,0,0);
                  SetSpriteAnimation(player.spriteNum,0,6,8,PlayerAnimation);   // Stand up player
                  Update(0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","082","083",0,0);
         		}
            	break;
            case 3:
            	Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","144",0,0,0);
               if(player.mission_bag == 1){
               	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","008",0,0,0);
               	Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","040","041",0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","043",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","045","046","047",0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","050","051","052",0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","054",0,0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","056",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","060","061",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","064","065",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","067",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","069","070",0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","073","074",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","075",0,0,0);
                  Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","077","078",0,0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","080",0,0,0);
                  SetSpriteAnimation(player.spriteNum,0,6,8,PlayerAnimation);   // Stand up player
                  Update(0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2THUG.TXT","082","083",0,0);
         		}
               break;
         	case 99:
               Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","146","147","148",0);
               Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","150",0,0,0);
               Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","152","153",0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D2_STR.DAT","D2THUG.TXT","155","156","157","158");
               Speech("SPRFACE1.DAT","jonf.pcx","D2_STR.DAT","D2THUG.TXT","160",0,0,0);
               Speech("SPRFACE1.DAT","erikf.pcx","D2_STR.DAT","D2THUG.TXT","162","163",0,0);
            	break;
            default:
            	break;
         }
      	break;
      case 1: //////////////////////////// day 1 //////////////////////////////
      	switch(player.scn_thugs){
         	case 0:
               GoToFight();
               if(player.mission_fight == 2){ // fight stopped
               	if(player.popular<18){UpdatePopularity(1);}
               	if(player.good<18){UpdateGoodness(1);}
                  SetNewTime(time_seconds-30);
               	GoToFloor1(426,356);

               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","155","156","157",0);
               	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","160","161","162",0);
               } else {
                  if(player.popular>2){UpdatePopularity(-1);}
               	GoToExt2(254,316);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","163","164",0,0);
                  player.mission_fight = 3;
               }
               player.floor1_hotspot_mask[16] = 1;
               player.ext2_hotspot_mask[8] = 1;
               player.ext2_hotspot_mask[9] = 1;
               player.ext2_hotspot_mask[10] = 0;
               player.ext2_hotspot_mask[11] = 0;
               player.floor1_event_mask[5] = 1;
               player.floor1_event_mask[10] = 0;
               player.scn_thugs = 1;
               player.scn_nerds = 1;
               player.scn_janitor = 1;
               player.scn_main = 1;
               break;
            case 1:
               if(player.mission_fight == 2){
               	Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","035",0,0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","036",0,0,0);
               }
               if(player.mission_fight == 3){
                  Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","025","026",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","027","028",0,0);
             	}
               if(player.mission_band == 1){
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","170","171","172","173");
                  Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","176","177","178",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","180","181","182",0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","185","186","187",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","190",0,0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","193","194","195",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1THUG.TXT","197","198","199","200");
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","202","203","204",0);
                  Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","206","207",0,0);
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","209",0,0,0);
                 	player.scn_thugs=2;
               }
               break;
            case 2:
               Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","211",0,0,0);
               Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","212",0,0,0);
               Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1THUG.TXT","213","214",0,0);
            	break;
            case 99:
               Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","216","217","218","219");
               Speech("SPRFACE1.DAT","erikf.pcx","D1_STR.DAT","D1THUG.TXT","220",0,0,0);
               Speech("SPRFACE1.DAT","tonif.pcx","D1_STR.DAT","D1THUG.TXT","222","223","224",0);
            	break;
         }
         break;
   }
}


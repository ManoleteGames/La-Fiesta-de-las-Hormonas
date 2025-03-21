 /***********************
*  DAY 10 THE EXAM THEFT
************************/

#include "source\engine\engine.h"
/////////////////////////////////////////////////////////
// Go to encounter with nerds
/////////////////////////////////////////////////////////
void near GoToNerds_D4(void){
	byte option;

	SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAGES.DAT","frikis.pcx",2); // Load menu background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","001","002","003",0);
   Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","005","006","007","008");
   Speech("SPRFACE1.DAT","alainf.pcx","D4_STR.DAT","D4NERD.TXT","010","011","012","013");
   Speech("SPRFACE1.DAT","davidf.pcx","D4_STR.DAT","D4NERD.TXT","017","018","019","020");
   Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","021","022",0,0);
   Speech("SPRFACE1.DAT","alainf.pcx","D4_STR.DAT","D4NERD.TXT","025","026","027","028");
   Speech("SPRFACE1.DAT","davidf.pcx","D4_STR.DAT","D4NERD.TXT","031","032","033",0);
   Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","035","036","037",0);
   Speech("SPRFACE1.DAT","davidf.pcx","D4_STR.DAT","D4NERD.TXT","040","041","042","043");
   Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","045","046","047",0);
   Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","050","051",0,0);
   Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","055","056",0,0);

   option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","058","059",0,0);
   switch(option){
   	case 1: // stay playing
      	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","062",0,0,0);
         Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","065","066","067",0);
         Fade_out();
         LoadImage("IMAGES2.DAT","later.pcx",1);
         SetPage(1);
         Fade_in();
         if(player.popular<18){UpdatePopularity(1);}
         SetNewTime(time_seconds-30);
         Delay(100);
         Fade_out();
         SetPage(2);
         Fade_in();

         Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","070","071","072",0);
         Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","075","076",0,0);
         Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","077","078","079",0);
         Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","080",0,0,0);

         break;
      case 2: // go away
      	Speech("SPRFACE1.DAT","alainf.pcx","D4_STR.DAT","D4NERD.TXT","115",0,0,0);
         break;
   }
}

/////////////////////////////////////////////////////////
// Nerds
/////////////////////////////////////////////////////////
void far Nerds(void){
	byte option = 1;
   byte end_conversation = 0;
	switch(player.day){
   	case 4:  //////////////////////////// day 4 ///////////////////////////
      	switch(player.scn_nerds){
         	case 0: //first time speak
            	GoToNerds_D4();
   				GoToFloor1(355, 155);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","124","125","126","127");
               player.scn_nerds++;
               player.floor1_event_mask[9] = 1; // Enable event. thugs assault
               break;
            case 1: // second time speak
            	Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","105","106","107",0);
               player.scn_nerds++;
               break;
            case 2:
         		Speech("SPRFACE1.DAT","davidf.pcx","D4_STR.DAT","D4NERD.TXT","082","083","084",0);
               player.scn_nerds++;
               break;
            case 3:
            	Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","086","087","088","089");
               Speech("SPRFACE1.DAT","xavif.pcx","D4_STR.DAT","D4NERD.TXT","091","092",0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","094","095",0,0);
               player.scn_nerds++;
               break;
            case 4:
            	Speech("SPRFACE1.DAT","alainf.pcx","D4_STR.DAT","D4NERD.TXT","097","098","099","100");
               player.scn_nerds++;
               break;
            case 99:
               Speech("SPRFACE1.DAT","alainf.pcx","D4_STR.DAT","D4NERD.TXT","130","131",0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D4_STR.DAT","D4NERD.TXT","135","136","137",0);
               Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","140","141","142","143");
            	break;
            default:
         		Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4NERD.TXT","124","125","126","127");
               break;
         }
      	break;
      case 3:  //////////////////////////// day 3 ///////////////////////////
      	switch(player.scn_nerds){
         	case 0:
            	SetLoadingInterrupt();   // Start loading animation

   				LoadImage("IMAGES2.DAT","nerds2.pcx",2); // Load menu background image to non visible page

   				ResetLoadingInterrupt();   // Stop loading animation
               SetPage(2);
				   Update(0);

   				Fade_in();


            	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","001",0,0,0);
            	Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","005","006",0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","007","008",0,0);
               Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","110","111","112",0);
               option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","010","011",0,0);
               switch(option){
               	case 1: // play
                  	Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","015","016",0,0);

                     Fade_out();
         				LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
         				Fade_in();
         				if(player.popular<20){UpdatePopularity(1);}
                     SetNewTime(time_seconds-30);
                     Delay(100);
                     Fade_out();
         				LoadImage("IMAGES2.DAT","nerds2.pcx",2); // Load menu background image to non visible page
         				Fade_in();

                     Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","115","116",0,0);
                     Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","018","019","020",0);
                     Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","022","023","024",0);
                     Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","026","027","028",0);
                     Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","030","031",0,0);
                     break;
                  case 2: // not play
                  	Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","040",0,0,0);
                     option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","042","043",0,0);
                     switch(option){
                     	case 1: // do not like
                        	if(player.popular>0){UpdatePopularity(-1);}
                     		Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","045","046","047",0);
                           Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","048",0,0,0);
                        	break;
                        case 2: // just books
                           if(player.popular<20){UpdatePopularity(+1);}
                        	Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","105","106","107",0);
                           break;
                     }
                  	break;
               }
               player.scn_nerds++;
               GoToExt2(274,356);
               break;
            case 1:
            	Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","070",0,0,0);
               player.scn_nerds++;
               break;
            case 2:
            	Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","075","076",0,0);
               player.scn_nerds++;
               break;
            case 99:
            	Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","120","121","122",0);
               Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","124",0,0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","127",0,0,0);
               Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","130","131",0,0);
               Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","133",0,0,0);
               Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","135",0,0,0);
            	break;
            default:
            	Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","065","066","067",0);
               break;
         }

         if((player.mission_doll > 0)&&(player.scn_nerds < 10)){
         	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","035","036",0,0);
            switch(option){
            	case 1: // doll mission
                 	if(player.good>0){UpdateGoodness(-1);}
                  if(player.popular<20){UpdatePopularity(1);}
                  Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","080","081","082",0);
                  Speech("SPRFACE1.DAT","antof.pcx","D3_STR.DAT","D3NERD.TXT","085","086","087",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","090","091","092","093");
                  Speech("SPRFACE1.DAT","alainf.pcx","D3_STR.DAT","D3NERD.TXT","095",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","097","098",0,0);
                  Speech("SPRFACE1.DAT","xavif.pcx","D3_STR.DAT","D3NERD.TXT","100",0,0,0);
                  Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","101",0,0,0);
               	break;
               case 2: // bye
               	Speech("SPRFACE1.DAT","davidf.pcx","D3_STR.DAT","D3NERD.TXT","050","051","052",0);
                  Speech("SPRFACE1.DAT","alainf.pcx","D3_STR.DAT","D3NERD.TXT","055","056","057",0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3NERD.TXT","060","061",0,0);
                  break;
            }
            player.scn_nerds = 10;
         }
      	break;
      case 2: //////////////////////////// day 2 ///////////////////////////
      	switch(player.scn_nerds){
         	case 0:
         		SetLoadingInterrupt();   // Start loading animation
            	LoadImage("IMAGES2.DAT","nerds3.pcx",2); // Load menu background image to non visible page
            	ResetLoadingInterrupt();   // Stop loading animation
            	SetPage(2);
            	Update(0);

            	Fade_in();

      			Speech("SPRFACE1.DAT","davidf.pcx","D2_STR.DAT","D2NERD.TXT","001","002","003","004");
         		Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","005","006",0,0);
      			Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","008",0,0,0);
         		Speech("SPRFACE1.DAT","xavif.pcx","D2_STR.DAT","D2NERD.TXT","010","011",0,0);
         		Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","014","015","016",0);
         		Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","017","018","019",0);
         		Speech("SPRFACE1.DAT","alainf.pcx","D2_STR.DAT","D2NERD.TXT","020","021",0,"022");
         		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","024",0,0,0);
         		Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","026","027","028",0);
         		Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","030","031",0,0);
         		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","032",0,0,0);
         		Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","033","034","035",0);
            	option = SpeechSelection(3,"SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","037","038","039",0);
            	switch(option){
         			case 1: // help
                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","095","096",0,0);
                  	Fade_out();
                  	LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
                  	Fade_in();
                  	if(player.popular<18){UpdatePopularity(1);}
                     SetNewTime(time_seconds-30);
                  	
                  	Delay(100);
                  	Fade_out();
                  	LoadImage("IMAGES2.DAT","nerds3.pcx",2); // Load menu background image to non visible page
                  	Fade_in();

               		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","040","041","042",0);
                  	Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","045","046","047",0);
               		break;
            		case 2: // not help
               		Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","052","053","054",0);
                  	if(player.popular>2){UpdatePopularity(-1);}
              	 		break;
               	case 3: // write a letter
                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","100","101","102",0);
                  	Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","105",0,0,0);
                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","110","111","112",0);
                  	Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","115",0,0,0);
                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","117",0,"118",0);
                  	Fade_out();
                  	LoadImage("IMAGES2.DAT","later.pcx",2); // Load menu background image to non visible page
                  	Fade_in();
                  	if(player.popular<18){UpdatePopularity(1);}
                     if(player.popular<18){UpdatePopularity(1);}
                     SetNewTime(time_seconds-30);
                  	
                  	Delay(100);
                  	Fade_out();
                  	LoadImage("IMAGES2.DAT","nerds3.pcx",2); // Load menu background image to non visible page
                  	Fade_in();

                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","120","121",0,0);
                  	Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","123","124","125",0);
                  	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","127",0,"128",0);
               		break;
            	}
            	player.scn_nerds++;
            	GoToFloor2(155, 200);
               break;
         	case 1:
              	Speech("SPRFACE1.DAT","davidf.pcx","D2_STR.DAT","D2NERD.TXT","080","081",0,0);
              	Speech("SPRFACE1.DAT","xavif.pcx","D2_STR.DAT","D2NERD.TXT","085","086",0,0);
             	Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","090",0,0,0);
               break;
         	case 99:
               Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","130","131","132","133");
               Speech("SPRFACE1.DAT","alainf.pcx","D2_STR.DAT","D2NERD.TXT","135","136","137",0);
               Speech("SPRFACE1.DAT","alainf.pcx","D2_STR.DAT","D2NERD.TXT","139","140",0,0);
            	break;
         }

         // bag mission
         if(player.mission_bag == 1){
          	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","057","058",0,0);
            Speech("SPRFACE1.DAT","xavif.pcx","D2_STR.DAT","D2NERD.TXT","061","062","063","064");
            Speech("SPRFACE1.DAT","antof.pcx","D2_STR.DAT","D2NERD.TXT","066","067",0,0);
            Speech("SPRFACE1.DAT","alainf.pcx","D2_STR.DAT","D2NERD.TXT","069",0,0,0);
            Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2NERD.TXT","071","072","073",0);
       	}
      	break;
      case 1:  //////////////////////////// day 1 ///////////////////////////
        	if(player.floor == 1){ // hall
      		switch(player.mission_fight){
         		case 0: // in the hall, first time
                  Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","002",0,0,0);
         			Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","003",0,0,0);
                  Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","010",0,0,0);
                  Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","012","013",0,0);
                  end_conversation = 0;
                  while(end_conversation == 0){
                  	option = SpeechSelection(4,"SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","016","017","018","019");
            			switch(option){
         					case 1: // why?
                        	Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","025","026","027",0);
                           Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","030","031","032",0);
                           Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","034","035","036","037");
                           Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","040","041","042","043");
                           Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","045","046","047","048");
                           Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","050","051","052","053");
                           Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","055",0,0,0);
                        	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","058","059",0,0);
                        	break;
                        case 2: // why u here?
                           Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","062","063","064",0);
                           Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","067","068",0,0);
                           Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","070",0,0,0);
									break;
                        case 3: // stop it
                        	Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","073","074",0,0);
                        	break;
                        case 4: // bye
                        	Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","002",0,0,0);
         						Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","003",0,0,0);
                        	end_conversation = 1;
                        	break;
                  	}
                  }
            		player.mission_fight = 1;
               	break;
            	case 1: //
                  Speech("SPRFACE1.DAT","jonf.pcx","D1_STR.DAT","D1NERD.TXT","008",0,0,0);
                  Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","009",0,0,0);
             		break;
            }
         }
         if(player.floor == 4){ // ext2, after the fight
         	switch(player.scn_nerds){
            	case 0:
               	break;
            	case 1:
         			if(player.mission_fight == 3){
            			Speech("SPRFACE1.DAT","davidf.pcx","D1_STR.DAT","D1NERD.TXT","115","116",0,0);
               		Speech("SPRFACE1.DAT","alainf.pcx","D1_STR.DAT","D1NERD.TXT","118","119","120",0);
               		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","123",0,0,0);
            		}
            		if(player.mission_fight == 2){
                  	Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","125",0,0,0);
               		Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","128","129",0,0);
            		}
                  if(player.mission_band == 1){
                     Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","140","141",0,0);
                     Speech("SPRFACE1.DAT","davidf.pcx","D1_STR.DAT","D1NERD.TXT","143",0,0,0);
                     Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","146","147","148","149");
                     Speech("SPRFACE1.DAT","davidf.pcx","D1_STR.DAT","D1NERD.TXT","151",0,0,0);
                     Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","152","153","154",0);
                     Speech("SPRFACE1.DAT","alainf.pcx","D1_STR.DAT","D1NERD.TXT","155","156","157","158");
                     Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","161",0,0,0);
                     Speech("SPRFACE1.DAT","alainf.pcx","D1_STR.DAT","D1NERD.TXT","163","164",0,0);
                     Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1NERD.TXT","166","167","168",0);
                     Speech("SPRFACE1.DAT","alainf.pcx","D1_STR.DAT","D1NERD.TXT","170",0,0,0);
                 		player.scn_nerds=2;
               	}
                  break;
               case 2:
                  Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","173",0,0,0);
                  Speech("SPRFACE1.DAT","alainf.pcx","D1_STR.DAT","D1NERD.TXT","175",0,0,0);
                  Speech("SPRFACE1.DAT","antof.pcx","D1_STR.DAT","D1NERD.TXT","177","178","179",0);
                  Speech("SPRFACE1.DAT","alainf.pcx","D1_STR.DAT","D1NERD.TXT","180",0,0,0);
               	break;
               case 99:
                  Speech("SPRFACE1.DAT","xavif.pcx","D1_STR.DAT","D1NERD.TXT","132","133","134",0);
               	break;
            }
         }
			break;
   }
}



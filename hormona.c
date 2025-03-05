/***********************
*  LA FIESTA DE LAS HORMONAS
*  - Autor: jmartin
*  - Agradecimientos especiales a mills32 por su proyecto Little Game Engine,
*    el cual ha servido de base para este programa
************************/

#include "source\engine\engine.h"
#include "source\engine\keyb\keyb.h"

byte option = 1;
byte end_game = 0;
byte save_game = 0;
byte existingSaveGame = 0;
byte PlayerAnimation[] = {0,0,0,0,0,0,0,1,2,1,0,2,1,3,4,3,5,6,7,6,8,9,10,9,11,12,13,12,14};
byte PlayerFaceAnimation[] = {0,1,2};
byte EnterAnimation[] = {0,0,0,1};
byte JessyAnimation[] = {0,0,0,0,0,0,0,1,2,1,0,2,1,3,4,3,5,6,7,6,8,9,10,9,11,12,13,12,14};
byte BirdAnimation[] = {0,1,2,3,4,3,4,3,2,1,0,0,0,0,0};
byte DirectorAnimation[] = {0,1,0,1,0,0,2,2,3,3,4,0,0,0,1};
byte CharacterAnimation2[] = {0,0,0,1,0,0,0};
byte CharacterAnimation3[] = {0,0,0,1,2,0,0};

/////////////////////////////////////////////////////////
// Save game
/////////////////////////////////////////////////////////
void near SaveGame(void){
	FILE *savefile;
   int i;
   byte aux1 = 0;

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

   savefile = fopen("savegame.ini","w");
   fprintf(savefile,"#SAVEG\n");
   fprintf(savefile,"------\n");
   fprintf(savefile,"[1]INTEL =%03u\n",player.intell);
   fprintf(savefile,"[2]POPUL =%03u\n",player.popular);
	fprintf(savefile,"[3]GOOD  =%03u\n",player.good);
	fprintf(savefile,"[4]MONEY =%03u\n",player.money);
	fprintf(savefile,"[5]DAY   =%03u\n",player.day);
	fprintf(savefile,"[6]FLOOR =%03u\n",player.floor);
	fprintf(savefile,"[7]CHEAT =%03u\n",player.mission_cheat);
	fprintf(savefile,"[8]PARTY =%03u\n",player.mission_party);
	fprintf(savefile,"[9]DOLL  =%03u\n",player.mission_doll);
	fprintf(savefile,"[10]ARC  =%03u\n",player.mission_arcade);
   fprintf(savefile,"[11]BAG  =%03u\n",player.mission_bag);
   fprintf(savefile,"[12]FIGHT=%03u\n",player.mission_fight);
   fprintf(savefile,"[13]KEYS =%03u\n",player.mission_keys);
   fprintf(savefile,"[14]BAND =%03u\n",player.mission_band);
   fprintf(savefile,"[15]CHAIR=%03u\n",player.mission_chair);
   fprintf(savefile,"[16]SCNMA=%03u\n",player.scn_main);
   fprintf(savefile,"[17]SCNNE=%03u\n",player.scn_nerds);
   fprintf(savefile,"[18]SCNDI=%03u\n",player.scn_director);
   fprintf(savefile,"[19]SCNJA=%03u\n",player.scn_janitor);
   fprintf(savefile,"[20]SNCTH=%03u\n",player.scn_thugs);
   fprintf(savefile,"[21]SCNGI=%03u\n",player.scn_girls);
   fprintf(savefile,"[22]SCNJE=%03u\n",player.scn_jessy);
   fprintf(savefile,"[23]SCNSN=%03u\n",player.scn_sensei);
   fprintf(savefile,"[24]SCR01=%03u\n",player.score[1]);
   fprintf(savefile,"[25]SCR02=%03u\n",player.score[2]);
   fprintf(savefile,"[26]SCR03=%03u\n",player.score[3]);
   fprintf(savefile,"[27]SCR04=%03u\n",player.score[4]);
   fprintf(savefile,"[28]IEXAM=%03u\n",player.item_exams);
   fprintf(savefile,"[29]ICHAL=%03u\n",player.item_chalk);
   fprintf(savefile,"[30]IBAG =%03u\n",player.item_bag);
   fprintf(savefile,"[31]IKEYS=%03u\n",player.item_keys);
   fprintf(savefile,"[32]TIME =%03u\n",time_seconds);
   fprintf(savefile,"[33]POSX =%03u\n",sprite[player.spriteNum].pos_x);
   fprintf(savefile,"[34]POSY =%03u\n",sprite[player.spriteNum].pos_y);
   fprintf(savefile,"[35]VAR35=%03u\n",0);
   fprintf(savefile,"[36]VAR36=%03u\n",0);
   fprintf(savefile,"[37]VAR37=%03u\n",0);

   // ext 1 event mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_event_mask[i];
   }
   fprintf(savefile,"[38]E1EM1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_event_mask[i];
   }
   fprintf(savefile,"[39]E1EM2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_event_mask[i];
   }
   fprintf(savefile,"[40]E1EM3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_event_mask[i];
   }
   fprintf(savefile,"[41]E1EM4=%03u\n",aux1);

   // ext 2 event mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_event_mask[i];
   }
   fprintf(savefile,"[42]E2EM1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_event_mask[i];
   }
   fprintf(savefile,"[43]E2EM2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_event_mask[i];
   }
   fprintf(savefile,"[44]E2EM3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_event_mask[i];
   }
   fprintf(savefile,"[45]E2EM4=%03u\n",aux1);

   // floor 1 event mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_event_mask[i];
   }
   fprintf(savefile,"[46]F1EM1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_event_mask[i];
   }
   fprintf(savefile,"[47]F1EM2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_event_mask[i];
   }
   fprintf(savefile,"[48]F1EM3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_event_mask[i];
   }
   fprintf(savefile,"[49]F1EM4=%03u\n",aux1);

   // floor 2 event mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_event_mask[i];
   }
   fprintf(savefile,"[50]F2EM1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_event_mask[i];
   }
   fprintf(savefile,"[51]F2EM2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_event_mask[i];
   }
   fprintf(savefile,"[52]F2EM3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_event_mask[i];
   }
   fprintf(savefile,"[53]F2EM4=%03u\n",aux1);

   // gym event mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_event_mask[i];
   }
   fprintf(savefile,"[54]GYEM1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_event_mask[i];
   }
   fprintf(savefile,"[55]GYEM2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_event_mask[i];
   }
   fprintf(savefile,"[56]GYEM3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_event_mask[i];
   }
   fprintf(savefile,"[57]GYEM4=%03u\n",aux1);

   // ext 1 hotspot mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_hotspot_mask[i];
   }
   fprintf(savefile,"[58]E1HS1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_hotspot_mask[i];
   }
   fprintf(savefile,"[59]E1HS2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_hotspot_mask[i];
   }
   fprintf(savefile,"[60]E1HS3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext1_hotspot_mask[i];
   }
   fprintf(savefile,"[61]E1HS4=%03u\n",aux1);

   // ext 2 hotspot mask
   aux1 = 0;
   for(i = 7; i>=0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_hotspot_mask[i];
   }
   fprintf(savefile,"[62]E2HS1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>=8; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_hotspot_mask[i];
   }
   fprintf(savefile,"[63]E2HS2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_hotspot_mask[i];
   }
   fprintf(savefile,"[64]E2HS3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.ext2_hotspot_mask[i];
   }
   fprintf(savefile,"[65]E1HS4=%03u\n",aux1);

   // floor 1 hotspot mask
   aux1 = 0;
   for(i = 7; i>0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_hotspot_mask[i];
   }
   fprintf(savefile,"[66]F1HS1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>7; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_hotspot_mask[i];
   }
   fprintf(savefile,"[67]F1HS2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_hotspot_mask[i];
   }
   fprintf(savefile,"[68]F1HS3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor1_hotspot_mask[i];
   }
   fprintf(savefile,"[69]E1HS4=%03u\n",aux1);

   // floor 2 hotspot mask
   aux1 = 0;
   for(i = 7; i>0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_hotspot_mask[i];
   }
   fprintf(savefile,"[70]F2HS1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>7; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_hotspot_mask[i];
   }
   fprintf(savefile,"[71]F2HS2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_hotspot_mask[i];
   }
   fprintf(savefile,"[72]F2HS3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.floor2_hotspot_mask[i];
   }
   fprintf(savefile,"[73]E1HS4=%03u\n",aux1);

   // gym hotspot mask
   aux1 = 0;
   for(i = 7; i>0; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_hotspot_mask[i];
   }
   fprintf(savefile,"[74]GYHS1=%03u\n",aux1);

   aux1 = 0;
   for(i = 15; i>7; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_hotspot_mask[i];
   }
   fprintf(savefile,"[75]GYHS2=%03u\n",aux1);

   aux1 = 0;
   for(i = 23; i>=16; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_hotspot_mask[i];
   }
   fprintf(savefile,"[76]GYHS3=%03u\n",aux1);

   aux1 = 0;
   for(i = 31; i>=24; i--){
   	aux1 = (aux1 << 1);
      aux1 = aux1 | player.gym_hotspot_mask[i];
   }
   fprintf(savefile,"[77]GYHS4=%03u\n",aux1);

   fclose(savefile);

   existingSaveGame = 1;
}


/////////////////////////////////////////////////////////
// Logo function
// - Little sequence with logos and stuff
/////////////////////////////////////////////////////////
void near Logo(void){
	byte counter = 0;

	Fade_out();
   LoadImage("LOGO.DAT","LCONTEST.pcx",1); // Dos contest logo
   SetPage(1);
   Fade_in();

   Delay(200);
   LoadImage("LOGO.DAT","LDOSCLUB.pcx",2); // MS-DOS club logo

   Fade_out();
   SetPage(2);
   Fade_in();
   RotatePalette(48,83,98);
   LoadImage("LOGO.DAT","LMANOL.pcx",1); // Manolete logo

   Fade_out();
   SetPage(1);
   Fade_in();
   Delay(200);


   Fade_out();
   LoadImage("LOGO.DAT","oneman1.pcx",2);  // One man logo
   SetPage(2);
   Fade_in();
   Delay(200);

   LoadImage("LOGO.DAT","oneman2.pcx",1);  // One man logo
   SetPage(1);
   LoadImage("LOGO.DAT","oneman3.pcx",2);  // One man logo
   SetPage(2);
   Delay(20);
   SetPage(1);
   Delay(20);
   SetPage(2);
   Delay(20);
   SetPage(1);
   LoadImage("LOGO.DAT","oneman4.pcx",2);  // One man logo
   SetPage(2);
   LoadImage("LOGO.DAT","oneman5.pcx",1);  // One man logo
   SetPage(1);
   Delay(200);

   LoadImage("LOGO.DAT","warn.pcx",2);  // Warning
   Fade_out();
   SetPage(2);
   Fade_in();
   while(counter < 5){
   	RotatePalette(101,104,50);
      Delay(20);
      counter++;
   }

   Fade_out();
}

/////////////////////////////////////////////////////////
// Main menu
// - Shows a menu with 4 options
//	-- New game
// -- Continue game
// -- Options
// -- Quit game
/////////////////////////////////////////////////////////
void near Menu(void)
{
   word length;
   int menu_pos[5] = {92,100,108,116,124};
   int confirm_pos[3] = {92,108,116};
   byte MenuCursorAnimation[8] = {0,1,2,3,3,3,3,3};

   // Load animation
	SetLoadingInterrupt();   // Start loading animation

   // Load resources
   LoadImage("IMAGES.DAT","MENU.pcx",2); // Load menu background image to non visible page
   LoadFont("FONTS.DAT","FONT.bmp"); //Load font
   LoadSprite("SPRMISC.DAT","cursor.pcx",1,16); //Load sprites to one of the fixed structs
   InitSprite(1,110,menu_pos[option] + vga_page[2]);
   SetSpriteAnimation(1,0,7,6,MenuCursorAnimation);

   LoadMusic(2);

   ResetLoadingInterrupt();   // Stop loading animation

   PlayNonStopMusic();

   SetPage(2);

   // Draw menu options
   option = 1;
   Draw_EmptyBox(13,12,14,4);
   LoadText("GLB_STR.DAT","global.txt","001",string,&length);
   if(option == 1){PrintText(15,13,length,string,1);}
   else{PrintText(15,13,length,string,0);}
   if(existingSaveGame){
   	LoadText("GLB_STR.DAT","global.txt","002",string,&length);
   	if(option == 2){PrintText(15,14,length,string,1);}
   	else{PrintText(15,14,length,string,0);}
   }
   LoadText("GLB_STR.DAT","global.txt","003",string,&length);
   if(option == 3){PrintText(15,15,length,string,1);}
   else{PrintText(15,15,length,string,0);}
   LoadText("GLB_STR.DAT","global.txt","004",string,&length);
   if(option == 4){PrintText(15,16,length,string,1);}
   else{PrintText(15,16,length,string,0);}

   Fade_in();
   
   // Menu loop
   while( keys[K_ENTER] != 1 )
   {
      sprite[1].pos_y = menu_pos[option] + vga_page[2];

      if( fp_keys[K_UP] == 1) {
      	switch(option){
         	case 1: // Do nothing
            	break;
            case 2: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","002",string,&length);
				   PrintText(15,14,length,string,0);
	            option--; // Change option
              	PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","001",string,&length);
				   PrintText(15,13,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,0);
               PlaySound(1);
               if(existingSaveGame == 0){
               	option--; // Change option
               	option--; // Change option
                  LoadText("GLB_STR.DAT","global.txt","001",string,&length);
				   	PrintText(15,13,length,string,1);
               }
               else{
               	option--; // Change option
               	LoadText("GLB_STR.DAT","global.txt","002",string,&length);
               	PrintText(15,14,length,string,1);
               }
				  	break;
            case 4: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","004",string,&length);
				   PrintText(15,16,length,string,0);
               option--; // Change option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,1);
				  	break;
         }
      }
      if( fp_keys[K_DOWN] == 1){
      	switch(option){
         	case 1: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","001",string,&length);
				   PrintText(15,13,length,string,0);
               PlaySound(1);
               if(existingSaveGame == 0){
               	option++;
                  option++;
               	LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   	PrintText(15,15,length,string,1);
               }
               else{
               	option++;
               	LoadText("GLB_STR.DAT","global.txt","002",string,&length);
               	PrintText(15,14,length,string,1);
               }
            	break;
            case 2: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","002",string,&length);
				   PrintText(15,14,length,string,0);
	            option++; // Change option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
               LoadText("GLB_STR.DAT","global.txt","003",string,&length);
				   PrintText(15,15,length,string,0);
               option++; // Change option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","004",string,&length);
				   PrintText(15,16,length,string,1);
				  	break;
            case 4: // Do nothing
				  	break;
         }
      }

     	if(option < 1){ option = 1;}
      if(option > 4){ option = 4;}

      Update(0);
   }

   // Selection sound
   PlaySound(1);

   // wait until enter key is released
   while( keys[K_ENTER] == 1 )
   {
   	// do nothig..
   }
   Fade_out();
}

/////////////////////////////////////////////////////////
// Main loop
// - Starts the party...
/////////////////////////////////////////////////////////
void near MainLoop(void) {
	while(end_game == 0){
   	Events(player.event);
      if(keys[K_ENTER] == 1){ Hotspots(player.hotspot); }
      // Main loop
      MovePlayer();
      Update(1);

      if(keys[K_ESC]== 1){
      	if((map_loaded == 1) && (speech_active == 0)){
          	option = SpeechSelection(2,"SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","GLOBAL.TXT","053","054",0,0);
   			switch(option){
     				case 1: // YES
         			SaveGame();
      				break;
      			case 2: // NO
         			break;
            }
         }
         UnloadMusic();
         end_game = 1;
      }
   }

   while( keys[K_ESC] == 1 )
   {
   	// Wait until esc key is releassed
   }

   end_game = 0;
}


/////////////////////////////////////////////////////////
// Init game
// - Initialize all variables for a new game
/////////////////////////////////////////////////////////
void near Init(void){
	// Initialize player status
   player.day = 4;

   //////////debug///////
   //player.day = 2;
   //player.mission_party = 1;
   //player.item_exams = 1;
   /////////////////////

   // Starting player status
   player.intell = 10;
   player.popular = 10;
   player.good = 10;
   player.money = 0;

   player.score[1] = 0;
   player.score[2] = 0;
	player.score[3] = 0;
	player.score[4] = 0;
	player.score[5] = 0;
	player.score[6] = 0;
	player.score[7] = 0;
	player.score[8] = 0;
	player.score[9] = 0;
	player.score[10] = 0;

   LoadFont("FONTS.DAT","FONT.bmp"); //Load text font
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   PanelUpdate();

   InitDay();
   GoToFloor1(100, 185);
}

/////////////////////////////////////////////////////////
// New game
// - Initialize game and call main loop function
/////////////////////////////////////////////////////////
void near NewGame(void) {

   UnloadMusic();
	Init();
   LoadMusic(1);
   PlayNonStopMusic();

   MainLoop();
   if(save_game == 1){SaveGame();}

   UnloadMusic();
}

/////////////////////////////////////////////////////////
// Load game
/////////////////////////////////////////////////////////
void near LoadGame(void){
	FILE *savefile;
   byte buffer[1200];
   int spare;
   int i;
   byte aux1 = 0;
   byte aux2 = 0;
   byte aux3 = 0;
   byte aux4 = 0;

   savefile = fopen("savegame.ini","rb+");
   fread(buffer,1,1200,savefile);
   fclose(savefile);

	player.intell	= (buffer[26]-48)*100 + (buffer[27]-48)*10 + (buffer[28]-48);
	player.popular = (buffer[41]-48)*100 + (buffer[42]-48)*10 + (buffer[43]-48);
   player.good 	= (buffer[56]-48)*100 + (buffer[57]-48)*10 + (buffer[58]-48);
   player.money 	= (buffer[71]-48)*100 + (buffer[72]-48)*10 + (buffer[73]-48);
   player.day 		= (buffer[86]-48)*100 + (buffer[87]-48)*10 + (buffer[88]-48);
   player.floor 	= (buffer[101]-48)*100 + (buffer[102]-48)*10 + (buffer[103]-48);
   player.mission_cheat = (buffer[116]-48)*100 + (buffer[117]-48)*10 + (buffer[118]-48);
   player.mission_party  = (buffer[131]-48)*100 + (buffer[132]-48)*10 + (buffer[133]-48);
   player.mission_doll   = (buffer[146]-48)*100 + (buffer[147]-48)*10 + (buffer[148]-48);
   player.mission_arcade = (buffer[161]-48)*100 + (buffer[162]-48)*10 + (buffer[163]-48);
   player.mission_bag    = (buffer[176]-48)*100 + (buffer[177]-48)*10 + (buffer[178]-48);
   player.mission_fight  = (buffer[191]-48)*100 + (buffer[192]-48)*10 + (buffer[193]-48);
   player.mission_keys   = (buffer[206]-48)*100 + (buffer[207]-48)*10 + (buffer[208]-48);
   player.mission_band   = (buffer[221]-48)*100 + (buffer[222]-48)*10 + (buffer[223]-48);
   player.mission_chair  = (buffer[236]-48)*100 + (buffer[237]-48)*10 + (buffer[238]-48);
   player.scn_main	  = (buffer[251]-48)*100 + (buffer[252]-48)*10 + (buffer[253]-48);
   player.scn_nerds	  = (buffer[266]-48)*100 + (buffer[267]-48)*10 + (buffer[268]-48);
   player.scn_director = (buffer[281]-48)*100 + (buffer[282]-48)*10 + (buffer[283]-48);
   player.scn_janitor  = (buffer[296]-48)*100 + (buffer[297]-48)*10 + (buffer[298]-48);
   player.scn_thugs    = (buffer[311]-48)*100 + (buffer[312]-48)*10 + (buffer[313]-48);
   player.scn_girls	  = (buffer[326]-48)*100 + (buffer[327]-48)*10 + (buffer[328]-48);   //var 21
   player.scn_jessy	  = (buffer[341]-48)*100 + (buffer[342]-48)*10 + (buffer[343]-48);   //var 22
   player.scn_sensei	  = (buffer[356]-48)*100 + (buffer[357]-48)*10 + (buffer[358]-48);   //var 23
   player.score[1]	  = (buffer[371]-48)*100 + (buffer[372]-48)*10 + (buffer[373]-48);   //var 24
   player.score[2]	  = (buffer[386]-48)*100 + (buffer[387]-48)*10 + (buffer[388]-48);   //var 25
   player.score[3]	  = (buffer[401]-48)*100 + (buffer[402]-48)*10 + (buffer[403]-48);   //var 26
   player.score[4]	  = (buffer[416]-48)*100 + (buffer[417]-48)*10 + (buffer[418]-48);   //var 27
   player.item_exams	  = (buffer[431]-48)*100 + (buffer[432]-48)*10 + (buffer[433]-48);   //var 28
   player.item_chalk	  = (buffer[446]-48)*100 + (buffer[447]-48)*10 + (buffer[448]-48);   //var 29
   player.item_bag	  = (buffer[461]-48)*100 + (buffer[462]-48)*10 + (buffer[463]-48);   //var 30
   player.item_keys	  = (buffer[476]-48)*100 + (buffer[477]-48)*10 + (buffer[478]-48);   //var 31
   time_seconds		  = (buffer[491]-48)*100 + (buffer[492]-48)*10 + (buffer[493]-48);   //var 32
   sprite[player.spriteNum].pos_x = (buffer[506]-48)*100 + (buffer[507]-48)*10 + (buffer[508]-48);   //var 33
   sprite[player.spriteNum].pos_y = (buffer[521]-48)*100 + (buffer[522]-48)*10 + (buffer[523]-48);   //var 34
   spare					  = (buffer[536]-48)*100 + (buffer[537]-48)*10 + (buffer[538]-48);   //var 35
   spare					  = (buffer[551]-48)*100 + (buffer[552]-48)*10 + (buffer[553]-48);   //var 36
   spare					  = (buffer[566]-48)*100 + (buffer[567]-48)*10 + (buffer[568]-48);   //var 37

   // ext1 event mask
   aux1 = (buffer[581]-48)*100 + (buffer[582]-48)*10 + (buffer[583]-48);   //E1EM1 (var 38)
   aux2 = (buffer[596]-48)*100 + (buffer[597]-48)*10 + (buffer[598]-48);   //E1EM2 (var 39)
   aux3 = (buffer[611]-48)*100 + (buffer[612]-48)*10 + (buffer[613]-48);   //E1EM3 (var 40)
   aux4 = (buffer[626]-48)*100 + (buffer[627]-48)*10 + (buffer[628]-48);   //E1EM4 (var 41)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.ext1_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.ext1_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // ext2 event mask
   aux1 = (buffer[641]-48)*100 + (buffer[642]-48)*10 + (buffer[643]-48);   //E2EM1 (var 42)
   aux2 = (buffer[656]-48)*100 + (buffer[656]-48)*10 + (buffer[657]-48);   //E2EM2 (var 43)
   aux3 = (buffer[671]-48)*100 + (buffer[672]-48)*10 + (buffer[673]-48);   //E2EM3 (var 44)
   aux4 = (buffer[686]-48)*100 + (buffer[687]-48)*10 + (buffer[688]-48);   //E2EM4 (var 45)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.ext2_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.ext2_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // floor1 event mask
   aux1 = (buffer[701]-48)*100 + (buffer[702]-48)*10 + (buffer[703]-48);   //F1EM1 (var 46)
   aux2 = (buffer[716]-48)*100 + (buffer[717]-48)*10 + (buffer[718]-48);   //F1EM2 (var 47)
   aux3 = (buffer[731]-48)*100 + (buffer[732]-48)*10 + (buffer[733]-48);   //F1EM3 (var 48)
   aux4 = (buffer[746]-48)*100 + (buffer[747]-48)*10 + (buffer[748]-48);   //F1EM4 (var 49)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.floor1_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.floor1_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // floor2 event mask
   aux1 = (buffer[761]-48)*100 + (buffer[762]-48)*10 + (buffer[763]-48);   //F2EM1 (var 50)
   aux2 = (buffer[776]-48)*100 + (buffer[777]-48)*10 + (buffer[778]-48);   //F2EM2 (var 51)
   aux3 = (buffer[791]-48)*100 + (buffer[792]-48)*10 + (buffer[793]-48);   //F2EM3 (var 52)
   aux4 = (buffer[806]-48)*100 + (buffer[807]-48)*10 + (buffer[808]-48);   //F2EM4 (var 53)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.floor2_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.floor2_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // gym event mask
   aux1 = (buffer[821]-48)*100 + (buffer[822]-48)*10 + (buffer[823]-48);   //GYEM1 (var 54)
   aux2 = (buffer[836]-48)*100 + (buffer[836]-48)*10 + (buffer[837]-48);   //GYEM2 (var 55)
   aux3 = (buffer[851]-48)*100 + (buffer[852]-48)*10 + (buffer[853]-48);   //GYEM3 (var 56)
   aux4 = (buffer[866]-48)*100 + (buffer[867]-48)*10 + (buffer[868]-48);   //GYEM4 (var 57)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.gym_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.gym_event_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // ext1 hotspot mask
   aux1 = (buffer[881]-48)*100 + (buffer[882]-48)*10 + (buffer[883]-48);   //E1HS1 (var 58)
   aux2 = (buffer[896]-48)*100 + (buffer[897]-48)*10 + (buffer[898]-48);   //E1HS2 (var 59)
   aux3 = (buffer[911]-48)*100 + (buffer[912]-48)*10 + (buffer[913]-48);   //E1HS3 (var 60)
   aux4 = (buffer[926]-48)*100 + (buffer[927]-48)*10 + (buffer[928]-48);   //E1HS4 (var 61)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.ext1_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.ext1_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // ext2 hotspot mask
   aux1 = (buffer[941]-48)*100 + (buffer[942]-48)*10 + (buffer[943]-48);   //E2HS1 (var 62)
   aux2 = (buffer[956]-48)*100 + (buffer[957]-48)*10 + (buffer[958]-48);   //E2HS2 (var 63)
   aux3 = (buffer[971]-48)*100 + (buffer[972]-48)*10 + (buffer[973]-48);   //E2HS3 (var 64)
   aux4 = (buffer[986]-48)*100 + (buffer[987]-48)*10 + (buffer[988]-48);   //E2HS4 (var 65)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.ext2_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.ext2_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // floor1 hotspot mask
   aux1 = (buffer[1001]-48)*100 + (buffer[1002]-48)*10 + (buffer[1003]-48);   //F1HS1 (var 66)
   aux2 = (buffer[1016]-48)*100 + (buffer[1017]-48)*10 + (buffer[1018]-48);   //F1HS2 (var 67)
   aux3 = (buffer[1031]-48)*100 + (buffer[1032]-48)*10 + (buffer[1033]-48);   //F1HS3 (var 68)
   aux4 = (buffer[1046]-48)*100 + (buffer[1047]-48)*10 + (buffer[1048]-48);   //F1HS4 (var 69)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.floor1_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.floor1_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // floor2 hotspot mask
   aux1 = (buffer[1061]-48)*100 + (buffer[1062]-48)*10 + (buffer[1063]-48);   //F2HS1 (var 70)
   aux2 = (buffer[1076]-48)*100 + (buffer[1077]-48)*10 + (buffer[1078]-48);   //F2HS2 (var 71)
   aux3 = (buffer[1091]-48)*100 + (buffer[1092]-48)*10 + (buffer[1093]-48);   //F2HS3 (var 72)
   aux4 = (buffer[1106]-48)*100 + (buffer[1107]-48)*10 + (buffer[1108]-48);   //F2HS4 (var 73)
  	spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.floor2_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.floor2_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   // gym hotspot mask
   aux1 = (buffer[1121]-48)*100 + (buffer[1122]-48)*10 + (buffer[1123]-48);   //GYHS1 (var 74)
   aux2 = (buffer[1136]-48)*100 + (buffer[1137]-48)*10 + (buffer[1138]-48);   //GYHS2 (var 75)
   aux3 = (buffer[1151]-48)*100 + (buffer[1152]-48)*10 + (buffer[1153]-48);   //GYHS3 (var 76)
   aux4 = (buffer[1166]-48)*100 + (buffer[1167]-48)*10 + (buffer[1168]-48);   //GYHS4 (var 77)
   spare = aux1 | (aux2<<8);
   for(i = 0; i<16; i++){
      player.gym_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }
   spare = aux3 | (aux4<<8);
   for(i = 16; i<32; i++){
      player.gym_hotspot_mask[i] = spare & 0x01;
      spare = (spare >> 1);
   }

   //sprintf(error1, "%d", player.good);
   //sprintf(error2, "%d", player.money);
   //Error("buffer 25 value",error1, error2);
}


/////////////////////////////////////////////////////////
// Check savegame
// - Returns true if there is any file saved
/////////////////////////////////////////////////////////
byte CheckSavegame() {
	FILE *savefile;
   savefile = fopen("savegame.ini","rb+");

   // No hay partida guardada
   if(savefile == NULL){
   	fclose(savefile);
		return 0;
   }
   else
   {
      fclose(savefile);
   	return 1;
   }
}

/////////////////////////////////////////////////////////
// Continue game
// -Load last savegame and call main loop
/////////////////////////////////////////////////////////
void near ContinueGame(void) {

   UnloadMusic();
	LoadGame();
   LoadFont("FONTS.DAT","FONT.bmp"); //Load text font
   LoadPanelBackground("IMAGES.DAT","PANEL.pcx");
   VGA_PanelUpdate();

   // Set current items
   if(player.item_exams){ SetItem(2,16,"exams.pcx"); }
   if(player.item_chalk){ SetItem(2,16,"chalk.pcx"); }
   if(player.item_bag){ SetItem(1,16,"bitem.pcx"); }
   if(player.item_keys){ SetItem(1,16,"kitem.pcx"); }

   if(player.floor == 1){GoToFloor1(sprite[player.spriteNum].pos_x, sprite[player.spriteNum].pos_y);}
   if(player.floor == 2){GoToFloor2(sprite[player.spriteNum].pos_x, sprite[player.spriteNum].pos_y);}
   if(player.floor == 3){GoToExt1(sprite[player.spriteNum].pos_x, sprite[player.spriteNum].pos_y);}
   if(player.floor == 4){GoToExt2(sprite[player.spriteNum].pos_x, sprite[player.spriteNum].pos_y);}
	if(player.floor == 5){GoToGym(sprite[player.spriteNum].pos_x, sprite[player.spriteNum].pos_y);}

   LoadMusic(1);
   PlayNonStopMusic();

	MainLoop();

   if(save_game == 1){SaveGame();}
}

/////////////////////////////////////////////////////////
// Options
// - ...
/////////////////////////////////////////////////////////
void near Options(){

	byte end;
	word length;
   int menu_pos[8] = {20,76,92,100,108,124,140,156};
   byte MenuCursorAnimation[8] = {0,1,2,3,3,3,3,3};

	// Draw menu options
   end = 0;
   option = 1;
   sprite[1].pos_x = 0;
   sprite[1].pos_y = 0;
   Update(0);

   Draw_EmptyBox(10,7,23,13);
   sprite[1].pos_x = 84;
   Update(0);

   // Video mode
   LoadText("GLB_STR.DAT","global.txt","025",string,&length);
   PrintText(12,10,length,string,1);
   switch(video_mode){
   	case 1: //VGA
         PrintText(23,10,10,"VGA       ",0);
      	break;
      case 2: //EGA
         PrintText(23,10,10,"EGA       ",0);
      	break;
      case 3: //CGA
      	PrintText(23,10,10,"CGA       ",0);
         break;
      default:
      	break;
   }

   // Audio mode
   LoadText("GLB_STR.DAT","global.txt","030",string,&length);
   PrintText(12,12,length,string,0);

   switch(audio_mode){
   	case 0: // OFF
         PrintText(23,12,10,"OFF       ",0);
         break;
   	case 1: //PC speaker
         PrintText(23,12,10,"PC SPEAKER",0);
      	break;
      case 2: //Tandy
         PrintText(23,12,10,"TANDY     ",0);
      	break;
      case 3: //Adlib
      	PrintText(23,12,10,"ADLIB     ",0);
         break;
      case 4: //Sound blaster
      	PrintText(23,12,10,"S.BLASTER ",0);
         break;
      default:
      	PrintText(23,12,10,"??        ",0);
      	break;
   }

   // Sound volume
   LoadText("GLB_STR.DAT","global.txt","040",string,&length);
   PrintText(12,13,length,string,0);

   sprintf(string, "%d", sound_volume);
   PrintText(23,13,10,string,0);

   // Music volume
   LoadText("GLB_STR.DAT","global.txt","041",string,&length);
   PrintText(12,14,length,string,0);

   sprintf(string, "%d", music_volume);
   PrintText(23,14,10,string,0);

   // Language
	LoadText("GLB_STR.DAT","global.txt","045",string,&length);
   PrintText(12,16,length,string,0);

   switch(language){
   	case 1: //spanish
         PrintText(23,16,10,"ESPANOL   ",0);
      	break;
      case 2: //english
         PrintText(23,16,10,"ENGLISH   ",0);
      	break;
      default:
      	PrintText(23,16,10,"??",0);
      	break;
   }

   // Go back
   LoadText("GLB_STR.DAT","global.txt","050",string,&length);
   PrintText(12,18,length,string,0);

   Fade_in();

   while( end == 0 )
   {
      sprite[1].pos_y = menu_pos[option] + vga_page[2];

      if( fp_keys[K_UP] == 1) {

      	switch(option){
         	case 1: // Do nothing
            	break;
            case 2: // Rewrite old and new option
            	PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","030",string,&length);
   				PrintText(12,12,length,string,0);
	            option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","025",string,&length);
   				PrintText(12,10,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
            	PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","040",string,&length);
               PrintText(12,13,length,string,0);
               option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","030",string,&length);
   				PrintText(12,12,length,string,1);
				  	break;
            case 4: // Rewrite old and new option
            	PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","041",string,&length);
   				PrintText(12,14,length,string,0);
               option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","040",string,&length);
               PrintText(12,13,length,string,1);
               break;
            case 5: // Rewrite old and new option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","045",string,&length);
   				PrintText(12,16,length,string,0);
               option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","041",string,&length);
   				PrintText(12,14,length,string,1);
               break;
            case 6: // Rewrite old and new option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","050",string,&length);
   				PrintText(12,18,length,string,0);
               option--; // Change option
               LoadText("GLB_STR.DAT","global.txt","045",string,&length);
   				PrintText(12,16,length,string,1);
               break;
         }
      }
      if( fp_keys[K_DOWN] == 1){
      	switch(option){
         	case 1: // Rewrite old and new option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","025",string,&length);
   				PrintText(12,10,length,string,0);
               option++;
               LoadText("GLB_STR.DAT","global.txt","030",string,&length);
   				PrintText(12,12,length,string,1);
            	break;
            case 2: // Rewrite old and new option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","030",string,&length);
   				PrintText(12,12,length,string,0);
	            option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","040",string,&length);
   				PrintText(12,13,length,string,1);
				  	break;
            case 3: // Rewrite old and new option
               PlaySound(1);
               LoadText("GLB_STR.DAT","global.txt","040",string,&length);
   				PrintText(12,13,length,string,0);
               option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","041",string,&length);
   				PrintText(12,14,length,string,1);
				  	break;
            case 4: // Rewrite old and new option
               PlaySound(1);
				  	LoadText("GLB_STR.DAT","global.txt","041",string,&length);
   				PrintText(12,14,length,string,0);
               option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","045",string,&length);
   				PrintText(12,16,length,string,1);
				  	break;
            case 5: // Do nothing
               PlaySound(1);
            	LoadText("GLB_STR.DAT","global.txt","045",string,&length);
   				PrintText(12,16,length,string,0);
               option++; // Change option
               LoadText("GLB_STR.DAT","global.txt","050",string,&length);
   				PrintText(12,18,length,string,1);
				  	break;
            case 7:
            	break;
         }
      }

     	if(option < 1){ option = 1;}
      if(option > 6){ option = 6;}

      if(fp_keys[K_ENTER]){
      	if( option == 6){
         	PlaySound(1);
            SaveConfig();
            UnloadMusic();
            //RestartProgram();
            player.spriteNum = 1; // Player sprite is always sprite 1!
   			existingSaveGame = CheckSavegame();
         	end = 1;
         }
      }

      if(fp_keys[K_RIGHT]){
      	switch(option){
            case 1: 	// video mode
            	switch(video_mode){
   					case 1: //VGA
                  	PlaySound(1);
                  	//video_mode = 2;
         				//PrintText(23,10,10,"EGA       ",0);
                     video_mode = 1;
                     PrintText(23,10,10,"VGA       ",0);
      					break;
      				case 2: //EGA
                  	PlaySound(1);
                  	//video_mode = 3;
         				//PrintText(23,10,10,"CGA       ",0);
                     video_mode = 1;
                     PrintText(23,10,10,"VGA       ",0);
      					break;
      				case 3: //CGA
                     PlaySound(1);
         				break;
      				default:
      					break;
               }
               break;
            case 2: 	// audio mode
            	switch(audio_mode){
   					case 0: // OFF
                     PlaySound(1);
                  	audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
         				break;
   					case 1: //PC speaker
                     PlaySound(1);
                     //audio_mode = 2;
     					   //PrintText(23,12,10,"TANDY     ",0);
                     audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
      					break;
      				case 2: //Tandy
                     PlaySound(1);
                  	//audio_mode = 3;
         				//PrintText(23,12,10,"ADLIB     ",0);
                     audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
      					break;
      				case 3: //Adlib
                     PlaySound(1);
                  	//audio_mode = 4;
      					//PrintText(23,12,10,"S.BLASTER ",0);
                     audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
                     break;
      				case 4: //Sound blaster
                     break;
      				default:
      					break;
   				}
               break;

            case 3: 	// audio volume +
            	if(sound_volume < 100){ sound_volume ++; }
               PlaySound(1);
               sprintf(string, "%d", sound_volume);
               PrintText(23,13,10,"          ",0);
   				PrintText(23,13,strlen(string),string,0);
               break;
            case 4:
            	if(music_volume < 100){ music_volume ++; }
               PlaySound(1);
               sprintf(string, "%d", music_volume);
               PrintText(23,14,10,"          ",0);
				   PrintText(23,14,strlen(string),string,0);
            	break; // music volume +
            case 5: // language
            	if(language == 1){
               	PlaySound(1);
               	language = 2;
                  PrintText(23,16,10,"ENGLISH      ",0);
               }
            	break;
            default:
            	break;
         }
      }

      if(fp_keys[K_LEFT]){
      	switch(option){
         	case 1: 	// video mode
            	switch(video_mode){
   					case 1: //VGA
                  	PlaySound(1);
      					break;
      				case 2: //EGA
                  	PlaySound(1);
                  	video_mode = 1;
         				PrintText(23,10,10,"VGA       ",0);
      					break;
      				case 3: //CGA
                     PlaySound(1);
                  	//video_mode = 2;
         				//PrintText(23,10,10,"EGA       ",0);
                     video_mode = 1;
         				PrintText(23,10,10,"VGA       ",0);
         				break;
      				default:
      					break;
               }
               break;
            case 2: 	// audio mode
            	switch(audio_mode){
   					case 0: // OFF
                  	PlaySound(1);
                  	break;
   					case 1: //PC speaker
                     PlaySound(1);
                     audio_mode = 0;
         				PrintText(23,12,10,"OFF       ",0);
                  	break;
      				case 2: //Tandy
                  	PlaySound(1);
                     audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
      					break;
      				case 3: //Adlib
                     PlaySound(1);
                  	//audio_mode = 2;
     					   //PrintText(23,12,10,"TANDY     ",0);
                     audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
      					break;
      				case 4: //Sound blaster
                  	PlaySound(1);
                  	//audio_mode = 3;
         				//PrintText(23,12,10,"ADLIB     ",0);
                     audio_mode = 1;
         				PrintText(23,12,10,"PC SPEAKER",0);
                     break;
      				default:
      					break;
   				}
               break;
            case 3: 	// audio volume -
            	if(sound_volume > 0){ sound_volume --; }
               PlaySound(1);
               sprintf(string, "%d", sound_volume);
               PrintText(23,13,10,"          ",0);
   				PrintText(23,13,strlen(string),string,0);
               break;
            case 4:
            	if(music_volume > 0){ music_volume --; }
               PlaySound(1);
               sprintf(string, "%d", music_volume);
               PrintText(23,14,10,"          ",0);
				   PrintText(23,14,strlen(string),string,0);
            	break; // music volume -
            case 5: // language
            	if(language == 2){
               	PlaySound(1);
               	language = 1;
                  PrintText(23,16,10,"ESPANOL     ",0);
               }
            	break;
            default:
            	break;
         }
      }

      // Wait until enter key is released
      while(keys[K_ENTER] == 1){
      	// do nothing
      }

      Update(0);
   }
}

/////////////////////////////////////////////////////////
// Main function
// - Main entry function of the program
/////////////////////////////////////////////////////////
void main(){

	system("cls");
   //printf("\n************************************************\n");
   //printf("*********** LA FIESTA DE LAS HORMONAS **********\n");
   //printf("************************************************\n");
   //printf("\n");

   InitEngine(); // Initialize system

   //Logo(); // Show logos and stuff before start the party
   //Intro();  // Show little intro

   player.spriteNum = 1; // Player sprite is always sprite 1!
   existingSaveGame = CheckSavegame();

   while( 1 )
   {
      end_game = 0;

		Menu(); // Show game main menu
      switch(option)
      {
      	case 1: // New game
            NewGame();
      		break;
         case 2: // Continue
            ContinueGame();
         	break;
         case 3: // Options
            Options();
         	break;
         case 4: // Exit
         	ExitDOS();
         	break;
         default:
         	break;
      }
   }
}


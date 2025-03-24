/***********************
*  END GAME
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// End game
// - Extinguisher
/////////////////////////////////////////////////////////
void far EndGameExtinguisher(void){
	word length;

	panelScrolling = 0;
   showPanel = 0;
   Update(0);

   UnloadMusic();

   LoadSprite("SPRMISC.DAT","smoke.pcx",17, 64); //Load sprites to one of the fixed structs
  	SetSpriteAnimation(17,0,1,64,PlayerFaceAnimation);
   sprite[17].pos_x = sprite[player.spriteNum].pos_x + 0;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y + 0;
   HideSprite(player.spriteNum); // Hide player
   DrawSpriteDestructive(17);
   Update(0);
   Delay(10);
   sprite[17].pos_x = sprite[player.spriteNum].pos_x + 16;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y + 16;
   DrawSpriteDestructive(17);
   Update(0);
   Delay(10);
   sprite[17].pos_x = sprite[player.spriteNum].pos_x - 16;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y - 16;
   DrawSpriteDestructive(17);
   Update(0);
   Delay(10);
   sprite[17].pos_x = sprite[player.spriteNum].pos_x + 16;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y - 16;
   DrawSpriteDestructive(17);
   Update(0);
   Delay(10);
   sprite[17].pos_x = sprite[player.spriteNum].pos_x - 16;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y + 16;
   DrawSpriteDestructive(17);
   Update(0);
   Delay(10);
   sprite[17].pos_x = sprite[player.spriteNum].pos_x - 8;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y + 16;
   DrawSpriteDestructive(17);
   Update(0);
   Delay(10);
   SetSpriteAnimation(player.spriteNum,0,6,8,PlayerAnimation);   // Stand up
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","GLB_STR.DAT","MISC.TXT","095",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadMusic(2);
   LoadImage("IMAEND.DAT","end0_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   PlayNonStopMusic();

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","001",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","002",string,&length);
   PrintText(1,19,length,string,0);
   Delay(50);
   LoadText("D0_END.DAT","D0END0.TXT","003",string,&length);
   PrintText(1,21,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","004",string,&length);
   PrintText(1,22,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","005",string,&length);
   PrintText(1,23,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","012",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","013",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","018",string,&length);
   PrintText(1,21,length,string,0);
   Delay(50);
   LoadText("D0_END.DAT","D0END0.TXT","020",string,&length);
   PrintText(1,22,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","021",string,&length);
   PrintText(1,23,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","027",string,&length);
   PrintText(1,20,length,string,0);
   Delay(50);
   LoadText("D0_END.DAT","D0END0.TXT","030",string,&length);
   PrintText(1,21,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","031",string,&length);
   PrintText(1,22,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","032",string,&length);
   PrintText(1,23,length,string,0);

   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();

   UnloadMusic();
   end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Falling from roof
/////////////////////////////////////////////////////////
void far EndGameRoof(void){
	word length;

	panelScrolling = 0;
   showPanel = 0;
   Update(0);

   UnloadMusic();

   LoadSprite("SPRMISC.DAT","window.pcx",17, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(17,0,1,64,PlayerFaceAnimation);
   Speech("SPRFACE2.DAT","windowf.pcx","D0_END.DAT","D0END0.txt","040",0,0,0);

   SetSpriteAnimation(player.spriteNum,0,6,8,PlayerAnimation);   // Stand up
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END0.txt","045","046",0,0);
   HideSprite(player.spriteNum); // Hide player

   sprite[17].pos_x = sprite[player.spriteNum].pos_x;
   sprite[17].pos_y = sprite[player.spriteNum].pos_y;
   DrawSpriteDestructive(17);

   Delay(100);

   SetLoadingInterrupt();   // Start loading animation

   LoadMusic(2);
   LoadImage("IMAEND.DAT","end0_2.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   PlayNonStopMusic();

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","050",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","051",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","052",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","053",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","055",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","056",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","057",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","060",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","061",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","062",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","063",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","065",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","066",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","067",string,&length);
   PrintText(1,20,length,string,0);

   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END0.TXT","070",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","071",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","072",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","073",string,&length);
   PrintText(1,21,length,string,0);
   LoadText("D0_END.DAT","D0END0.TXT","074",string,&length);
   PrintText(1,22,length,string,0);

   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();

   UnloadMusic();
  
   //Error("End of game: rOOF",0,0);
	end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Like a dream (good end)
/////////////////////////////////////////////////////////
void near EndGameLikeADream(void){
   word length;
   byte step = 0; // Current step
   byte endSequence = 0; // End  flag

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 170){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,17,1,8,PlayerAnimation); // Set animation >> right
   Update(0);

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END8.txt","001","002",0,0);

   SetSpriteAnimation(2,13,1,12,PlayerAnimation);  // left
   Update(0);
   Speech("SPRFACE1.DAT","jessyf.pcx","D0_END.DAT","D0END8.txt","005","006",0,0);
   Delay(20);

   SetLoadingInterrupt();   // Start loading animation

   UnloadMusic();

   LoadImage("IMAEND.DAT","end8_1.pcx",2); // Load menu background image to non visible page
   LoadPanelBackground("IMAEND.DAT","PEND.pcx");
   LoadMusic(51);

   panelScrolling = 1;

   ResetLoadingInterrupt();   // Stop loading animation

   PlayMusic();

   SetPage(2);
   Update(0);

   Fade_in();

   // End loop
   while( (keys[K_ESC] != 1) && (endSequence != 1) )
   {
   	// Animation
      switch(step){
      	case 0:  // Step 0
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","010",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(180);
            if(panelShown == 1){step++;}
            break;
         case 1:
         	LoadText("D0_END.DAT","D0END8.TXT","011",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(180);
            LoadImage("IMAEND.DAT","end8_2.pcx",1); // Load menu background image to non visible page
            step++;
            break;
         case 2:
            if(musicPlaying==0){step++;}
				break;
         case 3:
            showPanel = 0;
         	UnloadMusic();
            LoadMusic(52);
            PlayMusic();
            step++;
            break;
         case 4:
            if(panelHiden == 1){step++;}
         	break;
         case 5:
            SetPage(1);
         	showPanel = 1;
         	LoadText("D0_END.DAT","D0END8.TXT","015",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            if(panelShown == 1){step++;}
            break;
         case 6:
         	LoadText("D0_END.DAT","D0END8.TXT","016",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            step++;
            break;
         case 7:
         	LoadText("D0_END.DAT","D0END8.TXT","017",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            LoadImage("IMAEND.DAT","end8_3.pcx",2); // Load menu background image to non visible page
            step++;
            break;
         case 8:
            if(musicPlaying==0){step++;}
				break;
         case 9:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(53);
            PlayMusic();
            step++;
            break;
         case 10:
            if(panelHiden == 1){step++;}
         	break;
        	case 11:
         	SetPage(2);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","020",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            if(panelShown == 1){step++;}
            break;
         case 12:
         	LoadText("D0_END.DAT","D0END8.TXT","021",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            step++;
            break;
         case 13:
         	LoadText("D0_END.DAT","D0END8.TXT","022",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND.DAT","end8_4.pcx",1); // Load menu background image to non visible page
            Delay(150);
            step++;
            break;
         case 14:
            if(musicPlaying==0){step++;}
				break;
         case 15:
            showPanel = 0;
         	UnloadMusic();
            LoadMusic(54);
            PlayMusic();
            step++;
            break;
         case 16:
            if(panelHiden == 1){step++;}
            break;
         case 17:
         	SetPage(1);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","025",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(130);
            if(panelShown == 1){step++;}
            break;
         case 18:
            LoadText("D0_END.DAT","D0END8.TXT","026",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(130);
            step++;
            break;
         case 19:
            LoadText("D0_END.DAT","D0END8.TXT","027",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(130);
            step++;
            break;
         case 20:
            LoadText("D0_END.DAT","D0END8.TXT","028",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(130);
            step++;
            break;
         case 21:
            LoadText("D0_END.DAT","D0END8.TXT","029",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(130);
            step++;
            break;
         case 22:
            LoadText("D0_END.DAT","D0END8.TXT","030",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_5.pcx",2); // Load menu background image to non visible page2
            Delay(120);
            step++;
            break;
         case 23:
            if(musicPlaying==0){step++;}
				break;
         case 24:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(55);
            PlayMusic();
            step++;
            break;
         case 25:
				if(panelHiden == 1){step++;}
         	break;
			case 26:
            SetPage(2);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","035",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(120);
            step++;
         	break;
         case 27:
            LoadText("D0_END.DAT","D0END8.TXT","036",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(120);
            step++;
         	break;
         case 28:
            LoadText("D0_END.DAT","D0END8.TXT","037",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(120);
            step++;
         	break;
         case 29:
            LoadText("D0_END.DAT","D0END8.TXT","038",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(120);
            step++;
         	break;
         case 30:
            LoadText("D0_END.DAT","D0END8.TXT","039",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_6.pcx",1); // Load menu background image to non visible page2
            step++;
         	break;
         case 31:
            if(musicPlaying==0){step++;}
				break;
         case 32:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(56);
            PlayMusic();
            step++;
            break;
         case 33:
				if(panelHiden == 1){step++;}
         	break;
         case 34:
            SetPage(1);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","045",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            step++;
         	break;
         case 35:
            LoadText("D0_END.DAT","D0END8.TXT","046",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            step++;
         	break;
         case 36:
            LoadText("D0_END.DAT","D0END8.TXT","047",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_7.pcx",2); // Load menu background image to non visible page2
            Delay(150);
            step++;
         	break;
         case 37:
            if(musicPlaying==0){step++;}
				break;
         case 38:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(57);
            PlayMusic();
            step++;
            break;
         case 39:
				if(panelHiden == 1){step++;}
         	break;
         case 40:
            SetPage(2);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","050",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(150);
            step++;
         	break;
         case 41:
            LoadText("D0_END.DAT","D0END8.TXT","051",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_8.pcx",1); // Load menu background image to non visible page2
            Delay(150);
            step++;
         	break;
         case 42:
            if(musicPlaying==0){step++;}
				break;
         case 43:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(58);
            PlayMusic();
            step++;
            break;
         case 44:
				if(panelHiden == 1){step++;}
         	break;
         case 45:
            SetPage(1);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","055",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(120);
            step++;
         	break;
         case 46:
            LoadText("D0_END.DAT","D0END8.TXT","056",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(120);
            step++;
         	break;
         case 47:
            LoadText("D0_END.DAT","D0END8.TXT","057",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_9.pcx",2); // Load menu background image to non visible page2
            Delay(120);
            step++;
         	break;
         case 48:
            if(musicPlaying==0){step++;}
				break;
         case 49:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(59);
            PlayMusic();
            step++;
            break;
         case 50:
				if(panelHiden == 1){step++;}
         	break;
         case 51:
            SetPage(2);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","060",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(100);
            step++;
         	break;
         case 52:
            LoadText("D0_END.DAT","D0END8.TXT","061",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(100);
            step++;
         	break;
         case 53:
            LoadText("D0_END.DAT","D0END8.TXT","062",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(100);
            step++;
         	break;
         case 54:
         	LoadText("D0_END.DAT","D0END8.TXT","063",string,&length);
         	PrintPanelText(2,1,length,string);
				LoadImage("IMAEND2.DAT","end8_10.pcx",1); // Load menu background image to non visible page2
            Delay(100);
            step++;
         	break;
         case 55:
            if(musicPlaying==0){step++;}
				break;
         case 56:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(60);
            PlayMusic();
            step++;
            break;
         case 57:
				if(panelHiden == 1){step++;}
         	break;
         case 58:
            SetPage(1);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","065",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(200);
            step++;
         	break;
         case 59:
            LoadText("D0_END.DAT","D0END8.TXT","066",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_11.pcx",2); // Load menu background image to non visible page2
            step++;
         	break;
         case 60:
            if(musicPlaying==0){step++;}
				break;
         case 61:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(61);
            PlayMusic();
            step++;
            break;
         case 62:
				if(panelHiden == 1){step++;}
         	break;
         case 63:
            SetPage(2);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","070",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(200);
            step++;
         	break;
			case 64:
            LoadText("D0_END.DAT","D0END8.TXT","071",string,&length);
         	PrintPanelText(2,1,length,string);
            LoadImage("IMAEND2.DAT","end8_12.pcx",1); // Load menu background image to non visible page2
            step++;
         	break;
         case 65:
            if(musicPlaying==0){step++;}
				break;
         case 66:
         	showPanel = 0;
         	UnloadMusic();
            LoadMusic(62);
            PlayMusic();
            step++;
            break;
         case 67:
				if(panelHiden == 1){step++;}
         	break;
         case 68:
            SetPage(1);
            showPanel = 1;
            LoadText("D0_END.DAT","D0END8.TXT","075",string,&length);
         	PrintPanelText(2,1,length,string);
            Delay(300);
            step++;
         	break;
         case 69:
            if(musicPlaying==0){step++;}
				break;
         case 70:
            Fade_out();
         	showPanel = 0;
         	step++;
            break;
         case 71:
				if(panelHiden == 1){step++;}
         	break;
         case 72:
            Delay(50);
            LoadImage("IMAEND2.DAT","end8_13.pcx",2); // Load menu background image to non visible page2
            SetPage(2);
            Fade_in();
            Delay(200);
            step++;
				break;
         default:
         	endSequence = 1;
         	break;
      }
      Update(0);
   }

   Fade_out();

   UnloadMusic();

	//Error("End of game: Like a dream",0,0);
   end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Arrogant genius
/////////////////////////////////////////////////////////
void near EndArrogantGenious(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END7.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end2_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END7.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END7.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","012",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","013",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END7.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","018",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END7.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","022",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","023",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END7.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","027",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","028",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END7.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END7.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();


	//Error("End of game: Arrogant genius",0,0);
   end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Missundestood romantic
/////////////////////////////////////////////////////////
void near EndGameMissunderstoodRomantic(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END6.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end2_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END6.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END6.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","012",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","013",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END6.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","018",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END6.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","022",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","023",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END6.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","027",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","028",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END6.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END6.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();

	//Error("End of game: Misunderstood romantic",0,0);
	end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Brilliant solitaire
/////////////////////////////////////////////////////////
void near EndGameBrilliantSolitaire(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END5.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end2_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END5.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END5.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","012",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","013",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END5.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","018",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END5.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","022",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","023",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END5.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","027",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","028",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END5.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END5.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();


	//Error("End of game: Brilliant solitaire",0,0);
   end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Heart of group
/////////////////////////////////////////////////////////
void near EndGameHeartOfGroup(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END4.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end2_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END4.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END4.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","012",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","013",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END4.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","017",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END4.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","022",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","023",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END4.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","027",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","028",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END4.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END4.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();

	//Error("End of game: Heart of group",0,0);
   end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Superficial jocker
/////////////////////////////////////////////////////////
void near EndGameSuperficialJocker(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END3.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end2_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END3.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END3.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","012",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","013",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END3.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","018",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END3.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","022",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","023",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END3.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","027",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END3.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END3.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();

	//Error("End of game: Superficial jocker",0,0);
	end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Pagafantas
/////////////////////////////////////////////////////////
void near EndGamePagafantas(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }

   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END2.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end2_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END2.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END2.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","012",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END2.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","018",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END2.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","022",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","023",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END2.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","027",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END2.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END2.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();

	//Error("End of game: Pagafantas",0,0);
	end_game = 1;
}

/////////////////////////////////////////////////////////
// End game
// - Looser
/////////////////////////////////////////////////////////
void near EndGameLooser(void){
   word length;

   InitSprite(8,130,170);

   Delay(300);

   InitSprite(1,0,296);
   SetSpriteAnimation(1,17,4,8,PlayerAnimation); // Set animation >> right

   while(sprite[1].pos_x < 90){
   	sprite[1].pos_x++;
      Update(0);
   }

   SetSpriteAnimation(1,0,6,8,PlayerAnimation);   // Stand up player
   Update(0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","001","002",0,0);
   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0GLB.txt","005","006","007",0);

   SetSpriteAnimation(1,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[1].pos_x < 120){
   	sprite[1].pos_x++;
      sprite[1].pos_y--;
      Update(0);
   }
   while(sprite[1].pos_y > 200){
   	scroll_y--;
   	sprite[1].pos_y--;
      Update(0);
   }
   
   SetSpriteAnimation(1,25,1,8,PlayerAnimation);   // Stand up player

   while(scroll_y > 64)
   {
   	scroll_y --;
   	Update(0);
   }

   Speech("SPRFACE1.DAT","playerf.pcx","D0_END.DAT","D0END1.txt","001",0,0,0);

   SetLoadingInterrupt();   // Start loading animation

   LoadImage("IMAEND.DAT","end1_1.pcx",2); // Load menu background image to non visible page
   LoadSprite("SPRMISC.DAT","enter.pcx",18, 16); //Load sprites to one of the fixed structs
   SetSpriteAnimation(18,0,4,8,EnterAnimation);

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   sprite[18].pos_x = scroll_x + 298;
   sprite[18].pos_y = scroll_y + 176;

   Fade_in();

   Delay(30);
   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END1.TXT","005",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","006",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","007",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","008",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END1.TXT","010",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","011",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","012",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END1.TXT","015",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","016",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","017",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","018",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END1.TXT","020",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","021",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","022",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END1.TXT","025",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","026",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","027",string,&length);
   PrintText(1,20,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Draw_EmptyBox(0,17,38,6);
   LoadText("D0_END.DAT","D0END1.TXT","030",string,&length);
   PrintText(1,18,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","031",string,&length);
   PrintText(1,19,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","032",string,&length);
   PrintText(1,20,length,string,0);
   LoadText("D0_END.DAT","D0END1.TXT","033",string,&length);
   PrintText(1,21,length,string,0);

   Delay(50);
   DrawSpriteDestructive(18);
   while(keys[K_ENTER]==0){ Update(0); }
   while(keys[K_ENTER]==1){ }

   Fade_out();
   UnloadMusic();

	//Error("End of game: Looser",0,0);
	end_game = 1;
}


void far GoToEnd(void){

	byte good_end = 0;
	byte AmayaAnimation3[] = {0,1,2,1,2,1,0};
   byte XabiAnimation3[] = {2,0,1,0,2,0,1};
   byte GitarAnimation3[] = {1,2,0,1,2,0,2};
   byte BassAnimation3[] = {0,2,0,1,2,0,2};
   byte BateryAnimation3[] = {2,1,0,1,2,0,0};

	Fade_out();

   panelScrolling = 0;
   showPanel = 0;
   Update(0);

	SetLoadingInterrupt();   // Start loading animation
   LoadMap("MAPS.DAT","gym_1.tmx");
   LoadTiles("TILESETS.DAT","gym.pcx");

   LoadSprite("SPRBAND.DAT","bateria.pcx",3, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(3,0,6,30,BateryAnimation3);
   InitSprite(3,128,102);
   LoadSprite("SPRBAND.DAT","xabi.pcx",4, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(4,0,6,30,XabiAnimation3);
   InitSprite(4,168,102);
   LoadSprite("SPRBAND.DAT","guitar.pcx",5, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(5,0,6,30,GitarAnimation3);
   InitSprite(5,118,122);
   LoadSprite("SPRBAND.DAT","amaya.pcx",6, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(6,0,6,30,AmayaAnimation3);
   InitSprite(6,148,132);
   LoadSprite("SPRBAND.DAT","bass.pcx",7, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(7,0,6,30,BassAnimation3);
   InitSprite(7,178,122);
   LoadSprite("SPRCHR1.DAT","antonio.pcx",8, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(8,0,6,19,CharacterAnimation2);

   LoadSprite("SPRCHR1.DAT","player.pcx",player.spriteNum, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(1,0,6,8,PlayerAnimation); // Set animation >> right
   sprite[player.spriteNum].pos_x = 50;
   sprite[player.spriteNum].pos_y = 50;

   LoadSprite("SPRCHR1.DAT","jessy.pcx",2, 32); //Load sprites to one of the fixed structs
   SetSpriteAnimation(2,0,6,16,JessyAnimation);  // Moving up

   LoadMusic(3);

   ResetLoadingInterrupt(); // Stop loading animation

   PlayNonStopMusic();

   scrolling_enabled = 1;

   // Draw map
   SetMap();

	Fade_in();

   Delay(500);

   while(scroll_y < 220){
   	scroll_y++;
      Update(0);
   }

   SetSpriteAnimation(2,17,4,8,PlayerAnimation); // Set animation >> right
   InitSprite(2,0,296);
   while(sprite[2].pos_x < 170){
   	sprite[2].pos_x++;
      Update(0);
   }
   SetSpriteAnimation(2,25,4,8,PlayerAnimation); // Set animation >> up
   while(sprite[2].pos_y > 170){
   	sprite[2].pos_y--;
      Update(0);
   }
   SetSpriteAnimation(2,0,6,8,PlayerAnimation);   // Stand up player

   if((player.intell > 17)&(player.popular > 17)&(player.good > 17)){
   	EndGameLikeADream();
   }
   else if((player.intell > 17)&(player.popular > 17)&(player.good <= 17)){
      EndArrogantGenious();
   }
   else if((player.intell > 17)&(player.popular <= 17)&(player.good > 17)){
      EndGameMissunderstoodRomantic();
   }
   else if((player.intell > 17)&(player.popular <= 17)&(player.good <= 17)){
      EndGameBrilliantSolitaire();
   }
   else if((player.intell <= 17)&(player.popular > 17)&(player.good > 17)){
      EndGameHeartOfGroup();
   }
   else if((player.intell <=17)&(player.popular > 17)&(player.good <=17)){
      EndGameSuperficialJocker();
   }
   else if((player.intell <=17)&(player.popular <=17)&(player.good > 17)){
   	EndGamePagafantas();
   }
   else {
   	EndGameLooser();
   } 
}

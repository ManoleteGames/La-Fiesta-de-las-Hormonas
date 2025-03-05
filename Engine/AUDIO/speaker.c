/***********************
*  PC Speaker functions
************************/

#include "source\engine\engine.h"

byte musicBufferIndex = 0;
byte noteTime = 0;
byte duration = 0;
int speakerSoundOffset = 2;
int speakerMusicOffset = 2;

byte *speakerSFX;

//byte *speakerMusicNote;
//byte *speakerMusicOctave;
//byte *speakerMusicDuration;

int speakerSoundSize = 16;
int speakerMusicSize = 16;

byte speakerMenu[4] = {56,52,51,45};

//byte speakerMenu[16] = {0,0,56,52,51,45,40,30,25,15,10,5,0,0,0,0};
byte speakerSelect[16] = {0,0,90,80,70,60,50,30,10,5,10,30,50,60,70,60};
byte speakerCrash[16] = {0,0,69,3,120,32,39,200,20,60,16,106,12,87,8,70};
byte speakerJump[16] = {0,0,30,35,40,43,44,45,46,47,48,49,50,51,52,53};
byte speakerGetItem[16] = {0,0,69,70,71,72,69,64,58,40,30,12,12,16,20,70};
byte speakerOctave0[16] = {1,2,3,4,5,6,7,8,9,10,11,0,0,0,0,0};
byte speakerOctave1[16] = {12,13,14,15,16,17,18,19,20,21,22,23,0,0,0,0};
byte speakerOctave2[16] = {24,25,26,27,28,29,30,31,32,33,34,35,0,0,0,0};
byte speakerOctave3[16] = {36,37,38,39,40,41,42,43,44,45,46,47,0,0,0,0};
byte speakerOctave4[16] = {48,49,50,51,52,53,54,55,56,57,58,59,0,0,0,0};
byte speakerOctave5[16] = {60,61,62,63,64,65,66,67,68,69,70,71,0,0,0,0};
byte speakerOctave6[16] = {72,73,74,75,76,77,78,79,80,81,82,83,0,0,0,0};

/*
	NOTE VALUES
	-----------
	Octave 0    1    2    3    4    5    6    7
	Note
	 C     0    12   24   36   48   60   72   84
	 C#    1    13   25   37   49   61   73   85
	 D     2    14   26   38   50   62   74   86
	 D#    3    15   27   39   51   63   75   87
	 E     4    16   28   40   52   64   76   88
	 F     5    17   29   41   53   65   77   89
	 F#    6    18   30   42   54   66   78   90
	 G     7    19   31   43   55   67   79   91
	 G#    8    20   32   44   56   68   80   92
	 A     9    21   33   45   57   69   81   93
	 A#    10   22   34   46   58   70   82   94
	 B     11   23   35   47   59   71   83   95
*/
//1193180/Value

int speakerNote[96] = {
	//value = 1.9MHz/f
	//Note	    C    C#     D    D#     E     F    F#     G    G#     A    A#     B
	//Octave
	/*0	*/	 65535 ,65535,65535,62799,56818,54235,51877,49716,45892,44192,41144,38490,
	/*1   */	 36157 ,34091,32248,30594,29102,27118,25939,24351,22946,21694,20572,19245,
	/*2   */  18357 ,17292,16345,15297,14551,13715,12969,12175,11473,10847,10286, 9701,
	/*3   */   9108 ,8584 ,8117 ,7698 ,7231 ,6818 ,6450 ,6088 ,5736 ,5424 ,5121 , 4870,
	/*4   */   4554 ,4308 ,4058 ,3837 ,3616 ,3419 ,3225 ,3044 ,2875 ,2712 ,2560 , 2415,
	/*5	*/   2281 ,2154 ,2033 ,1918 ,1811 ,1709 ,1612 ,1522 ,1436 ,1356 ,1280 ,1208 ,
	/*6	*/   1141 ,1076 ,1015 ,959  ,898  ,854  ,806  ,761  ,718  ,678  ,640  ,604  ,
	/*7	*/   570  ,538  ,508  ,479  ,452  ,427  ,403  ,380  ,359  ,339  ,320  ,302  ,
};

/////////////////////////////////////////////////////////
// Interrupt speaker handler declaration
/////////////////////////////////////////////////////////
void interrupt (*old_speaker_handler)(void);
void interrupt Speaker_handler(void){
	byte index;
   byte note2;
   byte sust;
   byte octave;
   byte dummy;

	int note;
	asm cli

   /////////////////// sound player ///////////////////////////
   if (soundPlaying == 1){
   	if (speakerSoundOffset != speakerSoundSize){
			index = speakerSFX[speakerSoundOffset];

      	if(index == 0){
         	//note = 0;
           	// mute speaker
           	asm in al, 61h        //Disable speaker
				asm and al, 252
				asm out 61h, al
         }
         else{
           	// Unmute speaker
            // When audio is off, all functions are linked to speaker but buzzer will be not activated
   			if(audio_mode == 1){
         		asm in al, 61h			//Enable speaker
					asm or al, 3
					asm out 61h, al      // 61h >> Speaker output port (bit0: connects pit with speaker)
            }

         	note = speakerNote[index]; //speakerMusic[index]; // calculated frequency (1193180/Value)
            asm mov ax, note
				asm out PTI_CH2,al
				asm mov al,ah
				asm out PTI_CH2,al
         }
         speakerSoundOffset++;
		} else {
      	asm in al, 61h        //Disable speaker
         asm and al, 252
         asm out 61h, al
			soundPlaying = 0;
         speakerSoundOffset = 0;
		}
   }

   /////////////////// music player ///////////////////////
	if((musicPlaying == 1)||(musicNonStopPlaying == 1)){

   	if(noteTime < duration){ // current note being played
      	noteTime++;
      }else{ // load new note
      	noteTime = 0;

         duration = music.sdata[music.offset];
         note2 = music.sdata[music.offset+1];
         sust = music.sdata[music.offset+2];
         octave = music.sdata[music.offset+3];
         dummy = music.sdata[music.offset+4];
         music.offset = music.offset + 5;

         // not end of song yet
      	if(duration != 70){ // ASCII CHAR 'F'
      		switch(note2){
         		case 67: //C
            		if(sust == 35){ note2 = 2; }// #
               	else{ note2 = 1; }
            		break;
            	case 68: //D
            		if(sust == 35){ note2 = 4; }// #
               	else{ note2 = 3; }
               	break;
            	case 69: //E
            		note2 = 5;
               	break;
            	case 70: //F
               	if(sust == 35){ note2 = 7; }// #
               	else{ note2 = 6; }
               	break;
            	case 71: //G
            		if(sust == 35){ note2 = 9; }// #
               	else{ note2 = 8; }
               	break;
            	case 65: //A
            		if(sust == 35){ note2 = 11; }// #
               	else{ note2 = 10; }
               	break;
            	case 66: //B
            		note2 = 12;
               	break;
            	default:
            		note2 = 0;
               	break;
         	}
         	duration = duration - 48;
         	octave = octave - 48;

      		index = (note2 - 1 )+(octave*12);

            // no sound being player
         	if(soundPlaying == 0){
         		if(note2 == 0){
            		// mute speaker
            		asm in al, 61h        //Disable speaker
						asm and al, 252
						asm out 61h, al
         		}
         		else{
               	// When audio is off, all functions are linked to speaker but buzzer will be not activated
   					if(audio_mode == 1){
            			// Unmute speaker
         				asm in al, 61h			//Enable speaker
							asm or al, 3
							asm out 61h, al      // 61h >> Speaker output port (bit0: connects pit with speaker)
               	}

						note = speakerNote[index]; //speakerMusic[index]; // calculated frequency (1193180/Value)
            		asm mov ax, note
						asm out PTI_CH2,al
						asm mov al,ah
						asm out PTI_CH2,al
         		}
         	}
            noteTime++;
			} else {
         	noteTime = 0;
            duration = 0;
      		if(musicNonStopPlaying == 1){ music.offset = 0; }
         	if(musicPlaying == 1){ SPEAKER_StopMusic(); }
			}
      }
	}

	asm mov al, 020h
   asm out 020h, al    //Send 0x20 to 0x20 port (end of interrupt)
	asm sti
}



/////////////////////////////////////////////////////////
// Set speaker handler
/////////////////////////////////////////////////////////
void Set_speaker_handler(void){
   old_speaker_handler = getvect(TIMER_IRQ); // Save old keyb irq
   setvect(TIMER_IRQ,Speaker_handler); // Set interrupt x to interrupt handler function
}

/////////////////////////////////////////////////////////
// Reset speaker handler
/////////////////////////////////////////////////////////
void Reset_speaker_handler(void){
   setvect(TIMER_IRQ,old_speaker_handler); // Set interrupt x to interrupt handler function
}

/////////////////////////////////////////////////////////
// Initialize pc speaker
/////////////////////////////////////////////////////////
void SPEAKER_Init(void){

	// The clock we're dealing with here runs at 1.193182mhz, so we
   // just divide 1.193182 by the number of triggers we want per
   // second to get our divisor.
   int c = 1193181 / (int)1000;

	asm mov al, 0B6h     // Initialize PIT (programable interval timer)
   asm out 43h,al

   //set timer
   asm mov al,0x36  // 0b0011 0110 >> Channel 0, lobyte/hibyte, Mode 3 (square wave), 16bit binary
   // 00  = Select counter 0 (counter divisor)
   // 11  = Command to read/write counter bits (low byte, then high
   //       byte, in sequence).
   // 011 = Mode 3 - square wave.
   // 0   = Binary counter 16 bits (instead of BCD counter).
   asm out PTI_MODE,al

   //unsigned long spd = 1193182/60;= 19886;
   // The clock we're dealing with here runs at 1.193182mhz, so we
   // just divide 1.193182 by the number of triggers we want per
   // second to get our divisor.

   //asm mov al,255 //spd lo-byte
   //asm out PTI_CH0,al
   //asm mov al,255 //spd  hi-byte
   //asm out PTI_CH0,al
   // Set divisor low byte.
    outp(0x40, (byte)(c & 0xff));

    // Set divisor high byte.
    outp(0x40, (byte)((c >> 8) & 0xff));


   //set interrupt
   Set_speaker_handler();
}

/////////////////////////////////////////////////////////
// Disable speaker
/////////////////////////////////////////////////////////
void SPEAKER_Deinit(void){
	asm cli

   musicPlaying = 0;
   soundPlaying = 0;

	asm in al, 61h        //Disable speaker
	asm and al, 252
	asm out 61h, al

	//reset timer
	asm mov al,0x36
	asm out PTI_MODE,al

   // The clock we're dealing with here runs at 1.193182mhz, so we
    // just divide 1.193182 by the number of triggers we want per
    // second to get our divisor.
	asm mov al,0xFF
	asm out PTI_CH2,al
   asm mov al,0xFF
	asm out PTI_CH2,al

	Reset_speaker_handler();
	asm sti
}

/////////////////////////////////////////////////////////
// Stop speaker
/////////////////////////////////////////////////////////
void SPEAKER_StopMusic(void){
	// mute speaker
   asm in al, 61h        //Disable speaker
	asm and al, 252
	asm out 61h, al

   speakerMusicOffset = 0;
   musicPlaying = 0;
   musicNonStopPlaying = 0;
	soundPlaying = 0;
}

/////////////////////////////////////////////////////////
// Pause speaker
/////////////////////////////////////////////////////////
void SPEAKER_PauseMusic(void){
	// mute speaker
   asm in al, 61h        //Disable speaker
	asm and al, 252
	asm out 61h, al

   musicPlaying = 0;
   musicNonStopPlaying = 0;
	soundPlaying = 0;
}

/////////////////////////////////////////////////////////
// Play speaker
/////////////////////////////////////////////////////////
void SPEAKER_PlaySound(byte sound){//77.556
	switch(sound){
   	case 1: //Menu sound
      	speakerSoundSize = sizeof(speakerMenu);
      	speakerSFX = &speakerMenu[2];
      	break;
      case 2: //Select sound
      	speakerSoundSize = sizeof(speakerSelect);
      	speakerSFX = &speakerSelect[2];
      	break;
      case 3: //Crash sound
      	speakerSoundSize = sizeof(speakerCrash);
      	speakerSFX = &speakerCrash[2];
      	break;
      case 4: //Jump sound
      	speakerSoundSize = sizeof(speakerJump);
      	speakerSFX = &speakerJump[2];
      	break;
      case 5: //Get item sound
      	speakerSoundSize = sizeof(speakerGetItem);
      	speakerSFX = &speakerGetItem[2];
      	break;
      default:
      	speakerSoundSize = sizeof(speakerMenu);
      	speakerSFX = &speakerMenu[2];
      	break;
   }

   speakerSoundOffset = 0;
   soundPlaying = 1;

}

/////////////////////////////////////////////////////////
// Play music
/////////////////////////////////////////////////////////
void SPEAKER_PlayMusic(void){//77.556
	if(musicLoaded){
   	musicPlaying = 1;
   }
}

/////////////////////////////////////////////////////////
// Play non stop music
/////////////////////////////////////////////////////////
void SPEAKER_PlayNonStopMusic(void){//77.556
	if(musicLoaded){
   	musicNonStopPlaying = 1;
   }
}

/////////////////////////////////////////////////////////
// Load music
/////////////////////////////////////////////////////////
void SPEAKER_LoadMusic(byte song){
	FILE *fsong;
   int count;
   byte data;

	// Check if there was a song already loaded
   if(musicLoaded){ Error("Music already loaded ",0,0); } //SPEAKER_UnloadMusic(); }

 	switch(song){
   	case 1:
         // Open file
   		fsong = fopen("SONG1.DAT","rb");
         if(!fsong) Error("Can't find ","SONG1.DAT",0);
         break;
      case 2:
         fsong = fopen("SONG2.DAT","rb");
         if(!fsong) Error("Can't find ","SONG2.DAT",0);
      	break;
      case 3:
         fsong = fopen("SONG3.DAT","rb");
         if(!fsong) Error("Can't find ","SONG3.DAT",0);
      	break;
   	case 4:
      	fsong = fopen("SONG4.DAT","rb");
         if(!fsong) Error("Can't find ","SONG4.DAT",0);
         break;
      case 5:
      	fsong = fopen("SONG5.DAT","rb");
         if(!fsong) Error("Can't find ","SONG5.DAT",0);
         break;
      default:
      	fsong = fopen("SONG1.DAT","rb");
         if(!fsong) Error("Can't find ","SONG1.DAT",0);
         break;
   }

   // transfer song to buffer
   count = 0;
   while(count < 32000 ){
   	// get data
      if(fread(&data, sizeof(byte), 1, fsong)){
      	music.sdata[count] = data;
      	count++;
      } else { // end of file
      	//sprintf(error1, "%d", count);
		   //sprintf(error2, "%d", music.sdata[count]);
 			//Error("music eof found",error1, error2);
      	break;
      }
   }
   music.size = count-1;
   music.offset = 0;
   musicBufferIndex = 0;
   musicLoaded = 1;
   fclose(fsong);

   //sprintf(error1, "%d", count);
   //sprintf(error2, "%d", music.sdata[100]);
   //Error("music size",error1, error2);

}

/////////////////////////////////////////////////////////
// Unload music
/////////////////////////////////////////////////////////
void SPEAKER_UnloadMusic(void){
   SPEAKER_StopMusic();
	musicLoaded = 0;
}


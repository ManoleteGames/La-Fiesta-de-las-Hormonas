/***********************
*  PC Speaker functions
************************/

#include "source\engine\engine.h"

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


int speakerPlaying = 0;
int speakerOffset = 0;
byte *speakerSFX;
byte speakerSize = 16;


byte Speaker_Select[16] = {90,80,70,60,50,30,10,5,10,30,50,60,70,60,50,30};
byte Speaker_Crash[16] = {69,3,120,32,39,200,20,60,16,106,12,87,8,70,32,60};
byte Speaker_Jump[16] = {30,35,40,43,44,45,46,47,48,49,50,51,52,53,54,55};
byte Speaker_Get_Item[16] = {69,70,71,72,69,64,58,40,30,12,12,16,20,70,32,60};
byte Speaker_Get_Item_Adlib[] = {0xC8,0xF2,0x00,0x10,0xE6,0xC4,0x4C,0x40,0x0A,0x02,0x00};

int speakerNote[96] = {
	//Note		C    C#     D    D#     E     F    F#     G    G#     A    A#     B
	//Octave
	/*0	*/	65535,65535,65535,62799,56818,54235,51877,49716,45892,44192,41144,38490,
	/*1	*/	36157,34091,32248,30594,29102,27118,25939,24351,22946,21694,20572,19245,
	/*2	*/  18357,17292,16345,15297,14551,13715,12969,12175,11473,10847,10286, 9701,
	/*3	*/  9108 ,8584 ,8117 ,7698 ,7231 ,6818 ,6450 ,6088 ,5736 ,5424 ,5121 , 4870,
	/*4	*/  4554 ,4308 ,4058 ,3837 ,3616 ,3419 ,3225 ,3044 ,2875 ,2712 ,2560 , 2415,
	/*5	*/ 	2281 ,2154 ,2033 ,1918 ,1811 ,1709 ,1612 ,1522 ,1436 ,1356 ,1280 ,1208 ,
	/*6	*/ 	1141 ,1076 ,1015 ,959  ,898  ,854  ,806  ,761  ,718  ,678  ,640  ,604  ,
	/*7	*/ 	570  ,538  ,508  ,479  ,452  ,427  ,403  ,380  ,359  ,339  ,320  ,302  ,
};

void SpeakerDisable(void);

/////////////////////////////////////////////////////////
// Interrupt speaker handler declaration
/////////////////////////////////////////////////////////
void interrupt (*old_speaker_handler)(void);
void interrupt Speaker_handler(void){
	byte counter;
	int note;
	asm cli
	if (speakerPlaying == 1){
		if (speakerOffset != speakerSize){
			counter = speakerSFX[speakerOffset];
			note = speakerNote[counter]; // calculated frequency (1193180/Value)
			if (counter){
				asm mov ax, note
				asm out 42h,al
				asm mov al,ah
				asm out 42h,al
				speakerOffset++;
			} else speakerOffset = speakerSize;

		} else {
			speakerPlaying = 0;
			SpeakerDisable();
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
   old_speaker_handler = getvect(SPEAKER_IRQ); // Save old keyb irq
   setvect(SPEAKER_IRQ,Speaker_handler); // Set interrupt x to interrupt handler function
}

/////////////////////////////////////////////////////////
// Reset speaker handler
/////////////////////////////////////////////////////////
void Reset_speaker_handler(void){
   setvect(SPEAKER_IRQ,old_speaker_handler); // Set interrupt x to interrupt handler function
}

/////////////////////////////////////////////////////////
// Disable speaker
/////////////////////////////////////////////////////////
void SpeakerDisable(){
	asm cli
	asm in al, 61h        //Disable speaker
	asm and al, 252
	asm out 61h, al

	//reset timer
	asm mov al,0x36
	asm out 0x43,al
	asm mov al,0xFF
	asm out 0x42,al
	asm out 0x42,al
	//outportb(0x43, 0x36);
	//outportb(0x40, 0xFF);	//lo-byte
	//outportb(0x40, 0xFF);	//hi-byte
	Reset_speaker_handler();
	asm sti
}

/////////////////////////////////////////////////////////
// Play speaker
/////////////////////////////////////////////////////////
void PlaySpeaker_SFX(byte *note_array){//77.556
	//unsigned long spd = 1193182/60;= 19886;
	//if (LT_PC_Speaker_Playing == 0) {
	speakerPlaying = 0;
		asm in al, 61h			//Enable speaker
		asm or al, 3
		asm out 61h, al
		asm mov al, 0B6h
		asm out 43h,al
		speakerPlaying = 1;
		speakerOffset = 0;
		speakerSFX = &note_array[0];

		//set timer
		asm mov al,0x36
		asm out 0x43,al
		asm mov al,174	//spd % 0x100 lo-byte
		asm out 0x40,al
		asm mov al,77	//spd / 0x100 hi-byte
		asm out 0x40,al
		//set interrupt
		//setvect(0x1C, SpeakerSFX_Player);		//interrupt 1C not available on NEC 9800-series PCs.
   	Set_speaker_handler();

	//}
}



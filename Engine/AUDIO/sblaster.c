/***********************
*  Sound blaster functions
************************/

#include "source\engine\engine.h"

unsigned int baseAddress; //Sound Blaster base address
unsigned int version;     // DSP version
unsigned char loDMA; // DMA Channel
unsigned char hiDMA; // DMA Channel
unsigned char irq;   // IRQ
int playing;

///////////////////////////////////////////
// Set port address
///////////////////////////////////////////
void SB_SetAddress(unsigned int addr){
 	baseAddress = addr;
}

///////////////////////////////////////////
// Set low DMA (8bit)
///////////////////////////////////////////
void SB_SetLoDMA(unsigned char dma){
 	loDMA = dma;
}

///////////////////////////////////////////
// Set high DMA (16bit)
///////////////////////////////////////////
void SB_SetHiDMA(unsigned char dma){
 	hiDMA = dma;
}

///////////////////////////////////////////
// Set IRC
///////////////////////////////////////////
void SB_SetIRQ(unsigned char i){
 	irq = i;
}

///////////////////////////////////////////
// Read a byte from the DSP (Digital Signal Processor) on the Sound Blaster
///////////////////////////////////////////
unsigned char ReadDSP (void)
{
	while (!(inportb (baseAddress + 0xE) & 0x80)){
   	// do nothing, just wait
   }
   return (inportb (baseAddress + 0xA));
}

///////////////////////////////////////////
// Send a byte to the DSP (Digital Signal Processor) on the Sound Blaster
///////////////////////////////////////////
void WriteDSP (unsigned char Value)
{
  	//Wait for the DSP to be ready to accept data
  	while ((inportb (baseAddress + 0xC) & 0x80) == 0x80){
   	// do nothing, just wait
  	}
  	//Send byte
  	outportb (baseAddress + 0xC, Value);
}

///////////////////////////////////////////
// Returns the version number of the DSP.
///////////////////////////////////////////
void DSPVersion (void)
{
  WriteDSP (0xE1);
  version = ReadDSP();
}

///////////////////////////////////////////
// Checks to see if a Sound Blaster exists at a given address, returns
// true if Sound Blaster found, false if not.
///////////////////////////////////////////
char ResetDSP(unsigned int addr)
{
  //Reset the DSP
  outportb (addr + 0x6, 1);
  delay(10);
  outportb (addr + 0x6, 0);
  delay(10);
  //Check if reset was succesfull
  if (((inportb(addr + 0xE) & 0x80) == 0x80) && (inportb (addr + 0xA) == 0xAA)) {
    //DSP was found
    //baseAddress = addr;
    return (1);
  } else
    //No DSP was found
    return (0);
}

/////////////////////////////////////////////////////////
// Check if Sound Blaster sound card is present
// - returns: 0: No card; 1: Card detected
/////////////////////////////////////////////////////////
byte SB_Present(void){

   int i;
   char *blaster;

   // Find address port avaliable
   if( ResetDSP (0x220) ) { baseAddress = 0x220; }
   if( ResetDSP (0x230) ) { baseAddress = 0x230; }
   if( ResetDSP (0x240) ) { baseAddress = 0x240; }
   if( ResetDSP (0x250) ) { baseAddress = 0x250; }
   if( ResetDSP (0x260) ) { baseAddress = 0x260; }
   if( ResetDSP (0x280) ) { baseAddress = 0x280; }
   if( baseAddress == 0) { return 0; }

   // Check sound blaster type
   //There are several different type of Sound Blaster
  	// 0x01 - Sound Blaster (8 bit)
  	// 0x02 - Sound Blaster 1.5 (8 bit)
	// 0x02 - Sound Blaster 2.0 (8 bit)
 	// 0x03 - Sound Blaster Pro 1 (8 bit)
 	// 0x03 - Sound Blaster Pro 2 (8 bit)
  	// 0x04 - Sound Blaster 16/ASP/AWE 32/AWE 64 (16 bit)
   DSPVersion();
   if( version == 0) { return 0; }

   blaster = getenv("BLASTER");

   // Get DMA channel
   for(i=0;i< strlen(blaster);i++){
   	if(blaster[i] == 'D'){ loDMA = blaster[i + 1] - '0'; }
   }
   if( loDMA == 0) { return 0; }

   // Get IRQ channel
   for(i=0;i< strlen(blaster);i++){
   	if(blaster[i] == 'I'){
   		if(blaster[i + 2] == ' '){
         	irq = blaster[i + 1] - '0';
         }
         else{
         	irq = (blaster[i+1]-'0')*10 + blaster[i+2]-'0';
         }
      }
   }
   if( irq == 0) { return 0; }

   // This means all data has been found, so sound blaster is here
	// Print data
   switch(version)
   {
     	case 0x01:
	   	printf(" - Sound Blaster 1.0 detected\n");
         break;
      case 0x02:
         printf(" - Sound Blaster >1.0 detected\n");
         break;
      case 0x03:
         printf(" - Sound Blaster pro detected\n");
         break;
      case 0x04:
         printf(" - Sound Blaster 16/ASP/AWE32 detected\n");
         break;
      default:
         printf(" - Unidentified Sound Blaster detected\n");
         break;
   }

   printf(" -- ADDR: %x\n", baseAddress);
   printf(" -- IRQ: %d\n", irq);
  	printf(" -- DMA Channel (8 bit): %d\n", loDMA);
   if(version>=4){
     	printf(" -- DMA Channel (16 bit): %d\n",hiDMA);
   }
   return 1;
}

/////////////////////////////////////////////////////////
// Initialize sound card
/////////////////////////////////////////////////////////
void SB_InitSoundCard(void){

}

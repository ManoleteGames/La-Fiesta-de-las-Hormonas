/***********************
*  EGA graphics functions
************************/

#include "source\engine\engine.h"

// Detects VSYNC
/////////////////////////////////////////////////////////
void EGA_Vsync(void){
	// pending...
}

/////////////////////////////////////////////////////////
// Check if EGA graphics card is present
// - returns: 0: No card; 1: EGA detected
/////////////////////////////////////////////////////////
byte EGA_Present(void){
	union REGS regs;

   byte cardPresent = 0;

  	// - INT 10,12 - Video Subsystem Configuration (EGA/VGA)
  	regs.h.ah=0x12;
  	regs.h.bh=0x10;
  	regs.h.bl=0x10;  // Return video configuration information
  	int86(0x10, &regs, &regs);

  	if (regs.h.bh == 0) {  // 0-Color mode; 1-mono mode
		printf(" - EGA card detected\n");
     	switch( regs.h.bl)
   	{
  	  		case 0x00:
        		printf(" -- 64k EGA memory\n");
            printf(" -- no compatible video card was detected\n");
     	   	break;
     		case 0x01:
     			printf(" -- 128k EGA memory\n");
            printf(" -- no compatible video card was detected\n");
        		break;
	     	case 0x02:
        		printf(" -- 192k EGA memory\n");
            printf(" -- no compatible video card was detected\n");
          	break;
	     	case 0x03:
       		printf(" -- 256k EGA memory\n");
            printf(" -- no compatible video card was detected\n");
            cardPresent = 1;
          	break;
	     	default:
	 			printf(" -- Unknown configuration %u \n", regs.h.bl);
      }
   }

   return cardPresent;
}

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Detects VSYNC
/////////////////////////////////////////////////////////
void CGA_Vsync(void){
	// pending...
}

/////////////////////////////////////////////////////////
// Check if CGA graphics card is present
// - returns: 0: No card; 1: CGA detected
/////////////////////////////////////////////////////////
byte CGA_Present(void){
	union REGS regs;

   byte cardPresent = 0;

   // Check if CGA is avaliable
   /// - INT 10,F - Get Video State
   regs.h.ah=0x0F;
   regs.h.bl=0x00;
   int86(0x10, &regs, &regs);

   switch( regs.h.al)
   {
   	case 0x00:
   		printf(" - CGA card detected\n");
      	printf(" -- 40x25 B/W text (CGA,EGA,MCGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
        	break;
      case 0x01:
     		printf(" - CGA card detected\n");
      	printf(" -- 40x25 16 color text (CGA,EGA,MCGA,VGA)\n");
       	printf(" -- no compatible video card was detected\n");
        	break;
      case 0x02:
     		printf(" - CGA card detected\n");
   		printf(" -- 80x25 16 shades of gray text (CGA,EGA,MCGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
        	break;
      case 0x03:
     		printf(" - CGA card detected\n");
   	  	printf(" -- 80x25 16 color text (CGA,EGA,MCGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
      	break;
      case 0x04:
   	case 0x05:
      	printf(" - CGA card detected\n");
   	  	printf(" -- 320x200 4 color graphics (CGA,EGA,MCGA,VGA)\n");
        	cardPresent = 1;
      	break;
      case 0x06:
      	printf(" - CGA card detected\n");
   	  	printf(" -- 640x200 B/W graphics (CGA,EGA,MCGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
        	break;
      case 0x07:
     		printf(" - MDA/HERC card detected\n");
      	printf(" -- 80x25 Monochrome text (MDA,HERC,EGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
        	break;
      case 0x08:
      	printf(" - PCjr card detected\n");
   	  	printf(" -- 160x200 16 color graphics (PCjr)\n");
        	printf(" -- no compatible video card was detected\n");
        	break;
      case 0x09:
     		printf(" - PCjr video card detected\n");
   		printf(" -- 320x200 16 color graphics (PCjr)\n");
        	printf(" -- no compatible video card was detected\n");
      	break;
      case 0x0A:
     		printf(" - PCjr video card detected\n");
   		printf(" -- 640x200 4 color graphics (PCjr)\n");
        	printf(" -- no compatible video card was detected\n");
      	break;
      case 0x11:
     		printf(" - MCGA video card detected\n");
   	  	printf(" -- 640x480 B/W graphics (MCGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
      	break;
      case 0x13:
     		printf(" - MCGA video card detected\n");
   		printf(" -- 320x200 256 color graphics (MCGA,VGA)\n");
        	printf(" -- no compatible video card was detected\n");
      	break;
      default:
			printf(" -- Unknown configuration %u \n", regs.h.al);
        	printf(" -- no compatible video card was detected\n");
         break;
   }

   return cardPresent;
}
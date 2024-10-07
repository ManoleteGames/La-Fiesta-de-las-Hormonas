/**************************************************
  VGA graphics functions
    - Manages all the video issues about vga video card
    - Video memory allocation on UMA for VGA (320x200 256 colours)
		*** A0000h - FFFFFh ***** UMA
 		****** A0000h - AFFFFh ***** UMA>> EGA/VGA Buffer (64kb)
 		****** B0000h - B7FFFh ***** UMA>> MDA/HERCULES Monochrome video adapter (32kb)
 		****** B8000h - BFFFFh ***** UMA>> CGA/VGA Text mode (32kb)           
      ****** C0000h - FFFFFh ***** UMA>> ROM Code memory, BIOS, etc... (256kb)
		********* C0000h - C7FFFh ***** UMA>> EGA/VGA BIOS rom
		************ C4000**************** UMA >> Video adapter ROM space
		************ C6000**************** UMA >> PGA Communication (254 bytes)
 		********* C8000h - CFFFFh ***** UMA>> BIOS, etc...
      ************ C8000h ************** UMA >> Hard disk adapter bios ROM (16kb)
      ************ C8000:5h ************ UMA >> XT Hard disk ROM format, AH=Drive, AL=Interleave
 		********* D0000h - DFFFFh ***** UMA>> BIOS >> Free.
 		************ D0000h - D4999h ***** UMA>> Cluster adapter BIOS ROM (32kb)
 		************ D5000h - D5BFFh ***** UMA>> Free>> Spare.
 		************ D5C00h - D83FFh ***** UMA>> Free>> Spare.
 		************ D8400h - DCBFFh ***** UMA>> Free>> Spare
 		************ DCC00h - D????h ***** UMA>> Free>> Fonts
 		********* E0000h - EFFFFh ***** UMA>> Expansion ROM space (hardwired on AT+)(64kb) & PS/2 System ROM (thru F000) (128kb)
 		********* F0000h - FFFFFh ***** UMA>> Motherboard
 		************ F0000h - F3FFFh ***** UMA>> System monitor ROM
 		************ F4000h - F5FFFh ***** UMA>> System expansion ROM
 		************ F6000h - F7FFFh ***** UMA>> IBM ROM BASIC (AT)
 		************ F8000h - FBFFFh ***** UMA>> PCjr software cartridge override address
 		************ FC000h - FEFFFh ***** UMA>> BIOS ROM
 		************ FF000h - FFA60h ***** UMA>> System ROM
 		************ FFA60:E ************ UMA>>	ROM graphics character table
 		************ FFFFF:0 ************ UMA>>	ROM bootstrap code
 		************ FFFFF:5 ************ UMA>> (8 bytes)	ROM date (not applicable for all clones)
 		************ FFFFF:E ************ UMA>>	(byte)	ROM machine id	(see MACHINE ID)

       0xD500,0xD518,0xD530,0xD548,0xD560,0xD578,0xD590,0xD5A8 - 8x8 sprite[0..7]
//       0xD5C0,0xD610,0xD660,0xD6B0,0xD700,0xD750,0xD7A0,0xD7F0 - 16x16 sprite[8..15]
//       0xD840,0xD960,0xDA80,0xDBA0 - 32x32 sprite[16..19]
//       0xDCC0 - Font
//       0xE0C0 - Tiles
//			** UMA distribution
//
//		- Palette colors
// 		[0..207]>> Colors reserved for tiles and images
//			[208..256]>> Colors reserved for sprites                     
//




************************/

#include "source\engine\engine.h"
#include "source\engine\video\vga.h"

// Global variables
// Video memory allocation addresses
byte *VGA=(byte *)0xA0000000L; // VGA buffer address

byte vga_tempPalette[256*3]; // temporary palette, just for fade in/out

// Dimensions of each page and offset
static word vga_width = 352;
static word vga_height = 240;
static word vga_visible_width = 320;
static word vga_visible_height = 200;

// Page flipping variables
// - Page 0 is reserved for window
word vga_page[3] = {0,64,304};
unsigned char vga_loadingPalette[] = { //Loading transition palette
	0x00,0x00,0x00,	//colour 0
	0xff,0xff,0xff	   //colour 1
};

// Old handler
void interrupt (*old_loading_handler)(void);

// variables for mode 13
byte pix;
byte p[4] = {0,2,4,6};

word vga_sprites[21] = {//// Sprite addresses in VRAM D500, pos 21 is reserved for player sprite background
		//8x8
		0xBA00,0xBA18,0xBA30,0xBA48,0xBA60,0xBA78,0xBA90,0xBAA8,
		//16x16
		0xBAC0,0xBB10,0xBB60,0xBBB0,0xBC00,0xBC50,0xBCA0,0xBCF0,
		//32x32
		0xBD40,0xBE60,0xBF80,0xC0A0,0xC1C0
	};

/////////////////////////////////////////////////////////
// Detects VSYNC
/////////////////////////////////////////////////////////
void VGA_Vsync(void){
	asm mov		dx,VGA_INPUT_STATUS
	WaitVsync:
	asm in      al,dx
	asm test    al,VGA_VRETRACE
	asm jz		WaitVsync
	WaitNotVsync:
	asm in      al,dx
	asm test    al,VGA_VRETRACE
	asm jnz		WaitNotVsync
}

/////////////////////////////////////////////////////////
// Check if VGA graphics card is present
// - returns: 0: No card; 1: VGA detected
/////////////////////////////////////////////////////////
byte VGA_Present(void){
	union REGS regs;

   byte cardPresent = 0;

   // Check if VGA is avaliable
   //  - INT 10,1A - Video Display Combination (VGA)
	regs.h.ah=0x1A;
	regs.h.al=0x00;
	regs.h.bl=0x32;
	int86(0x10, &regs, &regs);

	if (regs.h.al == 0x1A) // 0x1A - means a valid request in AH
   {
		printf(" - VGA card detected\n");

      switch( regs.h.bl)
      {
      	case 0x00:
         	printf(" -- No display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x01:
         	printf(" -- MDA with monochrome display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x02:
         	printf(" -- CGA with color display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x04:
         	printf(" -- EGA with color display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x05:
         	printf(" -- EGA with monochorme display\n");
            printf(" -- no compatible video card was detected\n");
            break;
      	case 0x06:
         	printf(" -- Professional graphics controller\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x07:
         	printf(" -- VGA with analog monochorme display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x08:
         	printf(" -- VGA with analog color display \n");
            cardPresent = 1;
            break;
         case 0x0A:
         	printf(" -- MCGA with digital color display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x0B:
         	printf(" -- MCGA with analog monochorme display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         case 0x0C:
         	printf(" -- MCGA with analog color display\n");
            printf(" -- no compatible video card was detected\n");
            break;
         default:
				printf(" -- Unknown configuration %u \n",regs.h.bl );
            printf(" -- no compatible video card was detected\n");
      }
   }

   return cardPresent;
}

/////////////////////////////////////////////////////////
// Set text mode
/////////////////////////////////////////////////////////
void VGA_TextMode(void){
	union REGS regs;

   regs.h.ah = 0x00;
	regs.h.al = VGA_TEXT_MODE;
	int86(VGA_VIDEO_INT, &regs, &regs);
}

/////////////////////////////////////////////////////////
// Initialize VGA (first things first)
//  - Set unchained mode at 320x200 256 color
//  - Set dimensions at 352x240 to keep space arround
//    each screen
//  - Set UMA memory addresses for resources
/////////////////////////////////////////////////////////
void VGA_InitVideoCard(void){
   union REGS regs;

   system("cls"); // Clear screen

   // Make a fade out before change nothing
   //Fade_out_VGA();
   //ClearPalette_VGA();           // Clear palette
   //memset(VGA,0x00,(320*200)/4); // Clear VRAM

 	//SET MODE X (unchained mode)(tweak 13h)
	// -- This mode allows to access 256kb of video memory
   //    instead of 64kb.
   // -- After this, video mode exists in 4 planes of 64kb
   // -- Plane 0 contains pixels 0, 4, 8, etc..
   // -- Plane 1 contains pixels 1, 5, 9, etc..
   // -- Plane 2 contains columns 2, 6, 10, etc..
   // -- Plane 3 contains columns 3, 7, 11, etc..
   // -- ie. pixel (5,7) >> Plane 1 offset (320*7+5)/4 = 561
   // -- Instead of select typical 320x200 dimensions we
   //    will set 352*240 to keep some space arroung the
   //    visible zone. It will be necessary for smooth
   //    scrolling issues, but we will lose 1 page
   //    for animations and flip issues

   // Set VGA 256 color mode
	regs.h.ah = 0x00;
	regs.h.al = VGA_MODE_13;
	int86(VGA_VIDEO_INT, &regs, &regs);

   // Disable Chain-4
  	outportb(VGA_SEQ_INDEX,  VGA_MEMORY_MODE);       // 0x04>>Port 0x3C4. Selects memory mode register (bit3.Chain 4;bit2.Odd/even disable;bit1.Ext.mem.)
	outportb(VGA_SEQ_DATA,   0x06);                  // (0x06>>Data) Turns off chain-4 mode, disables odd/even host memory addressing and sets extended mem.
   // set all planes
  	outportb( VGA_SEQ_INDEX, VGA_MAP_MASK );
  	outportb( VGA_SEQ_DATA, 0xFF );
   // Disable doubleword mode
	outportb(VGA_CRTC_INDEX,VGA_CRTC_ULINE_LOC);// turn off long mode (bit6=0>No doubleword to address video)
	outportb(VGA_CRTC_DATA, 0x00);
	// Disable word mode
   outportb(VGA_CRTC_INDEX,VGA_CRTC_MODE_CONTROL);       // bit7>SyncEnable;bit6>turn on byte mode;bit5>address wrap selected;bit1>map display address 14;bit0>map display address 13
	outportb(VGA_CRTC_DATA, 0xe3); 						// 0b1110 0011

	// Turn off write protect to CRTC registers
   outportb(VGA_CRTC_INDEX,VGA_CRTC_RETRACE_END);
	outportb(VGA_CRTC_DATA, 0x00);

   // New vertical total=523 lines, bits 0-7 (see also overflow register). Vertical total (10 0000 1011 = 523)
   outportb(VGA_CRTC_INDEX,VGA_CRTC_V_TOTAL_REG);
   outportb(VGA_CRTC_DATA, 0x0B);

   // New vertical start=scanline 441, bits 0-7 (see also overflor register). Total ( 1B9 = 441)
   outportb(VGA_CRTC_INDEX,VGA_CRTC_V_START_REG);
   outportb(VGA_CRTC_DATA, 0xB9);

   // New Vertical display end=scanline 399, bits 0-7  (see also overflor register). Total ( 18F = 399)
   outportb(VGA_CRTC_INDEX,VGA_CRTC_V_DISPLAY_END);
   outportb(VGA_CRTC_DATA, 0x8F);

   // New Vertical blanking start=scanline 440, bits 0-7 (see also overflor register). Total ( 1B8 = 440)
   outportb(VGA_CRTC_INDEX,VGA_CRTC_V_BLANK_START);
   outportb(VGA_CRTC_DATA, 0xB8);

   // New Vertical blanking end= 226 scanlines after, bits 0-6. Total (E2 = 226)
   outportb(VGA_CRTC_INDEX,VGA_CRTC_V_BLANK_END);
   outportb(VGA_CRTC_DATA, 0xE2);

   // New overflow value (updates most significative bits of previous registers)
   outportb(VGA_CRTC_INDEX,VGA_CRTC_OVERFLOW_REG);
   outportb(VGA_CRTC_DATA, 0x3E);    //0b0011 1110

   // Turn back on protection and set new vertical retrace end=5 scanlines
   outportb(VGA_CRTC_INDEX,VGA_CRTC_RETRACE_END);
   outportb(VGA_CRTC_DATA, 0x85); // 0b1000 0101

   asm STI

	//delete vram
	asm mov ax,0xA000
	asm mov es,ax
	asm mov di,0			//es:di destination
	asm mov al,0
	asm mov cx,65535
	asm rep STOSB 			//Store AL at address ES:DI.

   // logical width = screen_width / 4 because mode x active
   vram_LogicalWidth = vga_width >> 2 ; // 354 / 4 = 88

	// Set offset  (Offset = Width / ( PixelsPerAddress * MemoryAddressSize * 2 ) > Offset = 88/2 = 44
   //	-- where with is not the real pixel with (352) but logical with = 352/4 = 88  for mode x
   //word_out(VGA_CRTC_INDEX,VGA_CRTC_OFFSET_REG,44);
   outportb(VGA_CRTC_INDEX,VGA_CRTC_OFFSET_REG);
   outportb(VGA_CRTC_DATA, 44);

   // Turn back on protection and set new vertical retrace end=14 scanlines
   outportb(VGA_CRTC_INDEX,VGA_CRTC_RETRACE_END);
   outportb(VGA_CRTC_DATA, 0x8e); // 0b1000 0101

   // Select memory map 00b -- A0000h-BFFFFh (128K region)
   // Disable Chain-4
   // Disable alpha
   outportb(VGA_GC_INDEX,0x06);
   outportb(VGA_GC_DATA, 0x01); // 0b0000 0001

   // Set VRAM addresses for fonts
   vram_Font = 0xB000; //0xB000; //0xAE00; //0xDCC0;


   // Set VRAM addresses for tiles
   vram_Tiles = 0xB410; //0xE000; //0xE0C0; //0xDCC0; //0xE0C0;

 	// Set sprites background vram address
   vram_SpritesBack = 0xD400; //0xE500; //0xE000; //0xB410;

   // Sets the scroll to page 1
   VGA_SetPage(1);

   VGA_Set_Window();
}

/////////////////////////////////////////////////////////
// Set palette
/////////////////////////////////////////////////////////
void VGA_SetPalette(unsigned char *pal){
	int i;
	outp(VGA_PALETTE_INDEX,0);
	for(i=0;i<256*3;i++){
   	outp(VGA_PALETTE_DATA,pal[i]); // Set the 256 palette colors
   }
}

/////////////////////////////////////////////////////////
// Fade in
// - Restores the saved palette (previously saved on Fade_out func
/////////////////////////////////////////////////////////
void VGA_Fade_in(void){
	int i = 0;
	unsigned char *pal = vga_tempPalette; // Palette of last image loaded
	memset(vga_tempPalette,256*3,0x00);//All colours black

	//Fade in
	asm mov	dx,VGA_PALETTE_INDEX //003c8h
	asm mov al,0
	asm out	dx,al
	while (i < 14){//SVGA FAILED with 15
		asm lds si,pal		//Get palette address in ds:si
		asm les di,pal		//Get palette address in es:di
		asm mov dx,VGA_PALETTE_DATA //003c9h //Palete register
		asm mov cx,256*3
		asm mov bx,0
		fade_in_loop:
			asm LODSB //Load byte from DS:SI into AL, then advance SI
			asm cmp	al,byte ptr palette[bx]
			asm jae	pal_is_greater
			asm add al,4
			pal_is_greater:
			asm STOSB //Store byte in AL to ES:DI, then advance DI
			asm out dx,al
			asm inc bx
			asm loop fade_in_loop

		i ++;
		asm mov		dx,VGA_INPUT_STATUS
		WaitNotVsync:
		asm in      al,dx
		asm test    al,VGA_DISPLAY_ENABLE
		asm jnz		WaitNotVsync
		WaitVsync:
		asm in      al,dx
		asm test    al,VGA_VRETRACE
		asm jz		WaitVsync


	}
	VGA_SetPalette(palette);
}

/////////////////////////////////////////////////////////
// Fade out
// - Save the current palette and fade it out
/////////////////////////////////////////////////////////
void VGA_Fade_out(void){
	int i = 0;
	unsigned char *pal = vga_tempPalette; // temporary palette

	//Fade to black
	asm mov	dx,VGA_PALETTE_INDEX //003c8h
	asm mov ax,0
	asm out	dx,al
	while (i < 15){
		asm lds si,pal		//Get palette address in ds:si
		asm les di,pal		//Get palette address in es:di
		asm mov dx,VGA_PALETTE_DATA //003c9h //Palete register
		asm mov cx,256*3
		asm mov bx,0
		fade_out_loop:
			asm LODSB //Load byte from DS:SI into AL, then advance SI
			asm cmp al,0
			asm jz	pal_is_zero
			asm sub al,4
			pal_is_zero:
			asm STOSB //Store byte in AL to ES:DI, then advance DI
			asm out dx,al
			asm loop fade_out_loop
		i ++;
		//Wait Vsync
		asm mov		dx,VGA_INPUT_STATUS
		WaitNotVsync:
		asm in      al,dx
		asm test    al,VGA_DISPLAY_ENABLE
		asm jnz		WaitNotVsync
		WaitVsync:
		asm in      al,dx
		asm test    al,VGA_VRETRACE
		asm jz		WaitVsync
	}
}

/////////////////////////////////////////////////////////
// Load PCX image
// - file := filename of .DAT file
// - dat_string := filename of .PCX file inside .DAT file
// - page := VRAM page destination (1:=first page; 2:=second page)
/////////////////////////////////////////////////////////
void VGA_LoadImage(char *file,char* dat_string, word page){
	dword VGA_index = 0;
	word h = 0;
	word x = 0;
	word y = 0;
	byte plane = 0;
	dword buffer_index = 0;
	dword offset_Image = 0;

   // Check page number
   if((page < 1 ) || (page > 2)){
   	sprintf(error1, "%d", page);
   	Error("Trying to load image on wrong page",dat_string, error1);
   }

   // Load image on temporary buffer (tempdata1 & tempdata2)
   LoadImage_PCX(file,dat_string);

	// Start writing VRAM on unchained mode
	for (plane = 0; plane < 4; plane ++){
		// select plane
		asm CLI //disable interrupts
		outp(VGA_SEQ_INDEX, VGA_MAP_MASK);
		outp(VGA_SEQ_DATA, 1 << plane);

      // Sets index of VGA memory
      VGA_index = (vga_page[page]*vram_LogicalWidth);
      buffer_index = plane;

      for (y = 0; y < 200; y++){
      	for(x = 0; x < 80; x++){ // 80 because on unchained mode we will write 4 bytes at time, that means 80*4 = 320
         	VGA[VGA_index] = tempdata1[buffer_index];
            VGA_index++;
            buffer_index +=4;
         }
         VGA_index+=8; //Point to the begining of the scanline (each scanline has 8 non visible bytes)
      }

      if(buffer_index > 64003){
  	      sprintf(error1, "%ld", buffer_index);
      	Error("Buffer overrun loading image file (max = 64003)", dat_string, error1); }
      if((VGA_index < 0) || (VGA_index > ((vga_page[2]+200) * 88))){ //42240
      	sprintf(error1, "%ld", VGA_index);
      	Error("VGA index out of range loading image file (max = ((vga_page[2]+200) * 88) )", file, dat_string);
      }

      asm STI //Re enable interrupts
   }
}

/////////////////////////////////////////////////////////
// Load Panel PCX image
// - file := filename of .DAT file
// - dat_string := filename of .PCX file inside .DAT file
// - Always load on page 0
// - Dimensions 320x64
/////////////////////////////////////////////////////////
void VGA_LoadPanelBackground(char *file,char* dat_string){
	dword VGA_index = 0;
	word h = 0;
	word x = 0;
	word y = 0;
	byte plane = 0;                                 
	dword buffer_index = 0;
	dword offset_Image = 0;

   // Load image on temporary buffer (tempdata1 & tempdata2)
   LoadImage_PCX(file,dat_string);

	// Start writing VRAM on unchained mode
	for (plane = 0; plane < 4; plane ++){
		// select plane
		asm CLI //disable interrupts
		outp(VGA_SEQ_INDEX, VGA_MAP_MASK);
		outp(VGA_SEQ_DATA, 1 << plane);

      // Sets index of VGA memory
      VGA_index = 0;
      buffer_index = plane;

      for (y = 0; y < 64; y++){
      	for(x = 0; x < 80; x++){ // 80 because on unchained mode we will write 4 bytes at time, that means 80*4 = 320
         	VGA[VGA_index] = tempdata1[buffer_index];
            VGA_index++;
            buffer_index +=4;
         }
         VGA_index+=8; //Point to the begining of the scanline (each scanline has 8 non visible bytes)
      }

      if(buffer_index > 64003){
  	      sprintf(error1, "%ld", buffer_index);
      	Error("Buffer overrun loading image file (max = 64003)", dat_string, error1); }
      if((VGA_index < 0) || (VGA_index > ((vga_page[2]+200) * 88))){ //42240
      	sprintf(error1, "%ld", VGA_index);
      	Error("VGA index out of range loading image file (max = ((vga_page[2]+200) * 88) )", file, dat_string);
      }

      asm STI //Re enable interrupts
   }
}

/////////////////////////////////////////////////////////
// Hardware scrolling (private)
// -
/////////////////////////////////////////////////////////
void VGA_HardwareScrolling(void){

	word vram_pointer;

	// Scroll hardware limitation
   //if(scroll_x < 0) { scroll_x = 0; }
  	//if(scroll_x > 640) { scroll_x = 640; }
	//if(scroll_y > vga_page[2]){ scroll_y = vga_page[2]; }

	vram_pointer = scroll_y;

   // Calculate pointer
	vram_pointer*=vram_LogicalWidth;
   vram_pointer += scroll_x>>2;

	//change scroll registers:
	asm mov dx,VGA_CRTC_INDEX
	asm mov cl,8
	asm mov ax,vram_pointer
	asm shl ax,cl
	asm or  ax,00Dh	//LOW_ADDRESS 0x0D
	asm out dx,ax	//(vram_pointer << 8) | 0x0D to VGA port
	asm mov ax,vram_pointer
	asm and ax,0FF00h
	asm or  ax,00Ch	//HIGH_ADDRESS 0x0C;
	asm out dx,ax	//(y & 0xFF00) | 0x0C to VGA port

   //The smooth panning magic happens here
	//disable interrupts
	asm cli

   //Wait Vsync
	asm mov		dx,VGA_INPUT_STATUS
	WaitNotVsync:
	asm in      al,dx
	asm test    al,08h
	asm jnz		WaitNotVsync
	WaitVsync:
	asm in      al,dx
	asm test    al,08h
	asm jz		WaitVsync

	asm mov		dx,VGA_INPUT_STATUS //Read input status, to Reset the VGA flip/flop
	pix = p[scroll_x & 3]; //VGA

   // Update the horizontal pixel panning register
	// - Attribute address register
   // -- bits 0..4 - Attribute address
   // -- bit 5 - PAS (palette address source)
	asm mov 		dx,VGA_AC_WRITE
	asm mov 		al,0x33 //0b0011 0011	 // Palette normal operation, Attribute addres = 13h (Horizontal pixel panning register)
	asm out 		dx,al
	asm mov 		al,byte ptr pix
	asm out 		dx,al

	//enable interrupts
	asm sti
}

/////////////////////////////////////////////////////////
// Sets visible page 1-2
// - Just moves the scroll to the predefined
//   position of page 1 or 2
/////////////////////////////////////////////////////////
void VGA_SetPage(int page){
	scroll_x = 0;
   scroll_y = vga_page[page];
   VGA_HardwareScrolling();
}

/////////////////////////////////////////////////////////
// Rotate palette
/////////////////////////////////////////////////////////
void VGA_RotatePalette(int index1, int index2, int speed){
	int i,j;
	int iterances,bytes,colors;
   int waitcount;
   int waitcounter;

   unsigned char auxColorR;
   unsigned char auxColorG;
   unsigned char auxColorB;

   int firstIndex = index1*3;
   int lastIndex = index2*3;
   bytes = lastIndex - firstIndex;
   colors = index2-index1;
   iterances =  index2 - index1;

   waitcount = 100 - speed;

   for(i=0; i<=iterances; i++){

   	// first thing first...save last index colour
	  	auxColorR = palette[lastIndex];
	  	auxColorG = palette[lastIndex+1];
	  	auxColorB = palette[lastIndex+2];

	   // rotate all colors
   	for(j=0; j<colors; j++){
			palette[lastIndex -(j*3)] 	   = palette[lastIndex -(j*3) -3];
      	palette[lastIndex -(j*3) + 1] = palette[lastIndex -(j*3) -2];
        	palette[lastIndex -(j*3) + 2] = palette[lastIndex -(j*3) -1];
	   }

   	// restore last index colour on first index
	   palette[firstIndex] = auxColorR;
	   palette[firstIndex+1] = auxColorG;
	   palette[firstIndex+2] = auxColorB;

		VGA_SetPalette(palette);

      waitcounter = 0;
	   while(waitcounter < waitcount)
   	{
   		waitcounter++;
      	VGA_Vsync();
   	}
   }
}

/////////////////////////////////////////////////////////
// Load font VGA
// load_8x8 fonts to VRAM (64 characters)
/////////////////////////////////////////////////////////
void VGA_LoadFont(char *file, char *dat_string){
	word VGA_index = 0;
	word w = 0;
	int h = 0;
	word ty = 0;
	word jx = 0;
	word x = 0;
	word y = 0;
	word tileX = 0;
	word tileY = 0;
	byte plane = 0;
	dword offset = 0;

   // load font
   LoadFont_BMP(file, dat_string);

	//COPY TO VRAM
	w = 16;
	h = 4;
	jx = 128+8;

	for (plane = 0; plane < 4; plane ++){
		asm CLI //disable interrupts so that loading animation does not interfere

		// select plane
		asm mov dx,03c4h
		asm mov ax,0F02h
		asm out dx,ax
		asm inc dx
		asm mov al,1
		asm mov cl,plane
		asm shl al,cl
		asm out	dx,al

		VGA_index = vram_Font;	//VRAM FONT ADDRESS

		//SCAN ALL TILES
		for (tileY = h; tileY > 0 ; tileY--){
			ty = (tileY<<3)-1;
			for (tileX = 0; tileX < w; tileX++){
				offset = plane + (ty*128) + (tileX<<3);
				//LOAD TILE
				x=0;
				for(y = 0; y < 16; y++){
					VGA[VGA_index] = (tempdata1[offset] + 252); //Font color from 252 to 255
					VGA_index++;
					offset +=4;
					x++;
					if (x == 2){
						x = 0;
						offset -= jx;
					}
				}
			}
		}
		asm STI //Re enable interrupts so that loading animation is played again
	}
}

/////////////////////////////////////////////////////////
// Load_16x16 tiles to VRAM
// - Maximum number of tiles on the tileset file =
/////////////////////////////////////////////////////////
void VGA_LoadTiles(char *file,char* dat_string){
	dword VGA_index = 0;
	word w = 0;
	word h = 0;
	word ty = 0;
	word x = 0;
	word y = 0;
	word tileX = 0;
	word tileY = 0;
	byte plane = 0;
	dword offset = 0;

   LoadTileset_PCX(file, dat_string);

	//COPY TO VGA VRAM
	w = tilesetWidth>>4;
	h = tilesetHeight>>4;

   for (plane = 0; plane < 4; plane ++){

		// select plane
		asm CLI //disable interrupts so that loading animation does not interfere

		outp(VGA_SEQ_INDEX, VGA_MAP_MASK);
		outp(VGA_SEQ_DATA, 1 << plane);
		VGA_index = vram_Tiles;

		//SCAN ALL TILES
		for (tileY = 0; tileY < h ; tileY++){
			ty = (tileY<<4);   // number of tile * 16 >> gets the pixel

			for (tileX = 0; tileX < w; tileX++){

            offset = plane + (ty*tilesetWidth) + (tileX<<4);  // offset of first pixel of tile

				//LOAD TILE
				x=0;
				for(y = 0; y < 64; y++){
					VGA[VGA_index] = tempdata1[offset];
					VGA_index++;
					offset +=4;
					x++;
					if (x == 4){
						x = 0;
                  offset = offset + tilesetWidth-16; // offset to the first pixel of next tile line
					}
				}
				if (VGA_index > 0xFFFF){
            	sprintf(error1, "%d", tileY * tileX);
               Error(" Error loading tileset, it is too big!", file,error1);
            	break; //Out of VRAM
            }
			}
			if (VGA_index > 0xFFFF){
         	sprintf(error1, "%d", tileY * tileX);
            Error(" Error loading tileset, it is too big!", file,error1);
         	break; //Out of VRAM
         }
		}
		asm STI //Re enable interrupts so that loading animation is played again
	}

	//Populate palettes for colour cycling, colours 136-200
	//cycle_palcounter = 0;
  	//cycle_palframe = 0;

   //Palette 1
	//memcpy(&cycle_paldata[0],&palette[200*3],8*3);
	//memcpy(&cycle_paldata[8*3],&palette[200*3],8*3);
	//Palette 2
	//memcpy(&cycle_paldata[16*3],&palette[200*3],8*3);
   //memcpy(&cycle_paldata[24*3],&palette[200*3],8*3);
   //Polulate palette for parallax, colours 176-239
	//memcpy(&parallax_paldata[0],&palette[136*3],64*3);
	//memcpy(&parallax_paldata[64*3],&palette[136*3],64*3);
}

/////////////////////////////////////////////////////////
// Print text
// - Each char is 8x8 px
// - panel: eliminates the current scroll to print text on panel
/////////////////////////////////////////////////////////
void VGA_PrintText(word x, word y, word lineLength, unsigned char *string){
	word fontAddress = vram_Font; // Pointer to font memory
	word screen_offset;
	byte datastring;
	word size = strlen(string);
	word i = 0;
	word charIndex = 0;
	word lwidth = vram_LogicalWidth-2;
	word lwidth2 = vram_LogicalWidth*7;
	word line_jump = (vram_LogicalWidth*8) - (lineLength*2);    // mal
	y = (y<<3);
   y += scroll_y;
	screen_offset = (y<<6)+(y<<4)+(y<<3);

	asm{
		push ds
		push di
		push si

		mov dx,VGA_SEQ_INDEX //dx = indexregister
		mov ax,0F02h	//INDEX = MASK MAP,
		out dx,ax 		//write all the bitplanes.
		mov dx,VGA_GC_INDEX //dx = indexregister
		mov ax,0008h
		out dx,ax

		//
		mov di,screen_offset
		mov ax,x
		shl ax,1
		add di,ax
		mov ax,0A000h
		mov ds,ax
		mov bx,size
	}

	printloop3:
	asm push bx
	datastring = string[i]; // Get current char
   // Filter chars > 96
	if (datastring > 96) datastring -=32;
	asm{
		mov	dx,word ptr datastring
		sub	dx,32
	}

	asm{
		mov	si,fontAddress;			//ds:si VRAM FONT TILE ADDRESS

		//go to desired tile
		mov	cl,4						//dx*16
		shl	dx,cl
		add	si,dx

		mov 	ax,0A000h
		mov 	es,ax						//es:di destination address
		mov	bx,lwidth

		//UNWRAPPED COPY 8x8 TILE LOOP
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		//END LOOP
		sub	di,lwidth2

	   mov 	ax,charIndex
	   inc	ax
	   mov	charIndex,ax
	   cmp	ax,lineLength
	   jne	no_jump_line

		add	di,line_jump
		mov 	charIndex,0
	}
	no_jump_line:
	i++;
	asm{
		pop 	bx
		dec	bx
		jnz	printloop3

		//END
		mov dx,VGA_GC_INDEX +1 //dx = indexregister
		mov ax,00ffh
		out dx,ax

		pop si
		pop di
		pop ds
	}
}

/////////////////////////////////////////////////////////
// Print text on screen 0 (window panel)
// - Each char is 8x8 px
// - Eliminates the current y scroll to print on panel
/////////////////////////////////////////////////////////
void VGA_PrintPanelText(word x, word y, word lineLength, unsigned char *string){
	word fontAddress = vram_Font; // Pointer to font memory
	word screen_offset;
	byte datastring;
	word size = strlen(string);
	word i = 0;
	word charIndex = 0;
	word lwidth = vram_LogicalWidth-2;
	word lwidth2 = vram_LogicalWidth*7;
	word line_jump = (vram_LogicalWidth*8) - (lineLength*2);    // mal
	y = (y<<3);
	screen_offset = (y<<6)+(y<<4)+(y<<3);

	asm{
		push ds
		push di
		push si

		mov dx,VGA_SEQ_INDEX //dx = indexregister
		mov ax,0F02h	//INDEX = MASK MAP,
		out dx,ax 		//write all the bitplanes.
		mov dx,VGA_GC_INDEX //dx = indexregister
		mov ax,0008h
		out dx,ax

		//
		mov di,screen_offset
		mov ax,x
		shl ax,1
		add di,ax
		mov ax,0A000h
		mov ds,ax
		mov bx,size
	}

	printloop3:
	asm push bx
	datastring = string[i]; // Get current char
   // Filter chars > 96
	if (datastring > 96) datastring -=32;
	asm{
		mov	dx,word ptr datastring
		sub	dx,32
	}

	asm{
		mov	si,fontAddress;			//ds:si VRAM FONT TILE ADDRESS

		//go to desired tile
		mov	cl,4						//dx*16
		shl	dx,cl
		add	si,dx

		mov 	ax,0A000h
		mov 	es,ax						//es:di destination address
		mov	bx,lwidth

		//UNWRAPPED COPY 8x8 TILE LOOP
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		add 	di,bx
		movsb
		movsb
		//END LOOP
		sub	di,lwidth2

	   mov 	ax,charIndex
	   inc	ax
	   mov	charIndex,ax
	   cmp	ax,lineLength
	   jne	no_jump_line

		add	di,line_jump
		mov 	charIndex,0
	}
	no_jump_line:
	i++;
	asm{
		pop 	bx
		dec	bx
		jnz	printloop3

		//END
		mov dx,VGA_GC_INDEX +1 //dx = indexregister
		mov ax,00ffh
		out dx,ax

		pop si
		pop di
		pop ds
	}
}


/////////////////////////////////////////////////////////
// Draw empty box
// - Maximum width allowable = 38 characters (+2 for frames)
// - Maximum heigth allowable = 23 characters (+2 for frames)
// - Pages avaliable {1,2}
// - Uses current scroll
/////////////////////////////////////////////////////////
void VGA_Draw_EmptyBox(word x, word y, byte w, byte h){
	int i;
	unsigned char up[41];
	unsigned char mid[41];
	unsigned char down[41];

   // Check maximum width and heigth has not been reached
   //if ((x+w)>38){
   //   sprintf(error1, "%d", x);
   //   sprintf(error2, "%d", w);
   //	Error(" Draw_EmptyBox_VGA >> Wrong empty box width. start >> width : ",error1,error2);
   //}

   //if ((y+h)>23){
   //  	sprintf(error1, "%d", y);
   //   sprintf(error2, "%d", h);
   //	Error(" Draw_EmptyBox_VGA >> Wrong empty box heigth. start >> heigth : ",error1,error2);
   //}

   // Print frame
	up[0] = '#'; up[w+1] = '$'; up[w+2] = 0;
	mid[0] = '*'; mid[w+1] = '+'; mid[w+2] = 0;
	down[0] = '%'; down[w+1] = '&'; down[w+2] = 0;
	for (i = 1; i<w+1; i++){
   	up[i] = '(';
      mid[i] = ' ';
      down[i] = ')';
   }

   // Print empty frame
   VGA_PrintText(x,y,40,up);
   y++;
	for (i = 0; i<h; i++) {
   	VGA_PrintText(x,y,40,mid);
   	y++;
   }
	VGA_PrintText(x,y,40,down);

	free(up);free(mid);free(down);
}

/////////////////////////////////////////////////////////
// Clear pallete
/////////////////////////////////////////////////////////
void VGA_ClearPalette(){
	asm {
		mov	dx,VGA_PALETTE_INDEX
		mov al,0
		out	dx,al
		mov cx,64

		mov al,0
		mov dx,VGA_PALETTE_DATA
	}
	ploop:
	asm{
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al
		out dx,al

		loop ploop
	}
	VGA_Vsync();
}


/////////////////////////////////////////////////////////
// Update scroll x & y (??)
/////////////////////////////////////////////////////////
void VGA_Scroll(word x, word y){
	scroll_x = x;
	scroll_y = y;
}

/////////////////////////////////////////////////////////
// Clear page 1 VRAM (public)
// - Clear visible screen and all the non visible margins
/////////////////////////////////////////////////////////
void VGA_ClearScreen(){
	// Enable all planes
	outport(VGA_SEQ_INDEX,VGA_ALL_PLANES);
	memset(&VGA[vram_LogicalWidth*vga_page[1]],0,vram_LogicalWidth*vga_visible_height);
}


/////////////////////////////////////////////////////////
// Run compiled sprite bitmap
/////////////////////////////////////////////////////////
byte CMask[] = {0x11,0x22,0x44,0x88};
void VGA_RunCompiledSprite(word XPos, word YPos, char *Sprite){
	asm{
		push si
		push ds

		mov ax, vram_LogicalWidth //width
		mul word ptr [YPos] // height in bytes
		mov si, [XPos]

		mov bx, si				// move xpos to bx to keep original xpos
		mov cl,2					// move 2 to cl
		shr si,cl				// shift si (xpos) 2 bits right >> /4
		add si,ax				// add si to ax (vram logical width*ypos)
		add si, 128          // add si 128 >> si = vram * ypos + (Xpos / 4) + 128 ==> starting pos

		and bx, 3				// filter 2 first bits of bx (xpos)
		mov ah,byte ptr CMask[bx] // Mask planes
		mov dx, VGA_SEQ_INDEX //03c4h
		mov al, 02h
		out dx, ax

		inc dx              //ready to send out other masks as bytes
		mov al, ah

		mov bx, VGA_ADDRESS
		mov ds, bx          // We do this so the compiled shape won't need  segment overrides.

		call dword ptr [Sprite] //the business end of the routine

		pop ds
		pop si
	}
}

/////////////////////////////////////////////////////////
// Loading transition interrupt (private)
/////////////////////////////////////////////////////////
void interrupt VGA_LoadingTransition(void){
	asm CLI
	{

	}
	asm STI

   // Acknowledge interrupt
	asm mov al,020h
	asm mov dx,020h
	asm out dx, al	//PIC, EOI
}

/////////////////////////////////////////////////////////
// Set loading transition interrupt (public)
// - sets an animation on the page 1, meanwhile images
//   can be loaded on other pages.
/////////////////////////////////////////////////////////
void VGA_SetLoadingInterrupt(void){
	unsigned long spd = 1193182L/30; //
	//cycle_palette_counter = 0;
	VGA_Fade_out();

   scrolling_enabled = 0;

	//Wait Vsync
	VGA_Vsync();

   UnloadSprites();

   ResetScroll();

	//Reset scroll and point to first page
	outport(VGA_CRTC_INDEX, 0x0D | (0 << 8));
	outport(VGA_CRTC_INDEX, 0x0C | (0 & 0xFF00));

   VGA_SetPage(1);

	VGA_ClearPalette();
	VGA_ClearScreen();//clear screen

	asm CLI

	//set timer on programable internal time interrupt
   // -   Bits         Usage
	//   6 and 7      Select channel :
   //		             0 0 = Channel 0
   //		             0 1 = Channel 1
   //		             1 0 = Channel 2
   //		             1 1 = Read-back command (8254 only)
	//	  4 and 5      Access mode :
   //		             0 0 = Latch count value command
   //		             0 1 = Access mode: lobyte only
   //		             1 0 = Access mode: hibyte only
   //		             1 1 = Access mode: lobyte/hibyte
	//		1 to 3       Operating mode :
   //		             0 0 0 = Mode 0 (interrupt on terminal count)
   //		             0 0 1 = Mode 1 (hardware re-triggerable one-shot)
   //		             0 1 0 = Mode 2 (rate generator)
   //		             0 1 1 = Mode 3 (square wave generator)
   //		             1 0 0 = Mode 4 (software triggered strobe)
   //		             1 0 1 = Mode 5 (hardware triggered strobe)
   //		             1 1 0 = Mode 2 (rate generator, same as 010b)
   //		             1 1 1 = Mode 3 (square wave generator, same as 011b)
	//		0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD
	outportb(PTI_MODE, 0x36); // 0b0011 0110 >> Channel 0, lobyte/hibyte, Mode 3 (square wave), 16bit binary
	outportb(PTI_CH0, (word)(spd % 0x100));	//lo-byte
	outportb(PTI_CH0, (word)(spd / 0x100));	//hi-byte

   old_loading_handler = getvect(0x1C); // Save old IRQ

	//set interrupt handler
	setvect(0x1C, VGA_LoadingTransition);		//interrupt 1C not available on NEC 9800-series PCs.

	asm STI

	//Wait Vsync
	VGA_Vsync();
	VGA_Fade_in();
}

/////////////////////////////////////////////////////////
// Reset loading transition interrupt (public)
/////////////////////////////////////////////////////////
void VGA_ResetLoadingInterrupt(void){

	VGA_Fade_out();
	asm CLI

	//set frame counter
	outportb(PTI_MODE, 0x36);
	outportb(PTI_CH0, 0xFF);	//lo-byte
	outportb(PTI_CH0, 0xFF);	//hi-byte


   // Restore old handler
	setvect(0x1C, old_loading_handler);

	asm STI

   VGA_ClearScreen();//clear screen
}


/////////////////////////////////////////////////////////
// Enable 4 planes
/////////////////////////////////////////////////////////
void VGA_Enable4Planes(void){
	// Enables the 4 planes writing mode
	asm mov dx,VGA_SEQ_INDEX  	//dx = indexregister
	asm mov ax,0F02h	//INDEX = MASK MAP, 3d4
	asm out dx,ax 		//write all the bitplanes.
   // Set Graphics controller bit mask register to 8?? dbg
	asm mov dx,VGA_GC_INDEX 	//dx = indexregister 3ce
	asm mov ax,0008h
	asm out dx,ax
}

/////////////////////////////////////////////////////////
// Disable 4 planes
/////////////////////////////////////////////////////////
void VGA_Disable4Planes(void){ // dbg ??? why set GC index + 1 to 00ff??
	asm mov dx,VGA_GC_INDEX + 1 //dx = indexregister
	asm mov ax,00ffh
	asm out dx,ax
}


/////////////////////////////////////////////////////////
// Draw sprites
/////////////////////////////////////////////////////////
void VGA_Draw_Sprites(void){
   int x;
   int y;
   int lx;
   int ly;
   word next_scanline;
   word bkgAddress;
   word spriteBkgData;
	word screenPrevAddress;
   word screenNewAddress;
   word rows;
   word cols;
   word spriteBkgAddress;
	int spriteStackIndex; //sprite_number
   byte spriteSize = 2;


   VGA_Enable4Planes();

   // Check for active sprites on the stack
   for (spriteStackIndex = 0; spriteStackIndex < spriteStack; spriteStackIndex++)
   {
   	SPRITE *s = &sprite[spriteStackTable[spriteStackIndex]];
		lx = s->last_x;
		ly = s->last_y;
      x = s->pos_x;
		y = s->pos_y;
      next_scanline = s->next_scanline;

      // 1st. Restore the background if sprite has been initialized
      if( s->init == 1)
      {
         rows = s->rows; //s->size;
         cols = s->cols;
         spriteBkgAddress = s->bkg_data;
         screenPrevAddress = (ly<<6)+(ly<<4)+(ly<<3)+(lx>>spriteSize);

         // Restore background to the previous position
         	asm{
					push 	ds
					push 	di
					push 	si

					mov 	ax,0A000h
					mov 	es,ax
					mov 	di,screenPrevAddress	//es:di destination vram

					mov 	ds,ax
					mov 	si,spriteBkgAddress			//ds:si source vram
					mov 	ax,rows
					mov 	bx,next_scanline
					mov 	dx,cols
				}
				scanline2:
				asm{
					mov	cx,dx //2
					rep 	movsb //77			// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
					rep 	movsb				// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
					rep 	movsb				// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
					rep 	movsb				// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
					rep 	movsb				// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
					rep 	movsb				// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
	  				rep	movsb				// copy bytes from ds:si to es:di
					add 	di,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	di,bx				//632 -> 576
					dec 	ax
					jnz	scanline2
				}

				asm pop 	si
				asm pop 	di
				asm pop 	ds

         // if it is outside limits, reset init status
      	if((x < scroll_x) || (x > scroll_x + 304)){ s->init = 0; }
         //if((x < (scroll_x + 8)) || (x > (scroll_x + 296))){ s->init = 0; }

         // if hide is requested just hide it
         if( s->hide ){
         	s->hidden = 1;
            s->init = 0;
         }
      }

      // 2nd. Check for active sprites on the stack and copy background of new pos
      if( s->init == 1)
      {
      	// Copy background only if new position is inside limits
      	if((x >= scroll_x) && (x <= scroll_x + 304)){
         //if((x >= (scroll_x+8)) && (x <= (scroll_x + 296))){

         	rows = s->rows; //s->size;
         	cols = s->cols;
         	spriteBkgAddress = s->bkg_data;
         	screenPrevAddress = (ly<<6)+(ly<<4)+(ly<<3)+(lx>>spriteSize);
            screenNewAddress = (y<<6)+(y<<4)+(y<<3)+(x>>spriteSize);


            // 4th. Save new position background
            asm{
					push 	ds
					push 	di
					push 	si

					mov 	ax,0A000h
					mov 	ds,ax
					mov	si,screenNewAddress	//ds:si source vram

					mov 	es,ax
					mov	di,spriteBkgAddress			//es:di destination

					mov	ax,rows				//Scanlines
					mov	bx,next_scanline
					mov	dx,cols
				}
				scanline3:
				asm{
					mov 	cx,dx				// copy width + 4 pixels
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					dec 	ax
					jnz	scanline3

					pop 	si
					pop 	di
					pop 	ds
				}
         }
      }

      // 3rd. Save background if sprite has not being initialized
      if( (s->init == 0) && (s->hidden == 0)){

      	// Save background only if new position is inside limits
      	if((lx >= scroll_x) && (lx <= scroll_x + 304)){
      	//if((lx >= (scroll_x+8)) && (lx <= (scroll_x + 296))){

         	rows = s->rows; // s->size;
         	cols = s->cols;   //cols
         	spriteBkgData = s->bkg_data;


            bkgAddress = (y<<6)+(y<<4)+(y<<3)+(x>>spriteSize);

         	//Copy bkg chunk to a reserved VRAM part, before destroying it
         	asm{
					push 	ds
					push 	di
					push 	si

					mov 	ax,0A000h
					mov 	ds,ax
					mov	si,bkgAddress		//ds:si source vram

            	mov 	es,ax
					mov	di,spriteBkgData	//es:di destination

					mov	ax,rows				//number of rows
            	mov	bx,next_scanline  //
            	mov	dx,cols
         	}
         	scanline1:
				asm{
					mov 	cx,dx				// copy width + 4 pixels
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					mov 	cx,dx
					rep	movsb				// copy bytes from ds:si to es:di
					add 	si,bx
					dec 	ax
					jnz	scanline1

         		pop 	si
					pop 	di
					pop 	ds
				}

         	s->init = 1;
         }
      }
   }


   VGA_Disable4Planes();


   // Print sprite in new position
   // Check for active sprites on the stack
   for (spriteStackIndex = 0; spriteStackIndex < spriteStack; spriteStackIndex++)
   {
   	SPRITE *s = &sprite[spriteStackTable[spriteStackIndex]];
      int x = s->pos_x;
		int y = s->pos_y;
		int lx = s->last_x;
		int ly = s->last_y;
      word next_scanline = s->next_scanline;

      // Do it just if it is initialized
      if( s->init == 1){

			// Write sprite on VGA only if it is inside visible screen
      	if((x >= scroll_x) && (x <= scroll_x + 304)){
         //if((x >= (scroll_x+8)) && (x <= (scroll_x + 296))){

         	// Check animation enabled
      		if(s->animate == 1){

         		s->frame = s->animation[s->anim_counter];

            	if(s->anim_speed > s->speed){
            		s->anim_speed = 0;
               	s->anim_counter ++;
                  // Reset animation counter
                  if (s->anim_counter == s->aframes) s->anim_counter = 0;

            	}
            	s->anim_speed++;
         	}

				if(s->hide == 0){
            	VGA_RunCompiledSprite(x,y,s->frames[s->frame].compiled_code);
            }
      	}
      }

   	s->last_x = x;
      s->last_y = y;
 	}
}


/////////////////////////////////////////////////////////
// Draw tile VGA
//  - arg 0: source address (tiles memory)
//  - arg 1: destination address (screen memory)
/////////////////////////////////////////////////////////
void VGA_DrawTile(word saddr, word daddr){
	word lwidth = vram_LogicalWidth-4;  // logical screen width

	asm{
		push ds
		push di
	 	push si

      mov 		ax,0A000h
		mov 		ds,ax
      mov		es,ax
      mov 		si,saddr             //ds:si Tile data VRAM address
		mov		di,daddr					//es:di screen address
		mov		bx,lwidth

      // DRAW TILE
     	//COPY TILE (16 LINES) use movsb to enable hardware copy (4 pixels)
      movsb     // Write first row
      movsb
      movsb
      movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
      movsb
      movsb
      movsb

      add 	di,bx  // go to next row offset
		movsb        // wirte next row
	   movsb
		movsb
		movsb

		add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

		add 	di,bx  // go to next row offset
		movsb        // wirte next row
		movsb
		movsb
		movsb

		add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

		add 	di,bx  // go to next row offset
      movsb        // wirte next row
      movsb
      movsb
      movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

		add 	di,bx  // go to next row offset
      movsb        // wirte next row
      movsb
      movsb
      movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

	  	add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

		add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

      add 	di,bx  // go to next row offset
      movsb        // wirte next row
		movsb
		movsb
		movsb

      pop si
      pop di
      pop ds
   }
}


/////////////////////////////////////////////////////////
// Draw map column VGA
//  - arg 0: x value on pixels
//  - arg 1: y value on pixels
//  - arg 2: map_offset x (logic)
//  - arg 3: map_offset y (logic)
//  - arg 4: ntiles (logic)
/////////////////////////////////////////////////////////
void VGA_DrawMapColumn(word x_px, word y_px, word offset_x, word offset_y,word ntiles){
   word saddr; // Source address
   word daddr; // Destination address
   int i = 0;
   word tilenum;

   word m_width = map_width<<1;
	word m_offset = offset_x + (offset_y*map_width);

   // draw map column
   for(i = 0; i<ntiles; i++)
   {
   	//map_data[index] = tile_vram + ((tile -1)<<6);
      tilenum  =  map_data[m_offset];

      saddr = vram_Tiles + ((tilenum -1)<<6);  // Source address >> VGA address where tiles are located
      daddr = (y_px<<6)+(y_px<<4)+(y_px<<3) + (x_px>>2); // Destination address >> VGA address where tile will be printed

      VGA_DrawTile(saddr, daddr);

      m_offset = m_offset + map_width; // next map line
      y_px = y_px + 16; // next scanline
   }

   // map collision
	/*if (flipScroll==1){
		if (!map_setting) atr_offset -= 2560;
		if (spriteStack < 8){
			int j;
			int nsprite;
			for (i = 0; i <19;i++){
				int sprite0 = map_collision[atr_offset]; //sprite0-16 for sprite type
				switch (sprite0){
					case 16:
					for (j = 0; j < 3; j++){
						if (spritesActiveAI[j]){
							word posIdTable = (i<<8) + (x_px>>4);
							if (spriteIdTable[posIdTable] == 1) break;
							nsprite = spritesActiveAI[j];
							spritesActiveAI[j] = 0;
							spriteStackTable[spriteStack] = nsprite;
							if (sprite[nsprite].init == 0)
								SetAI_Sprite(nsprite,sprite[nsprite].mode,x_px>>4,i,scrollSide,0,posIdTable);//also increase sprite range
							spriteStack++;
							spriteIdTable[posIdTable] = 1;
							break;
						}
					}
					break;
					case 17:
					for (j = 4; j < 7; j++){
						if (spritesActiveAI[j]){
							word posIdTable = (i<<8) + (x_px>>4);
							if (spriteIdTable[posIdTable] == 1) break;
							nsprite = spritesActiveAI[j];
							spritesActiveAI[j] = 0;
							spriteStackTable[spriteStack] = nsprite;
							if (sprite[nsprite].init == 0)
								SetAI_Sprite(nsprite,sprite[nsprite].mode,x_px>>4,i,scrollSide,0,posIdTable);
							spriteStack++;
							spriteIdTable[posIdTable] = 1;
							break;
						}
					}
					break;
				}
				atr_offset+= map_width;
			}
		}
	}*/
}

/////////////////////////////////////////////////////////
// Draw map row VGA
//  - arg 0: x value on pixels
//  - arg 1: y value on pixels
//  - arg 2: map_offset x (logic)
//  - arg 3: map_offset y (logic)
//  - arg 4: ntiles (logic)
/////////////////////////////////////////////////////////
void VGA_DrawMapRow(word x_px, word y_px, word offset_x, word offset_y, word ntiles){
	word saddr; // Source address
   word daddr; // Destination address
   int i = 0;
   word tilenum;

   word m_width = map_width<<1;
	word m_offset = offset_x + (offset_y*map_width);

   // draw map row
   for(i = 0; i<ntiles; i++)
   {
   	//map_data[index] = tile_vram + ((tile -1)<<6);
      tilenum  =  map_data[m_offset];

      saddr = vram_Tiles + ((tilenum -1)<<6);  // Source address >> VGA address where tiles are located
      daddr = (y_px<<6)+(y_px<<4)+(y_px<<3) + (x_px>>2); // Destination address >> VGA address where tile will be printed

      VGA_DrawTile(saddr, daddr);

      m_offset = m_offset + 1; // next map line
      x_px = x_px + 16; // next scanline
   }
}

/////////////////////////////////////////////////////////
// Draw map VGA
//  Draw current loaded map on screen
//  - arg 0: x value on tiles
//  - arg 1: y value on tiles
/////////////////////////////////////////////////////////
void VGA_SetMap(int x, int y){
  	int j = 0;
   int i = 0;
  	byte rows = 15; //19; // rows to print

   // Recalculate y if it is out of limits
   // - Hardware limits
	//if(y > ((vga_page[2]>>4)-2)){ y = (vga_page[2]>>4)-2;}
   // - Map limits

	if((y+15) > map_height) { y = map_height-15; }
	//if((x+9) > map_width) { x = map_width-9; }
   if((x+16) > map_width) { x = map_width-16; }


   // Map starts always on page 1
   scroll_y = (y<<4) + vga_page[1];
 	scroll_x = x<<4;

	map_width_px = map_width<<4;
	map_height_px = map_height<<4;

	map_offset_x = x;
	map_offset_y = y;

 	VGA_Enable4Planes();

   // number of cols shown on screen = 20
   // 16 pixel width each tile
   // 21 x 15 = 336
   // 22 x 16 = 352
   for (i = 0;i<352;i+=16) {  // prevoius value 352
   	if(y > 0){
         if(x > 0){ VGA_DrawMapColumn(scroll_x+i-16,scroll_y-16,map_offset_x+j-1,map_offset_y-1,rows); }
         else{ VGA_DrawMapColumn(scroll_x+i,scroll_y-16,map_offset_x+j,map_offset_y-1,rows);}
      }
      else{
         if(x > 0){ VGA_DrawMapColumn(scroll_x+i-16,scroll_y,map_offset_x+j-1,map_offset_y,rows); }
      	else{ VGA_DrawMapColumn(scroll_x+i-16,scroll_y,map_offset_x+j-1,map_offset_y,rows);}
      }
      j++;  // next column
   }

   VGA_Disable4Planes();
}


/////////////////////////////////////////////////////////
// Scroll map
/////////////////////////////////////////////////////////
void VGA_ScrollMap(void){

	VGA_Enable4Planes();

   map_current_x = ((scroll_x)>>4)<<4;
   map_current_y = ((scroll_y)>>4)<<4;

   map_offset_x = scroll_x>>4;
   map_offset_y = (scroll_y-vga_page[1])>>4;

   // check if direction has change
   //if(scroll_x < last_scroll_x){ // move left
   // 	if( scrollSide == -1 ){  // last movement was right
      	//DrawMapColumn_VGA(current_x,current_y,map_offset_x,map_offset_y,19); // number of tiles was tiles-1
   //   	DrawMapColumn_VGA(current_x-16,current_y,map_offset_x,map_offset_y,19); // number of tiles was tiles-1
   //   }
   //}

   // check if direction has change
   //if(scroll_x > last_scroll_x){ // move right
   // 	if( scrollSide == 1 ){  // last movement was left
   //   	//DrawMapColumn_VGA(current_x,current_y,map_offset_x,map_offset_y,19); // number of tiles was tiles-1
   ///   	DrawMapColumn_VGA(current_x+320,current_y,map_offset_x+20,map_offset_y,19);   // number of tiles was tiles-1
   //   }

   if ((map_current_x != map_last_x) || (map_current_y != map_last_y)){

      // Moving left
		if (map_current_x < map_last_x){
			map_scrollSide = 1;

         if(map_offset_x > 0){
         	if(map_offset_y + 13 >= map_height){
          		VGA_DrawMapColumn(map_current_x-16,map_current_y-16,map_offset_x-1,map_offset_y-1,14); // number of tiles was tiles-1
         	}
         	else if(map_offset_y + 14 >= map_height){
            	VGA_DrawMapColumn(map_current_x-16,map_current_y-16,map_offset_x-1,map_offset_y-1,15); // number of tiles was tiles-1
         	}
        	 	else if(map_offset_y > 0){
         		VGA_DrawMapColumn(map_current_x-16,map_current_y-16,map_offset_x-1,map_offset_y-1,15); // number of tiles was tiles-1
         	}
         	else{
            	VGA_DrawMapColumn(map_current_x-16,map_current_y,map_offset_x-1,map_offset_y,14); // number of tiles was tiles-1
         	}
         }
      	else{
            if(map_offset_y + 13 >= map_height){
          		VGA_DrawMapColumn(map_current_x,map_current_y-16,map_offset_x,map_offset_y-1,14); // number of tiles was tiles-1
         	}
         	else if(map_offset_y + 14 >= map_height){
            	VGA_DrawMapColumn(map_current_x,map_current_y-16,map_offset_x,map_offset_y-1,15); // number of tiles was tiles-1
         	}
        	 	else if(map_offset_y > 0){
         		VGA_DrawMapColumn(map_current_x,map_current_y-16,map_offset_x,map_offset_y-1,15); // number of tiles was tiles-1
         	}
         	else{
            	VGA_DrawMapColumn(map_current_x,map_current_y,map_offset_x,map_offset_y,14); // number of tiles was tiles-1
         	}

         }
		}

      // Moving right
      if (map_current_x > map_last_x) {
			map_scrollSide = -1;
         if(map_offset_y + 13 >= map_height){
          	VGA_DrawMapColumn(map_current_x+320,map_current_y-16,map_offset_x+20,map_offset_y-1,14);   // number of tiles was tiles-1
         }
         else if(map_offset_y + 14 >= map_height){
            VGA_DrawMapColumn(map_current_x+320,map_current_y-16,map_offset_x+20,map_offset_y-1,15);   // number of tiles was tiles-1
         }
         else if(map_offset_y > 0){
         	VGA_DrawMapColumn(map_current_x+320,map_current_y-16,map_offset_x+20,map_offset_y-1,15);   // number of tiles was tiles-1
         }
         else{
            VGA_DrawMapColumn(map_current_x+320,map_current_y,map_offset_x+20,map_offset_y,14);   // number of tiles was tiles-1
         }
		}

      // Moving up
      if (map_current_y < map_last_y){
      	map_scrollSide = 2;
         if(map_current_y > 0){
         	if(map_current_x > 0){
            	if( map_current_y > 0)
          			VGA_DrawMapRow(map_current_x-16,map_current_y-16,map_offset_x-1,map_offset_y-1,22);
               else{
                  VGA_DrawMapRow(map_current_x-16,map_current_y,map_offset_x-1,map_offset_y,22);
               }
            }
            else{
            	if( map_current_y > 0)
               	VGA_DrawMapRow(map_current_x,map_current_y-16,map_offset_x,map_offset_y-1,21);
               else{
                  VGA_DrawMapRow(map_current_x,map_current_y,map_offset_x,map_offset_y,21);
               }
            }
         }
      }
      // Moving down
      if (map_current_y > map_last_y){
      	map_scrollSide = -2;
         if(map_current_x > 0){
         	if(map_offset_y + 13 >= map_height){
          		VGA_DrawMapRow(map_current_x-16,map_current_y+192,map_offset_x-1,map_offset_y+12,22);
            }
            else{
               VGA_DrawMapRow(map_current_x-16,map_current_y+208,map_offset_x-1,map_offset_y+13,22);
            }
         }
         else{
         	if(map_offset_y + 13 >= map_height){
            	VGA_DrawMapRow(map_current_x,map_current_y+192,map_offset_x,map_offset_y+12,21);
            }
            else{
               VGA_DrawMapRow(map_current_x,map_current_y+208,map_offset_x,map_offset_y+13,21);
            }
         }
      }
	}

	VGA_Disable4Planes();

	map_last_x = map_current_x;
	map_last_y = map_current_y;

}

/////////////////////////////////////////////////////////
// Restore map
// - Restores current map to fill the existing text box
/////////////////////////////////////////////////////////
void VGA_Draw_MapBack(void){
	VGA_Enable4Planes();
	VGA_DrawMapRow(map_current_x,map_current_y,map_offset_x,map_offset_y,22);
  	VGA_DrawMapRow(map_current_x,map_current_y+16,map_offset_x,map_offset_y+1,22);
   VGA_DrawMapRow(map_current_x,map_current_y+32,map_offset_x,map_offset_y+2,22);
   VGA_DrawMapRow(map_current_x,map_current_y+48,map_offset_x,map_offset_y+3,22);
   VGA_DrawMapRow(map_current_x,map_current_y+64,map_offset_x,map_offset_y+4,22);
   VGA_Disable4Planes();
}

/////////////////////////////////////////////////////////
// Split screen
// - Shows a window on the bottom screen from a different vram address
/////////////////////////////////////////////////////////
void VGA_SplitScreen(int line){
	line = line<<1;
   asm{
		push    ax
    	push    cx
    	push    dx
		//Set the split screen scan line.
    	cli		// make sure all the registers get set at once

		mov		dx,VGA_CRTC_INDEX
		mov		ax,line
		mov    	cl,8
		shl		ax,cl
		add		ax,VGA_CRTC_LINE_COMPARE
		out    	dx,ax		// set bits 7-0 of the split screen scan line

    	mov    ah,byte ptr [line+1]
    	and    ah,1
    	mov    cl,4
    	shl    ah,cl                      // move bit 8 of the split split screen scan line into position for the Overflow reg
    	mov    al,VGA_OVERFLOW

		//The Split Screen, Overflow, and Line Compare registers all contain part of the split screen start scan line on the VGA
		out    dx,al                      //set CRTC Index reg to point to Overflow
    	inc    dx                         //point to CRTC Data reg
    	in     al,dx                      //get the current Overflow reg setting
    	and    al,not 10h                 //turn off split screen bit 8
    	or     al,ah                      //insert the new split screen bit 8 (works in any mode)
    	out    dx,al                      //set the new split screen bit 8

		dec    dx                         //point to CRTC Index reg
    	mov    ah,byte ptr [line+1]
    	and    ah,2
    	mov    cl,3
    	ror    ah,cl                      // move bit 9 of the split split screen scan line into position for the Maximum Scan Line register
    	mov    al,VGA_MAX_SCANLINE
    	out    dx,al                      //set CRTC Index reg to point to Maximum Scan Line
    	inc    dx                         //point to CRTC Data reg
    	in     al,dx                      //get the current Maximum Scan Line setting
    	and    al,not 40h                 //turn off split screen bit 9
    	or     al,ah                      //insert the new split screen bit 9 (works in any mode)
    	out    dx,al                      //set the new split screen bit 9


		//Turn on split screen pel panning suppression, so the split screen
		//won't be subject to pel panning as is the non split screen portion.
		mov  dx,VGA_INPUT_STATUS
		in   al,dx                  	//Reset the AC Index/Data toggle to index state
		mov  al,VGA_AC_MODE_CONTROL+20h 	//Bit 5 set to prevent screen blanking
		mov  dx,VGA_AC_INDEX				//Point AC to Index/Data register
		out  dx,al
		inc  dx							//Point to AC Data reg (for reads only)
		in   al,dx						//Get the current AC Mode Control reg
		or   al,20h						//Enable split scrn Pel panning suppress.
		dec  dx							//Point to AC Index/Data reg (for writes only)
		out  dx,al						//Write the new AC Mode Control setting with split screen pel panning suppression turned on

    	sti
    	pop    dx
    	pop    cx
    	pop    ax
	}
}



//Reduced split screen function, just to move the position in 320x240 mode
void VGA_MoveWindow(void){
	asm{
		push    ax
    	push    cx
    	push    dx

		//rep		movsw
		mov		dx,VGA_CRTC_INDEX
		mov		ax,scroll_wy
		mov    	cl,8
		shl		ax,cl
		add		ax,VGA_CRTC_LINE_COMPARE
		out    	dx,ax

    	mov    ah,byte ptr [scroll_wy+1]
    	and    ah,1
    	mov    cl,4
    	shl    ah,cl
    	mov    al,VGA_OVERFLOW

		out    dx,al
    	inc    dx
    	in     al,dx
    	and    al,not 10h
    	or     al,ah
    	out    dx,al

    	pop    dx
    	pop    cx
    	pop    ax
   }
}

void VGA_Window_in(){
	if (scroll_wy != 0){
		if (scroll_wy == 240*2)
			//if (Scene != 20) Print(0,6, "LOADING",1);
		scroll_wy-=8;
		VGA_MoveWindow();
	} else {
		//Window can't be at line 0, so we move the vram scroll to 0
		//to hide line 0
		scroll_x = 0;
		scroll_y = -240;
		VGA_Vsync();
		scroll_wy = 0;
		VGA_MoveWindow();
		//Scene++;
	}
}

void VGA_Window_out(){
	asm cli
	//vram scroll was set to 0 to show the entire window, now we reset it to 240
	//to show cute things
	if (scroll_wy == 0) scroll_y = 0;
	if (scroll_wy !=240*2){
		scroll_wy+=8;
		VGA_MoveWindow();
	}
	asm sti
}

void VGA_Set_Window(void){
	VGA_SplitScreen(0);
	scroll_wy= 400;
	VGA_MoveWindow();
}

void VGA_UpdatePanel(void){

	int aux;

	if( fp_keys[K_SPACE] ) {
   	if(showPanel){ showPanel = 0; }
      else{
         showPanel = 1;
      }
   }

	if(showPanel){
   	if(scroll_wy > 336){
      	scroll_wy --;
         VGA_MoveWindow();
      }

		//sprintf(string, "X: %d", scroll_x);
      //VGA_PrintPanelText(1,1,8,"        ");
		//VGA_PrintPanelText(1,1,strlen(string),string);

		//sprintf(string, "Y: %d", scroll_y);
      //VGA_PrintPanelText(1,2,8,"        ");
		//VGA_PrintPanelText(1,2,strlen(string),string);

   	//sprintf(string, "WY: %d", scroll_wy);
      //VGA_PrintPanelText(1,3,8,"        ");
		//VGA_PrintPanelText(1,3,strlen(string),string);

		//sprintf(string, "Player x %d", player.tile_x );

		//sprintf(string, "Max h x %d", map_height_px );
      //VGA_PrintPanelText(9,1,16,"                ");
		//VGA_PrintPanelText(9,1,strlen(string),string);

  		//sprintf(string, "Player y: %d", player.tile_y);
      //VGA_PrintPanelText(9,2,16,"                ");
		//VGA_PrintPanelText(9,2,strlen(string),string);

      //sprintf(string, "Player e: %d", player.event);
      //VGA_PrintPanelText(9,3,16,"                ");
		//VGA_PrintPanelText(9,3,strlen(string),string);

      //sprintf(string, "Player h: %d", player.hotspot);
      //VGA_PrintPanelText(9,4,16,"                ");
		//VGA_PrintPanelText(9,4,strlen(string),string);

      //sprintf(string, "Player move: %d", player.move);
      //VGA_PrintPanelText(25,1,14,"              ");
		//VGA_PrintPanelText(25,1,strlen(string),string);

      //aux = (  (player.tile_y) * map_width ) + player.tile_x;
      //sprintf(string, "P. col up: %d", map_collision[aux] );
      //VGA_PrintPanelText(25,2,14,"              ");
		//VGA_PrintPanelText(25,2,strlen(string),string);

      //aux = (  (player.tile_y) * map_width ) + player.tile_x;
      //sprintf(string, "P. col lft: %d", map_collision[aux] );
      //VGA_PrintPanelText(25,3,14,"              ");
		//VGA_PrintPanelText(25,3,strlen(string),string);

	}
   else{
   	if(scroll_wy < 400){
      	scroll_wy ++;
         VGA_MoveWindow();
      }
	}
}


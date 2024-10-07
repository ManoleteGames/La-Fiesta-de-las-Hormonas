/***********************
*  Keyboard functions
************************/

#include "source\engine\engine.h"
#include "source\engine\keyb\keyb.h"

int keys[256];
int prev_keys[256];
int fp_keys[256];
unsigned char keyhit;

/////////////////////////////////////////////////////////
// Interrupt keyboard handler declaration
/////////////////////////////////////////////////////////
void interrupt (*old_Key_handler)(void);
void interrupt Key_handler(void)
{
	asm{
		cli	// Disable interrupts
    	in    al, 060h
    	mov   keyhit, al

    	in    al, 061h
    	mov   bl, al
    	or    al, 080h
    	out   061h, al

    	mov   al, bl
    	out   061h, al

    	mov   al, 020h
    	out   020h, al

    	sti	// Enable interrupts
    }

    // Key released
    if (keyhit & 0x80) { // AND 1000 0000 - Checks the MSB
    	keyhit &= 0x7F;    // AND 0111 1111 - Clears the MSB
      keys[keyhit] = 0;  // Reset key pressed flag
    }
    else{ // Key pressed
    	keys[keyhit] = 1;  // Set key pressed flag
    }
}

/////////////////////////////////////////////////////////
// Set key handler
/////////////////////////////////////////////////////////
void Set_key_handler(void){
	int i;

   old_Key_handler = getvect(KEYB_IRQ); // Save old keyb irq
   setvect(KEYB_IRQ,Key_handler); // Set interrupt 9 to interrupt handler function
   // Initialize key array
   for (i = 0; i != 256; i++) { keys[i] = 0; }
}

/////////////////////////////////////////////////////////
// Reset key handler
/////////////////////////////////////////////////////////
void Reset_key_handler(void){
   setvect(KEYB_IRQ,old_Key_handler); // Set interrupt 9 to interrupt handler function
}

/////////////////////////////////////////////////////////
// Update Positive flange keys
/////////////////////////////////////////////////////////
void Update_FP_Keys(void)
{
	int i;
	for(i = 0; i<256; i++) {
    	if(keys[i] > prev_keys[i]){ fp_keys[i] = 1; }
      else{ fp_keys[i] = 0; }
		prev_keys[i] = keys[i];
   }
}

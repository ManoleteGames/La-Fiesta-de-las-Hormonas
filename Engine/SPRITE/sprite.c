/***********************
*  Sprite functions
************************/

#include "source\engine\engine.h"

SPRITE far *sprite;
SPRITE loadingAnimation;

byte spriteStack = 0;
byte spriteStackTable[33] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/////////////////////////////////////////////////////////
// Compile sprite bitmap
/////////////////////////////////////////////////////////
word CompileBitmap(word logical_width, unsigned char *bitmap, unsigned char *output){

	word bwidth,scanx,scany,outputx,outputy,column,set_column,input_size,code_size;

	asm push si
	asm push di
	asm push ds

	asm mov word ptr [scanx],0
	asm mov word ptr [scany],0
	asm mov word ptr [outputx],0
	asm mov word ptr [outputy],0
	asm mov word ptr [column],0
	asm mov word ptr [set_column],0

	asm lds si,[bitmap]     // 32-bit pointer to source bitmap

	asm les di,[output]     // 32-bit pointer to destination stream

	asm lodsb               // load width byte
	asm xor ah, ah          // convert to word
	asm mov [bwidth], ax    // save for future reference
	asm mov bl, al          // copy width byte to bl
	asm lodsb               // load height byte -- already a word since ah=0
	asm mul bl              // mult height word by width byte
	asm mov [input_size], ax//  to get pixel total

_MainLoop:
	asm mov bx, [scanx]     // position in original bitmap
	asm add bx, [scany]

	asm mov al, [si+bx]     // get pixel
	asm or  al, al          // skip empty pixels
	asm jnz _NoAdvance
	asm jmp _Advance
_NoAdvance:

	asm mov dx, [set_column]
	asm cmp dx, [column]
	asm je _SameColumn
_ColumnLoop:
	asm mov word ptr es:[di],0c0d0h// emit code to move to new column
	asm add di,2
	asm mov word ptr es:[di],0d683h
	asm add di,2
	asm mov byte ptr es:[di],0
	asm inc di

	asm inc dx
	asm cmp dx, [column]
	asm jl _ColumnLoop

	asm mov byte ptr es:[di],0eeh
	asm inc di// emit code to set VGA mask for new column

	asm mov [set_column], dx
_SameColumn:
	asm mov dx, [outputy]   // calculate output position
	asm add dx, [outputx]
	asm sub dx, 128

	asm add word ptr [scanx], 4
	asm mov cx, [scanx]     // within four pixels of right edge?
	asm cmp cx, [bwidth]
	asm jge _OnePixel

	asm inc word ptr [outputx]
	asm mov ah, [si+bx+4]   // get second pixel
	asm or ah, ah
	asm jnz _TwoPixels
_OnePixel:
	asm cmp dx, 127         // can we use shorter form?
	asm jg _OnePixLarge
	asm cmp dx, -128
	asm jl _OnePixLarge
	asm mov word ptr es:[di],044c6h
	asm add di,2

	asm mov byte ptr es:[di],dl
	asm inc di// 8-bit position in output

	asm jmp _EmitOnePixel
_OnePixLarge:
	asm mov word ptr es:[di],084c6h
	asm add di,2
	asm mov word ptr es:[di],dx
	asm add di,2 //position in output
_EmitOnePixel:
	asm mov byte ptr es:[di],al
	asm inc di
	asm jmp short _Advance
_TwoPixels:
	asm cmp dx, 127
	asm jg _TwoPixLarge
	asm cmp dx, -128
	asm jl _TwoPixLarge
	asm mov word ptr es:[di],044c7h
	asm add di,2
	asm mov byte ptr es:[di],dl
	asm inc di            // 8-bit position in output
	asm jmp _EmitTwoPixels
_TwoPixLarge:
	asm mov word ptr es:[di],084c7h
	asm add di,2
	asm mov word ptr es:[di],dx
	asm add di,2 // position in output
_EmitTwoPixels:
	asm mov word ptr es:[di],ax
	asm add di,2

_Advance:
	asm inc word ptr [outputx]
	asm mov ax, [scanx]
	asm add ax, 4
	asm cmp ax, [bwidth]
	asm jl _AdvanceDone
	asm mov dx, [outputy]
	asm add dx, [logical_width]
	asm mov cx, [scany]
	asm add cx, [bwidth]
	asm cmp cx, [input_size]
	asm jl _NoNewColumn
	asm inc word ptr [column]
	asm mov cx, [column]
	asm cmp cx, 4
	asm je _Exit           // Column 4: there is no column 4.
	asm xor cx, cx          // scany and outputy are 0 again for
	asm mov dx, cx          // the new column
_NoNewColumn:
	asm mov [outputy], dx
	asm mov [scany], cx
	asm mov word ptr [outputx], 0
	asm mov ax,[column]
_AdvanceDone:
	asm mov [scanx], ax
	asm jmp _MainLoop

_Exit:
	asm mov byte ptr es:[di],0cbh
	asm inc di
	asm mov ax,di
	asm sub ax,word ptr [output] // size of generated code
	asm mov [code_size],ax
	asm pop ds
	asm pop di
	asm pop si

	return code_size;
}

/////////////////////////////////////////////////////////
// Reset sprite stack
/////////////////////////////////////////////////////////
void ResetSpriteStack(void){
	int i;
	spriteStack = 0;
	for (i = 0; i<33; i++) spriteStackTable[i] = 0;
	//spriteAI[0] = 0;
	//memset(spriteIdTable,0,19*256*2); // dgb why this numbeR??
}

/////////////////////////////////////////////////////////
// Unload a single loaded sprite
/////////////////////////////////////////////////////////
void Unload_sprite(int sprite_number){
	SPRITE *s = &sprite[sprite_number];
	int i;
	s->init = 0;
	for (i=0;i<s->nframes;i++){
		farfree(s->frames[i].compiled_code);
		//s->frames[i].compiled_code = NULL;
	}
	//farfree(s->frames);
   //s->frames = NULL;
}

/////////////////////////////////////////////////////////
// Unload all loaded sprites
/////////////////////////////////////////////////////////
void UnloadSprites(void){
	int i = 0;
	for (i=0;i<20;i++){Unload_sprite(i);}
   ResetSpriteStack();
   vram_SpritesBack = 0xDF00; //0xD400;;
}

/////////////////////////////////////////////////////////
// Load sprite
// - load sprites with transparency (size = 8,16,32)
// - load sprites without transparency (size = 64)
// - size := 8,16,32,64
/////////////////////////////////////////////////////////
void LoadSprite(char *file, char *dat_string, int sprite_number, byte size){
	SPRITE *s = &sprite[sprite_number];
	long index;
   long offset;
	word x;
	word frame = 0;
	byte tileX;
	byte tileY;
   word fsize = 0;
   int siz;
   int code_size;

   // Check sprite pointer
   sprintf(error1, "%d", sprite_number);
   if(s == NULL){ Error("Error loading sprite ",error1,dat_string);}

	// Load file data
   // - palette will be stored on tilesetPalette[208..256]
   // - image will be stores on tempdata1
   LoadSprite_PCX(file,dat_string,sprite_number);

	index = 0; //use a chunk of temp allocated RAM to rearrange the sprite frames
	//Rearrange sprite frames one after another in temp memory
	for (tileY = 0; tileY<s->height; tileY += size){
		for (tileX=0; tileX<s->width; tileX += size){
			offset = (tileY * s->width) + tileX; // Calculate offset for each frame
         // Temp data stores pixel width and heigth of each sprite frame
         // index[0] := sprite frame 1 > width in pixels
         // index[1] := sprite frame 1 > height in pixels
         // index[2] := sprite frame 2 > width in pixels
         // index[3] := sprite frame 2 > height in pixels
         // ...
         tempdata2[index] = size;
			tempdata2[index+1] = size;
			index+=2; // Next frame

         // Recompose sprite on frames form tempdata1 to tempdata2
			for(x=0;x<size;x++){
				memcpy(&tempdata2[index],&tempdata1[offset+(x * s->width)],size);
				index+=size;
			}
		}
	}

   // Number of frames of the sprite
   if (size == 8) siz = 3;
	if (size == 16) siz = 4;
	if (size == 32) siz = 5;
	s->nframes = (s->width>>siz) * (s->height>>siz);

	//Estimated size
	fsize = ((size * size * 7) >> 1) + 25;

   //calculate frames size
	if ((s->frames = farcalloc(s->nframes,sizeof(SPRITEFRAME))) == NULL) { Error("Impossible allocate memory for sprite frames", 0,0);} //LT_Error("Error loading ",file);

	for (frame = 0; frame < s->nframes; frame++){
      // Check avaliable memory
      s->frames[frame].compiled_code = farcalloc(fsize,sizeof(unsigned char));
      if (s->frames[frame].compiled_code == NULL){
      //if (( farrealloc(s->frames[frame].compiled_code,fsize)) == NULL){
      	sprintf(error1, "%d", sprite_number);
			Error("Not enough RAM to allocate sprite frames",dat_string,error1);
		}

      //COMPILE SPRITE FRAME TO X86 MACHINE CODE
		//& Store the compiled data at it's final destination
      code_size = CompileBitmap(vram_LogicalWidth, &tempdata2[(frame*2)+(frame*(size*size))],s->frames[frame].compiled_code);
      s->frames[frame].compiled_code = farrealloc(s->frames[frame].compiled_code, code_size);
	}

	//s->bkg_data // Is a pointer (word) set in init function (system.c) allocated on VRAM[0...X]
   s->bkg_data = vram_SpritesBack; //vram_SpritesBack[sprite_number];
	s->width = size;
	s->height = size;
	s->init = 0;
	s->frame = 0;
	s->baseframe = 0;
	s->animate = 0;
	s->anim_speed = 0;
	s->speed = 4;
	s->anim_counter = 0;
	s->speed_x = 8*16;
	s->speed_y = 8*16;
	s->s_delete = 0;
	s->fixed_sprite_number = sprite_number;
	s->mspeed_x = 1;
	s->mspeed_y = 1;
	s->rows = (s->height>>3);
   s->cols = (s->width>>2) + 1;
	s->next_scanline = vram_LogicalWidth - s->cols;
	s->mode = 0;
	s->stack = 0;
   s->loaded = 1;

   // Recalculate next sprite background address
   vram_SpritesBack += (size*size)>>1;

}

/////////////////////////////////////////////////////////
// Set sprite animation
/////////////////////////////////////////////////////////
void SetSpriteAnimation(int sprite_number, byte firstFrame, byte aframes, byte speed, byte *anim){
	SPRITE *s = &sprite[sprite_number];
   if(s->loaded){
   	int i;
   	s->animate = 1;
   	s->aframes = aframes;
   	s->baseframe = firstFrame;
   	s->anim_counter = 0;
   	s->speed = speed;
   	for( i=0;i<aframes;i++){s->animation[i] = anim[i+firstFrame];}
   }
   else{
   	sprintf(error1, "%d", sprite_number);
   	Error("Trying to set animation on non loaded sprite",error1,0);
   }
}

/////////////////////////////////////////////////////////
// Initialize sprite
/////////////////////////////////////////////////////////
void InitSprite(int sprite_number,int x,int y){
   SPRITE *s = &sprite[sprite_number];
   if(s->loaded){
		spriteStackTable[spriteStack] = sprite_number;
		sprite[sprite_number].pos_x = x;
		sprite[sprite_number].pos_y = y;
		sprite[sprite_number].stack = spriteStack;
		sprite[sprite_number].init = 0;
   	sprite[sprite_number].hide = 0;
		sprite[sprite_number].hidden = 0;
		spriteStack++;
   }
   else{
   	sprintf(error1, "%d", sprite_number);
   	Error("Trying to init a non loaded sprite",error1,0);
   }
}

/////////////////////////////////////////////////////////
// Reset sprite animation
/////////////////////////////////////////////////////////
void ResetSpriteAnimation(int sprite_number, byte anim){
	SPRITE *s = &sprite[sprite_number];
   s->baseframe = anim;
   s->anim_counter = 0;
   s->animate = 0;
}

void HideSprite(int sprite_number){
	SPRITE *s = &sprite[sprite_number];
   s->hide = 1;
   Update(0,0);
}

void ShowSprite(int sprite_number){
	SPRITE *s = &sprite[sprite_number];
   s->hide = 0;
   s->hidden = 0;
}




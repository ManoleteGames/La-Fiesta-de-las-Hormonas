/***********************
*  Files functions
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
//Seek files inside LDAT files (custom format similar to WAD)
// max. 64 files
/////////////////////////////////////////////////////////
void DAT_Seek(FILE *fp,char *dat_string){
	unsigned char line = 0;
	char name[17]; //name of the file inside DAT
	unsigned char data_name = 0;
	dword offset = 0;   //LDAT_Offset

	//Check LDAT file
	//Seek data
	fseek(fp,32,SEEK_SET);  // Check first line of names inside the .DAT
	while(data_name == 0){  // Read 16 byte lines of a total of 64 lines
		memset(name, 0, 16);
		fgets(name, 17, fp); // Get filename
		if (!stricmp(name,dat_string)) data_name = 1;  // Returns 0 if strings are equal
		else fseek(fp,16,SEEK_CUR);  // Go to next line
		line++;
		if (line == 64) {fclose(fp); Error("Can't find inside DAT file: ",dat_string,0);}
	}

	fread(&offset,sizeof(offset),1,fp);//read offset of file in DAT file
	fseek(fp,offset,SEEK_SET);  // Set file pointer at the begining of the file
}

/////////////////////////////////////////////////////////
// PCX Image reader
// - Reads a 256 colors pcx file inside a .DAT file
// - Image must be 320x200 256 color
// - Image must be 8 bits per pixel
// - Sets image width in global variable "tilesetWidth"
// - Sets image height in global variable "tilesetHeight"
// - Sets image information in temp buffer "tempdata1" & "tempdata2"
//   320x200 = 64000 >> tempdata1 (32000) + tempdata2 (32000)
/////////////////////////////////////////////////////////
void LoadImage_PCX(char* filename, char* dat_string){
	FILE *fp;
   int index;
   byte ident; // must be 0x0A for PCX file
   byte version;
   byte encoding;
   byte bitsPerPixel;
   byte checkByte;

   word xMin;
   word xMax;
   word yMin;
   word yMax;

  	word width;
   word height;

   word num_colors;
   byte pal_colors = 0;
   byte first_color = 0;
   byte get_pal = 1;

   int i;
   long l;
   //long bufferSize;
   long imageSize;
   int cnt;
   byte chr;

   // Open file
   fp = fopen(filename,"rb");
	if(!fp) Error("Can't find ",filename,dat_string);

   // Search for filename inside a DAT file
   // and set the filepointer to the begining of data if it exists
	if (dat_string) DAT_Seek(fp,dat_string);

   //Read header
   fread(&ident, sizeof(byte), 1, fp);
   if (ident != 0x0A) Error("Not a PCX file",filename,dat_string);
   fread(&version, sizeof(byte), 1, fp);
   fread(&encoding, sizeof(byte), 1, fp);
   if (encoding != 1) Error("Not a RLE encoding file",filename,dat_string);
   fread(&bitsPerPixel, sizeof(byte), 1, fp);
   if (bitsPerPixel != 8) Error("Not 8 bits per pixel image",filename,dat_string);
   fread(&xMin, sizeof(word), 1, fp);
   fread(&yMin, sizeof(word), 1, fp);
   fread(&xMax, sizeof(word), 1, fp);
   fread(&yMax, sizeof(word), 1, fp);

   // Calculate image width and heigth
   width  = xMax - xMin + 1;
   height = yMax - yMin + 1;
   if (width > 320) Error("Only 320 pixels with image allowed",filename,dat_string);
   if (height > 200) Error("Only 200 pixels height image allowed",filename,dat_string);
   imageSize = (long) width * height;
   if (imageSize > 64000) Error("Loading image bigger than destination memory",filename,dat_string);

   // Skip some data with no use in this case, like hDpi, vDpi, EGA palette, planes, bytes per line, palette info, device width and device heigth
   fseek(fp, 116, SEEK_CUR);  // skip some more data like planes, bytes per line, palette info, device width and device heigth

   // Get image data
   l = 0;
   while(l < imageSize ){
      // Get value
      fread(&chr, sizeof(byte), 1, fp);

      if (EOF == chr){ Error("Unexpected end of fole detected while loading image",filename,dat_string); }

      if (0xC0 == (0xC0 & chr)){ // is it a RLE repeater
         cnt =  0x3F & chr; // Get count
         fread(&chr, sizeof(byte), 1, fp); // Get color
         for (i = 0; i < cnt; i++){
         	tempdata1[l] = chr;
         	l++;
        	}
      }
      else{ // not a RLE...just a single color
      	tempdata1[l] = chr;
       	l++;
      }
   }

   // Get 256 colour palette
   // - Pallete data starts with value 0x0C, so lets go and search it
   fread(&checkByte, sizeof(byte), 1, fp);
   if( checkByte != 12 ) {Error("Expected a 256 color palette, didn't find it",filename,dat_string);}

   pal_colors = 208;
   first_color = 0;

  	for(index=first_color;index<first_color+pal_colors;index++){
		if (get_pal){
			palette[(int)(index*3+0)] = fgetc(fp) >> 2;
			palette[(int)(index*3+1)] = fgetc(fp) >> 2;
			palette[(int)(index*3+2)] = fgetc(fp) >> 2;
		}
	}
   fclose(fp);
}

/////////////////////////////////////////////////////////
// BMP Animation reader
// - Reads a 256 colors bmp file inside a .DAT file
// - Sets image width in local variable "width"
// - Sets image height in local variable "height"
// - Sets image information in temp buffer "->??"
/////////////////////////////////////////////////////////
void LoadAnimation_BMP(char* filename, char* dat_string){
 	FILE *fp;
   int index;
   word header;
   word num_colors;
   byte pal_colors = 0;
   byte get_pal = 1;
   byte pixel_format = 0;
   word width;
	word height;
   byte first_color = 0;
   word x;

   fp = fopen(filename,"rb");
	if(!fp)Error("Can't find ",filename,dat_string);
	if (dat_string) DAT_Seek(fp,dat_string);

   //Read header
	fread(&header, sizeof(word), 1, fp);
	if (header != 0x4D42) Error("Not a BMP file",filename,dat_string);
	fseek(fp, 16, SEEK_CUR);
	fread(&width, sizeof(word), 1, fp);
	fseek(fp, 2, SEEK_CUR);
	fread(&height,sizeof(word), 1, fp);
	fseek(fp, 4, SEEK_CUR);
	fread(&pixel_format,sizeof(byte), 1, fp);
	fseek(fp, 17, SEEK_CUR);
	fread(&num_colors,sizeof(word), 1, fp);
	fseek(fp, 6, SEEK_CUR);

   if (num_colors==0)  num_colors=256;
	if (num_colors > 256) Error("Image has more than 256 colors",filename,dat_string);

   if (height !=32) Error("Wrong size for animation, image must be 128x32: ",filename,dat_string);
   if (width !=128) Error("Wrong size for animation, image must be 128x32: ",filename,dat_string);

   if (pixel_format !=4) Error("Wrong format for animation image, must be 4 bit per pixel: ",filename,dat_string);

   pal_colors = 4;
   first_color = 248;

   //Load Palette
	for(index=first_color;index<first_color+num_colors;index++){
		if (index-first_color == pal_colors) get_pal = 0;
		if (get_pal){
			palette[(int)(index*3+2)] = fgetc(fp) >> 2;
			palette[(int)(index*3+1)] = fgetc(fp) >> 2;
			palette[(int)(index*3+0)] = fgetc(fp) >> 2;
		} else {
			fgetc(fp);
			fgetc(fp);
			fgetc(fp);
		}
		fgetc(fp);
	}

   width = 128;
   //w = 7;

	for(index=31*64;index>=0;index-=64){
		for(x=0;x<64;x++){
			unsigned char c = (byte)fgetc(fp);
      	tempdata1[((index+x)<<1)]   = ((c & 0xF0)>>4) + 248; //1111 0000c
			tempdata1[((index+x)<<1)+1] =  (c & 0x0F)     + 248; //0000 1111c Animation colors from 248 to 251
		}
	}
   fclose(fp);
}

/////////////////////////////////////////////////////////
// BMP Font reader
// - Reads a 256 colors bmp file inside a .DAT file
// - Sets image width in local variable "width"
// - Sets image height in local variable "height"
// - Sets image information in temp buffer "->??"
/////////////////////////////////////////////////////////
void LoadFont_BMP(char* filename, char* dat_string){
 	FILE *fp;
   int index;
   word header;
   word num_colors;
   byte pal_colors = 0;
   byte get_pal = 1;
   byte pixel_format = 0;
   word width;
	word height;
   byte first_color = 0;
   dword offset = 0;
   word x = 0;

   fp = fopen(filename,"rb");
	if(!fp)Error("Can't find ",filename,dat_string);
	if (dat_string) DAT_Seek(fp,dat_string);

   //Read header
	fread(&header, sizeof(word), 1, fp);
	if (header != 0x4D42) Error("Not a BMP file",filename,dat_string);
	fseek(fp, 16, SEEK_CUR);
	fread(&width, sizeof(word), 1, fp);
	fseek(fp, 2, SEEK_CUR);
	fread(&height,sizeof(word), 1, fp);
	fseek(fp, 4, SEEK_CUR);
	fread(&pixel_format,sizeof(byte), 1, fp);
	fseek(fp, 17, SEEK_CUR);
	fread(&num_colors,sizeof(word), 1, fp);
	fseek(fp, 6, SEEK_CUR);

   if (num_colors==0)  num_colors=256;
	if (num_colors > 256) Error("Image has more than 256 colors",filename,dat_string);

   if (height !=32) Error("Wrong size for font, image must be 128x32: ",filename,dat_string);
   if (width !=128) Error("Wrong size for font, image must be 128x32: ",filename,dat_string);

   if (pixel_format !=4) Error("Wrong format for font image, must be 4 bit per pixel: ",filename,dat_string);

   pal_colors = 4; first_color = 252;//If reading font

   //Load Palette
	for(index=first_color;index<first_color+num_colors;index++){
		if (index-first_color == pal_colors) get_pal = 0;
		if (get_pal){
			palette[(int)(index*3+2)] = fgetc(fp) >> 2;
			palette[(int)(index*3+1)] = fgetc(fp) >> 2;
			palette[(int)(index*3+0)] = fgetc(fp) >> 2;
		} else {
			fgetc(fp);
			fgetc(fp);
			fgetc(fp);
		}
		fgetc(fp);
	}

    //LOAD TO TEMP RAM
	x = 0; //data offset
	for (offset = 0; offset < 128*32/2; offset ++){
		unsigned char c = fgetc(fp); //it is a 4 bit BMP, every byte contains 2 pixels
		tempdata1[x  ] = (((c & 0xF0)>>4)); //1111 0000
		tempdata1[x+1] =  ((c & 0x0F)    ); //0000 1111
		x+=2;
	}
   fclose(fp);
}

/////////////////////////////////////////////////////////
// PCX Tileset reader
// - Reads a 256 colors bmp file inside a .DAT file
// - Sets image width in global variable "tilesetWidth"
// - Sets image height in global variable "tilesetHeight"
// - Sets image information in temp buffer "tempdata1"
/////////////////////////////////////////////////////////
void LoadTileset_PCX(char* filename, char* dat_string)
{
	FILE *fp;
   int index;
   byte ident; // must be 0x0A for PCX file
   byte version;
   byte encoding;
   byte bitsPerPixel;
	byte planes;
   byte checkByte;

   word xMin;
   word xMax;
   word yMin;
   word yMax;

   word hDpi;
   word vDpi;

   word bytesPerLine;
   word paletteInfo;

   word deviceWidth;
   word deviceHeight;

   word num_colors;
   byte pal_colors = 0;
   byte first_color = 0;
   byte get_pal = 1;

   int i;
   long l;
   //long bufferSize;
   long imageSize;
   int cnt;
   byte chr;

   fp = fopen(filename,"rb");
	if(!fp)Error("Can't find ",filename,dat_string);
	if (dat_string) DAT_Seek(fp,dat_string);

   //Read header
   fread(&ident, sizeof(byte), 1, fp);
   if (ident != 0x0A) Error("Not a PCX file",filename,dat_string);
   fread(&version, sizeof(byte), 1, fp);
   fread(&encoding, sizeof(byte), 1, fp);
   if (encoding != 1) Error("Not a RLE encoding file",filename,dat_string);
   fread(&bitsPerPixel, sizeof(byte), 1, fp);
   if (bitsPerPixel != 8) Error("Not 8 bits per pixel image",filename,dat_string);
   fread(&xMin, sizeof(word), 1, fp);
   fread(&yMin, sizeof(word), 1, fp);
   fread(&xMax, sizeof(word), 1, fp);
   fread(&yMax, sizeof(word), 1, fp);

   /* do a little precomputing... */
   tilesetWidth  = xMax - xMin + 1;
   tilesetHeight = yMax - yMin + 1;

   fread(&hDpi, sizeof(word), 1, fp);
   fread(&vDpi, sizeof(word), 1, fp);

   fseek(fp, 49, SEEK_CUR);  // EGA palette + 1 byte
   fread(&planes, sizeof(byte), 1, fp);
   fread(&bytesPerLine, sizeof(word), 1, fp);
   fread(&paletteInfo, sizeof(word), 1, fp);
   fread(&deviceWidth, sizeof(word), 1, fp);
   fread(&deviceHeight, sizeof(word), 1, fp);
   fseek(fp, 54, SEEK_CUR);

   /* Here's a program fragment using PCX_encget.  This reads an
	entire file and stores it in a (large) buffer, pointed
	to by the variable "bufr". "fp" is the file pointer for
	the image */
   imageSize = (long) tilesetWidth * tilesetHeight;

   l = 0;
   while(l < imageSize ){
      // Get value
      fread(&chr, sizeof(byte), 1, fp);

      if (EOF == chr){
      	//printf( " EOF detected  \n " );
      	break;
      }

      if (0xC0 == (0xC0 & chr)){ // is it a RLE repeater
         cnt =  0x3F & chr; // Get count
         // Get color
         fread(&chr, sizeof(byte), 1, fp);
         for (i = 0; i < cnt; i++){
         	tempdata1[l] = chr;
         	l++;
        	}
      }
      else{ // not a RLE... end of data
      	tempdata1[l] = chr;
       	l++;
      }
   }


	 // Search 256 colour palette
   // - Pallete data starts with value 0x0C, so lets go and search it
   fread(&checkByte, sizeof(byte), 1, fp);
   if( checkByte != 12 ) {Error("Expected a 256 color palette, didn't find it",filename,dat_string);}

   pal_colors = 208;
   num_colors = 256;
   first_color = 0;

   //Load Palette
	for(index=first_color;index<first_color+num_colors;index++){
		if (index-first_color == pal_colors) get_pal = 0;
		if (get_pal){
			palette[(int)(index*3+0)] = fgetc(fp) >> 2;
			palette[(int)(index*3+1)] = fgetc(fp) >> 2;
			palette[(int)(index*3+2)] = fgetc(fp) >> 2;
		}
	}

   tileset_ntiles = (tilesetWidth>>4) * (tilesetHeight>>4);

   fclose(fp);
}

/////////////////////////////////////////////////////////
// Load text file
// - Reads a TXT file inside a .DAT file
// - Text lines must start with '#<line_number>'
// - Text lines must finish with '$'
// - String is returned as a pointer
/////////////////////////////////////////////////////////
void LoadText(char* filename, char* dat_string, char* line,unsigned char* str, word *length){
	FILE *fp;
   int found = 0;
   int currLine = 0;
   byte data;
   byte num[4] = {0,0,0,0};
   unsigned char st[40];
   word character = 0;

   fp = fopen(filename,"rb");
	if(!fp) Error("Can't find ",filename,dat_string);

   // Search for filename inside a DAT file
   // and set the filepointer to the begining of data if it exists
	if (dat_string) DAT_Seek(fp,dat_string);

   while(found == 0)
   {
   	// search for firts char = '#'
   	fread(&data, sizeof(byte), 1, fp);

      if(data == EOF) { Error("Can't find string number xxx",0,0); }
   	if(data == 35){
      	fread(&num, sizeof(byte), 3, fp);
      	if (!stricmp(line,num)){ // Returns 0 if strings are equal
	  			found = 1;
            // Get all charactes of the line
            fread(&data, sizeof(char), 1, fp);
            while(data != 36){ // 36 == '$'
               st[character] = data;

               fread(&data, sizeof(char), 1, fp);
               character++;
               if(character == 40){
               	fclose(fp);
   					Error(" No end of line detected loading text",dat_string,line);
					}
            }
            st[character] = '\0';
      	}

         currLine ++;

      	if (currLine == 50) {
      		fclose(fp);
   			Error(" Text line not found on file ",dat_string,line);
      	}
      }
   }

   *length = character;
   strcpy(str, st);
   free(num);
   free(st);
   fclose(fp);
}

/////////////////////////////////////////////////////////
// PCX Sprite reader
// - Reads a 256 colors pcx file inside a .DAT file
// - Sets image width in global variable "sprite->width"
// - Sets image height in global variable "sprite->height"
// - Sets image information in temp buffer "sprite->??"
/////////////////////////////////////////////////////////
void LoadSprite_PCX(char* filename, char* dat_string, int sprite_number){
	FILE *fp;
   int index;
   byte ident; // must be 0x0A for PCX file
   byte version;
   byte encoding;
   byte bitsPerPixel;
	byte planes;
   byte checkByte;

   word xMin;
   word xMax;
   word yMin;
   word yMax;

   word hDpi;
   word vDpi;

   word bytesPerLine;
   word paletteInfo;

   word deviceWidth;
   word deviceHeight;

   byte pal_colors = 32;
   byte first_color = 208;
   byte get_pal = 1;
   SPRITE *s = &sprite[sprite_number];

   int i;
   long l;
   long imageSize;
   int cnt;
   byte chr;

   fp = fopen(filename,"rb");
	if(!fp)Error("Can't find ",filename,dat_string);
	if (dat_string) DAT_Seek(fp,dat_string);

   //Read header
   fread(&ident, sizeof(byte), 1, fp);
   if (ident != 0x0A) Error("Not a PCX file",filename,dat_string);
   fread(&version, sizeof(byte), 1, fp);
   fread(&encoding, sizeof(byte), 1, fp);
   if (encoding != 1) Error("Not a RLE encoding file",filename,dat_string);
   fread(&bitsPerPixel, sizeof(byte), 1, fp);
   if (bitsPerPixel != 8) Error("Not 8 bits per pixel image",filename,dat_string);
   fread(&xMin, sizeof(word), 1, fp);
   fread(&yMin, sizeof(word), 1, fp);
   fread(&xMax, sizeof(word), 1, fp);
   fread(&yMax, sizeof(word), 1, fp);

   /* do a little precomputing... */
   s->width  = xMax - xMin + 1;
   s->height = yMax - yMin + 1;
   imageSize = (long) s->width * s->height;

   fseek(fp, 116, SEEK_CUR);  // hDpi,vDpi, EGA palette + 1 byte

   //
   l = 0;
   while(l < imageSize ){

      fread(&chr, sizeof(byte), 1, fp);   // Get value

      if (EOF == chr){ Error("Unexpected EOF on PCX sprite", filename, dat_string); }
      if (0xC0 == (0xC0 & chr)){ // is it a RLE repeater

         cnt =  0x3F & chr; // Get count

         fread(&chr, sizeof(byte), 1, fp); // Get color
         if (EOF == chr){ Error("Unexpected EOF on PCX sprite", filename, dat_string); }

         for (i = 0; i < cnt; i++){
         	if(chr != 0){ tempdata1[l] = chr + first_color; }
            else{tempdata1[l] = chr;}
         	l++;
        	}
      }
      else{ // not a RLE... get single color
      	if(chr != 0){ tempdata1[l] = chr + first_color; }
         else{tempdata1[l] = chr;}
       	l++;
      }
   }

   // Search colour palette
   // - Pallete data starts with value 0x0C, so lets go and search it
   fread(&checkByte, sizeof(byte), 1, fp);
   if( checkByte != 12 ) {Error("Expected a 256 color palette, didn't find it",filename,dat_string);}

   pal_colors = 32;
   first_color = 208;

   //Load Palette
	for(index=first_color;index<first_color+pal_colors;index++){
		if ((index-first_color) == pal_colors) get_pal = 0;
		if (get_pal){
			palette[(int)(index*3+0)] = fgetc(fp) >> 2;
			palette[(int)(index*3+1)] = fgetc(fp) >> 2;
			palette[(int)(index*3+2)] = fgetc(fp) >> 2;
		}
      else {
         fgetc(fp);
			fgetc(fp);
			fgetc(fp);
      }
	}
   fclose(fp);
   free(fp);
}


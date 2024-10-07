/***********************
*  Map functions
************************/

#include "source\engine\engine.h"

word map_width;
word map_height;
word map_width_px;
word map_height_px;
word map_ntiles;
word *map_data;
byte *map_flip;
byte *map_collision;
byte *map_hotspot;
byte *map_event;
int map_offset_x = 0;
int map_offset_y = 0;
int map_setting = 0;
int map_offset_endless = 0;
word map_current_x = 0;
word map_current_y = 0;
word map_last_x;
word map_last_y;
word map_scrollSide;



/////////////////////////////////////////////////////////
// Load map
//  - arg 0: DAT file name pointer
//  - arg 1: TMX map file name
// -----------------------------------------
//   Load tiled TMX map in CSV format
//   Be sure bkg layer map is the first to be exported, (before collision layer map)
//   Does not allow rotation or flip tiles, just straight ones
//   Opacity must be set to 100% !!!
/////////////////////////////////////////////////////////
void LoadMap(char *file, char* dat_string){
	FILE *f;
	word start_bkg_data = 0;
	word start_col_data = 0;
   word start_hspot_data = 0;
   word start_event_data = 0;
   word start_gid = 0;
	word tile;
   //byte coll;
   word gid_back;
   word gid_coll;
   word gid_hspot;
   word gid_event;
   word aux;
	word index = 0;
	//word tindex = 0;
   //word tileheigth = 0;
   //word tilewidth = 0;
	//word tilecount = 0; //Just to get the number of tiles to substract to collision tiles
   word id;

	char line[128];
	char name[64]; //name of the layer in TILED
   
   // Open DAT file and search TMX file inside
   f = fopen(file,"rb");
	if(!f) Error("Can't find ",file,0);
	if (dat_string) DAT_Seek(f,dat_string);
	else fseek(f, 0, SEEK_SET);

   memset(line, 0, 64); // Reserve 64 bytes mem

   // First read firstgid of first layer (first layer must be background, so firstgid must be "1"
	while(start_gid == 0){	//read lines
   	// Read line
		fgets(line, 64, f);  // Get next 64 bytes from file

      // Check firstgid of first layer (first layer must be background, so firstgid must be "1")
      //Ex: <tileset firstgid="xxx" source="name.tsx"/>
		if((line[1] == '<')&&(line[2] == 't')){
			sscanf(line," <tileset firstgid=\"%i[^\"]\" name=\"%24[^\"]\"" ,&gid_back,&aux);
         start_gid = 1;
		}
   }

   // Check if map is correctly made...gid must be equal to 1!!
   if(gid_back != 1) {
   	Error(" Error loading map!!. First gid of firts layer must be equal to 1 ",file,dat_string);
   }

   // Get next line to find next gid
   fgets(line, 64, f);  // Get next 64 bytes from file
   //Ex: <tileset firstgid="xxx" source="name.tsx"/>
   if((line[1] == '<')&&(line[2] == 't')){
		sscanf(line," <tileset firstgid=\"%i[^\"]\" name=\"%24[^\"]\"" ,&gid_coll,&aux);
   }

   // Check if map is correctly made...gid must be grather than 1!!
   if(gid_coll <= 1) {
   	Error(" Error loading map!!. Firts gid of second layer must be grather than 1 ",file,dat_string);
   }

   // Get next line to find next gid
   fgets(line, 64, f);  // Get next 64 bytes from file
   //Ex: <tileset firstgid="xxx" source="name.tsx"/>
   if((line[1] == '<')&&(line[2] == 't')){
		sscanf(line," <tileset firstgid=\"%i[^\"]\" name=\"%24[^\"]\"" ,&gid_hspot,&aux);
   }

   // Check if map is correctly made...gid must be equal to gid_coll + 1!!!
   if(gid_hspot <= gid_coll) {
   	Error(" Error loading map!!. Firts gid of third layer must grather than collision gid ",file,dat_string);
   }

   // Get next line to find next gid
   fgets(line, 64, f);  // Get next 64 bytes from file
   //Ex: <tileset firstgid="xxx" source="name.tsx"/>
   if((line[1] == '<')&&(line[2] == 't')){
		sscanf(line," <tileset firstgid=\"%i[^\"]\" name=\"%24[^\"]\"" ,&gid_event,&aux);
   }

   // Check if map is correctly made...gid must be equal to gid_coll + 1!!!
   if(gid_event <= gid_hspot) {
   	Error(" Error loading map!!. Firts gid of fourth layer must grather than hotspot gid ",file,dat_string);
   }

	// Read file
	while(start_bkg_data == 0){
   	//read line
      fgets(line, 64, f);  // Get next 64 bytes from file

      // Then, find the map begining
		//Ex: <layer id="5" name="name" width="40" height="30">
		if((line[1] == '<')&&(line[2] == 'l')){// get map dimensions
         sscanf(line," <layer id=\"%i\" name=\"%24[^\"]\" width=\"%i\" height=\"%i\"",&id,&name,&map_width,&map_height);
			start_bkg_data = 1;
		}
	}

   // Calculate number of tiles in map
	map_ntiles = map_width * map_height;
   if( (map_ntiles<1) ||(map_ntiles>1800)){
		sprintf(error1, "%d", map_width);
   	sprintf(error2, "%d", map_height);
   	Error("Wrong number of map tiles ",error1, error2);
   }

	fgets(line, 64, f); //skip line: <data encoding="csv">

	//read tile array
	for (index = 0; index < map_ntiles; index++){
		fscanf(f, "%d,",&tile);    // get the tile number
      map_data[index] = tile;
	}

	//Search for collision layer
	while(start_col_data == 0){	//read lines
		memset(line, 0, 64);
		fgets(line, 64, f);
		if((line[1] == '<')&&(line[2] == 'l')){
			sscanf(line," <layer id=\"%i\" name=\"%24[^\"]\" width=\"%i\" height=\"%i\"",&id,&name,&map_width,&map_height);
			start_col_data = 1;
		}
	}
	fgets(line, 64, f); //skip line: <data encoding="csv">

	//read collision array
	for (index = 0; index < map_ntiles; index++){
		fscanf(f, "%d,",&tile);    // get the tile number
		if( tile != 0 ) map_collision[index] = tile - gid_coll + 1;
      else map_collision[index] = tile;
	}

   //Search for hotspot layer
	while(start_hspot_data == 0){	//read lines
		memset(line, 0, 64);
		fgets(line, 64, f);
		if((line[1] == '<')&&(line[2] == 'l')){
			sscanf(line," <layer id=\"%i\" name=\"%24[^\"]\" width=\"%i\" height=\"%i\"",&id,&name,&map_width,&map_height);
			start_hspot_data = 1;
		}
	}
	fgets(line, 64, f); //skip line: <data encoding="csv">

	//read collision array
	for (index = 0; index < map_ntiles; index++){
		fscanf(f, "%d,",&tile);    // get the tile number
		if( tile != 0 ) map_hotspot[index] = tile - gid_hspot + 1;
      else map_hotspot[index] = 0;
	}

   //Search for event layer
	while(start_event_data == 0){	//read lines
		memset(line, 0, 64);
		fgets(line, 64, f);
		if((line[1] == '<')&&(line[2] == 'l')){
			sscanf(line," <layer id=\"%i\" name=\"%24[^\"]\" width=\"%i\" height=\"%i\"",&id,&name,&map_width,&map_height);
			start_event_data = 1;
		}
	}
	fgets(line, 64, f); //skip line: <data encoding="csv">

	//read collision array
	for (index = 0; index < map_ntiles; index++){
		fscanf(f, "%d,",&tile);    // get the tile number
		if( tile != 0 ) map_event[index] = tile - gid_event + 1;
      else map_event[index] = 0;
	}

	fclose(f);
}




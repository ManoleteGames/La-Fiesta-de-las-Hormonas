/***********************
*  common
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Go to next day
/////////////////////////////////////////////////////////
void far InitDay(void){

	// Update day on panel
	sprintf(string, "%02d", player.day);
	VGA_PrintPanelText(1,1,strlen(string),string);

   SetNewTime(120);
   UpdateGoodness(0);
   UpdateInteligence(0);
   UpdatePopularity(0);

   switch(player.day){
   	case 4:  //////////////////////////// day 4 ///////////////////////////
         player.score[4] = 0;

      	// Initialize events masks
   		player.ext1_event_mask[1] = 1;
   		player.ext1_event_mask[2] = 1;
			player.ext1_event_mask[3] = 1;
			player.ext1_event_mask[4] = 0;
   		player.ext1_event_mask[5] = 0;
   		player.ext1_event_mask[6] = 0;
   		player.ext1_event_mask[7] = 0;
   		player.ext1_event_mask[8] = 0;
   		player.ext1_event_mask[9] = 0;
   		player.ext1_event_mask[10] = 0;
   		player.ext1_event_mask[11] = 0;
   		player.ext1_event_mask[12] = 0;
   		player.ext1_event_mask[13] = 0;
   		player.ext1_event_mask[14] = 0;
   		player.ext1_event_mask[15] = 0;

   		player.ext2_event_mask[1] = 1;
   		player.ext2_event_mask[2] = 1;
			player.ext2_event_mask[3] = 1;
			player.ext2_event_mask[4] = 0;
   		player.ext2_event_mask[5] = 0;
   		player.ext2_event_mask[6] = 0;
   		player.ext2_event_mask[7] = 0;
   		player.ext2_event_mask[8] = 0;
   		player.ext2_event_mask[9] = 0;
   		player.ext2_event_mask[10] = 0;
   		player.ext2_event_mask[11] = 0;
   		player.ext2_event_mask[12] = 0;
   		player.ext2_event_mask[13] = 0;
   		player.ext2_event_mask[14] = 0;
   		player.ext2_event_mask[15] = 0;

         player.floor1_event_mask[1] = 1;
   		player.floor1_event_mask[2] = 1;
			player.floor1_event_mask[3] = 1;
			player.floor1_event_mask[4] = 1;
   		player.floor1_event_mask[5] = 0;
   		player.floor1_event_mask[6] = 0;
   		player.floor1_event_mask[7] = 0;
   		player.floor1_event_mask[8] = 0;
   		player.floor1_event_mask[9] = 0;
   		player.floor1_event_mask[10] = 0;
   		player.floor1_event_mask[11] = 0;
   		player.floor1_event_mask[12] = 0;
   		player.floor1_event_mask[13] = 0;
   		player.floor1_event_mask[14] = 0;
   		player.floor1_event_mask[15] = 0;

   		player.floor2_event_mask[1] = 1;
   		player.floor2_event_mask[2] = 1;
			player.floor2_event_mask[3] = 1;
			player.floor2_event_mask[4] = 0;
   		player.floor2_event_mask[5] = 0;
   		player.floor2_event_mask[6] = 0;
   		player.floor2_event_mask[7] = 0;
   		player.floor2_event_mask[8] = 0;
   		player.floor2_event_mask[9] = 0;
   		player.floor2_event_mask[10] = 0;
   		player.floor2_event_mask[11] = 0;
   		player.floor2_event_mask[12] = 0;
   		player.floor2_event_mask[13] = 0;
   		player.floor2_event_mask[14] = 0;
   		player.floor2_event_mask[15] = 0;

   		player.gym_event_mask[1] = 1;
   		player.gym_event_mask[2] = 0;
			player.gym_event_mask[3] = 0;
			player.gym_event_mask[4] = 0;
   		player.gym_event_mask[5] = 0;
   		player.gym_event_mask[6] = 0;
   		player.gym_event_mask[7] = 0;
   		player.gym_event_mask[8] = 0;
   		player.gym_event_mask[9] = 0;
   		player.gym_event_mask[10] = 0;
   		player.gym_event_mask[11] = 0;
   		player.gym_event_mask[12] = 0;
   		player.gym_event_mask[13] = 0;
   		player.gym_event_mask[14] = 0;
   		player.gym_event_mask[15] = 0;

   		// Initialize hotspot masks
   		player.ext1_hotspot_mask[1] = 0;
   		player.ext1_hotspot_mask[2] = 0;
			player.ext1_hotspot_mask[3] = 0;
			player.ext1_hotspot_mask[4] = 0;
   		player.ext1_hotspot_mask[5] = 0;
   		player.ext1_hotspot_mask[6] = 0;
   		player.ext1_hotspot_mask[7] = 0;
   		player.ext1_hotspot_mask[8] = 0;
   		player.ext1_hotspot_mask[9] = 0;
   		player.ext1_hotspot_mask[10] = 0;
   		player.ext1_hotspot_mask[11] = 0;
   		player.ext1_hotspot_mask[12] = 0;
   		player.ext1_hotspot_mask[13] = 0;
   		player.ext1_hotspot_mask[14] = 0;
   		player.ext1_hotspot_mask[15] = 0;

   		player.ext2_hotspot_mask[1] = 0;
   		player.ext2_hotspot_mask[2] = 0;
			player.ext2_hotspot_mask[3] = 0;
			player.ext2_hotspot_mask[4] = 0;
   		player.ext2_hotspot_mask[5] = 0;
   		player.ext2_hotspot_mask[6] = 0;
   		player.ext2_hotspot_mask[7] = 0;
   		player.ext2_hotspot_mask[8] = 0;
   		player.ext2_hotspot_mask[9] = 0;
   		player.ext2_hotspot_mask[10] = 0;
   		player.ext2_hotspot_mask[11] = 0;
   		player.ext2_hotspot_mask[12] = 0;
   		player.ext2_hotspot_mask[13] = 0;
   		player.ext2_hotspot_mask[14] = 0;
   		player.ext2_hotspot_mask[15] = 0;

   		player.floor1_hotspot_mask[1] = 1; // window
   		player.floor1_hotspot_mask[2] = 1; // extinguisher
			player.floor1_hotspot_mask[3] = 1; // girls bathroom
			player.floor1_hotspot_mask[4] = 1; // boys bathroom
   		player.floor1_hotspot_mask[5] = 1; // jon sign
   		player.floor1_hotspot_mask[6] = 0; // spare
   		player.floor1_hotspot_mask[7] = 0; // spare
   		player.floor1_hotspot_mask[8] = 1; // news board
   		player.floor1_hotspot_mask[9] = 0; // arcade
   		player.floor1_hotspot_mask[10] = 1; // bar
   		player.floor1_hotspot_mask[11] = 1; // exams
   		player.floor1_hotspot_mask[12] = 1; // computer
   		player.floor1_hotspot_mask[13] = 1; // lockers
   		player.floor1_hotspot_mask[14] = 1; // nerds
   		player.floor1_hotspot_mask[15] = 1; // director
   		player.floor1_hotspot_mask[16] = 1; // janitor
   		player.floor1_hotspot_mask[17] = 0; // nerds moved
         player.floor1_hotspot_mask[18] = 1; // printer

   		player.floor2_hotspot_mask[1] = 1;
   		player.floor2_hotspot_mask[2] = 0;
			player.floor2_hotspot_mask[3] = 1;
			player.floor2_hotspot_mask[4] = 0;
   		player.floor2_hotspot_mask[5] = 0;
   		player.floor2_hotspot_mask[6] = 1;
   		player.floor2_hotspot_mask[7] = 1;
   		player.floor2_hotspot_mask[8] = 1;
   		player.floor2_hotspot_mask[9] = 0;
         player.floor2_hotspot_mask[10] = 1;
   		player.floor2_hotspot_mask[11] = 1;
   		player.floor2_hotspot_mask[12] = 1;
   		player.floor2_hotspot_mask[13] = 1; // window
   		player.floor2_hotspot_mask[14] = 0;
   		player.floor2_hotspot_mask[15] = 0;

   		player.gym_hotspot_mask[1] = 1;
   		player.gym_hotspot_mask[2] = 1;
			player.gym_hotspot_mask[3] = 0;
			player.gym_hotspot_mask[4] = 0;
   		player.gym_hotspot_mask[5] = 0;
   		player.gym_hotspot_mask[6] = 0;
   		player.gym_hotspot_mask[7] = 0;
   		player.gym_hotspot_mask[8] = 1;
         player.gym_hotspot_mask[9] = 0;
   		player.gym_hotspot_mask[10] = 0;
   		player.gym_hotspot_mask[11] = 0;
   		player.gym_hotspot_mask[12] = 0;
   		player.gym_hotspot_mask[13] = 0;
   		player.gym_hotspot_mask[14] = 0;
   		player.gym_hotspot_mask[15] = 0;

         player.scn_girls = 0;
   		player.scn_main = 0;
   		player.scn_nerds = 0;
   		player.scn_director = 0;
   		player.scn_janitor = 0;
   		player.scn_thugs = 0;
   		player.scn_girls = 0;
   		player.scn_jessy = 0;
         player.scn_sensei = 0;

   		player.mission_cheat = 0;
         player.mission_party = 0;
   		player.mission_doll = 0;
   		//player.mission_arcade = 0;
   		player.mission_bag = 0;

   		player.item_chalk = 0;
   		player.item_exams = 0;
   		player.item_bag = 0;
         player.item_keys = 0;

         time_minutes = 0;
         SetNewTime(120);

			break;
   	case 3:  //////////////////////////// day 3 ///////////////////////////
      	player.score[3] = 0;
         // Initialize events masks
   		player.ext1_event_mask[1] = 1;
   		player.ext1_event_mask[2] = 1;
			player.ext1_event_mask[3] = 1;
			player.ext1_event_mask[4] = 0;
   		player.ext1_event_mask[5] = 0;
   		player.ext1_event_mask[6] = 0;
   		player.ext1_event_mask[7] = 0;
   		player.ext1_event_mask[8] = 0;
   		player.ext1_event_mask[9] = 0;
   		player.ext1_event_mask[10] = 0;
   		player.ext1_event_mask[11] = 0;
   		player.ext1_event_mask[12] = 0;
   		player.ext1_event_mask[13] = 0;
   		player.ext1_event_mask[14] = 0;
   		player.ext1_event_mask[15] = 0;

   		player.ext2_event_mask[1] = 1;
   		player.ext2_event_mask[2] = 1;
			player.ext2_event_mask[3] = 1;
			player.ext2_event_mask[4] = 0;
   		player.ext2_event_mask[5] = 0;
   		player.ext2_event_mask[6] = 0;
   		player.ext2_event_mask[7] = 0;
   		player.ext2_event_mask[8] = 0;
   		player.ext2_event_mask[9] = 0;
   		player.ext2_event_mask[10] = 0;
   		player.ext2_event_mask[11] = 0;
   		player.ext2_event_mask[12] = 0;
   		player.ext2_event_mask[13] = 0;
   		player.ext2_event_mask[14] = 0;
   		player.ext2_event_mask[15] = 0;

         player.floor1_event_mask[1] = 1;
   		player.floor1_event_mask[2] = 1;
			player.floor1_event_mask[3] = 1;
			player.floor1_event_mask[4] = 1;
   		player.floor1_event_mask[5] = 0;
   		player.floor1_event_mask[6] = 0;
   		player.floor1_event_mask[7] = 0;
   		player.floor1_event_mask[8] = 0;
   		player.floor1_event_mask[9] = 0;
   		player.floor1_event_mask[10] = 0;
   		player.floor1_event_mask[11] = 0;
   		player.floor1_event_mask[12] = 0;
   		player.floor1_event_mask[13] = 0;
   		player.floor1_event_mask[14] = 0;
   		player.floor1_event_mask[15] = 0;

   		player.floor2_event_mask[1] = 1;
   		player.floor2_event_mask[2] = 1;
			player.floor2_event_mask[3] = 1;
			player.floor2_event_mask[4] = 0;
   		player.floor2_event_mask[5] = 0;
   		player.floor2_event_mask[6] = 0;
   		player.floor2_event_mask[7] = 0;
   		player.floor2_event_mask[8] = 0;
   		player.floor2_event_mask[9] = 0;
   		player.floor2_event_mask[10] = 0;
   		player.floor2_event_mask[11] = 0;
   		player.floor2_event_mask[12] = 0;
   		player.floor2_event_mask[13] = 0;
   		player.floor2_event_mask[14] = 0;
   		player.floor2_event_mask[15] = 0;

   		player.gym_event_mask[1] = 1;
   		player.gym_event_mask[2] = 0;
			player.gym_event_mask[3] = 0;
			player.gym_event_mask[4] = 0;
   		player.gym_event_mask[5] = 0;
   		player.gym_event_mask[6] = 0;
   		player.gym_event_mask[7] = 0;
   		player.gym_event_mask[8] = 0;
   		player.gym_event_mask[9] = 0;
   		player.gym_event_mask[10] = 0;
   		player.gym_event_mask[11] = 0;
   		player.gym_event_mask[12] = 0;
   		player.gym_event_mask[13] = 0;
   		player.gym_event_mask[14] = 0;
   		player.gym_event_mask[15] = 0;

   		// Initialize hotspot masks
   		player.ext1_hotspot_mask[1] = 0;
   		player.ext1_hotspot_mask[2] = 0;
			player.ext1_hotspot_mask[3] = 0;
			player.ext1_hotspot_mask[4] = 0;
   		player.ext1_hotspot_mask[5] = 0;
   		player.ext1_hotspot_mask[6] = 0;
   		player.ext1_hotspot_mask[7] = 0;
   		player.ext1_hotspot_mask[8] = 0;
   		player.ext1_hotspot_mask[9] = 0;
   		player.ext1_hotspot_mask[10] = 0;
   		player.ext1_hotspot_mask[11] = 0;
   		player.ext1_hotspot_mask[12] = 0;
   		player.ext1_hotspot_mask[13] = 0;
   		player.ext1_hotspot_mask[14] = 0;
   		player.ext1_hotspot_mask[15] = 0;

   		player.ext2_hotspot_mask[1] = 0;
   		player.ext2_hotspot_mask[2] = 0;
			player.ext2_hotspot_mask[3] = 0;
			player.ext2_hotspot_mask[4] = 0;
   		player.ext2_hotspot_mask[5] = 0;
   		player.ext2_hotspot_mask[6] = 0;
   		player.ext2_hotspot_mask[7] = 0;
   		player.ext2_hotspot_mask[8] = 0;
   		player.ext2_hotspot_mask[9] = 1;
   		player.ext2_hotspot_mask[10] = 0;
   		player.ext2_hotspot_mask[11] = 0;
   		player.ext2_hotspot_mask[12] = 0;
   		player.ext2_hotspot_mask[13] = 0;
   		player.ext2_hotspot_mask[14] = 0;
   		player.ext2_hotspot_mask[15] = 0;

   		player.floor1_hotspot_mask[1] = 1; // window
   		player.floor1_hotspot_mask[2] = 1; // extinguisher
			player.floor1_hotspot_mask[3] = 1; // girls bathroom
			player.floor1_hotspot_mask[4] = 1; // boys bathroom
   		player.floor1_hotspot_mask[5] = 1; // jon sign
   		player.floor1_hotspot_mask[6] = 0; // spare
   		player.floor1_hotspot_mask[7] = 0; // spare
   		player.floor1_hotspot_mask[8] = 1; // news board
   		player.floor1_hotspot_mask[9] = 0; // arcade
   		player.floor1_hotspot_mask[10] = 1; // bar
   		player.floor1_hotspot_mask[11] = 0; // exams
   		player.floor1_hotspot_mask[12] = 1; // computer
   		player.floor1_hotspot_mask[13] = 1; // lockers
   		player.floor1_hotspot_mask[14] = 1; // nerds / thugs
   		player.floor1_hotspot_mask[15] = 1; // director
   		player.floor1_hotspot_mask[16] = 1; // janitor
   		player.floor1_hotspot_mask[17] = 0; // nerds moved
         player.floor1_hotspot_mask[18] = 0; //
         player.floor1_hotspot_mask[19] = 1; // keys

   		player.floor2_hotspot_mask[1] = 1;
   		player.floor2_hotspot_mask[2] = 1;
			player.floor2_hotspot_mask[3] = 1;
			player.floor2_hotspot_mask[4] = 1;
   		player.floor2_hotspot_mask[5] = 1;
   		player.floor2_hotspot_mask[6] = 0;
   		player.floor2_hotspot_mask[7] = 0;
   		player.floor2_hotspot_mask[8] = 0;
   		player.floor2_hotspot_mask[9] = 0;
         player.floor2_hotspot_mask[10] = 0;
   		player.floor2_hotspot_mask[11] = 0;
   		player.floor2_hotspot_mask[12] = 0;
   		player.floor2_hotspot_mask[13] = 1;  // window
   		player.floor2_hotspot_mask[14] = 0;
   		player.floor2_hotspot_mask[15] = 0;

   		player.gym_hotspot_mask[1] = 1;
   		player.gym_hotspot_mask[2] = 1;
			player.gym_hotspot_mask[3] = 0;
			player.gym_hotspot_mask[4] = 0;
   		player.gym_hotspot_mask[5] = 0;
   		player.gym_hotspot_mask[6] = 0;
   		player.gym_hotspot_mask[7] = 0;
   		player.gym_hotspot_mask[8] = 1; // sensei
         player.gym_hotspot_mask[9] = 1; // Girls
   		player.gym_hotspot_mask[10] = 0;
   		player.gym_hotspot_mask[11] = 0;
   		player.gym_hotspot_mask[12] = 0;
   		player.gym_hotspot_mask[13] = 0;
   		player.gym_hotspot_mask[14] = 0;
   		player.gym_hotspot_mask[15] = 0;

   		player.scn_girls = 0;
   		player.scn_main = 0;
   		player.scn_nerds = 0;
   		player.scn_director = 0;
   		player.scn_janitor = 0;
   		player.scn_thugs = 0;
   		player.scn_girls = 0;
   		player.scn_jessy = 0;
         player.scn_sensei = 0;

   		//player.mission_cheat = 0;
         //player.mission_party = 0;
   		player.mission_doll = 0;
   		//player.mission_arcade = 0;
   		player.mission_bag = 0;

   		player.item_chalk = 0;
   		//player.item_exams = 0;
   		player.item_bag = 0;
         player.item_keys = 0;


         time_minutes = 0;
			SetNewTime(120);

      	break;
      case 2: //////////////////////////// day 2 ///////////////////////////
      	player.score[2] = 0;
         // Initialize events masks
   		player.ext1_event_mask[1] = 1;
   		player.ext1_event_mask[2] = 1;
			player.ext1_event_mask[3] = 1;
			player.ext1_event_mask[4] = 1;
   		player.ext1_event_mask[5] = 1;
   		player.ext1_event_mask[6] = 1;
   		player.ext1_event_mask[7] = 1;
   		player.ext1_event_mask[8] = 0;
   		player.ext1_event_mask[9] = 0;
   		player.ext1_event_mask[10] = 0;
   		player.ext1_event_mask[11] = 0;
   		player.ext1_event_mask[12] = 0;
   		player.ext1_event_mask[13] = 0;
   		player.ext1_event_mask[14] = 0;
   		player.ext1_event_mask[15] = 0;

   		player.ext2_event_mask[1] = 1;
   		player.ext2_event_mask[2] = 1;
			player.ext2_event_mask[3] = 1;
			player.ext2_event_mask[4] = 0;
   		player.ext2_event_mask[5] = 0;
   		player.ext2_event_mask[6] = 0;
   		player.ext2_event_mask[7] = 0;
   		player.ext2_event_mask[8] = 0;
   		player.ext2_event_mask[9] = 0;
   		player.ext2_event_mask[10] = 0;
   		player.ext2_event_mask[11] = 0;
   		player.ext2_event_mask[12] = 0;
   		player.ext2_event_mask[13] = 0;
   		player.ext2_event_mask[14] = 0;
   		player.ext2_event_mask[15] = 0;

         player.floor1_event_mask[1] = 1;
   		player.floor1_event_mask[2] = 1;
			player.floor1_event_mask[3] = 1;
			player.floor1_event_mask[4] = 1;
   		player.floor1_event_mask[5] = 0;
   		player.floor1_event_mask[6] = 0;
   		player.floor1_event_mask[7] = 0;
   		player.floor1_event_mask[8] = 0;
   		player.floor1_event_mask[9] = 0;
   		player.floor1_event_mask[10] = 0;
   		player.floor1_event_mask[11] = 0;
   		player.floor1_event_mask[12] = 0;
   		player.floor1_event_mask[13] = 0;
   		player.floor1_event_mask[14] = 0;
   		player.floor1_event_mask[15] = 0;

   		player.floor2_event_mask[1] = 1;
   		player.floor2_event_mask[2] = 1;
			player.floor2_event_mask[3] = 1;
			player.floor2_event_mask[4] = 0;
   		player.floor2_event_mask[5] = 0;
   		player.floor2_event_mask[6] = 0;
   		player.floor2_event_mask[7] = 0;
   		player.floor2_event_mask[8] = 0;
   		player.floor2_event_mask[9] = 0;
   		player.floor2_event_mask[10] = 0;
   		player.floor2_event_mask[11] = 0;
   		player.floor2_event_mask[12] = 0;
   		player.floor2_event_mask[13] = 0;
   		player.floor2_event_mask[14] = 0;
   		player.floor2_event_mask[15] = 0;

   		player.gym_event_mask[1] = 1;
   		player.gym_event_mask[2] = 0;
			player.gym_event_mask[3] = 0;
			player.gym_event_mask[4] = 0;
   		player.gym_event_mask[5] = 0;
   		player.gym_event_mask[6] = 0;
   		player.gym_event_mask[7] = 0;
   		player.gym_event_mask[8] = 0;
   		player.gym_event_mask[9] = 0;
   		player.gym_event_mask[10] = 0;
   		player.gym_event_mask[11] = 0;
   		player.gym_event_mask[12] = 0;
   		player.gym_event_mask[13] = 0;
   		player.gym_event_mask[14] = 0;
   		player.gym_event_mask[15] = 0;

   		// Initialize hotspot masks
   		player.ext1_hotspot_mask[1] = 0;
   		player.ext1_hotspot_mask[2] = 0;
			player.ext1_hotspot_mask[3] = 0;
			player.ext1_hotspot_mask[4] = 0;
   		player.ext1_hotspot_mask[5] = 0;
   		player.ext1_hotspot_mask[6] = 0;
   		player.ext1_hotspot_mask[7] = 0;
   		player.ext1_hotspot_mask[8] = 0;
   		player.ext1_hotspot_mask[9] = 0;
   		player.ext1_hotspot_mask[10] = 0;
   		player.ext1_hotspot_mask[11] = 0;
   		player.ext1_hotspot_mask[12] = 0;
   		player.ext1_hotspot_mask[13] = 1; // Window
   		player.ext1_hotspot_mask[14] = 1; // bag
   		player.ext1_hotspot_mask[15] = 0;

   		player.ext2_hotspot_mask[1] = 0;
   		player.ext2_hotspot_mask[2] = 0;
			player.ext2_hotspot_mask[3] = 0;
			player.ext2_hotspot_mask[4] = 0;
   		player.ext2_hotspot_mask[5] = 0;
   		player.ext2_hotspot_mask[6] = 0;
   		player.ext2_hotspot_mask[7] = 0;
   		player.ext2_hotspot_mask[8] = 1; // thugs
   		player.ext2_hotspot_mask[9] = 0;
   		player.ext2_hotspot_mask[10] = 0;
   		player.ext2_hotspot_mask[11] = 0;
   		player.ext2_hotspot_mask[12] = 0;
   		player.ext2_hotspot_mask[13] = 0;
   		player.ext2_hotspot_mask[14] = 0;
   		player.ext2_hotspot_mask[15] = 0;

   		player.floor1_hotspot_mask[1] = 1; // window
   		player.floor1_hotspot_mask[2] = 1; // extinguisher
			player.floor1_hotspot_mask[3] = 1; // girls bathroom
			player.floor1_hotspot_mask[4] = 1; // boys bathroom
   		player.floor1_hotspot_mask[5] = 1; // jon sign
   		player.floor1_hotspot_mask[6] = 0; // spare
   		player.floor1_hotspot_mask[7] = 0; // spare
   		player.floor1_hotspot_mask[8] = 1; // news board
   		player.floor1_hotspot_mask[9] = 1; // arcade
   		player.floor1_hotspot_mask[10] = 1; // bar
   		player.floor1_hotspot_mask[11] = 0; // exams
   		player.floor1_hotspot_mask[12] = 1; // computer
   		player.floor1_hotspot_mask[13] = 1; // lockers
   		player.floor1_hotspot_mask[14] = 1; // nerds / thugs
   		player.floor1_hotspot_mask[15] = 1; // director
   		player.floor1_hotspot_mask[16] = 1; // janitor
   		player.floor1_hotspot_mask[17] = 1; // jessy
         player.floor1_hotspot_mask[18] = 0; //
         player.floor1_hotspot_mask[19] = 0; // keys

   		player.floor2_hotspot_mask[1] = 1;
   		player.floor2_hotspot_mask[2] = 1;
			player.floor2_hotspot_mask[3] = 1;
			player.floor2_hotspot_mask[4] = 1;
   		player.floor2_hotspot_mask[5] = 1;
   		player.floor2_hotspot_mask[6] = 0;
   		player.floor2_hotspot_mask[7] = 0;
   		player.floor2_hotspot_mask[8] = 0;
   		player.floor2_hotspot_mask[9] = 0;
         player.floor2_hotspot_mask[10] = 0;
   		player.floor2_hotspot_mask[11] = 0;
   		player.floor2_hotspot_mask[12] = 1; // nerds
   		player.floor2_hotspot_mask[13] = 1; // window
   		player.floor2_hotspot_mask[14] = 0;
   		player.floor2_hotspot_mask[15] = 0;

   		player.gym_hotspot_mask[1] = 1;
   		player.gym_hotspot_mask[2] = 1;
			player.gym_hotspot_mask[3] = 0;
			player.gym_hotspot_mask[4] = 0;
   		player.gym_hotspot_mask[5] = 0;
   		player.gym_hotspot_mask[6] = 0;
   		player.gym_hotspot_mask[7] = 0;
   		player.gym_hotspot_mask[8] = 1; // sensei
         player.gym_hotspot_mask[9] = 1; // Girls
   		player.gym_hotspot_mask[10] = 0;
   		player.gym_hotspot_mask[11] = 0;
   		player.gym_hotspot_mask[12] = 0;
   		player.gym_hotspot_mask[13] = 0;
   		player.gym_hotspot_mask[14] = 0;
   		player.gym_hotspot_mask[15] = 0;

   		player.scn_girls = 0;
   		player.scn_main = 0;
   		player.scn_nerds = 0;
   		player.scn_director = 0;
   		player.scn_janitor = 0;
   		player.scn_thugs = 0;
   		player.scn_girls = 0;
   		player.scn_jessy = 0;
         player.scn_sensei = 0;

   		//player.mission_cheat = 0;
         //player.mission_party = 0;
   		//player.mission_doll = 0;
   		//player.mission_arcade = 0;
   		//player.mission_bag = 0;

   		player.item_chalk = 0;
   		//player.item_exams = 0;
   		player.item_bag = 0;
         player.item_keys = 0;


         time_minutes = 0;
			SetNewTime(120);

      	break;
      case 1: //////////////////////////// day 1 ///////////////////////////
      	player.score[1] = 0;
         // Initialize events masks
   		player.ext1_event_mask[1] = 1;
   		player.ext1_event_mask[2] = 1;
			player.ext1_event_mask[3] = 1;
			player.ext1_event_mask[4] = 0;
   		player.ext1_event_mask[5] = 0;
   		player.ext1_event_mask[6] = 0;
   		player.ext1_event_mask[7] = 0;
   		player.ext1_event_mask[8] = 0;
   		player.ext1_event_mask[9] = 0;
   		player.ext1_event_mask[10] = 0;
   		player.ext1_event_mask[11] = 0;
   		player.ext1_event_mask[12] = 0;
   		player.ext1_event_mask[13] = 0;
   		player.ext1_event_mask[14] = 0;
   		player.ext1_event_mask[15] = 0;

   		player.ext2_event_mask[1] = 1;
   		player.ext2_event_mask[2] = 1;
			player.ext2_event_mask[3] = 1;
			player.ext2_event_mask[4] = 0;
   		player.ext2_event_mask[5] = 0;
   		player.ext2_event_mask[6] = 0;
   		player.ext2_event_mask[7] = 0;
   		player.ext2_event_mask[8] = 0;
   		player.ext2_event_mask[9] = 0;
   		player.ext2_event_mask[10] = 0;
   		player.ext2_event_mask[11] = 0;
   		player.ext2_event_mask[12] = 0;
   		player.ext2_event_mask[13] = 0;
   		player.ext2_event_mask[14] = 0;
   		player.ext2_event_mask[15] = 0;

         player.floor1_event_mask[1] = 1;
   		player.floor1_event_mask[2] = 1;
			player.floor1_event_mask[3] = 1;
			player.floor1_event_mask[4] = 1;
   		player.floor1_event_mask[5] = 0;
   		player.floor1_event_mask[6] = 0;
   		player.floor1_event_mask[7] = 0;
   		player.floor1_event_mask[8] = 0;
   		player.floor1_event_mask[9] = 0;
   		player.floor1_event_mask[10] = 1; // anto and jon on the hall
   		player.floor1_event_mask[11] = 0;
   		player.floor1_event_mask[12] = 0;
   		player.floor1_event_mask[13] = 0;
   		player.floor1_event_mask[14] = 0;
   		player.floor1_event_mask[15] = 0;

   		player.floor2_event_mask[1] = 1;
   		player.floor2_event_mask[2] = 1;
			player.floor2_event_mask[3] = 1;
			player.floor2_event_mask[4] = 0;
   		player.floor2_event_mask[5] = 0;
   		player.floor2_event_mask[6] = 0;
   		player.floor2_event_mask[7] = 0;
   		player.floor2_event_mask[8] = 0;
   		player.floor2_event_mask[9] = 0;
   		player.floor2_event_mask[10] = 0;
   		player.floor2_event_mask[11] = 0;
   		player.floor2_event_mask[12] = 0;
   		player.floor2_event_mask[13] = 0;
   		player.floor2_event_mask[14] = 0;
   		player.floor2_event_mask[15] = 0;

   		player.gym_event_mask[1] = 1;
   		player.gym_event_mask[2] = 0;
			player.gym_event_mask[3] = 0;
			player.gym_event_mask[4] = 0;
   		player.gym_event_mask[5] = 0;
   		player.gym_event_mask[6] = 0;
   		player.gym_event_mask[7] = 0;
   		player.gym_event_mask[8] = 0;
   		player.gym_event_mask[9] = 0;
   		player.gym_event_mask[10] = 0;
   		player.gym_event_mask[11] = 0;
   		player.gym_event_mask[12] = 0;
   		player.gym_event_mask[13] = 0;
   		player.gym_event_mask[14] = 0;
   		player.gym_event_mask[15] = 0;

   		// Initialize hotspot masks
   		player.ext1_hotspot_mask[1] = 0;
   		player.ext1_hotspot_mask[2] = 0;
			player.ext1_hotspot_mask[3] = 0;
			player.ext1_hotspot_mask[4] = 0;
   		player.ext1_hotspot_mask[5] = 0;
   		player.ext1_hotspot_mask[6] = 0;
   		player.ext1_hotspot_mask[7] = 0;
   		player.ext1_hotspot_mask[8] = 0;
   		player.ext1_hotspot_mask[9] = 0;
   		player.ext1_hotspot_mask[10] = 0;
   		player.ext1_hotspot_mask[11] = 0;
   		player.ext1_hotspot_mask[12] = 0;
   		player.ext1_hotspot_mask[13] = 0;
   		player.ext1_hotspot_mask[14] = 0;
   		player.ext1_hotspot_mask[15] = 0;

   		player.ext2_hotspot_mask[1] = 0;
   		player.ext2_hotspot_mask[2] = 0;
			player.ext2_hotspot_mask[3] = 0;
			player.ext2_hotspot_mask[4] = 0;
   		player.ext2_hotspot_mask[5] = 0;
   		player.ext2_hotspot_mask[6] = 0;
   		player.ext2_hotspot_mask[7] = 0;
   		player.ext2_hotspot_mask[8] = 1; // thugs
   		player.ext2_hotspot_mask[9] = 0;
   		player.ext2_hotspot_mask[10] = 1; // janitor
   		player.ext2_hotspot_mask[11] = 1; // thugs & nerds fight
   		player.ext2_hotspot_mask[12] = 0;
   		player.ext2_hotspot_mask[13] = 0;
   		player.ext2_hotspot_mask[14] = 0;
   		player.ext2_hotspot_mask[15] = 0;

   		player.floor1_hotspot_mask[1] = 1; // window
   		player.floor1_hotspot_mask[2] = 1; // extinguisher
			player.floor1_hotspot_mask[3] = 1; // girls bathroom
			player.floor1_hotspot_mask[4] = 1; // boys bathroom
   		player.floor1_hotspot_mask[5] = 1; // jon sign
   		player.floor1_hotspot_mask[6] = 0; // spare
   		player.floor1_hotspot_mask[7] = 0; // spare
   		player.floor1_hotspot_mask[8] = 1; // news board
   		player.floor1_hotspot_mask[9] = 1; // arcade
   		player.floor1_hotspot_mask[10] = 1; // bar
   		player.floor1_hotspot_mask[11] = 0; // exams
   		player.floor1_hotspot_mask[12] = 1; // computer
   		player.floor1_hotspot_mask[13] = 1; // lockers
   		player.floor1_hotspot_mask[14] = 1; // nerds / thugs
   		player.floor1_hotspot_mask[15] = 1; // director
   		player.floor1_hotspot_mask[16] = 0; // janitor
   		player.floor1_hotspot_mask[17] = 1; // jon y anto
         player.floor1_hotspot_mask[18] = 0; //
         player.floor1_hotspot_mask[19] = 0; // keys

   		player.floor2_hotspot_mask[1] = 1;
   		player.floor2_hotspot_mask[2] = 1;
			player.floor2_hotspot_mask[3] = 1;
			player.floor2_hotspot_mask[4] = 1;
   		player.floor2_hotspot_mask[5] = 1;
   		player.floor2_hotspot_mask[6] = 0;
   		player.floor2_hotspot_mask[7] = 0;
   		player.floor2_hotspot_mask[8] = 0;
   		player.floor2_hotspot_mask[9] = 0;
         player.floor2_hotspot_mask[10] = 0;
   		player.floor2_hotspot_mask[11] = 0;
   		player.floor2_hotspot_mask[12] = 1; // nerds
   		player.floor2_hotspot_mask[13] = 1; // window
   		player.floor2_hotspot_mask[14] = 0;
   		player.floor2_hotspot_mask[15] = 0;

   		player.gym_hotspot_mask[1] = 1;
   		player.gym_hotspot_mask[2] = 1;
			player.gym_hotspot_mask[3] = 0;
			player.gym_hotspot_mask[4] = 0;
   		player.gym_hotspot_mask[5] = 0;
   		player.gym_hotspot_mask[6] = 0;
   		player.gym_hotspot_mask[7] = 0;
   		player.gym_hotspot_mask[8] = 1; // sensei
         player.gym_hotspot_mask[9] = 1; // Girls
   		player.gym_hotspot_mask[10] = 0;
   		player.gym_hotspot_mask[11] = 0;
   		player.gym_hotspot_mask[12] = 0;
   		player.gym_hotspot_mask[13] = 0;
   		player.gym_hotspot_mask[14] = 0;
   		player.gym_hotspot_mask[15] = 0;

         player.scn_girls = 0;
   		player.scn_main = 0;
   		player.scn_nerds = 0;
   		player.scn_director = 0;
   		player.scn_janitor = 0;
   		player.scn_thugs = 0;
   		player.scn_girls = 0;
   		player.scn_jessy = 0;
         player.scn_sensei = 0;

   		//player.mission_cheat = 0;
         //player.mission_party = 0;
   		//player.mission_doll = 0;
   		//player.mission_arcade = 0;
   		//player.mission_bag = 0;
         player.mission_fight = 0;

   		//player.item_chalk = 0;
   		//player.item_exams = 0;
   		player.item_bag = 0;
         //player.item_keys = 0;


         time_minutes = 0;
      	break;
      case 0:
      	// End game
      	break;
   }
}

/////////////////////////////////////////////////////////
//  Set item
// - Sets item on panel position
/////////////////////////////////////////////////////////
void SetItem(int pos, int spriteNum, char* itemImg){
	// Update panel item
	LoadSprite("SPRMISC.DAT",itemImg,16, 32); //Load sprites to one of the fixed structs
   switch(pos){
   	case 1:
   		sprite[spriteNum].pos_x = 221;
      	break;
      case 2:
      	sprite[spriteNum].pos_x = 247;
      	break;
   }
   sprite[spriteNum].pos_y = 0;
   DrawSpriteDestructive(spriteNum);
   UnloadSprite(spriteNum);
}

/////////////////////////////////////////////////////////
//  Reset item
// - Sets item on panel position
/////////////////////////////////////////////////////////
void ResetItem(int pos, int spriteNum){
  // Update panel item
	LoadSprite("SPRMISC.DAT","eitem.pcx",16, 32); //Load sprites to one of the fixed structs
   switch(pos){
   	case 1:
   		sprite[spriteNum].pos_x = 221;
      	break;
      case 2:
      	sprite[spriteNum].pos_x = 247;
      	break;
   }
   sprite[spriteNum].pos_y = 0;
   DrawSpriteDestructive(spriteNum);
   UnloadSprite(spriteNum);
}



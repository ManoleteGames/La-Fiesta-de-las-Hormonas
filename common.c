/***********************
*  common
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Go to next day
/////////////////////////////////////////////////////////
void far InitDay(void){
   switch(player.day){
   	case 10:
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
   		player.floor2_hotspot_mask[13] = 0;
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

   		player.mission_cheat = 0;
   		player.item_chalk = 0;

			break;
   	case 9:
      	player.score[2] = 0;
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
   		player.floor2_hotspot_mask[13] = 0;
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

   		player.mission_doll = 0;

   		player.item_chalk = 0;

      	break;
      case 8:
      	break;
      case 7:
      	break;
      case 6:
      	break;
      case 5:
      	break;
      case 4:
      	break;
      case 3:
      	break;
      case 2:
      	break;
      case 1:
      	break;
      case 0:
      	// End game
      	break;
   }
}



/***********************
*  DAY 1
************************/

#include "source\engine\engine.h"

void D1_Events(byte event){
	switch(player.floor){
   	case 1: // Floor 1
			if(player.floor1_event_mask[event] == 1){
        		if(player.event == 1){ GoToFloor2_Left();}
	        	if(player.event == 2){ GoToFloor2_Right();}
	         if(player.event == 3){ GoToExt1_Door();}
            if(player.event == 4){ GoToExt2_BackDoor();}
         }
      	break;
      case 2: // Floor 2
      	if(player.floor2_event_mask[event] == 1){
	         if(player.event == 1){ GoToFloor1_Left();}
         	if(player.event == 2){ GoToFloor1_Right();}
		   }
      	break;
     	case 3: // Ext 1
      	if(player.ext1_event_mask[event] == 1){
         	if(player.event == 1){ GoToNextDay();}
         	if(player.event == 2){ GoToFloor1_Entry();}
           	if(player.event == 3){ GoToExt2_Right();}
		   }
      	break;
      case 4: // Ext 2
      	if(player.ext2_event_mask[event] == 1){
         	if(player.event == 1){ GoToExt1_Right();}
         	if(player.event == 2){ GoToGym();}
         	if(player.event == 3){ GoToFloor1_BackDoor();}
		   }
      	break;
      case 5: // Gym
      	if(player.gym_event_mask[event] == 1){
		   }
      	break;
   }
}


void D1_Hotspots(byte hotspot){


}


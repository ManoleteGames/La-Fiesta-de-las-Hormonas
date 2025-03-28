/***********************
*  EXAMS
************************/

#include "source\engine\engine.h"

/////////////////////////////////////////////////////////
// Question
// - Exam question function
/////////////////////////////////////////////////////////
int near Question(char* filename, char* dat_string, int numQ){
   word length;
   unsigned char line[3];
   byte currentQ = 0;
   byte question[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   byte index = 0;
   byte end = 0;
   byte next = 0;
   byte found = 0;
   byte q1,q2,q3,q4;
   byte r1,r2,r3,r4;
   byte r_ok = 0;
   byte good_option = 0;
   byte option;
   byte second_chance = 0;
   int good_count = 0;
   byte last_time_minutes = 0;
	byte last_time_seconds = 0;

   time_minutes = time_seconds / 60;
   time_seconds = time_seconds % 60;
   time_countdown = 1;

   // Update timer
   // Print remaining time
   sprintf(string, "%02d", time_minutes);
   PrintText(34,22,2,string,1);
   last_time_minutes = time_minutes;

   sprintf(string, "%02d", time_seconds);
   PrintText(37,22,2,string,1);
   last_time_seconds = time_seconds;
   
   SetTimeInterrupt();

   while((currentQ < numQ)&&((time_minutes > 0)||(time_seconds > 0))){

      option = 1;

      srand(time(NULL));

   	while(!found){
   		index = rand() % 20;
      	if( question[index] == 0 ){
         	found = 1;
            question[index] = 1;
            index = index*10 + 20;  // apply offset
      		q1 = index;
      		q2 = index + 1;
      		q3 = index + 2;
      		q4 = index + 3;
      		r1 = index + 4;
      		r2 = index + 5;
         	r3 = index + 6;
      		r4 = index + 7;
      		r_ok = index + 8;
         }
   	}

      Draw_EmptyBox(0,0,38,8);

      // Question line 1
      sprintf(line, "%03d", q1);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,1,length,string,0);

      // Question line 2
      sprintf(line, "%03d", q2);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,2,length,string,0);

      // Question line 3
      sprintf(line, "%03d", q3);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,3,length,string,0);

      // Question line 4
      sprintf(line, "%03d", q4);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,4,length,string,0);

      // Response a
      sprintf(line, "%03d", r1);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,5,length,string,1);

      // Response b
      sprintf(line, "%03d", r2);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,6,length,string,0);

      // Response c
      sprintf(line, "%03d", r3);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,7,length,string,0);

      // Response d
      sprintf(line, "%03d", r4);
      LoadText(filename,dat_string,&line,string,&length);
   	PrintText(1,8,length,string,0);

      // Response OK
      sprintf(line, "%03d", r_ok);
      LoadText(filename,dat_string,&line,string,&length);
      good_option = string[1]-48; // convert to value

      // Print time separator
      PrintText(36,22,1,":",1);

      while( keys[K_ENTER] == 0) {
			//select response
      	if(fp_keys[K_UP]){
   			switch(option){
         		case 1: // Do nothing
            		break;
            	case 2: // Rewrite old and new option
               	sprintf(line, "%03d", r2);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,6,length,string,0);
	            	option--; // Change option
                  sprintf(line, "%03d", r1);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,5,length,string,1);
				  		break;
            	case 3: // Rewrite old and new option
               	sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,7,length,string,0);
	            	option--; // Change option
                  sprintf(line, "%03d", r2);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,6,length,string,1);
				  		break;
            	case 4: // Rewrite old and new option
               	sprintf(line, "%03d", r4);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,8,length,string,0);
	            	option--; // Change option
                  sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,7,length,string,1);
				  		break;
         	}
      	}

      	if(fp_keys[K_DOWN]){
      		switch(option){
         		case 1: // Rewrite old and new option
            		sprintf(line, "%03d", r1);
            		LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,5,length,string,0);
      	      	option++;
               	sprintf(line, "%03d", r2);
         	   	LoadText(filename,dat_string,line,string,&length);
   					PrintText(1,6,length,string,1);
               	break;
            	case 2: // Rewrite old and new option
            		sprintf(line, "%03d", r2);
	            	LoadText(filename,dat_string,line,string,&length);
            		PrintText(1,6,length,string,0);
               	option++;
               	sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
               	PrintText(1,7,length,string,1);
               	break;
            	case 3: // Rewrite old and new option
                  sprintf(line, "%03d", r3);
               	LoadText(filename,dat_string,line,string,&length);
               	PrintText(1,7,length,string,0);
               	option++;
               	sprintf(line, "%03d", r4);
               	LoadText(filename,dat_string,line,string,&length);
               	PrintText(1,8,length,string,1);
                  break;
            	case 4: // Do nothing
				  		break;
         	}
      	}
      	if(option < 1){option = 1;}
         if(option > 4){option = 4;}

         if(time_minutes != last_time_minutes){
         	// Print remaining time
         	sprintf(string, "%02d", time_minutes);
         	PrintText(34,22,2,string,1);
            last_time_minutes = time_minutes;
         }

         if(time_seconds != last_time_seconds){
	         sprintf(string, "%02d", time_seconds);
   	      PrintText(37,22,2,string,1);
            last_time_seconds = time_seconds;
         }

      	Update(0);
   	}

      while( keys[K_ENTER] == 1) {
			//wait enter released
      }

      if(option == good_option){
      	currentQ++;
         good_count++;
     		found = 0;
        	second_chance = 0;
      } else {
      	// if cheater
      	if(player.item_exams == 1) {
         	// second chance not done
      		if((option != good_option) && (second_chance == 0)) {
            	second_chance = 1;

         		// Clear screen
               Draw_EmptyBox(0,0,38,8);

            	sprintf(line, "%03d", 10);
           		LoadText(filename,dat_string,&line,string,&length);
   				PrintText(1,1,length,string,0);

            	sprintf(line, "%03d", 11);
            	LoadText(filename,dat_string,&line,string,&length);
   				PrintText(1,3,length,string,0);

               sprintf(line, "%03d", 12);
            	LoadText(filename,dat_string,&line,string,&length);
   				PrintText(1,4,length,string,0);

            	sprintf(line, "%03d", 13);
            	LoadText(filename,dat_string,&line,string,&length);
   				PrintText(1,5,length,string,0);

               sprintf(line, "%03d", 14);
            	LoadText(filename,dat_string,&line,string,&length);
   				PrintText(1,6,length,string,0);

               // Update time
               while( keys[K_ENTER] == 0) {
						// Print remaining time
         			sprintf(string, "%02d", time_minutes);
         			PrintText(34,22,2,string,1);
         			PrintText(36,22,1,":",1);
         			sprintf(string, "%02d", time_seconds);
         			PrintText(37,22,2,string,1);
               	Update(0);
               }

               // Clear screen
               Draw_EmptyBox(0,0,38,8);

            } else {
            	currentQ++;
               found = 0;
               second_chance = 0;
            }
         } else {
         	currentQ++;
            found = 0;
      	}
      }

   	while( keys[K_ENTER] == 1) {
			//wait enter released
   	}
   }

   ResetTimeInterrupt();

   return good_count;
}


/////////////////////////////////////////////////////////
// Go to exam (maths)
/////////////////////////////////////////////////////////
void far GoToExam(void){

	SetLoadingInterrupt();   // Start loading animation

   UnloadMusic();
   LoadImage("IMAGES2.DAT","exam.pcx",2); // Load exam background image to non visible page

   ResetLoadingInterrupt();   // Stop loading animation

   SetPage(2);
   Update(0);

   Fade_in();

   switch(player.day){
      case 4:
      	Speech("SPRFACE1.DAT","playerf.pcx","D4_STR.DAT","D4EXA.TXT","001","002",0,0);
         player.score[player.day] = Question("D4_STR.DAT","D4EXA.TXT",10);
         // update all events and hotspots after exam
         player.floor1_hotspot_mask[16] = 1; // Enable janitor hotspot
         player.ext2_hotspot_mask[8] = 1; // Enable hotspot of thugs on ext2
         player.floor2_hotspot_mask[11] = 0; // Disable hotspot of chalk on floor 2
         player.floor1_event_mask[5] = 0; // Disable event of director's place
         player.floor1_event_mask[9] = 0; // Disable event of thugs assault
         SetNewTime(0);
      	break;
      case 3:
      	Speech("SPRFACE1.DAT","playerf.pcx","D3_STR.DAT","D3EXA.TXT","001","002",0,0);
         player.score[player.day] = Question("D3_STR.DAT","D3EXA.TXT",10);
         SetNewTime(0);
      	break;
      case 2:
      	Speech("SPRFACE1.DAT","playerf.pcx","D2_STR.DAT","D2EXA.TXT","001","002",0,0);
         player.score[player.day] = Question("D2_STR.DAT","D2EXA.TXT",10);
         SetNewTime(0);
      	break;
      case 1:
      	Speech("SPRFACE1.DAT","playerf.pcx","D1_STR.DAT","D1EXA.TXT","001","002",0,0);
         player.score[player.day] = Question("D1_STR.DAT","D1EXA.TXT",10);
         player.floor1_event_mask[5] = 0; // Disable event of director's place
         SetNewTime(0);
      	break;
   }
}



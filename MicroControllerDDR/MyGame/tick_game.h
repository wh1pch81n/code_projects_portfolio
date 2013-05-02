//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#ifndef _tick_game_h
#define _tick_game_h
#include "level1.h"
#include <stdio.h>
#define TRUE 1
#define FALSE 0;
#define DUR 5 //smallest amount of timer_counter
#define SLR(COUNTER_VAL,POINT_IN_TIME,VAR)\
else if(COUNTER_VAL < POINT_IN_TIME)SetFrequency(VAR)

#define SLRR(COUNTER_VAL,POINT_IN_TIME,VAR)\
SLR(COUNTER_VAL, ((POINT_IN_TIME-1)*DUR), VAR);\
SLR(COUNTER_VAL, (POINT_IN_TIME*DUR), 0 );
#define WIDTH 5   
unsigned char resetGame, but1, but2, but3, but4; // add more buttons later
unsigned char IntroDone;
unsigned char Level1Done;//boolean values to determin whether to transition
//long int music_counter;

extern void play_level1();
extern int compare_button_to_bottom_array();
unsigned char youScored = 0;//flag to determin scoring
char* lcd_msg;//external declaration in main
enum Game_state {INTRO, LEVEL1, SCORE1};
int tick_game (int state)
{
    switch (state) {
        case -1:
            state = INTRO;
            break;
        case INTRO:
            if( IntroDone){
                state = LEVEL1;
            }
            else{ // intro still playing
                state = INTRO;
            }
            break;
        case LEVEL1:
            if( Level1Done){
                state = SCORE1; 
                //LCD_ClearScreen();
                //LCD_DisplayString( 0x01, "U WIN! plsReset");
                //lcd_msg = "U WIN! plsReset";
                lcd_msg = "SongOverPlsReset";
            }
//            else if( TOTAL_SCORE <40 && !Level1Done ){//lost game
//                state = SCORE1;
//               // LCD_ClearScreen();
//               // LCD_DisplayString( 0x01, "U LOSE! plsReset");
//                lcd_msg = "U LOSE! plsReset";
//            }
            else{
                state = LEVEL1;
            }
            break;
        case SCORE1://wait here for now
        {
            static long int scorecounter;
            if(scorecounter ==0)
            {
                LCD_init();//Setup LCD
                LCD_ClearScreen();//Clear the LCD
                LCD_DisplayString(0x01, lcd_msg);
                scorecounter++;
                state = SCORE1;
            }
            else if((scorecounter) < 40){
                state = SCORE1;
                scorecounter++;
            }
            else if((scorecounter) == 20){
                state = SCORE1;
                LCD_ClearScreen();//Clear the LCD
                scorecounter++;
            }
            else{
                state =SCORE1;
            }
        }
            break;
        default:
            state = -1;
            break;
    }
    ////////
    switch (state) {
        case -1:
            putPixel(6,0);//debug
            break;
        case INTRO:
            // putPixel(6,1);//debug
            //intro happens
            //....
        {
		static unsigned int blah;
		static  int counter_introduction;
            if( !(but4 || but3 || but2 || but1)){
				if(blah >=10){
					if(counter_introduction < 50){
                 	introduction(counter_introduction++); 
					}
					if(counter_introduction >=50)
						counter_introduction = 0;
					blah = 0;
			    }
				else blah++;
				//arr[4] =1;
			}
            else {
                arr[4]=0;
                IntroDone = TRUE;
            }
            

        }
            break;
        case LEVEL1:
            //putPixel(6,3);//debug
            play_level1();
            if(youScored) { if( TOTAL_SCORE < 100) ++TOTAL_SCORE;}// increment score
            if(!youScored){ if( TOTAL_SCORE > 50) --TOTAL_SCORE;}// decrement score
            
//            static unsigned char lcd_counter;
//            if((lcd_counter++) > 21)
//            {
//                //LCD_ClearScreen();
////                LCD_DisplayString(0x01, 
////                                  (TOTAL_SCORE > 90)?"Star 3":
////                                  (TOTAL_SCORE > 80)?"Star 2":
////                                  (TOTAL_SCORE > 60)?"Star 1": "Fail.....");
//                lcd_counter=0;
//            }
            
            break;
        case SCORE1:
            putPixel(6,4);//debug
            break;
    }
    
    return state;
}

unsigned char bottom_row_in_binary;
unsigned char but_seq_in_binary;

int compare_button_to_bottom_array(){
    
    if(but4==0) but_seq_in_binary &= ~(0x08);//clear bit
    else        but_seq_in_binary |=  (0x08);//set bit
    if(but3==0) but_seq_in_binary &= ~(0x04);//clear bit
    else        but_seq_in_binary |=  (0x04);//set bit
    if(but2==0) but_seq_in_binary &= ~(0x02);//clear bit
    else        but_seq_in_binary |=  (0x02);//set bit
    if(but1==0) but_seq_in_binary &= ~(0x01);//clear bit
    else        but_seq_in_binary |=  (0x01);//set bit
    
    
    if( bottom_row_in_binary == but_seq_in_binary) return TRUE;

    return FALSE;
}

#endif

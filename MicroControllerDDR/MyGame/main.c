//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "lab6_io.h"
#include "lab6_speaker.h"


//////defines for tick mechanic to use
#define NOTE_ON_BAR 0 
#define BLANK_ON_BAR 1 

volatile unsigned int counter =0;
volatile unsigned int timerFlag =0;
unsigned int TOTAL_SCORE = 99;
extern char* lcd_msg;
extern unsigned short int notes_q[10]; //Queue of frequency values to output.
extern unsigned char IntroDone;
extern unsigned char Level1Done;//boolean values to determin whether to transition
extern unsigned char but_seq_in_binary;
unsigned short int FreqVal=0;
///////////////////////////
///organize task periods
//timer based: 4 interrupts per ms* 10= 10 ms
const unsigned long int led_m_period = 2;//period for led task 1(100 ms);
//const unsigned long int lcd_period = 4*1000;// period of lcd 1000ms
const unsigned long int array_period = 4*500;//period of array refresh
const unsigned long int button_period = 4*50;//checks button ever 100 ms
const unsigned long int game_period = 4*50;
const unsigned long int music_period = 4*10;//
//const unsigned long int mech_period = 4*50;
const unsigned long int GCD = 1;//GCD of all task's period// keep as one

//Variables to implement our circular queue.
const unsigned int MAX_QUEUE_SIZE = 10;
unsigned short int notes_q[10]; //Queue of frequency values to output.
unsigned int queue_front = 0; //Queue front index.
unsigned int queue_back = 0; //Queue back index.
unsigned int num_objects = 0; //Number of objects in queue.

//Functionality - Push a character onto back of queue
//Parameter: takes in a single unsigned char.
//Returns: One if full else zero.
unsigned int push_queue(unsigned short int c) {
    //If queue is not full.
    //Increment back counter and modulate according to the max queue size.
    //Put data into correct location.
    //Return not full.
    //Else Return queue is full.
    if( num_objects < MAX_QUEUE_SIZE){
        notes_q[queue_back]= c;// back points to free space so insert it there
        queue_back++;
        queue_back %= MAX_QUEUE_SIZE;//and then increment tail to the next
        ++num_objects;
        return 0;
    }
    return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned short from queue else null character.
unsigned short int pop_queue() {
    //If queue is not empty.
    //Retrieve data in correct location.
    //Clear location with null character.
    //Increment front counter and modulate according to the max queue size.
    //Return data.
    //Else return null character to indicate empty.
    if(num_objects > 0){
        static unsigned short int latestCharVal;
        latestCharVal = notes_q[queue_front];//save it in global var
        notes_q[queue_front] = 0;
        queue_front++;
        queue_front %= MAX_QUEUE_SIZE;
        --num_objects;
        return latestCharVal;
    }
    return 0;
}

//------------------------
//Interrupt service routine
//We enter this function ~4 times per millisecond,
//we can set a flag that signals a period has passed every period*4 times the function is entered.
//If our period is 10 ms, then we would enter the function 10*4 = 40 times before transitioning to next state.
ISR(TIMER0_OVF_vect){
        timerFlag =1;
}

void InitTimer() {
    //Set prescaler.
    TCCR0 |= (1<<CS01);//CS01 corresponds to bit0 of TCCR0 ( prescale of 8)
    //Enable Overflow Interrupt Enable on Timer.
    TIMSK |= (1<<TOIE0);//TOIE0 corresponds to bit0 of TIMSK
    //Initialize starting value of timer
    TCNT0 = 0 ;
}
//////////////////////////////////
//Task structure
//////////////////////////////////
//Struct for Tasks represent a running process in our simple real-time operating system
typedef struct _task{
    //Task should have members that include: state, period, a measurement of elapsed time, and a function pointer.
    int state;//Tasks current state
    unsigned long int period;//task's period
    unsigned long int elapsedTime;//time elapsed since last task tick
    int (*TickFct)(int);//Task tick function
    
}task;

//Declare an array of tasks and an integer containing the number of tasks in our system
task              led_task,  array_task,  button_task,  game_task,  music_task;
task *tasks[] = {&led_task, &array_task, &button_task, &game_task, &music_task};
const int numTasks = sizeof(tasks)/sizeof(task*);

//////////////////////////////////
//Place tick functions below here
//////////////////////////////////

#include "led_matrix.h"
#include "tick_matrix.h"
//#include "tick_lcd.h"//lcd causes flickering
#include "tick_array.h"
#include "tick_buttons.h"
#include "intro.h"
#include "tick_game.h"
//#include "tick_mechanics.h"
#include "tick_music.h"


int main(){
    //////////////////////
    //initialize ports
    /////////////////////
    DDRD =0xFF;//cols-[0:4] lcd-[5:6] speaker-[7]
    DDRC =0xFF;//rows-[0:6] free[7]
    DDRB =0x00;//Buttons-[0:4] programmer-[5:7]
    DDRA =0xFF;//LCD [0:7]
    
    
    InitSpeaker();
    
    SREG |= (1<<7);//enable global interrupts
    InitTimer();
   // LCD_init();//Setup LCD
   // LCD_ClearScreen();//Clear the LCD
  
    //initialize();// gives array a box shape

    
    {
        //task1
        led_task.state = -1;//Task1 initial state
        led_task.period = led_m_period;//task 1 period
        led_task.elapsedTime = led_m_period;//task1 current elapsed time
        led_task.TickFct = &tick_matrix;//function pointer for the tick 2.
        
        //task2
        //LCD CAUSES FLICKERING
        ///
      //  lcd_task.state = -1;//initial state
      //  lcd_task.period = lcd_period;//period
       // lcd_task.elapsedTime = lcd_period;//current elapsed time.
       // lcd_task.TickFct = &tick_lcd;//function pointer
        //task3
        array_task.state = -1;//initial state
        array_task.period= array_period;
        array_task.elapsedTime=array_period;
        array_task.TickFct =&tick_array;
        
        button_task.state = -1;
        button_task.period = button_period;
        button_task.elapsedTime = button_period;
        button_task.TickFct = &tick_buttons;
        
        game_task.state = -1;
        game_task.period = game_period;
        game_task.elapsedTime = game_period;
        game_task.TickFct = &tick_game;
        
//        mech_task.state = -1;
//        mech_task.period = mech_task.elapsedTime = mech_period;
//        mech_task.TickFct = &tick_mechanics;
    
        music_task.state = -1;
        music_task.period = music_task.elapsedTime = music_period; 
        music_task.TickFct = &tick_music;
    }

    unsigned int i;

    while (1) {


        //Scheduler code
        for( i = 0; i <numTasks; i++){
			
            if(tasks[i]->elapsedTime== tasks[i]->period){//Task is ready to tick
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);//Setting next state for task
                tasks[i]->elapsedTime=0;//Reset the elapsed time for next tick.
            }
            //take away tick matrix and replace it with 
            //a function that is always going to run
            tasks[i]->elapsedTime += GCD;
        }       
        while(!timerFlag);
        timerFlag = 0;      
    }
    printf("%s \n", "Error: no mans land");
    return 0;
}


//////////




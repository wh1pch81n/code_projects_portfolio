/*
 Name:		Derrick Ho
 Login:		dho006
 email:		dho006@ucr.edu
 lab section:	021
 assignment:	lab6 
 group:		Mantej R.
 */
/*
 Derrick Ho made changes to buildfrequency() and 
 setFrequency() in such a way that
 the parameter directly gives a desired frequency
*/
#include "lab6_speaker.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>

//int freq[25];
unsigned char waveform[SAMPLE_RATE/2];
//const int mid_a_freq = 440;
int phase_accumulator = 0;
//unsigned int FLUX = 1;
//unsigned  char INFLUX=6;
unsigned short int frequency = 0;

ISR(TIMER1_COMPA_vect){
    //this is called SAMPLE_RATE times per second
    //in here we want to update OCR2 -- update the current sample on the PWM
    phase_accumulator =(phase_accumulator + frequency) % SAMPLE_RATE;
	//phase_accumulator = (++phase_accumulator) %  (FLUX + INFLUX);
    if(phase_accumulator < (SAMPLE_RATE/2))//first half
    //if( (phase_accumulator < (FLUX)))
	{	
		//INFLUX = (++INFLUX) %  255;
        //OCR2 = 200;
        OCR2 = waveform[phase_accumulator];
    }
    else{//second half
        //OCR2 = 0;
        //OCR = 255 - ();
		OCR2 = 255 - waveform[phase_accumulator - (SAMPLE_RATE/2)];
    }
    TCNT1 = 0;
}

void InitSpeaker() {
   TCCR2 |= (1 << 6) | (1 << 3);//We want FAST PWN mode
   TCCR2 |= (1 << 5);//COM21 = 1
   TCCR2 &= ~(1 << 4);//COM20 = 0 (non-inverting PWM)
   TCCR2 = (TCCR2 | 0x01);//No prescaler (as fast as possible)

        // Set initial pulse width = 0
   OCR2 = 0;

   SREG &= ~(1 << 7);//disable interrupt
   // Set CTC mode (Clear Timer on Compare Match) (p.133)
   // Have to set OCR1A *after*, otherwise it gets reset to 0!
   TCCR1A = 0;
   TCCR1B = 0 | (0 << 4) | (1 << 3) | 1;//CTC mode on Timer1, no prescaler

        //Set CTC mode
   TIMSK |= (1 << 4);
        //Now make sure timer1 interrupt is fired at the sample rate
   OCR1A = F_CPU / SAMPLE_RATE;

   //buildFreqs();
   buildWaveform();

}

void buildWaveform(){
    int i;
    for(i = 0; i < SAMPLE_RATE/2; ++i){
        waveform[i] = (unsigned char)(((sin( ((float)i / (SAMPLE_RATE/2)) * M_PI )) * 127.5) + 127.5);
    }
}

//void buildFreqs(){
//        double temp_freq = 0;
//        int final_freq = 0;
 //       double sq2 = pow(2.0, (1.0/12.0));
//        int i;
//        temp_freq = 0;
//        for(i = 1; i < 25; i++)
//        {
//                temp_freq = mid_a_freq * pow(sq2, (i - 12));
//                final_freq = ceil(temp_freq);
//                freq[i] = final_freq;
//        }
 
//sounds don't vibrate sufficiently before
//    freq [1] =423;//g4
//    freq [2] =473;//a4
//    freq [3] =530;//b4
//    freq [4] =554;//c#5
//    freq [5] =622;//d5?
//	freq [6] =698;//e5?
//	//sounds get weird beyond this point
//	freq [7] =783;//f5?
//	freq [8] =880;//g5?
//	freq [9] =988;//a5?
//    freq [10] =1046;//b5?
//}

void SetFrequency(unsigned short int val) {
//   frequency = freq[val];
    frequency = val;
}


//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#ifndef _tick_buttons_h
#define _tick_buttons_h

#define EUC extern unsigned char
//EUC means extern unsigned char

EUC resetGame;
EUC but1;
EUC but2;
EUC but3;
EUC but4;//global var for buttons

enum Button {notDown, Down};
// value should be the variable holding history
// input is either a one or zero
void history(unsigned char* value, unsigned char input){
    (*value) <<= 1;//left shift once
    if( input ==0x01) ++(*value);//insert a 1
    //else implicit zero
}

int tick_buttons(int state){
//reset uses reset built into the micro controller
//    if((PINB & 0x01)==0x01){//checks if Reset is pressed by checking B0 
//       resetGame = 1;
//    }else resetGame = 0;
    
    if((PINB & 0x02)==0x02){//checks if but1 is pressed by checking B1
        history(&but1, 1);
    }else history(&but1, 0);
    
    if((PINB & 0x04)==0x04){//checks if but2 is pressed by checking B2
        history(&but2 ,1);
    }else history(&but2 ,0);
    if((PINB & 0x08)==0x08){//checks if but3 is pressed by checking B3//
        history(&but3 ,1);
    }else history(&but3 ,0);    
    if((PINB & 0x10)==0x10){//checks if but4 is pressed by checking B4//
        history(&but4 ,1);
    }else history(&but4 ,0);
 
    return state;
}


#endif

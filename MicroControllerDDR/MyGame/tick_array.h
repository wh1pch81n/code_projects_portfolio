//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej 
//Work is original

#ifndef _tick_array_h
#define _tick_array_h

unsigned char arr[35];//extern declartion in tick_matrix.h
extern unsigned char next_row [MAXCOL];
extern unsigned char bottom_row_in_binary;
//unsigned short int FreqVal;//global declaration in main//
unsigned char but0, but1, but2, but3;//extern declaration in tick_button.h
enum Row {ROW0};

int tick_array( int state){
    if (!IntroDone) return state;//only go when inro done

    switch (state) {//transition
        case ROW0:
            state = ROW0;
        default:
            state = ROW0;
            break;
    }
    switch (state) { //action
        case ROW0:
        {
            //mantej did this nested for loop
            int c,d =0;
            for(c= 0; c  < 4; c++){
                for(d = 6; d  >0; d--){
                    arr[c  + MAXCOL*d ] = arr[c  + MAXCOL*(d -1)];
                } 
            }//Derrick Did everything else before and after
            break;
        }    
    }
    FreqVal = pop_queue();// this is to keep the but seq in sync with notes
    //SetFrequency( pop_queue() );
    //MAXCOL*6 = 5*6 =30// yay magic numbers
    if(arr[0 + 30] ==1) 
        bottom_row_in_binary|= (0x08);//set
    else
        bottom_row_in_binary&=~(0x08);//clear
    if(arr[1 + 30] ==1) 
        bottom_row_in_binary|= (0x04);//set
    else
        bottom_row_in_binary&=~(0x04);//clear
    if(arr[2 + 30] ==1) 
        bottom_row_in_binary|= (0x02);//set
    else
        bottom_row_in_binary&=~(0x02);//clear
    if(arr[3 + 30] ==1) 
        bottom_row_in_binary|= (0x01);//set
    else
        bottom_row_in_binary&=~(0x01);//clear
    
    return state;
}


#endif

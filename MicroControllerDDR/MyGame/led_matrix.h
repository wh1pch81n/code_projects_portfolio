//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

typedef struct _pixel{
	unsigned char ROW;
	unsigned char COL;
    
}pixel;


////////////////
#define ROW_BUS PORTC
#define COL_BUS PORTD
#define MAXROW 7
#define MAXCOL 5
unsigned char col_arr[] = {0x10, 0x08, 0x04, 0x02, 0x01};
//unsigned char row_arr[] = {0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
//unsigned char col_arr[]={0x01, 0x02, 0x04, 0x08, 0x10};
unsigned char row_arr[]={0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD};
//takes in two integers corresponding to the index's of the 
//row and columns
//it then outputs the result into ROW_BUS and COL_BUS
void putPixel(int  row, int col){ 
    COL_BUS =PIND | col_arr[col];
	ROW_BUS =PINC | row_arr[row];
    //    COL_BUS = col_arr[col];
    //	ROW_BUS = row_arr[row];
}
void resetPixel(){
    COL_BUS = PIND & 0x60;//portD[6:5] used by lcd, don't change their vals here
	ROW_BUS = PINC & 0x01;//portC[1] is free ATM don't over write it

    //    COL_BUS =0x00; 
    //	ROW_BUS =0x00;
}

#endif 

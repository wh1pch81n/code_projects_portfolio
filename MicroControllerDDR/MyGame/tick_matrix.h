//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#ifndef _tick_matrix_h
#define _tick_matrix_h

//35== 5*7==MAXROW* MAXCOL 
extern unsigned char arr[35];
 
//enumberation of states
int tick_matrix(int state){
    static int irow, icol,index;
//            //interate through extern arr and if equal to 1
//            //putPixel, else leave off
            if( arr[index++] == 1)
                putPixel(irow,icol);
            else
                resetPixel();
			if(index == 35) index =0;
            ++icol;  
            if(icol >=5){
                icol =0;
                ++irow;
				if(irow >= 7)
					irow = 0;
            }
    return state;  
}


#endif

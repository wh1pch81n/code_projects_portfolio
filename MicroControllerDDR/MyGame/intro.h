//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
// Original intro.h file created by Mantej but modified slightly by Derrick
// to fit with the Game better.

#ifndef _intro_h_
#define _intro_h_

#define WIDTH 5
unsigned char arr[35];//external declaration elsewhere

//these are the 50 arrays for the 50 collumns to 
//be marqued through
unsigned char G1[7] = {0, 1, 1, 1, 1, 1, 0};
unsigned char G2[7] = {1, 0, 0, 0, 0, 0, 1};
unsigned char G3[7] = {1, 0, 0, 0, 1, 0, 1};
unsigned char G4[7] = {1, 0, 0, 0, 1, 1, 0};
unsigned char G5[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char U1[7] = {0, 0, 1, 1, 1, 1, 0};
unsigned char U2[7] = {0, 0, 0, 0, 0, 0, 1};
unsigned char U3[7] = {0, 0, 0, 0, 0, 0, 1};
unsigned char U4[7] = {0, 0, 1, 1, 1, 1, 0};
unsigned char U5[7] = {0, 0, 0, 0, 0, 0, 0};


unsigned char I3[7] = {0, 1, 0, 1, 1, 1, 1};
unsigned char I5[7] = {0, 0, 0, 0, 0, 0, 0};


unsigned char T2[7] = {0, 1, 0, 0, 0, 0, 0};
unsigned char T3[7] = {1, 1, 1, 1, 1, 1, 1};
unsigned char T4[7] = {0, 1, 0, 0, 0, 0, 1};
unsigned char T5[7] = {0, 1, 0, 0, 0, 0, 0};
unsigned char T1[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char A1[7] = {0, 0, 0, 1, 1, 1, 1};
unsigned char A2[7] = {0, 0, 0, 1, 1, 1, 1};
unsigned char A3[7] = {0, 0, 0, 1, 1, 1, 1};
unsigned char A4[7] = {0, 0, 0, 0, 0, 1, 1};
unsigned char A5[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char R1[7] = {0, 1, 1, 1, 1, 1, 1};
unsigned char R2[7] = {0, 0, 1, 0, 0, 0, 0};
unsigned char R3[7] = {0, 0, 1, 0, 0, 0, 0};
unsigned char R4[7] = {0, 0, 0, 1, 1, 0, 0};
unsigned char R5[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char H1[7] = {1, 1, 1, 1, 1, 1, 1};
unsigned char H2[7] = {0, 0, 0, 1, 0, 0, 0};
unsigned char H3[7] = {0, 0, 0, 1, 0, 0, 0};
unsigned char H4[7] = {1, 1, 1, 1, 1, 1, 1};
unsigned char H5[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char E1[7] = {0, 0, 1, 1, 1, 1, 0};
unsigned char E2[7] = {0, 1, 0, 1, 0, 0, 1};
unsigned char E3[7] = {0, 1, 0, 1, 0, 0, 1};
unsigned char E4[7] = {0, 0, 1, 0, 0, 1, 1};
unsigned char E5[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char R12[7] = {0, 1, 1, 1, 1, 1, 1};
unsigned char R22[7] = {0, 0, 1, 0, 0, 0, 0};
unsigned char R32[7] = {0, 0, 1, 0, 0, 0, 0};
unsigned char R42[7] = {0, 0, 0, 1, 1, 0, 0};
unsigned char R52[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char O1[7] = {0, 0, 0, 1, 1, 1, 0};
unsigned char O2[7] = {0, 0, 1, 0, 0, 0, 1};
unsigned char O3[7] = {0, 0, 1, 0, 0, 0, 1};
unsigned char O4[7] = {0, 0, 0, 1, 1, 1, 0};
unsigned char O5[7] = {0, 0, 0, 0, 0, 0, 0};


unsigned char I1[7] = {0, 0, 0, 0, 0, 0, 0};
unsigned char I2[7] = {0, 0, 0, 0, 0, 0, 0};
unsigned char I4[7] = {0, 0, 0, 0, 0, 0, 0};



void introduction( int cnt_intro)
{

    //puts all 50 arrays into arr2
    unsigned char *arr2[] = { G1, G2, G3, G4, G5,
             U1, U2, U3, U4, U5,
             I3,  I5,
              T2, T3, T4, T5,T1,
             A1, A2, A3, A4, A5,
             R1, R2, R3, R4, R5,
             H1, H2, H3, H4, H5,
             E1, E2, E3, E4, E5,
             R12, R22, R32, R42, R52,
             O1, O2, O3, O4, O5

			 ,I1, I2, I4
    };

    //x and y are used for the for loops
    int x;
    int y;

    //travese goes from 0 to 7 to travese through each individual
    //array that comes in as the last collumn
    int traverse = 0;
    //cnt_intro is used to pick one of the 50 arrays at a time.
    //start at 0 and go till 49.

    //temp stores the current 1 of the 50 arrays we are using
    unsigned char *temp='\0';

    //this loop will go from 0 to 49, 
    //therefore using all 50 arrays
    //you might want to put this while loop in your program
    //so that this function adds one collumn to the right everytime its called
    //let me know if that makes sense
    
    
    //while(cnt_intro < 50){
    
        //temp variable is the collumn that we are adding
        temp = arr2[(cnt_intro)];
    
	    //traverse is reset
     	//traverse = 0;

        //nested for looop shifts everything to the left
        for(y = 0; y < 3; y++)
        {
            for(x = 0; x < 7; x++)
            {
                arr[y + (WIDTH*x)] = arr[y + ((WIDTH*x) + 1)];
                //replace arr with arr3
            }
        }
        
    //adds the array temp into the last collumn, after
    //everything has already been shifted
    //  for(z = 4; z <= 34; /*z+=5*/ 
    //     ++z,++z,++z,++z,++z)
    for(traverse =0; traverse<7; ++traverse)    
    {
        arr[3 + 5*traverse] = temp[traverse];
        //replace arr with arr3
    }   
        //cnt_intro is increased so that next time we use the 
        //next array in line.

    
    //}


}



#endif



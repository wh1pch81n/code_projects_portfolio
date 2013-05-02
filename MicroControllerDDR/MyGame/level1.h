//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#ifndef _level1_h
#define _level1_h

//factor is a variable to help scale the music to be
//same pace as the array falls down.
//currently array_period is 500 and game period is 50
//so that means game period has to be held through 10 cycles
unsigned char factor = 10;
unsigned char Level1Done;

//SVN means save note. does so by pushing the q
#define SVN(CNT, INK, SVN_FREQ )\
if(CNT == (INK*factor)-1 ) push_queue( SVN_FREQ ); 

//hold-button sequence
#define HSQ(CNT,INK,FOUR_BIT_BINARY)\
else if(CNT < INK*factor){\
    if(FOUR_BIT_BINARY == 0 ){arr[0]=0;arr[1]=0;arr[2]=0;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 1 ){arr[0]=0;arr[1]=0;arr[2]=0;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 2 ){arr[0]=0;arr[1]=0;arr[2]=1;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 3 ){arr[0]=0;arr[1]=0;arr[2]=1;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 4 ){arr[0]=0;arr[1]=1;arr[2]=0;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 5 ){arr[0]=0;arr[1]=1;arr[2]=0;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 6 ){arr[0]=0;arr[1]=1;arr[2]=1;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 7 ){arr[0]=0;arr[1]=1;arr[2]=1;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 8 ){arr[0]=1;arr[1]=0;arr[2]=0;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 9 ){arr[0]=1;arr[1]=0;arr[2]=0;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 10){arr[0]=1;arr[1]=0;arr[2]=1;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 11){arr[0]=1;arr[1]=0;arr[2]=1;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 12){arr[0]=1;arr[1]=1;arr[2]=0;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 13){arr[0]=1;arr[1]=1;arr[2]=0;arr[3]=1;}\
    if(FOUR_BIT_BINARY == 14){arr[0]=1;arr[1]=1;arr[2]=1;arr[3]=0;}\
    if(FOUR_BIT_BINARY == 15){arr[0]=1;arr[1]=1;arr[2]=1;arr[3]=1;}\
}
#define zSVN SVN(m_c, ++j, 0)
#define D4SVN SVN(m_c, ++j, nD4)
#define E4SVN SVN(m_c, ++j, nE4)
#define F4SVN SVN(m_c, ++j, nF4)
#define G4SVN SVN(m_c, ++j, nG4)
#define A4SVN SVN(m_c, ++j, nA4)
#define B4SVN SVN(m_c, ++j, nB4)
#define C5SVN SVN(m_c, ++j, nC5)
#define D5SVN SVN(m_c, ++j, nD5)
#define E5SVN SVN(m_c, ++j, nE5)
#define F5SVN SVN(m_c, ++j, nF5)
#define G5SVN SVN(m_c, ++j, nG5)
#define A5SVN SVN(m_c, ++j, nA5)
#define B5SVN SVN(m_c, ++j, nB5)
#define C6SVN SVN(m_c, ++j, nC6)
#define D6SVN SVN(m_c, ++j, nD6)
#define E6SVN SVN(m_c, ++j, nE6)
#define F6SVN SVN(m_c, ++j, nF6)
#define G6SVN SVN(m_c, ++j, nG6)
#define A6SVN SVN(m_c, ++j, nA6)
#define B6SVN SVN(m_c, ++j, nB6)

#define n0HSQ HSQ(m_c,++j,0 )
#define n1HSQ HSQ(m_c,++j,1  )
#define n2HSQ HSQ(m_c,++j,2  )
#define n3HSQ HSQ(m_c,++j,3 )
#define n4HSQ HSQ(m_c,++j,4 )
#define n5HSQ HSQ(m_c,++j,5 )
#define n6HSQ HSQ(m_c,++j,6 )
#define n7HSQ HSQ(m_c,++j,7  )
#define n8HSQ HSQ(m_c,++j,8 )
#define n9HSQ HSQ(m_c,++j,9 )
#define n10HSQ HSQ(m_c,++j,10 )
#define n11HSQ HSQ(m_c,++j,11 )
#define n12HSQ HSQ(m_c,++j,12 )
#define n13HSQ HSQ(m_c,++j,13)
#define n14HSQ HSQ(m_c,++j,14)
#define n15HSQ HSQ(m_c,++j,15)

void play_level1(){
    static long int m_c;//music_counter
    
    long int j=0;
//initialize start the button sequences
    if(m_c == j){arr[0]=0;arr[1]=0;arr[2]=0;arr[3]=0;}
   		HSQ(m_c, ++j, 0) //7 empty rows to clear the screen as intro shifts down
    	HSQ(m_c, ++j, 0)
	    HSQ(m_c, ++j, 0)
		HSQ(m_c, ++j, 0)
		HSQ(m_c, ++j, 0)
		HSQ(m_c, ++j, 0)
		HSQ(m_c, ++j, 0)

    
//    HSQ(m_c,++j, 8)HSQ(m_c, ++j, 0)
//    HSQ(m_c,++j, 1)HSQ(m_c, ++j, 0)
//    HSQ(m_c,++j, 2)HSQ(m_c, ++j, 0)
//    HSQ(m_c,++j, 4)HSQ(m_c, ++j, 0)
//    HSQ(m_c,++j, 8)HSQ(m_c, ++j, 0)
//    HSQ(m_c,++j, 9)HSQ(m_c, ++j, 0)
//    HSQ(m_c,++j, 12)HSQ(m_c,++j, 12)HSQ(m_c,++j, 12)
//    HSQ(m_c,++j, 12)HSQ(m_c,++j, 12)HSQ(m_c, ++j, 0)
    
    HSQ(m_c,++j, 4)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 3)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 2)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 9)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 4)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 8)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 12)HSQ(m_c,++j, 12)HSQ(m_c,++j, 12)
    HSQ(m_c,++j, 12)HSQ(m_c,++j, 12)HSQ(m_c, ++j, 0)
    
    HSQ(m_c,++j, 8)HSQ(m_c,++j, 8)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 4)HSQ(m_c,++j, 4)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 8)HSQ(m_c,++j, 8)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 4)HSQ(m_c,++j, 4)HSQ(m_c, ++j, 0)
    
    
    HSQ(m_c,++j, 9)HSQ(m_c,++j, 9)HSQ(m_c,++j, 9)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 1)HSQ(m_c, ++j, 0)
    HSQ(m_c,++j, 3)HSQ(m_c,++j, 3)HSQ(m_c,++j, 3)
    HSQ(m_c,++j, 3)HSQ(m_c,++j, 3)
    HSQ(m_c,++j, 3)HSQ(m_c,++j, 3)HSQ(m_c,++j, 3)
    HSQ(m_c,++j, 3)HSQ(m_c,++j, 3)HSQ(m_c, ++j, 0)
    
    //second line of song
    HSQ(m_c,++j,8)HSQ(m_c,++j, 8)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,4)HSQ(m_c,++j, 4)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,8)HSQ(m_c,++j,8)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,4)HSQ(m_c,++j,4)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,2)HSQ(m_c,++j,2)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,1)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,3)HSQ(m_c,++j,3)HSQ(m_c,++j,3)HSQ(m_c,++j,3)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,1)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,8)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,1)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,2)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,4)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,12)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,14)HSQ(m_c,++j,14)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,8)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,4)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,2)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,1)HSQ(m_c,++j,1)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,5)HSQ(m_c,++j,5)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,6)HSQ(m_c,++j,6)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,4)HSQ(m_c,++j,4)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,2)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,5)HSQ(m_c,++j,5)HSQ(m_c,++j, 0)
    HSQ(m_c,++j,7)HSQ(m_c,++j,7)HSQ(m_c,++j,7)HSQ(m_c,++j,7)HSQ(m_c,++j,7)HSQ(m_c,++j, 0)
    
    //3rd line
    n1HSQ n1HSQ n0HSQ
    n8HSQ n0HSQ
    n4HSQ n0HSQ
    n8HSQ n0HSQ
    n9HSQ n9HSQ n0HSQ
    n5HSQ n5HSQ n0HSQ
    n9HSQ n9HSQ n0HSQ
    n5HSQ n5HSQ n0HSQ
    n1HSQ n0HSQ
    n3HSQ n3HSQ n0HSQ
    n8HSQ n8HSQ n8HSQ n8HSQ n0HSQ
    n12HSQ n12HSQ n0HSQ
    n14HSQ n0HSQ
    n15HSQ n0HSQ
    n1HSQ n0HSQ
    n2HSQ n2HSQ n0HSQ
    n4HSQ n4HSQ n0HSQ
    n8HSQ n8HSQ n0HSQ
    n4HSQ n4HSQ n0HSQ
    n8HSQ n0HSQ
    n4HSQ n4HSQ n0HSQ
    n6HSQ n6HSQ n6HSQ n6HSQ n0HSQ
    n4HSQ n0HSQ
    n1HSQ n0HSQ
    //4th line n0HSQ
    n8HSQ n8HSQ n0HSQ
    n4HSQ n4HSQ n0HSQ
    n2HSQ n2HSQ n0HSQ
    n1HSQ n1HSQ n0HSQ
    n3HSQ n3HSQ n0HSQ
    n6HSQ n6HSQ n0HSQ
    n4HSQ n4HSQ n0HSQ
    n8HSQ n0HSQ
    n1HSQ n0HSQ
    n8HSQ n0HSQ
    n9HSQ  n0HSQ
    n4HSQ n0HSQ
    n2HSQ n0HSQ
    n4HSQ n0HSQ
//    n2HSQ n0HSQ
//    n4HSQ n0HSQ
//    n2HSQ n0HSQ
//    n6HSQ n6HSQ n6HSQ n6HSQ n0HSQ
//    n12HSQ n12HSQ n0HSQ
//    n8HSQ n8HSQ n0HSQ
//    n12HSQ n12HSQ n0HSQ
//    n14HSQ n14HSQ n0HSQ
//    n15HSQ n15HSQ n15HSQ n15HSQ n0HSQ
//    n4HSQ n0HSQ
//    // 5th line n0HSQ
//    n12HSQ n12HSQ n12HSQ n12HSQ n0HSQ
//    n6HSQ n6HSQ n6HSQ n6HSQ n0HSQ
//    n12HSQ n12HSQ n0HSQ
//    n8HSQ n8HSQ n8HSQ n8HSQ n0HSQ
//    n14HSQ n14HSQ n14HSQ n14HSQ n0HSQ
//    n2HSQ n2HSQ n0HSQ
//    n4HSQ n4HSQ n0HSQ
//    n8HSQ n8HSQ n8HSQ n8HSQ n0HSQ
//    n14HSQ n14HSQ n14HSQ n14HSQ n0HSQ
//    n2HSQ n2HSQ n0HSQ
//    n8HSQ n8HSQ n0HSQ
//    n4HSQ n4HSQ n0HSQ
//    n12HSQ n12HSQ n0HSQ
//    //6th line  n0HSQ
//    n14HSQ n14HSQ n14HSQ n14HSQ n0HSQ
//    n4HSQ n4HSQ n0HSQ
//    n6HSQ n6HSQ n6HSQ n6HSQ n0HSQ
//    n4HSQ n4HSQ n0HSQ
//    n8HSQ n8HSQ n0HSQ
//    n1HSQ n1HSQ n0HSQ
//    n2HSQ n2HSQ n2HSQ n2HSQ n0HSQ
//    n4HSQ n4HSQ  n0HSQ
//    n8HSQ n8HSQ n0HSQ
//    n1HSQ n0HSQ
//    n2HSQ n2HSQ n0HSQ
    n4HSQ n4HSQ n4HSQ n4HSQ n4HSQ n4HSQ n4HSQ n4HSQ  n0HSQ
    //needed for letting notes have proper delay
        HSQ(m_c, ++j, 0)HSQ(m_c, ++j, 0)
        HSQ(m_c, ++j, 0)HSQ(m_c, ++j, 0)
    
    else {
        Level1Done = 1;//true
    }
    //end button sequence
    
//initialize start of musiclal notes
    j = 0;
    {//needed for letting notes have proper delay
        SVN(m_c,++j, 0)SVN(m_c,++j, 0)
        SVN(m_c,++j, 0)SVN(m_c,++j, 0)
    	//SVN(m_c,++j, 0)
	}
    SVN(m_c,++j, 0)//7 blank notes for 7 empty rows
    SVN(m_c,++j, 0)
    SVN(m_c,++j, 0)
    SVN(m_c,++j, 0)
    SVN(m_c,++j, 0)
    SVN(m_c,++j, 0)
    SVN(m_c,++j, 0)

//    SVN(m_c,++j, nE5)SVN(m_c,++j, 0)
//    SVN(m_c,++j, nE4)SVN(m_c,++j, 0)
//    SVN(m_c,++j, nG4)SVN(m_c,++j, 0)
//    SVN(m_c,++j, nB4)SVN(m_c,++j, 0)
//    SVN(m_c,++j, nE5) SVN(m_c,++j, 0)
//    SVN(m_c,++j, nF5)    SVN(m_c,++j, 0)
//    SVN(m_c,++j, nG5)SVN(m_c,++j, nG5)SVN(m_c,++j, nG5)
//    SVN(m_c,++j, nG5)SVN(m_c,++j, nG5)    SVN(m_c,++j, 0)
    
    SVN(m_c,++j, nD5)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nD4)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nF4)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nA4)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nD5)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nE5)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nF5)SVN(m_c,++j, nF5)SVN(m_c,++j, nF5)SVN(m_c,++j, nF5)SVN(m_c,++j, nF5)    SVN(m_c,++j, 0)
    
    SVN(m_c,++j, nB4)SVN(m_c,++j, nB4)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nB4)SVN(m_c,++j, nB4)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nB4)SVN(m_c,++j, nB4)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nB4)SVN(m_c,++j, nB4)    SVN(m_c,++j, 0)

    SVN(m_c,++j, nA4)SVN(m_c,++j, nA4)SVN(m_c,++j, nA4)SVN(m_c,++j, 0)
    SVN(m_c,++j, nD5)    SVN(m_c,++j, 0)
    SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)
    SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, nE4)SVN(m_c,++j, 0)
    
    //second line of song
    SVN(m_c,++j,nE5)SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nD5)SVN(m_c,++j,nD5)SVN(m_c,++j,0)
    SVN(m_c,++j,nG5)SVN(m_c,++j,0)
    SVN(m_c,++j,nC6)SVN(m_c,++j,nC6)SVN(m_c,++j,nC6)SVN(m_c,++j,nC6)SVN(m_c,++j,0)
    SVN(m_c,++j,nF5)SVN(m_c,++j,0)
    SVN(m_c,++j,nC5)SVN(m_c,++j,0)
    SVN(m_c,++j,nF5)SVN(m_c,++j,0)
    SVN(m_c,++j,nG5)SVN(m_c,++j,0)
    SVN(m_c,++j,nA5)SVN(m_c,++j,0)
    SVN(m_c,++j,nC6)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nB4)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nF5)SVN(m_c,++j,0)
    SVN(m_c,++j,nG5)SVN(m_c,++j,nG5)SVN(m_c,++j,0)
    SVN(m_c,++j,nF5)SVN(m_c,++j,nF5)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nD5)SVN(m_c,++j,nD5)SVN(m_c,++j,0)
    SVN(m_c,++j,nE5)SVN(m_c,++j,0)
    SVN(m_c,++j,nD5)SVN(m_c,++j,nD5)SVN(m_c,++j,0)
    SVN(m_c,++j,nB4)SVN(m_c,++j,nB4)SVN(m_c,++j,nB4)SVN(m_c,++j,nB4)SVN(m_c,++j,nB4)SVN(m_c,++j,0)
    //thrid line
    E5SVN E5SVN  zSVN
    B4SVN  zSVN
    E5SVN zSVN
    F5SVN zSVN
    G5SVN G5SVN zSVN
    F5SVN F5SVN zSVN
    G5SVN G5SVN zSVN
    A5SVN A5SVN zSVN
    G5SVN zSVN
    A5SVN A5SVN zSVN
    B5SVN B5SVN B5SVN B5SVN zSVN
    E5SVN E5SVN  zSVN
    B4SVN zSVN
    E5SVN zSVN
    F5SVN zSVN
    G5SVN G5SVN zSVN
    F5SVN F5SVN zSVN
    E5SVN E5SVN zSVN
    D5SVN D5SVN zSVN
    E5SVN zSVN
    D5SVN D5SVN zSVN
    B4SVN B4SVN B4SVN B4SVN zSVN
    G4SVN  zSVN
    A4SVN zSVN
    //forth line
    B4SVN B4SVN zSVN
    B4SVN B4SVN zSVN
    B4SVN B4SVN zSVN
    B4SVN B4SVN zSVN
    A4SVN A4SVN zSVN
    D5SVN D5SVN zSVN
    G4SVN G4SVN zSVN
    G4SVN zSVN
    F4SVN zSVN
    D4SVN zSVN
    E4SVN E4SVN E4SVN E4SVN zSVN
    E5SVN zSVN
    E4SVN zSVN
    G4SVN zSVN
//    C5SVN zSVN
//    E5SVN zSVN
//    G5SVN zSVN
//    A5SVN A5SVN A5SVN A5SVN zSVN
//    E5SVN E5SVN zSVN
//    E5SVN E5SVN zSVN
//    D5SVN D5SVN zSVN
//    C5SVN C5SVN zSVN
//    B4SVN B4SVN B4SVN B4SVN zSVN
//    G5SVN G5SVN zSVN
//    //fifth line
//    G5SVN G5SVN G5SVN G5SVN zSVN
//    B4SVN B4SVN B4SVN B4SVN zSVN
//    F5SVN F5SVN zSVN
//    F5SVN F5SVN F5SVN F5SVN  zSVN
//    A4SVN A4SVN A4SVN A4SVN zSVN
//    E5SVN E5SVN zSVN
//    E5SVN E5SVN zSVN
//    D5SVN D5SVN D5SVN D5SVN zSVN
//    B4SVN B4SVN B4SVN B4SVN zSVN
//    F5SVN F5SVN zSVN
//    F5SVN F5SVN zSVN
//    E5SVN E5SVN zSVN
//    D5SVN D5SVN zSVN
//    //sixth line
//    C5SVN C5SVN C5SVN C5SVN zSVN
//    A5SVN A5SVN zSVN
//    A5SVN A5SVN A5SVN A5SVN  zSVN
//    G5SVN G5SVN zSVN
//    E5SVN E5SVN zSVN
//    C5SVN C5SVN zSVN
//    B4SVN B4SVN B4SVN B4SVN zSVN
//    D5SVN zSVN
//    A4SVN zSVN
//    F4SVN zSVN
//    A4SVN zSVN
    B4SVN B4SVN B4SVN B4SVN B4SVN B4SVN B4SVN B4SVN  zSVN
    
    
//end musical notes    
    m_c++;
}

#endif

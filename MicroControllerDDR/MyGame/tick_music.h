//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Work is original

#ifndef _tick_music_h
#define _tick_music_h

//int compare_button_to_bottom_array();//external declaration in tick_game

enum Music {WAIT, SOUND};
//since tick period  is 10 and array period is 500
//must have 50 cycles to catch up with array period

//unsigned short int FreqVal;//extern declaration in main
const unsigned short int tick_music_factor = 50;
#define TMF tick_music_factor
int tick_music(int zone){
    if(!IntroDone) return zone;// only play after intro
    
    static unsigned short int cnt;
    switch (zone) {//TRANS
        case -1:
            cnt = 0;
            
            zone = WAIT;
            break;
        case WAIT:
            if((cnt < TMF) && !compare_button_to_bottom_array() ) 
                zone = WAIT;
			else if(compare_button_to_bottom_array() && (cnt < TMF) && (cnt>2)){
                zone = SOUND;
            }
            else {//(!(cnt<TMF) && !compare_button_to_bottom_array()){
                cnt = 0;
                zone = WAIT;
            }
            break;
        case SOUND:
            // want to stay in SOUND regardless of 
            // button sequence being true or not...at 
            //least until the next inc of the array
            if(cnt < TMF)
                zone = SOUND;
            //if the next button sequence is correct stay here
            //applies for long blanks and held notes
            else if(compare_button_to_bottom_array() && !(cnt<TMF) && 
                    (   
                     ((but1 & 0x03)==0x01)||
                     ((but2 & 0x03)==0x01)||
                     ((but3 & 0x03)==0x01)||
                     ((but4 & 0x03)==0x01)||
                     
                     ((but1 & 0x03)==0x03)||
                     ((but2 & 0x03)==0x03)||
                     ((but3 & 0x03)==0x03)||
                     ((but4 & 0x03)==0x03)
                     )  
                    )//end of else if conditional
            {
                zone = SOUND; 
                cnt = 0;
            }
            else{// if(!compare_button_to_bottom_array() && !(cnt <TMF)){
                cnt = 0;
                zone = WAIT;
            }
            break;
        default:
            zone = -1;
            break;
    }
    switch (zone) {//ACTION
        case -1:
            break;
        case WAIT:
            cnt++;
            youScored = 0;
            SetFrequency(0);//play no sound
            break;
        case SOUND:
            cnt++;
            youScored = 1;
            if(cnt< (TMF-2))
                SetFrequency(FreqVal);
            break;
    } 
    return zone;
}

#endif

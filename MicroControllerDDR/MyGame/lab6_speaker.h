//Name: Derrick Ho
//Login: dho006
//email: dho006@ucr.edu
//lab section 021
//assignment Game Project
//Group: Mantej
//Original Speaker file from lab was modified
//
#ifndef __speaker_h__
#define __speaker_h__

#define F_CPU 8000000UL
#define SAMPLE_RATE 2200

#define nD4 294UL
#define nE4 330UL
#define nF4 349UL
#define nG4 423UL//g4
#define nA4 473UL//a4
#define nB4 530UL//b4
#define nC5 554UL//c#5
#define nCS5 554UL//c#5
#define nD5 622UL//d5
#define nE5 698UL//e5
#define nF5 740UL
#define nG5 784UL
#define nA5 880UL
#define nB_5 932UL
#define nB5 988UL
#define nC6 1067UL
#define nD6 1175UL
#define nE6 1319UL
#define nF6 1397UL
#define nG6 1568UL
#define nA6 1760UL
#define nB6 1976UL

void InitSpeaker();
void buildWaveform();
void buildFreqs();
void SetFrequency(unsigned short int);

#endif

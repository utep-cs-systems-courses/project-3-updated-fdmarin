#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
// define musical note and its frequency

#define A3 2273
#define B3 2025
#define G3 2551
#define E3 3033
#define C3 3846
#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012
#define C5 95
#define D5 1587

/////

#define F 349
#define E 330
#define G 392
#define D 294
#define C 523
#define A 440
#define B 494

/////

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 55
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

void buzzer_init()
{
  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}


// simple beep noise
void beep(){
  // array to hold notes for our loop
  int notes[] = {A4, 0};
  int i = 0;
  while(i < sizeof(notes)){
    int count = 0;
    while(count < 20){
      int count2 = 0;
      while(count2< 30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}
// loop through our array of notes until the end
// random set of notes to create a small tune
void randomSong()
{
  int notes[] = {E3,E3,A3,A4,G3,F4,E3,A4,G3,F4};
  int i = 0;
  while(i<sizeof(notes)){
    int count = 0;
    while(count<20){
      int count2 = 0;
      while(count2 < 30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}

// method to play a short clip of the baby shark song
void sharkSong(){
  int notes[] = {C5,C5,C5,C5,0,0,D4,D4,0,0,F4,0,0,0,F4,0,F4,0,F4,0,F4,0,F4,0,F4,0,F4,0,0,0};
  int i = 0;
  while(i< sizeof(notes)){
    int count = 0;
    while(count < 20){
      int count2 = 0;
      while (count2 < 30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}

// method to play a short clip of the mario theme song
void marioSong()
{
  int notes[] = {E4,E4,E4,C4,E4,G4,G3,C4,G3,E3,A3,B3,A3,A3};
  int i = 0;
  while(i <sizeof(notes)){
    int count = 0;
    while(count < 20){
      int count2 = 0;
      while(count2<30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}

// Method to play the last part of the spongebob squarepants theme song
void spongebobSong(){
  int notes[] = {G3,0,A4,0,B3,0,A4,0,0,B4,G3,0,0,D4,G3,0};
  int i = 0;
  while(i <sizeof(notes)){
    int count = 0;
    while(count<20){
      int count2 = 0;
      while(count2<30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}

void twinkletwinkleSong(){
  int notes[] = {C,C,G,G,A,A,G,F,F,E,E,D,D,C};
  int i =  0;
  while(i < sizeof(notes)){
    int count = 0;
    while(count<20){
      int count2 = 0;
      while(count2<30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}
// method to play an old cellphone ring tone
void nokiaSong()
{
  int notes[] = {E4,0,D4,0,F4,0,G3,0,C5,0,B3,0,D4,0,E4,0,B3,0,A4,0,C5,E4,E4,0,A4,A4,A4,0,0};
  int i = 0;
  while(i < sizeof(notes)){
    int count = 0;
    while(count <20){
      int count2 = 0;
      while(count2<30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    state_advance();
    i++;
  }
}

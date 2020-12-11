//Federico Marin
#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachine.h"

char state;
char switch_state_down;
char switch_state_changed; /* effectively boolean */
char B1, B2, B3, B4;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES); // if up then sense down
  P2IES &= (p2val | ~SWITCHES); // if down then sense up
  return p2val;
}

void switch_init() // initialize switch
{
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  B1 = (p2val & SW1) ? 0 : 1;
  B2 = (p2val & SW2) ? 0 : 1;
  B3 = (p2val & SW3) ? 0 : 1;
  B4 = (p2val & SW4) ? 0 : 1;
  if(B1){
    switch_state_down = B1;
    switch_state_changed = 1;
    led_update();
    nokiaSong();
  }
  if(B2){
    switch_state_down = B2;
    switch_state_changed = 2;
    led_update();
    sharkSong();
  }
  if(B3){
    switch_state_down = B3;
    switch_state_changed = 3;
    led_update();
    spongebobSong();
  }
  if(B4){
    switch_state_down = B4;
    switch_state_changed = 4;
    led_update();
    marioSong();
    // dim50();
  }
  switch_state_changed = 1;
  led_update();
}

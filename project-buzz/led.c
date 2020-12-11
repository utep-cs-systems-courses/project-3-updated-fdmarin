#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachine.h"


unsigned char red_on = 0;
unsigned char green_on = 0;
static char redVal[] ={0,LED_RED};
static char greenVal[] = {0, LED_GREEN};
unsigned char led_changed = 0;

void led_init()
{
  P1DIR |= LEDS;// bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update()
{
  if(led_changed){
    char ledFlags= redVal[red_on] | greenVal[green_on];
    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;
    led_changed = 0;
  }
}

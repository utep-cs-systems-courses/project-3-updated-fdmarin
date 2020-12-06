//Federico Marin

#include <msp430.h>

#include "libTimer.h"

#include "led.h"

#include "switches.h"

#include "buzzer.h"

#include "triangle.h"

#include <lcdutils.h>

#include "stateMachine.h"

#include <lcddraw.h>


void main(void)
{

  configureClocks();

  switch_init();
  
  buzzer_init();

  led_init();

  lcd_init();

  u_char width = screenWidth, height = screenHeight;
  
  //enableWDTInterrupts();

  clearScreen(COLOR_BLACK);

  drawTriforce();

  or_sr(0x18);  // CPU off, GIE on

} 

#include <msp430.h>

#include "stateMachines.h"


char switch_state_changed;


void
{

  __interrupt_vecc(WDT_VECTOR) WDT(){

    static char blink_count = 0;



    if(switch_state_changed == 4){

      switch(switch_state_changed){



      case 4:

	if(++blink_count < 62){

	  dim25();

	}

	else if(++blink_count < 125){

	  dim50();

	}

	else if(++blink_count == 250){

	  count = 0;

	}

	else{

	  dim75();

	  dimLight();

	}

	break;

      }

    }

    if(++blink_count == 125){

      state_advance();

      blink_count = 0;

    }

  }

}

#include <msp430.h>



#include <lcdutils.h>



#include <lcddraw.h>



#include <libTimer.h>



#include <p2switches.h>



#include "buzzer.h"



#include <shape.h>



#include <abCircle.h>







#define GREEN_LED BIT6







//Define everything needed to make field and base game







static int state = 0; //for switch case







AbRect rect = {abRectGetBounds, abRectCheck, {4,20}};



Region fence = {{20,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}};







//Draw the rectangles and circle, just gonna label everything layers to keep it consistent







AbRectOutline fieldOutline =



  {



    abRectOutlineGetBounds, abRectOutlineCheck,



    {screenWidth/2-5, screenHeight/2-15} //testing values



  };



Layer fieldLayer =



  {



    (AbShape *)&fieldOutline,



    {screenWidth/2, screenHeight/2},



    {0,0}, {0,0},



    COLOR_YELLOW,



  };







/*

  layer1 == left rectangle

  layer2 == right rectangle

  layer3 == circle

*/







Layer layer3 = //circle



  {



    (AbShape *) &circle20,



    {(screenWidth/2), (screenHeight/2)},



    {0,0}, {0,0},

    COLOR_PURPLE, &fieldLayer



  };







Layer layer1 = //left rectangle



  {



    (AbShape *) &rect, //Rectangle shape



    {screenWidth/2-55, screenHeight/2},



    {0,0}, {0,0},



    COLOR_PURPLE,



    &layer3 //circle layer



  };







Layer layer2 = //right rectangle



  {



    (AbShape *) &rect,



    {screenWidth/2+55, screenHeight/2+5},



    {0,0}, {0,0},



    COLOR_PURPLE,



    &layer1 //p1 layer



  };







//Now to draw the field and layer











//Add Moving layers to draw



typedef struct MovLayer_s //Using this from shape-motion-demo



{



  Layer *layer;



  Vec2 velocity;



  struct MovLayer_s *next;



} MovLayer;







MovLayer ml1 = { &layer1, {0,3}, 0}; //left rectangle



MovLayer ml2 = { &layer2, {0,3}, 0}; //right rectangle



MovLayer ml3 = { &layer3, {2,4}, 0}; //circle







//Move the circle







void movLayerDraw(MovLayer *movLayers, Layer *layers)



{



  int row, col;



  MovLayer *movLayer;







  and_sr(~8);/**< disable interrupts (GIE off) */



  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) {

    Layer *l = movLayer->layer;



    l->posLast = l->pos;



    l->pos = l->posNext;



  }



  or_sr(8);/**< disable interrupts (GIE on) */











  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */



    Region bounds;



    layerGetBounds(movLayer->layer, &bounds);



    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],



		bounds.botRight.axes[0], bounds.botRight.axes[1]);



    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {



      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {



	Vec2 pixelPos = {col, row};



	u_int color = bgColor;



	Layer *probeLayer;



	for (probeLayer = layers; probeLayer;



	     probeLayer = probeLayer->next) { /* probe all layers, in order */



	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {



	    color = probeLayer->color;



	    break;



	  } /* if probe check */



	} // for checking all layers at col, row



	lcd_writeColor(color);



      } // for col



    } //

  } // for moving layer being updated



}







void moveUp(MovLayer *ml, Region *fence)



{



  Vec2 newPos;



  u_char axis;



  Region shapeBoundary;



  for (; ml; ml = ml->next) {



    vec2Sub(&newPos, &ml->layer->posNext, &ml->velocity);



    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);



    for (axis = 0; axis < 2; axis ++) {



      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||



	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {



	int velocity = ml->velocity.axes[axis];



	newPos.axes[axis] += (2*velocity);



	buzzer_set_period(900);//make a sound for collision



      }/**< if outside of fence */



    } /**< for axis */



    ml->layer->posNext = newPos;



  } /**< for ml */



}







void moveDown(MovLayer *ml, Region *fence)



{



  Vec2 newPos;



  u_char axis;



  Region shapeBoundary;



  for (; ml; ml = ml->next) {



    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);



    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);



    for (axis = 0; axis < 2; axis ++) {



      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||



	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {



	int velocity =-ml->velocity.axes[axis];



	newPos.axes[axis] += (2*velocity);



	buzzer_set_period(720);//make a sound for collision



      }/**< if outside of fence */



    } /**< for axis */



    ml->layer->posNext = newPos;



  } /**< for ml */



}







void moveBall(MovLayer *ml, Region *fence1, MovLayer *ml2, MovLayer *ml3)



{



  Vec2 newPos;



  u_char axis;



  Region shapeBoundary;



  int velocity;



  buzzer_set_period(0); //No Sound







  for (; ml; ml = ml->next)



    {



      vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);



      abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);



      for(axis = 0; axis < 2; axis ++)



	{



	  if((shapeBoundary.topLeft.axes[axis] < fence1->topLeft.axes[axis]) || //kill program



	     (shapeBoundary.botRight.axes[axis] > fence1->botRight.axes[axis]) ||



	     (abShapeCheck(ml3->layer->abShape, &ml3->layer->posNext, &ml->layer->posNext)) ||



	     (abShapeCheck(ml2->layer->abShape, &ml2->layer->posNext, &ml->layer->posNext)))



	    {



	      velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];



	      newPos.axes[axis] += (2*velocity);



	      buzzer_set_period(300);



	    }







	  else if((shapeBoundary.topLeft.axes[0] < fence1->topLeft.axes[0]))



	    {



	      newPos.axes[0] = screenWidth/2;



	      newPos.axes[1] = screenHeight/2;



	    }







	  else if((shapeBoundary.botRight.axes[0] > fence1->botRight.axes[0]))



	    {



	      newPos.axes[0] = screenWidth/2;



	      newPos.axes[1] = screenHeight/2;



	    }







	} /**< for axis */



      ml->layer->posNext = newPos;



    } /**< for ml */



}



//Move handler to handle interrupts and use it for endgame







u_int bgColor = COLOR_BLACK; //this is the background color of the screen



int redrawScreen = 1;



Region fieldFence;







void wdt_c_handler()



{



  static short count = 0;







  P1OUT |= GREEN_LED;

  count ++;







  u_int switches = p2sw_read();







  if(count == 10)



    {



      switch(state)



	{



	case 0:



	  moveBall(&ml3, &fieldFence, &ml1, &ml2);



	  break;



	}



      redrawScreen = 1;



      count = 0;



    }



  P1OUT &= ~GREEN_LED;     /**< Green LED off when cpu off */



}











//Game execute



void main()



{



  P1DIR |= GREEN_LED;//Green led on when CPU on



  P1OUT |= GREEN_LED;







  configureClocks(); //initialize clocks



  lcd_init(); //initialize lcd



  buzzer_init(); //initialize buzzer



  p2sw_init(15); //initialize switches



  layerInit(&layer2); //Passes the first element from a MoveLayer LL to initilize shapes



  layerDraw(&layer2); //Passes the first element from a MoveLayer LL to draw shapes



  layerGetBounds(&fieldLayer, &fieldFence);



  enableWDTInterrupts();      // enable periodic interrupt



  or_sr(0x8);              // GIE (enable interrupts)







  u_int switches = p2sw_read();







  for(;;)//Dont get this part, would a while loop just work? Copied from shape demo



    {



      while (!redrawScreen)



	{ // Pause CPU if screen doesn't need updating



	  P1OUT &= ~GREEN_LED; // Green led off witHo CPU



	  or_sr(0x10); //< CPU OFF



	}



      P1OUT |= GREEN_LED; // Green led on when CPU on



      redrawScreen = 0;







      movLayerDraw(&ml3, &layer2);



      movLayerDraw(&ml2, &layer2);



      movLayerDraw(&ml1, &layer2);











      //Text on top of screen



      drawString5x7(5, 5, "*--fdmarin--*", COLOR_WHITE, COLOR_BLACK);







      //Text at bottom of screen



      drawString5x7(25, 150, "---Lab 3---", COLOR_WHITE, COLOR_BLACK);



    }



}

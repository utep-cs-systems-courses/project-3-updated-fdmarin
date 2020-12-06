#include "triangle.h"

#include <lcdutils.h>

#include <lcddraw.h>

/* Draws a triangle from the iconic video game series: The Legend of Zelda */



void drawTriforce() {



  int i, j = 0;



  for (i=62; i<82; i++) {



    drawPixel(i, i-30, COLOR_BLUE);



    drawPixel(i-(j*2), i-30, COLOR_BLUE);



    j++;



  }



  for (i=42; i<82; i++)



    drawPixel(i, 52, COLOR_BLUE);



  // Low Right



  j=0;



  for (i=82; i<102; i++) {



    drawPixel(i, i-30, COLOR_BLUE);



    drawPixel(i-(j*2), i-30, COLOR_BLUE);



    j++;



  }



  // Low Left



  j=0;



  for (i=42; i<62; i++) {



    drawPixel(i, i+10, COLOR_BLUE);



    drawPixel(i-(j*2), i+10, COLOR_BLUE);



    j++;



  }



  // Bottom line



  for (i=22; i<102; i++)



    drawPixel(i, 72, COLOR_BLUE);



}

#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "state_machines.c"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output

  //Just turn on led and turn off red
  green_on = 1;
  red_on = 0;
  led_update();
  switch_state_changed = 1;
}


void led_update()
{
  if (switch_state_changed){
    char ledFlags = redVal[red_on] | greenVal[green_on];

    P1OUT &= (0xff^LEDS) | ledFlags;   //clear bit for off leds
    P1OUT |= ledFlags;                 // set bit for on leds
    led_changed = 0;
  }
}

void dim_leds(char state)
{
  int count = 2000;

  switch(state){
  case 0 :
    //Starting 
    green_on = 0;
    red_on = 0;
    led_update();
    break;
    
  case 1:
    //Dims green
    count =2000;
    green_on = 0;
    red_on = 1;
    led_update();
    
    for (int i=0; i<count; i++){
      red_on =0;
      led_update();
      for(int j=0; j<i; j++);
      red_on=1;
      led_update();
      for(int j=0; j<count-i; j++);
    }
    green_on  = 0;
    red_on = 0;
    led_update();
    break;

  case 2:
     //Bright red
    count = 3000;
    green_on = 0;
    for(int i=0; i<count; i++){
      green_on = 1;
      led_update();
      for(int j=0; j<i; j++);
      green_on = 0;
      led_update();
      for (int j=0; j<count-i; j++);
    }
    green_on = 1;
    red_on = 0;
    led_update();
    break;

  case 3:
    //Dims red
    count = 2000;
    for(int i=0; i<count; i++){
      green_on = 0;
      led_update();
      for(int j=0; j<i; j++);
      green_on = 1;
      led_update();
      for(int j=0; j<count-i;j++);
    }
    green_on = 0;
    red_on = 0;
    led_update();
    break;
    
  case 4:
    //Brightens green
    count = 3000;
    red_on = 0;
    led_update();
    for (int i=0; i<count; i++){
      red_on = 1;
      led_update();
      for(int j=0; j<i; j++);
      red_on=0;
      led_update();
      for(int j=0; j<count-i; j++);
    }
    green_on = 0;
    red_on = 1;
    led_update();
    break;
  default:
    break;
  }

}







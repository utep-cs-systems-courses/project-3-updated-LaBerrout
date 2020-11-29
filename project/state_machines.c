#include <msp430.h>
#include "state_machines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}

void button_advance()
{
  if (down1){  //S1
    if(last_state){
      red_on = 0;
      green_on = 1;
      led_update();
      last_state = 0;
    }else{
      red_on = 1;
      green_on = 0;
      led_update();
      last_state = 1;
    }
  }
  if (down2){ //S2 Dim leds
    dim_leds(0);
    dim_leds(1);
    dim_leds(2);
    dim_leds(3);
    dim_leds(4);
  }
  if (down3){//S3 Buzzer state ...run out of time to use state_advance()
    last_state = 0;
    tada(0);
    tada(1);
    for(int i=0; i<2;i++){
      tada(2);
      tada(3);
      tada(1);
    }
  }
  if (down4){
    if(last_state){
      green_on = 1;
      red_on = 0;
      led_update();
      tada(2);
      last_state = 0;
    } else{
      green_on = 0;
      red_on = 1;
      led_update();
      tada(1);
      last_state = 1;
    }
  }
}


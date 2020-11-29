#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void turn_off_buzz()
{
  buzzer_set_period(0);
}

    
void tada(char state)
{
  int count;
  int period;

  switch(state){
  case 0:
    //Start
    green_on = 1;
    red_on = 0;
    led_update();
    break;

  case 1:
    //Goes up
    count=1500;
    period = 4000;
    buzzer_set_period(period);
    seudo_timer(count);
    buzzer_set_period(0);
    break;

  case 2:
    //short
    count = 1000;
    period = 3200;
    buzzer_set_period(period);
    seudo_timer(count);
    buzzer_set_period(0);
    break;

  case 3:
    count = 1000;
    period = 3520;
    buzzer_set_period(period);
    seudo_timer(count);
    buzzer_set_period(0);
    break;
  
  
  
   
  }
  
}

void seudo_timer(int count)
{
  for(int i = 0; i<count; i++){
    for(int j=0; j<i; j++);
    for(int j=0; j<count-i;j++);
  }
}


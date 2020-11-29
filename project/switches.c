#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "state_machines.h"


char switch_state_down, switch_state_changed; /* effectively boolean */
int switch_ID;
char last_state = 0;
char down1, down2, down3, down4;

static char 
switch_update_interrupt_sense()
{
  //char p1val = P1IN;
  char p2val = P2IN;            /* LB: added to get the buttons to work with the green board*/
                                /* Every part that stated P1 was changed to P2*/
  

  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  
  down1 = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  down2 = (p2val & SW2) ? 0 : 1; //S2
  down3 = (p2val & SW3) ? 0 : 1; //S3
  down4 = (p2val & SW4) ? 0 : 1; //S4

  button_advance();

}

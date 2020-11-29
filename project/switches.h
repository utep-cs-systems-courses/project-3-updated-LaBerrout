#ifndef switches_included
#define switches_included

#define SW4 BIT3		/* before " #define SW1 BIT3 */
                                /* switch1 is p1.3. LB: for some reason the button don't work,
                                   might be not in  p1, but p2 <- done */

#define SW1 BIT0                /* LB: Adding other switch */
#define SW2 BIT1
#define SW3 BIT2

#define SWITCHES (SW1 | SW2 | SW3 | SW4)   /* only 1 switch on this board. LB: (TEST) adding a seco                                              nd switch */


void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed; /* effectively boolean */


#endif // included

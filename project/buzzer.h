#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(short cycles);
void tada(char state);
void seudo_timer(int count);

#endif // included

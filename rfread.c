/*
 * blink.c:
 */

#include <stdio.h>
#include <wiringPi.h>
#include "manchester.h"


#define PIN_R   (1)
#define DELAY   (20)

unsigned int last_read = 0;
enum decoder_state { START, START1, MID1, START0, MID0 };
enum event_len { SHORT, LONG };
enum event_type { PULSE, SPACE };

enum decoder_state current_state = START;

int count = 0;
char buf = 0x00;
void emit(char c)
{
	buf <<= 1;
	buf |= (0x01 & c);
	count++;
	if (count == 8)
	{
		putchar(buf);
		fflush(stdout);
		count = 0;
		buf = 0x00;
	}
}

void myInterrupt1(void) 
{
  unsigned int now = micros();
  int read_ticks;
  enum event_type type;
  enum event_len length;

  read_ticks = now - last_read;
  last_read = now;

  type = digitalRead(PIN_R) == HIGH ? SPACE : PULSE;


  if (read_ticks < 0.5 * DELAY * 1000)
  {
    return;
  }
  else if (read_ticks > 0.5 * DELAY * 1000 && read_ticks < 1.5 * DELAY * 1000)
  {
    length = SHORT;
  }
  else
  {
    length = LONG;
  }

  switch (current_state)
  {
  case START:
    emit(1);
    current_state = MID1;
    break;
  case START1:
    if (length == SHORT && type == SPACE) {emit(1); current_state = MID1; }
    break;
  case MID1:
    if (length == SHORT && type == PULSE) { current_state = START1; }
    else if (length == LONG && type == PULSE) { emit(0); current_state = MID0; }
    break;
  case START0:
    if (length == SHORT && type == PULSE) { emit(0); current_state = MID0; }
    break;
  case MID0:
    if (length == SHORT && type == SPACE) { current_state = START0; }
    else if (length == LONG && type == SPACE) { emit(1); current_state = MID1; }
    break;
  default:
    current_state = START;
  }
};

int main (void)
{
  piHiPri(99);
  wiringPiSetup () ;
  wiringPiISR(PIN_R, INT_EDGE_BOTH, &myInterrupt1);
  for (;;) delay(1000);
  return 0 ;
}

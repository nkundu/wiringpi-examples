/*
 * blink.c:
 */

#include <stdio.h>
#include <wiringPi.h>
#include "manchester.h"


#define	PIN_W	(0)
#define PIN_R   (1)
#define DELAY   (20)
#define BUFSZ   (10)

unsigned int last_read = 0;
enum decoder_state { START, START1, MID1, START0, MID0 };
enum decoder_state current_state = START;
void myInterrupt1(void) 
{
  unsigned int now = millis();
  int pin_state;
  int read;
  read = now - last_read;
  last_read = now;
  pin_state = digitalRead(PIN_R);

  
  printf("read %d state %d ", read < 1.5*DELAY ? 1 : 0, pin_state);
};

void setLow()
{
  digitalWrite(PIN_W, LOW);
}

void setHigh()
{
  digitalWrite(PIN_W, HIGH);
}

int main (void)
{
  int c;
  int i;
  printf ("Raspberry Pi slow radio link\n") ;

  wiringPiSetup () ;
  wiringPiISR(PIN_R, INT_EDGE_BOTH, &myInterrupt1);
  pinMode (PIN_W, OUTPUT) ;

  printf("write preamble\n");
  manchesterWritePreamble(DELAY, delay, setLow, setHigh);
  printf("write data\n");
  for (;;)
  {
    c = getchar();
    if (EOF == c)
      break;
    manchesterWrite((char)c, DELAY, delay, setLow, setHigh);
    printf ("wrote 0x%08X\n", c);
  }

  printf("done\n");
  return 0 ;
}

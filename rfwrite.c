/*
 * blink.c:
 */

#include <stdio.h>
#include <wiringPi.h>
#include "manchester.h"


#define	PIN_W	(0)
#define DELAY   (20)

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

  piHiPri(99);
  wiringPiSetup () ;
  pinMode (PIN_W, OUTPUT) ;

  manchesterWritePreamble(DELAY, delay, setLow, setHigh);
  for (;;)
  {
    c = getchar();
    if (EOF == c)
      break;
    manchesterWrite((char)c, DELAY, delay, setLow, setHigh);
  }

  return 0 ;
}

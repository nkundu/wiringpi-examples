/*
 * blink.c:
 */

#include <stdio.h>
#include <wiringPi.h>
#include "manchester.h"


#define	LED	(0)
#define DELAY   (20)

char read = 0;
void myInterrupt1(void) { read = read | 0x01; };

PI_THREAD  (readClock)
{
  int i;
  for (i = 0;;i++)
  {
    delay(DELAY*3);
    read <<= 1;
    if (i == 7)
    {
      i = 0;
      printf("Read 0x%08X\n",read);
    }
  }
}

void setLow()
{
  digitalWrite(LED, LOW);
}

void setHigh()
{
  digitalWrite(LED, HIGH);
}

int main (void)
{
  char c;
  int i;
  printf ("Raspberry Pi slow radio link\n") ;

  wiringPiSetup () ;
  i = piThreadCreate(readClock);
  wiringPiISR(1, INT_EDGE_FALLING, &myInterrupt1);
  pinMode (LED, OUTPUT) ;

  for (;;)
  {
    c = getchar();
    manchesterWrite(c, DELAY, delay, setLow, setHigh);
    printf ("wrote 0x%08X\n", c);
  }
  return 0 ;
}

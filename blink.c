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

unsigned int read = 0;
void myInterrupt1(void) { read = millis() - read; };

PI_THREAD  (readClock)
{
  //char buf[BUFSZ];
  //int result;
  //result = manchesterRead(DELAY, &(buf[0]), BUFSZ, &read, delay);
  int i;
  for (i = 0;;i++)
  {
    delay(DELAY/2);
    printf("read %d ", read);
  }
}

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
  i = piThreadCreate(readClock);
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

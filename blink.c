/*
 * blink.c:
 *	Standard "blink" program in wiringPi. Blinks an LED connected
 *	to the first GPIO pin.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

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
    printf ("wrote 0x%08X\n", c);
    for (i = 7; i >= 0; i--)
    {
      if (0x01 & (c >> i))
  	    digitalWrite (LED, HIGH) ;	// On
      else
	    digitalWrite (LED, LOW);
    
      delay (DELAY*2) ;		// mS
      digitalWrite (LED, LOW) ;	// Off
      delay (DELAY) ;
    }
  }
  return 0 ;
}

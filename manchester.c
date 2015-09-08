
#include "manchester.h"

int manchesterRead(int T, char *buf, int bufsz, int *counts, void (*delay)(unsigned int))
{
	return 0;
}

void manchesterWritePreamble(int T, void (*delay)(unsigned int), void (*setLow)(void), void (*setHigh)(void))
{
	char c;

	c = 0b11111110;
	manchesterWrite(c, T, delay, setLow, setHigh);

}

void manchesterWrite(char c, int T, void (*delay)(unsigned int), void (*setLow)(void), void (*setHigh)(void))
{
	int i;
	setHigh();
	for (i = 7; i>= 0; i--)
	{
		if (0x01 & (c >> i))
		{
			setLow();
			delay(T);
			setHigh();
			delay(T);
		}
		else
		{
			setHigh();
			delay(T);
			setLow();
			delay(T);
		}
	}
	setHigh();
}

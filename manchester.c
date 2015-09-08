


void manchesterWrite(char c, int T, void (*delay)(unsigned int), void (*setLow)(void), void (*setHigh)(void))
{
	int i;
	setHigh();
	for (i = 7; i>= 0; i++)
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

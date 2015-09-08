
int manchesterRead(int T, char *buf, int bufsz, int *counts, void (*delay)(unsigned int));

void manchesterWritePreamble(int T, void (*delay)(unsigned int),  void (*setLow)(void), void (*setHigh)(void));
void manchesterWrite(char c, int T, void (*delay)(unsigned int),  void (*setLow)(void), void (*setHigh)(void));

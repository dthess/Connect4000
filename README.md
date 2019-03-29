# Connect4000
cs201 project

Video demonstration:
https://drive.google.com/open?id=1LrYzQqsKRyhAY2agxFALNjqxn5VyM8ji

Code borrowed for this project:

https://stackoverflow.com/questions/17167949/how-to-use-timer-in-c

 int msec = 0, trigger = 10; /* 10ms */
 clock_t before = clock();

 do {
  /*
   * Do something to busy the CPU just here while you drink a coffee
   * Be sure this code will not take more than `trigger` ms
   */

  clock_t difference = clock() - before;
  msec = difference * 1000 / CLOCKS_PER_SEC;
  iterations++;
} while ( msec < trigger );

printf("Time taken %d seconds %d milliseconds (%d iterations)\n",
  msec/1000, msec%1000, iterations);


https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in:-c

char * getLine(void) {
	char * line = malloc(100), * linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;

	if(line == NULL)
		return NULL;

	while(1){
		c = fgetc(stdin);
		if(c == EOF)
			break;

		if(--len == 0) {
			len = lenmax;
			char * linen = realloc(linep, lenmax *= 2);

			if(linen == NULL) {
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if((*line++ = c) == '\n')
			break;
	}
	*line = '\0';
	return linep;
}

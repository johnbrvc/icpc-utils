/* One and done version of guesser */
#include <stdio.h>
#define	MAX_VAL		1024

main()
{
	char ibuf[128];
	int llim, hlim, guess;
	int bDone = 0;

	llim = 1;
	hlim = MAX_VAL;
	/*
	 * first guess
	 */
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	for(;!bDone;) {
		guess = llim + (hlim-llim)/2;
		printf("%d\n", guess);
		if(fgets(&(ibuf[0]), sizeof(ibuf), stdin) == NULL){
			break;
		}
		switch(ibuf[0]){
		case 'l':	/* Lower */
			hlim = guess-1;
			if(hlim < 1){
				hlim = 1;
			}
			break;
		case 'h':	/* Higher */
			llim = guess+1;
			if(llim >= MAX_VAL){
				llim = MAX_VAL;
			}
			break;
		case 'c':	/* Correct done */
			bDone = 1;
			break;
		}
	}		
}


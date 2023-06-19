#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

int main()
{
	int n;
	char *p;

	for(n = 0; n < 128; n++){
		p = malloc(1024*1024);
		if(p == NULL){
			exit(3);
		}
		memset(p, n+'A', 1024*1024);
	}
	printf("Done!\n");
	return(0);
}

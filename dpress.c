#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void dpress(FILE *in, FILE *out) {
	int lastCh = 0;
	int ch = 0;
	do {
        ch = fgetc(in);
		if(ch == EOF) {
			break;
		}
		int d = ch - lastCh;
		fputc(d, out);
		lastCh = ch;
    } while(ch != EOF); 
}

int main(int argc, char **argv) {
	FILE *in = fopen(argv[1], "rb");
	if (in== NULL) {
    	printf ("Error opening file %s: %s\n", argv[1], strerror(errno));
		exit(errno);
	}

	FILE *out = fopen(argv[2], "wb");
	if (out== NULL) {
    	printf ("Error opening file %s: %s\n", argv[2], strerror(errno));
		exit(errno);
	}

	dpress(in, out);
	
	fclose(in);
	fclose(out);
}



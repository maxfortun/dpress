#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dpress.h"

#define BUFFER_SIZE 256

void freq(FILE *in, FILE *out) {
    _freq *freqBuffer = (_freq *)malloc(BUFFER_SIZE*sizeof(_freq));
    memset(freqBuffer, 0, BUFFER_SIZE*sizeof(_freq));

	unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE*sizeof(unsigned char));
    memset(buffer, 0, BUFFER_SIZE*sizeof(unsigned char));

	do {
		size_t inCount = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, in);
		for(int i = 0; i < inCount; i++) {
			unsigned char ch = buffer[i];
			freqBuffer[ch]++;
		}
    } while(!feof(in));

	size_t outCount = fwrite (freqBuffer, sizeof(_freq), BUFFER_SIZE, out);

    free(buffer);
    free(freqBuffer);
}

int main(int argc, char **argv) {
	FILE *in = fopen(argv[1], "rb");
	if (in == NULL) {
    	printf ("Error opening file %s: %s\n", argv[1], strerror(errno));
		exit(errno);
	}

	FILE *out = fopen(argv[2], "wb");
	if (out == NULL) {
    	printf ("Error opening file %s: %s\n", argv[2], strerror(errno));
		exit(errno);
	}

	freq(in, out);
	
	fclose(in);
	fclose(out);
}



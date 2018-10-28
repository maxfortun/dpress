#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dpress.h"

#define BUFFER_SIZE 256

void dec(FILE *in, FILE *out) {
	_freq *buffer = (_freq *)malloc(BUFFER_SIZE*sizeof(_freq));
	memset(buffer, 0, BUFFER_SIZE*sizeof(_freq));

	do {
		size_t inCount = fread(buffer, sizeof(_freq), BUFFER_SIZE, in);
		for(int i = 0; i < inCount; i++) {
			_freq freq = buffer[i];
			fprintf(out, "%d %lu\n", i, freq);
		}
    } while(!feof(in));

    free(buffer);
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

	dec(in, out);
	
	fclose(in);
	fclose(out);
}



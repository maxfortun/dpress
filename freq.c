#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dpress.h"

#define BUFFER_SIZE 256

void freq(FILE *in, FILE *out) {
	_freq *buffer = (_freq *)malloc(BUFFER_SIZE*sizeof(_freq));
	memset(buffer, 0, BUFFER_SIZE*sizeof(_freq));

	int ch = 0;
	_freq pos = 0;
	for(; pos < MAX_FREQ; pos++) {
        ch = fgetc(in);
		if(feof(in)) {
			break;
		}
		buffer[ch]++;
		printf("%d %d %d\n", pos, ch, buffer[ch]);
    }
	size_t count = fwrite (buffer, sizeof(_freq), BUFFER_SIZE, out);
	if(count != BUFFER_SIZE) {
    	printf ("Error writing data: %s\n", strerror(errno));
	}
	free(buffer);
	if(pos < MAX_FREQ) {
		printf("Frame incomplete at %d\n", pos);
	} else {
		printf("Frame complete at %d\n", pos);
	}
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



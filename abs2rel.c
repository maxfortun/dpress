#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 256

void abs2rel(FILE *in, FILE *out) {
	unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE*sizeof(unsigned char));
    memset(buffer, 0, BUFFER_SIZE*sizeof(unsigned char));

	int lastCh = 0;
	do {
		size_t inCount = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, in);
		for(int i = 0; i < inCount; i++) {
			unsigned char ch = buffer[i];
			int d = ch - lastCh;
			buffer[i] = d;
			lastCh = ch;
		}
		size_t outCount = fwrite (buffer, sizeof(unsigned char), inCount, out);
    } while(!feof(in));
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

	abs2rel(in, out);
	
	fclose(in);
	fclose(out);
}



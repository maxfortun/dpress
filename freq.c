#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 256

void freq(FILE *in, FILE *out) {
	char *buffer = (char *)malloc(BUFFER_SIZE);
	memset (buffer, 0, BUFFER_SIZE);

	int ch = 0;
	do {
        ch = fgetc(in);
		buffer[ch]++;
		if(ch == EOF) {
			break;
		}
    } while(ch != EOF); 
	size_t count = fwrite (buffer, sizeof(char), BUFFER_SIZE, out);
	if(count != BUFFER_SIZE) {
    	printf ("Error writing data: %s\n", strerror(errno));
	}
	free(buffer);
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

	freq(in, out);
	
	fclose(in);
	fclose(out);
}



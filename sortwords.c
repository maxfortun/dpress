#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dpress.h"

#define BUFFER_SIZE 256


int comparator(const void *a, const void *b)  { 
    int l = ((_char_seq *)a)->ch; 
    int r = ((_char_seq *)b)->ch; 
    return (l - r); 
} 

void sort_words(FILE *in, FILE *out) {
	char *buffer = (char *)malloc(BUFFER_SIZE*sizeof(char));
    memset(buffer, 0, BUFFER_SIZE*sizeof(char));

	size_t bufLen = BUFFER_SIZE*sizeof(char);
	int lastCh = 0;
	do {
		ssize_t inCount = getline(&buffer, &bufLen, in);
		if(inCount <= 0) {
			break;
		}

		_char_seq line[inCount];

		for(int i = 0; i < inCount; i++) {
			_char_seq chSeq;
			chSeq.pos = i;
			chSeq.ch = buffer[i];
			line[i] = chSeq;
		}

		qsort(line, inCount-1, sizeof(_char_seq), comparator);
		for(int i = 0; i < inCount-1; i++) {
			printf ("%c", line[i].ch);
		}
		for(int i = 0; i < inCount; i++) {
			printf (" %d", line[i].pos);
		}
		printf ("\n");

		/*
		size_t outCount = fwrite (buffer, sizeof(unsigned char), inCount, out);
		*/
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

	sort_words(in, out);
	
	fclose(in);
	fclose(out);
}



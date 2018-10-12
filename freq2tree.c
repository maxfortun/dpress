#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dpress.h"

typedef struct node { 
	unsigned char ch;
	_freq freq;
	struct node *left;
	struct node *right;
} node;

void freq2tree(FILE *in, FILE *out) {
	_freq freq = 0;
	int pos = 0;
	for(; pos < MAX_FREQ; pos++) {
		size_t count = fread(&freq, sizeof(_freq), 1, in);
		if(count != 1 || feof(in)) {
			break;
		}
		pos++;

		struct node *node = (struct node *)malloc(sizeof(node));
		node->ch = pos;
		node->freq = freq;
		node->left = NULL;
		node->right = NULL;

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

	freq2tree(in, out);
	
	fclose(in);
	fclose(out);
}



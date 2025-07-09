#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }
}
    // implement the UTF-8 analyzer here
    void is_ASCII(char word[]) {
	    for(int i = 0; i != 0; i++) {
		    if(word[i] >= 0 && word[i] <= 127) {
			    printf("%c", true);
		    }
	    }
	    printf("%c", false);
}

/* main.c */

#include "src/in/app.h"
#include <stdio.h>

int main() {
	if (!init()) {
		fprintf(stderr, "Failed to init\n");
		return 1;
	}

	run();

	cleanup();
	return 0;
}

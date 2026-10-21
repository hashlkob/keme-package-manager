#include <stdio.h>
#include <string.h>

static const char *argv0;

static void usage(void) {
    fprintf(stderr,"usage: %s [-i] ...\n", argv0);
}

int main(int argc, char *argv[]) {
    int info = 0;
    argv0 = argv[0];
    if (argc < 2)
	usage();
    for (int n = 1; n < argc; n++){
	if (strcmp(argv[1], "-i") == 0)
	    info = 1;
	else
	    fprintf(stderr,"unknown flag\n");
	usage();
    }

    if (info == 1) {
	char path[256];
	snprintf(path, 256, "/home/hash/keme-test/recipe/%s-r", argv[2]);
	FILE *f = fopen(path, "r");
	if (f == NULL) {
	    perror(path);
	    return 1;
	}
    char rb[256];
    while(fgets(rb, 256, f))
	fprintf(stdout,"%s", rb);
    }

    return 0;
}

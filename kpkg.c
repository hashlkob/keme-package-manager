#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static const char *argv0;

static void usage(void) {
    fprintf(stderr,"usage: %s [-i] ...\n", argv0);
}

int fetchsrc(const char *url) {
    pid_t cpid = fork();
    if (cpid == 0) {
    	execlp("wget", "wget", "-P", "/home/hash/keme-test/sources/", url, NULL);
    } else {
	waitpid(cpid, NULL, 0);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int info = 0;
    int ins = 0;
    argv0 = argv[0];
   
    char path[256];
    snprintf(path, 256, "/home/hash/keme-test/recipe/%s-r", argv[2]);

    if (argc < 2) {
	usage(); 
    }
    
    /* for flags */
    
    for (int n = 1; n < argc; n++) {
	if (strcmp(argv[1], "-i") == 0) {
	    info = 1; }
	else if (strcmp(argv[1], "-k") == 0) {
	    ins = 1;
	}
	else {
	    fprintf(stderr,"kpkg: unknown argument -- '%s'\n", argv[1]);
	usage(); }
    }

    if (info == 1) {
	FILE *f = fopen(path, "r");
	if (f == NULL) {
	    fprintf(stderr, "recipe not found, '%s'\n", argv[2]);
	    return 1;
	}

	char rb[256];
	while(fgets(rb, 256, f)) {
	    fprintf(stdout,"%s", rb);
	}
	fclose(f);
    }
    
    if (ins == 1) {

    }

    return 0;
}

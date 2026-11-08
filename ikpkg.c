/* rewrite in openbsd knf */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

static const char *argv0;

static void
usage(void)
{
	fprintf(stderr,"usage: %s [-d] [-k] [package ...]\n", argv0);
	exit(1);
}


static int
get_home(void)
{
	struct passwd pw;
	struct passwd *result;
	char passwd_buffer[512];
	getpwuid_r(getuid(), &pw, passwd_buffer, 512, &result);
	return 0;
}

int
fetchsrc(const char *url)
{
	pid_t childpid = fork();
	if (childpid == 0) {
		execlp("wget", "wget", "-P", "", NULL);
	} else {
		waitpid(childpid, NULL, 0);
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	argv0 = argv[0];
	if (geteuid() != 0) {
		fprintf(stderr, "%s: need root privileges\n" , argv0);
		exit(1);
	}
	return 0;
}

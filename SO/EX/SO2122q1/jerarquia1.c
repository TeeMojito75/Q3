#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <error.h>
#include <stdio.h>

void error_y_exit(int status, char *msg) {
	perror(msg);
	exit(status);
}

void Usage() {
	char buff[128];
	sprintf(buff, "./jerarquia2 arg1 [arg2...arg10]\n");
	write(1, buff, strlen(buff));
}


int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 10) Usage();
	else {
		int pids[10];
		for (int i = 1; i < argc; i++) {
			int pid = fork();
			if (pid == -1) error_y_exit(1, "Error en el fork");
			else if (pid == 0) {
				char buff[128];
				sprintf(buff, "Soy el proceso %d y me ha tocado el fichero %s\n", getpid(), argv[i]);
				write(1, buff, strlen(buff));
				exit(i);
			}
			else pids[i-1] = pid;
		}
		int i = 0, pid;
		int status;
		while((pid = waitpid(pids[i], &status, 0)) > 0) {
			if (WIFEXITED(status)) {
				char buff[128];
				sprintf(buff, "Ha muerto el proceso %d con exit status %d\n", pid, WEXITSTATUS(status));
				write(1, buff, strlen(buff));
			}
			i++;
		}
	}
}

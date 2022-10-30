#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void errorExit(char *msg, int status) {
	perror(msg);
	exit(status);
}

void Usage() {
	char buff[128];
	sprintf(buff, "./Procesos00 arg1 ... argN\n");
	write(1, buff, strlen(buff));
	exit(1);
}


int main(int argc, char *argv[]) {
	if (argc < 2) Usage();
	else {
		char buff[128];
		for(int i = 1; i < argc; i++) {
			int pid = fork();
			if (pid == -1) errorExit("Error en el fork", 1);
			if (pid == 0) {
				sprintf(buff, "Soy el proceso %d y me ha tocado el argumento %s\n", getpid(), argv[i]);
				write(1, buff, strlen(buff));
				exit(0);
			}
		}
		int pid;
		while ((pid = waitpid(-1, NULL, 0)) > 0) {
				sprintf(buff, "Ha terminado el proceso %d\n", pid);
				write(1, buff, strlen(buff));
		}
	}
}

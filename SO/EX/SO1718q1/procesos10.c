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
	char buffer[128];
	sprintf(buffer, "./Procesos00 arg1 ... argN\n");
	write(1, buffer, strlen(buffer));
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
				for (int j = 2; j < argc; j++) {
					if (j == 2) sprintf(buff, "%s", argv[j]);
					else sprintf(buff, "%s%s", buff, argv[j]);
				}
				if (execlp(argv[1], argv[1], buff, (char *)0) > 0) errorExit("Error en la mutación", 1);
			}
		}
		int pid;
		while ((pid = waitpid(-1, NULL, 0)) > 0) {
				sprintf(buff, "Ha terminado el proceso %d\n", pid);
				write(1, buff, strlen(buff));
		}
	}
}

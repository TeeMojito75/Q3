#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

int hijos;

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

void trataHijos(int pid, int status) {
	char buff[128];
	if (WIFEXITED(status)) {
		sprintf(buff, "Hijo %d ha temrinado con EXIT, status: %d\n", pid, WEXITSTATUS(status));
		write(1, buff, strlen(buff));
	}
	else if (WIFSIGNALED(status)) {
		sprintf(buff, "Hijo %d ha terminado con SIGNAL, status: %d\n", pid, WTERMSIG(status));
	}
}

void trata_SIGCHLD(int s) {
	if (s == SIGCHLD) {
		int pid, status;
		while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
			trataHijos(pid, status);
			--hijos;
		}
	}
	if (s == SIGALRM) {
		printf("procesando...\n");
	}
}


int main(int argc, char *argv[]) {
	if (argc < 2) Usage();
	else {
		hijos = argc - 1;
		struct sigaction sa;
		sigset_t mask;
		
		sigemptyset(&mask);
		sigaddset(&mask, SIGCHLD);
		sigaddset(&mask, SIGALRM);
		sigprocmask(SIG_BLOCK, &mask, NULL);

		sa.sa_flags = SA_RESTART;
		sa.sa_handler = trata_SIGCHLD;
		sigaction(SIGCHLD, &sa, NULL);
		sigaction(SIGALRM, &sa, NULL);

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
		sigfillset(&mask);
		sigdelset(&mask, SIGCHLD);
		sigdelset(&mask, SIGALRM);
		sigdelset(&mask, SIGINT);
		alarm(1);
		
		while (hijos > 0) {
			if (sigsuspend(&mask) != -1) errorExit ("Error en el sigsuspend", 1);
		}
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

int hijos;
char *msg = "procesando...\t";

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
		printf("%s",msg);
		alarm(1);
	}
	if (s == SIGHUP) {
		if (msg == "procesando...\t") msg = "processant...\t";
		else msg = "procesando...\t";
	}
}


int main(int argc, char *argv[])
{
	if (argc >= 2) {
		char *programa = argv[1];
		argv++;
		hijos = argc - 1;

		sigset_t mask;
		struct sigaction sa;

		// Block signals
		sigemptyset(&mask);
		sigaddset(&mask, SIGCHLD);
		sigaddset(&mask, SIGALRM);
		sigprocmask(SIG_BLOCK, &mask, NULL);

		// Reprogram SIGCHLD
		sa.sa_handler = trata_SIGCHLD;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &sa, NULL);
		sigaction(SIGALRM, &sa, NULL);

		for (int i = 1; i < argc; ++i) {
			int pid = fork();
			if (pid == 0) {
				// Como el proceso muta, se pierde la reprogramación de los signals
				execvp(programa, argv);
				errorExit("Error en el execvp", 1);
			}
			if (pid < 0) {
				errorExit("Error en el fork", 1);
			}
		}

		sigfillset(&mask);
		sigdelset(&mask, SIGCHLD);
		sigdelset(&mask, SIGALRM);
		sigdelset(&mask, SIGINT);

		alarm(1);
		while (hijos > 0) {
			if (sigsuspend(&mask) != -1) errorExit("Error en el sigsuspend", 1);
		}
	}
	else {
		Usage();
	}
}


#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <error.h>
#include <stdio.h>
#include <signal.h>

int recibido = 0;

void tratar(int s) {
	if (s == SIGUSR1) recibido++;
}

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
		struct sigaction trat;
		trat.sa_handler = &tratar;
		trat.sa_flags = 0;
		sigemptyset(&trat.sa_mask);
		sigaction(SIGUSR1, &trat, NULL);

		sigset_t mask;
		sigemptyset(&mask);
		sigaddset(&mask, SIGINT);
		sigaddset(&mask, SIGALRM);
		sigprocmask(SIG_BLOCK, &mask, NULL);

		int pids[10];
		for (int i = 1; i < argc; i++) {
			int pid = fork();
			if (pid == -1) error_y_exit(1, "Error en el fork");
			else if (pid == 0) {
				while(!recibido);
				char buff[128];
				sprintf(buff, "Soy el proceso %d y me ha tocado el fichero %s\n", getpid(), argv[i]);
				write(1, buff, strlen(buff));
				exit(i);
			}
			else pids[i-1] = pid;
		}
		sigaction(SIGINT, &trat, NULL);
		sigaction(SIGALRM, &trat, NULL);

		int i = 0;
		for (int j = 1; j < argc; ++j) {
			sigfillset(&mask);
			sigdelset(&mask, SIGINT);
			sigdelset(&mask, SIGALRM);
			alarm(2);
			sigsuspend(&mask);

			if (alarm(0) == 0) {
				for (int k = 1; k < argc; k++) kill(pids[k-1], SIGKILL);
				break;
			}
			else {
				char buff[128];
				sprintf(buff, "Soy el padre y he salido de la espera\n");
				write(1, buff, strlen(buff));
				kill(pids[i], SIGUSR1);
				++i;
			}
		}

		int status, pid;
		while((pid = waitpid(-1, &status, 0)) > 0) {
			char buff[128];
			if (WIFEXITED(status)) {
				sprintf(buff, "Ha muerto el proceso %d por EXIT, status: %d\n", pid, WEXITSTATUS(status));
				write(1, buff, strlen(buff));
			}
			else if (WIFSIGNALED(status)) {
				sprintf(buff, "Ha muerto el proceso %d por SIGNAL, status: %d\n", pid, WTERMSIG(status));
			}
			++i;
		}
	}
}

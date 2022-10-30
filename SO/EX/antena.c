#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void Usage() {
	printf("Usage: ./antena n (sea n la altura, n >= 2)\n");
	printf("El programa crea una antena de procesos\n");
}

int main(int argc, char *argv[]) {
	if (argc == 1 || atoi(argv[1]) <= 1) Usage();
	else {
		printf("Padre: pid %d\n", getpid());
		for (int i = 1; i <= atoi(argv[1])-1; ++i) {
			if (i <= atoi(argv[1])-2) {
				int pid = fork();
				if (pid != 0) exit(0);
				printf("Hijo: pid %d, mi padre es %d\n", getpid(), getppid());
			}
			else {
				int pid = fork();
				if (pid != 0) pid = fork();
				if (pid != 0) pid = fork();
				if (pid != 0) exit(0);    
			}
		}
		printf("Hijo: pid %d, mi padre es %d\n", getpid(), getppid());
	}
}

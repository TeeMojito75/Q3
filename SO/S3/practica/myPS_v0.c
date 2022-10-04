#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void error_y_exit (char *msg, int exit_estatus) {
    perror(msg);
    exit(exit_estatus);
}

int main(int argc, char* argv[]) {
    int pid = fork();
    char buffer [80];
	
    switch(pid) {
	case 0:
        	sprintf(buffer, "Soy el proceso HIJO: %d de %s\n", getpid(), argv[1]);
		write(1, buffer, strlen(buffer));
		while(1);
		break;
	case -1:
		sprintf(buffer, "Ha fallado el forj del proceso: %d\n", getpid());
		error_y_exit(buffer, 1);
		break;

	default:
		sprintf(buffer, "Soy el proceso PADRE: %d\n", getpid());
		write(1, buffer, strlen(buffer));
		while(1);
		break;

    }

}


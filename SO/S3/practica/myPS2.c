#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_y_exit (char *msg, int exit_estatus) {
    perror(msg);
    exit(exit_estatus);
}



int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        int pid = fork();
        char buffer [80];

	switch(pid) {
	    case 0:
	           sprintf(buffer, "Soy el parametro  HIJO: %d de %s\n", getpid(), argv[i]);
                   write(1, buffer, strlen(buffer));
		  
	    default:
		    waitpid(-1, NULL, 0);
	    
	    case -1:
		    sprintf(buffer, "Ha fallado el fork del proceso %d\n", getpid());
		    error_y_exit(buffer, 1);
	}
    }
	return 0;
}


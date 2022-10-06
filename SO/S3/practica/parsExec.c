#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void exit_y_error(char *msg, int error) {
	perror(msg);
	exit(error);
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < 4; ++i) {
		char buffer[100];
		int pid = fork();
		
		switch(pid) {
	case 0:
		if (i == 0) execlp("./listaparametros", "./listaparametros", "a", "b", NULL);	
		if (i == 1) execlp("./listaparametros","./listaparametros", NULL);
		if (i == 2) execlp("./listaparametros","./listaparametros", "25", "4", NULL);
		if (i == 3) execlp("./listaparametros","./listaparametros", "1024", "hola", "adios" , NULL);	
		exit_y_error("error_execlp",1);	

	case -1:
		sprintf(buffer, "Ha fallado el fork del proceso %d\n", getpid());
		exit_y_error(buffer, 1);
		}
	}
	while (waitpid(-1, NULL, 0) > 0);
}

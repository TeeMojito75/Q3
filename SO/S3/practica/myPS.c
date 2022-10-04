#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void error_y_exit (char *msg, int exit_estatus) {
    perror(msg);
    exit(exit_estatus);
}

/* Ejecuta el comando ps –u username mediante la llamada al sistema execlp */
/* Devuelve: el código de error en el caso de que no se haya podido mutar */
void muta_a_PS(char *username) {
	execlp("ps", "ps", "-u", username, (char*)NULL);
	error_y_exit("Ha fallado la mutación al ps", 1);
}

int main(int argc, char* argv[]) {
    int pid = fork();
    char buffer [80];
	
    switch(pid) {
	case 0:
        	sprintf(buffer, "Soy el proceso HIJO: %d de %s\n", getpid(), argv[1]);
		write(1, buffer, strlen(buffer));
		muta_a_PS(argv[1]);
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


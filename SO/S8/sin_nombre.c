#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_y_exit(int error, char *msg) {
  perror(msg);
  exit(error);
}

void main(int argc, char* argv[]) {
  char buff[256];
  int fd[2]; //Vector para los canales de entrada(0) y salida(1) de la pipe
  int ret;
  if (pipe(fd) == -1) error_y_exit(1, "La creación de la pipe ha fallado"); //Creamos la pipe, si falla imprimimos error
  ret = fork(); //Hacemos fork() para crear el hijo
  if (ret == 0) {
    dup2(fd[0], 0); //Con dup2, hacemos asociamos canal de entrada del hijo a la pipe creada
    close(fd[0]); close(fd[1]); //Cerramos los canales innecesarios para que no se bloquee
    execlp("cat","cat", NULL); //Mutamos
    error_y_exit(1, "La mutación ha fallado");
  }
  else {
    close(fd[0]); //Cerramos canal de escritura del padre por no usarse y para que no se bloquee
    sprintf(buff, "Inicio\n");
    write(fd[1], buff, strlen(buff));
   // close(fd[1]); //Cerramos el canal de escritura una vez usado
    waitpid(-1, NULL, 0); //Esperamos al hijo
    sprintf(buff, "Fin\n");
    write(1, buff, strlen(buff)); 
  }
}

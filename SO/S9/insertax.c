#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void error_y_exit(char* msg, int error_status) {
	perror(msg);
	exit(error_status);
}

int main() {
	char buf[256];
	char bufx[256];

	int f = open("salida.txt", O_RDWR); //abrimos el fichero para poder leer e insertar la x
	if (f == -1) error_y_exit("Ha fallado el open", 1);

	//Leemos el último carácter
	lseek(f, -1, SEEK_END);
	read(f, buf, sizeof(char));

	//Nos posicionamos en el penúltimo y añadimos la 'x'
	lseek(f, -1, SEEK_CUR);
	sprintf(bufx,"X");
	write(f, bufx, strlen(bufx));

	//Se añade el trozo con x al último carácter
	write(f, buf, strlen(buf));
}

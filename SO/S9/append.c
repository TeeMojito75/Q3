#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void main(int argc, char* argv[]) {
	if (argc == 1) printf("Usage(): ./append file \n");
	else {
		char buff[128];
		int fd = open(argv[1], O_RDONLY);  //Abrimos el archivo para leer
		int fd2 = open(argv[1], O_WRONLY); //Abrimos otra instancia para escribir
		if (fd == -1 | fd2 == -1) perror("Error en open"); //control errores
		lseek(fd, 0, SEEK_SET); //Ponemos la posición de fd al inicio del doc para leer el número
		int fi = lseek(fd2, 0, SEEK_END); // Creamos una var para poder ir leyendo byte a byte el documento y ponemos fd2 al final del documento para escribir ahí
		while (fi != 0) { //Iteramos en fd leyendo un byte y escribir en fd2
			read(fd, buff, 1);
			write(fd2, buff, 1);
			--fi;
		}
		close(fd);
		close(fd2); //Una vez acabado cerramos los archivos
	}
}

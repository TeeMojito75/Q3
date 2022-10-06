#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void Usage(int argc) {
    char *b1= "Usage:listaParametros arg1 [arg2..argn]\n";
    char *b2= "Este programa escribe por su salida la lista de argumentos que recibe\n";
    if (argc <= 1) {
	write(1, b1, strlen(b1));
	write(1, b2, strlen(b2));
	exit(1);
    }
}

void main(int argc,char *argv[])
{
char buf[80];
	Usage(argc);
	for (int i=0;i<argc;i++){
		if (i==0){
			sprintf(buf,"El argumento %d es %s (es el nombre del ejecutable)\n",i,argv[i]);
		}else{
			sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
		}
		write(1,buf,strlen(buf));
	}
}

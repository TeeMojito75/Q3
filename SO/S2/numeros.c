#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 8

int esNumero (char *str) {
    if (str == NULL) return 0;

    if (str[0] == '-') ++str;

    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9') return 0;
	if (i > MAX_SIZE) return 0;
    }
    return i > 0;
}

int main(int argc, char *argv[]) 
{
    char buffer[100];
    for (int i = 1; i < argc; i++)
	{
	    if (esNumero (argv[i]) == 1) sprintf(buffer, 
	        "El argumento %d de valor %s es un número con 8 o menos cifras\n",i, argv[i]);
	
          else  sprintf (buffer,
		 "El argumento %d de valor %s o no es un número, o es nulo, o tiene más de 8 cifras\n",
		 i, argv[i]);
	write(1, buffer, strlen(buffer));
	}
}

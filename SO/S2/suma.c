#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 8

unsigned int char2int(char c) {
    return c-'0';
}

int mi_atoi(char *s) {
    int suma = 0;
    int aux = 1;
    for (int i = strlen(s)-1; i >= 0; i--) {
	if (s[i] == '-') suma *= -1;
	else if (s[i] !='-') {
	     suma += char2int(s[i])*aux;
		aux*=10;
   }
	 }
    return suma;
}

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
    char buff[100];
    int suma = 0;
    for (int i = 1; i < argc; i++)
	{
	if (esNumero(argv[i])) suma += mi_atoi(argv[i]);
	else {
	    sprintf(buff, "Error: el parámetro \"%d\" no es un número\n", argv[i]);
	    write(1, buff, strlen(buff));
	    exit(1);
        	} 
	}
     sprintf(buff, "La suma es %d", suma);
     write(1, buff, strlen(buff));

}

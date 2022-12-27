#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void error_y_exit(char *msg, int error) {
	perror(msg);
	exit(error);
}

int main() {
	char buf[256];
	int f = creat("salida.txt", O_CREAT|O_TRUNC|S_IRUSR|S_IWUSR);
	if (f == -1) error_y_exit("error en el archivo", 1);
	sprintf(buf, "ABCD");
	write(f,buf,strlen(buf));
}

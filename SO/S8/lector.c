#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[]) {
  char buff[256];
  int leidos;
  int fd = open("PIPE1", O_RDONLY);
  dup2(fd, 0);
  while((leidos = read(0, buff, sizeof(buff))) > 0) {
    write(1, buff, leidos);
  }
  close(fd); 
}

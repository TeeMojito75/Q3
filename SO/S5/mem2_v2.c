#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define REGION_SIZE		4096

int *p;

void func(int s) {
  char buff[100];
  int *n = sbrk(0);
    sprintf (buff, "\t p address: %p, p value: %p, darrer val heap: %p\n", &p, p, n);
    write(1, buff, strlen(buff));
  exit(1);
}

int
main (int argc, char *argv[])
{
  int i = 0;
  char buff[256];

  struct sigaction sa;    
  sa.sa_handler = &func;
  sa.sa_flags = SA_RESTART;                                                               
  sigfillset(&sa.sa_mask);
  sigaction(SIGSEGV, &sa, NULL);       

  sprintf (buff, "Addresses:\n");
  write (1, buff, strlen (buff));
  sprintf (buff, "\tp: %p\n", &p);
  write (1, buff, strlen (buff));

  p = malloc (sizeof (int));

  if (p == NULL)
    {
      sprintf (buff, "ERROR en el malloc\n");
      write (2, buff, strlen (buff));
    }

  while (1)
    {
      *p = i;
      sprintf (buff, "\tProgram code -- p address: %p, p value: %p, *p: %d\n",
               &p, p, *p);
      write (1, buff, strlen (buff));
      p++;
      i++;
    }

}

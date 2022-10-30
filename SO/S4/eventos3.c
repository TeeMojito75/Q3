#include <unistd.h>                                                                                 
#include <stdlib.h>                                                                              
#include <stdio.h>                                                                                    
#include <signal.h>                                                                                    
#include <string.h> 

void error_y_exit (char *msg, int exit_status) {                                                          perror (msg);                                                                                      
  exit (exit_status);                                                                                  
}   

int segundos = 0;

void funcion_alarma(int s) {
  char buff[250];
   ++segundos;
  if (s == SIGUSR1) segundos = 0;
  else if (s == SIGUSR2) {
    sprintf (buff, "ALARMA pid=%d: %d segundos\n", getpid (), segundos);   
    write (1, buff, strlen(buff));
  }
  struct sigaction sa1;
    sa1.sa_handler = SIG_DFL;
    sa1.sa_flags = SA_RESTART;
    sigfillset(&sa1.sa_mask);
    sigaction(SIGUSR1, &sa1, NULL);
     
}

int main(int argc, char *argv[]) {
  struct sigaction sa;
  sigset_t mask;

  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  sigaddset(&mask, SIGUSR1);
  sigaddset(&mask, SIGUSR2);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  //Reprogramamos sigalarm
  sa.sa_handler = &funcion_alarma;
  sa.sa_flags = SA_RESTART;
  sigfillset(&sa.sa_mask);

  if (sigaction (SIGALRM, &sa, NULL) < 0 || sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)                         
   error_y_exit ("sigaction", 1); 

  while (1) {                                                        
        alarm (1);              /* Programamos la alarma para dentro de 10 segundos */               
        /* Nos bloqueamos a esperar que nos llegue un evento */                                        
        sigfillset (&mask);                                                                            
        sigdelset (&mask, SIGALRM);                                                                    
        sigdelset (&mask, SIGINT);                                                                     
        sigdelset(&mask, SIGUSR1);                                                                    
        sigdelset(&mask, SIGUSR2);
        sigsuspend (&mask);                                                                            
      }                                                                                                     exit (1);
}

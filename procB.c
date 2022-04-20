#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <ucontext.h>

sig_atomic_t check; //flag for signals

void signalHandler(int sig, siginfo_t* si, void* ucontext){
  if(sig == 2){
    //SIGINT
    check = 1;
  }
  if(sig == 10){
    //SIGUSR1
    check = 2;
  }
}

int main(){
    printf("in procB\n");
    //display procB pid if want to issue kill by pid (kill -2 <pid>) instead of ctrl^c
    printf("procB pid: %d\n", getpid());

    //get pid of procA by user input (procA displays it's pid on execution)
    pid_t Apid;
    printf("Input pid of ProcA: ");
    scanf("%d", &Apid);
    //error check if inputted pid is an active process
    if(kill(Apid, 0) == -1){
      printf("invalid pid of procA\n");
      exit(1);
    }
    printf("------------\n");

    //setup sigaction
    struct  sigaction sigact;
    sigact.sa_flags = SA_RESTART | SA_SIGINFO;
    sigact.sa_sigaction = signalHandler;
    sigaction(SIGINT ,&sigact, NULL);
    sigaction(SIGUSR1, &sigact, NULL);

    //ready to receive signals
    while (1){ //used to continuously keep proc running
      //sig_atomic t check changed to 1 for the SIGINT case
      if(check == 1){
        printf("procB received a SIGINT, sending a SIGUSR1 to procA\n");
        kill(Apid, SIGUSR1);
        check = 0;
      }
      //sig_atomic t check changed to 2 for the SIGUSR1 case
      if(check == 2){
        printf("received a SIGUSR1 from procA\n");
        check = 0;
      }
      (void)pause();
      }
    //have to manually exit to quit program 
    return 1;
}
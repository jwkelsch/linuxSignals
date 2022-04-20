#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <ucontext.h>

sig_atomic_t check; //flag for signals
sig_atomic_t procBpid;

void signalHandler(int sig, siginfo_t* si, void* ucontext){
  procBpid = si->si_pid; //gets procB pid from siginfo struct
  if(sig == 10){//SIGUSR1
    check = 1;
  }
}

int main(){
    //display pid for procB to input
    printf("in procA\n");
    pid_t Apid = getpid();
    printf("procA pid: %d\n", Apid);
    
    //setup sigaction
    struct  sigaction sigact;
    sigact.sa_flags = SA_RESTART | SA_SIGINFO;
    sigact.sa_sigaction = signalHandler;
    sigaction(SIGUSR1, &sigact, NULL);
    printf("------------\n");

    //ready tp receive signals
    while (1){ //used to continuously keep proc running
      //check = 1,  SIGUSR1 case
      if(check == 1){
        printf("SIGUSR1 received from procB, sending SIGUSR1 back to procB\n");
        kill(procBpid, SIGUSR1);
        check = 0;
    }
		  (void)pause();
      //have to manually exit to quit program 
    }
    return 1;
}
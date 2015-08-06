#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DO_PTHREAD_TEST

#ifdef DO_PTHREAD_TEST
#include "pthread.h"

pthread_mutex_t mutex;

void segFaultMe();

void threadBody( void *ptr ) {
	int lockMe = (int)ptr;

	if (lockMe) pthread_mutex_lock(&mutex);
	segFaultMe();
	if (lockMe) pthread_mutex_unlock(&mutex); 
}
#endif

void shutdownHook() {
	printf("shutdownHook...\n");
	if (pthread_mutex_trylock(&mutex) != 0) {
		printf("Mutex is locked. Unlocking...\n");
		//--locked;
		pthread_mutex_unlock(&mutex); 
	} else {
		printf("Mutex is NOT locked.\n");
		pthread_mutex_unlock(&mutex); 
	}
	printf("shutdownHook is done.\n");
}


void term(int signum)
{
    printf("Received SIGTERM, exiting...\n");
	shutdownHook();
}

void segv(int signum)
{
    printf("Received SIGSEGV, exiting...\n");
	shutdownHook();
	signal(signum, SIG_DFL);
	kill(getpid(), signum);
}

void segFaultMe() {
	int *p = 0;
	*p = 1;
}

int main(int argc, char **argv) {
	printf("Start...\n\n");
	printf("To test it     locking mutex: %s 1\n", argv[0]);
	printf("To test it NOT locking mutex: %s\n\n", argv[0]);
	
	atexit(shutdownHook);

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    
	struct sigaction action2;
    memset(&action2, 0, sizeof(struct sigaction));
    action2.sa_handler = segv;
    sigaction(SIGSEGV, &action2, NULL);

#ifdef DO_PTHREAD_TEST
	int lockMe = 0;
	if (argc > 1) {
		lockMe = 1;
	}

	pthread_mutex_init(&mutex, NULL);

	pthread_t thread1;
    pthread_create(&thread1, NULL, (void *) &threadBody, (void *)lockMe);
	
	while(1) {
	}
	
	pthread_mutex_destroy(&mutex);
#else

	segFaultMe();
#endif

	printf("End.\n");
}

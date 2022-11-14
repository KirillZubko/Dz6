#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *thread_function(void *arg){	
	int n = *(int*)arg, i;	

	if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0) 
		printf("Setcanselstate error!\n");

	for(i = 0; i < n*2; i++){
		printf("Iteration %d\n", i);
		sleep(1);			
	}
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong amount of arguments!\n"); 
		exit(0);
	}	
		
	pthread_attr_t attr;
	pthread_t thread;
	int *status;		
	int n = atoi(argv[1]);
	
	//sozdaem attr
	pthread_attr_init(&attr);
	if(pthread_create(&thread, &attr, &thread_function, &n) != 0) {
		printf("Error\n"); 
		exit(0);
	}

	sleep(n);
	
	if (pthread_cancel(thread) != 0) 
		printf("Cancel error!\n");
	
	if ((pthread_join(thread, (void*)&status) != 0)) {
		printf("Join error\n"); 
		exit(0);
	}	
	

	if (status == PTHREAD_CANCELED) 
		printf("Thread canceled\n");
	else 
		printf("Thread finished normally\n");
			
	pthread_attr_destroy(&attr);
	return 0;
}

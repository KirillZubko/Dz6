#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleanHandler(){
	fprintf(stderr, "Clean handler started\n");
}

void *thread_function(){	
	int i = 0;
	while(1){
		printf("Iteration: %d\n", i++);
		sleep(1);
		if (i == 10)
			break;			
	}
	fprintf(stderr, "Thread work has been finished\n");
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong amount of arguments!\n");
		exit(0);
	}	

	pthread_t thread;
	void* res;		
	int n = atoi(argv[1]);
	
	//sozdaem potok
	if(pthread_create(&thread, NULL, &thread_function, NULL) != 0) {
		fprintf(stderr, "Error\n"); 
		exit(0);
	}
	
	sleep(n);

	pthread_cleanup_push(cleanHandler, NULL);
	
	pthread_cancel(thread);
	
	pthread_cleanup_pop(1);
	
	if (!pthread_equal(pthread_self(), thread)){
		pthread_join(thread, &res);
	}

	if (res == PTHREAD_CANCELED){
		fprintf(stderr, "Main thread has finished thread's work\n");
	}

	return 0;
}

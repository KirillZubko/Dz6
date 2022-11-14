#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static pthread_key_t thread_key;

void *thread_function(void *arg){	
	int id = *(int*) arg, i, stringsAmount, r;

	
	char* str = "Random number: ";
	pthread_setspecific(thread_key, (void*) str);	
	char* spec = (char*) pthread_getspecific(thread_key);	

	stringsAmount = 1 + rand() % 10;	
	for (i = 0; i < stringsAmount; i++){
		r = 1 + rand() % 10;
		printf("Thread #%d. %s %d\n", id, spec, r);
	}	
	sleep(stringsAmount);	
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong amount of arguments!\n"); 
		exit(0);
	}	
	srand(time(NULL));

	//massiv potokov
	int n = atoi(argv[1]);	
	pthread_t threads[n];	
	int i;

	pthread_key_create(&thread_key, NULL);
		
	//sozdaem potoki
	for(i = 0; i < n; i++){
		if(pthread_create(&(threads[i]), NULL, &thread_function, &i) != 0){
			printf("Error\n");
			exit(0);
		}
		sleep(1);
	}	

	//zhdem, poka vse potoki zavershatca
	for (i = 0; i < n; i++){
		if ((pthread_join(threads[i], NULL) != 0)) {
			fprintf(stderr, "Join error\n"); 
			exit(0);
		}
	}	
	return 0;
}

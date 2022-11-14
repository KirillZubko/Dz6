#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int* check_massiv; 

//pechataem massiv
void *det_thread_func(void *arg){

	sleep(0.5);		
	int n = *(int*)arg, i, flag;
	while(1){
		flag = 0;
		
		for(i = 0; i < n; i++){		
			if (check_massiv[i] == 0) 
				flag = 1;			
		}	
			
		if (flag = 0) 
			break;
				
		for (i = 0; i < n; i++){
			printf(":[%d]", check_massiv[i]);
		}
		printf("\n");
		sleep(1);		
	}
}

void *join_thread_func(void *arg){	

	int num = *(int *)arg, i, r;
	sleep(num);
	//generim randomniw chisla
	r = 1 + rand() % 10;
	printf("Randomnoe chislo: %d\n", r);
	check_massiv[num] = r;
	sleep(r);	
	return NULL;
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong amount of arguments!\n");
		exit(0);
	}		
	srand(time(NULL));
	
	pthread_attr_t attr;
	pthread_t detached_thread, joinable_thread;		
	int n = atoi(argv[1]);
	int i;
	check_massiv = (int*)calloc(n, sizeof(int));

	//sozdaem attr
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(pthread_create(&detached_thread, &attr, &det_thread_func, &n) != 0){
		fprintf(stderr, "Error\n");
		exit(0);
	}
	
	//sozdaem n potokov	
	for(i = 0; i < n; i++){
		if(pthread_create(&joinable_thread, NULL, &join_thread_func, &i) != 0){
			printf("Error\n");
			exit(0);
		}
		sleep(1);
	}	

	if ((pthread_join(joinable_thread, NULL) != 0)) {
		printf("Join error\n"); 
		exit(0);
	}	
	pthread_attr_destroy(&attr);
	return 0;
}

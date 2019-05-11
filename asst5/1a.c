#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/shm.h> 
#include <sys/wait.h> 
#include<semaphore.h>
#include<pthread.h>
int	shmID,shmID1,shmID2,shmID3,shmID4,shmID5;	
key_t 	key1 = 54991, key2 = 784519, key3 = 882363, key4 = 23456,key5 = 10002,key6 = 23252;
int	*n;
sem_t *full, *empty;
int *buffer;
int *indp, *indc;
int main(){

	shmID = shmget(key1, sizeof(int), IPC_CREAT | 0660);
	if(shmID < 0){
		printf("Shared memory could not be allocated\n");
		exit(1);
	}
	n = (int *)shmat(shmID, NULL, 0); 
        if (n == (int *)-1 ) {
            printf("Failed to attach n to first process\n");
            exit(-1); 
        } 
	
	shmID1 = shmget(key2, sizeof(sem_t), IPC_CREAT | 0660);
	if(shmID1 < 0){
		printf("Shared memory could not be allocated\n");
		exit(1);
	}
	full = (sem_t *)shmat(shmID1, NULL, 0); 
        if (full == (sem_t *)-1 ) {
            printf("Failed to attach n to first process\n");
            exit(-1); 
        } 
        
        shmID2 = shmget(key3, sizeof(sem_t), IPC_CREAT | 0660);
	if(shmID2 < 0){
		printf("Shared memory could not be allocated\n");
		exit(1);
	}
	empty = (sem_t *)shmat(shmID2, NULL, 0); 
        if (empty == (sem_t *)-1 ) {
            printf("Failed to attach n to first process\n");
            exit(-1); 
        } 
        //printf("hi");
        shmID3 = shmget(key4, sizeof(int)*100, IPC_CREAT | 0660);
	if(shmID3 < 0){
		printf("Shared memory could not be allocated\n");
		exit(1);
	}
	//printf("hi");
	buffer = (int *)shmat(shmID3, NULL, 0);
	if (buffer == (int *)-1 ) {
            printf("Failed to attach n to first process\n");
            exit(-1); 
        } 
	//printf("hi"); 
        //buffer = (int *)malloc(sizeof(int)*100);
        //for(int i=0;i<100;i++){
        //	printf("%d ",buffer[i]);
        //}

	shmID4 = shmget(key5, sizeof(int), IPC_CREAT | 0660);
	if(shmID4 < 0){
		printf("Shared memory could not be allocated\n");
		exit(1);
	}
	indp = (int *)shmat(shmID4, NULL, 0); 
        if (indp == (int *)-1 ) {
            printf("Failed to attach n to first process\n");
            exit(-1); 
        }
        shmID5 = shmget(key6, sizeof(int), IPC_CREAT | 0660);
	if(shmID5 < 0){
		printf("Shared memory could not be allocated\n");
		exit(1);
	}
	indc = (int *)shmat(shmID5, NULL, 0); 
        if (indc == (int *)-1 ) {
            printf("Failed to attach n to first process\n");
            exit(-1); 
        }


	printf("Enter n\n");
	scanf("%d",n);
	sem_init(full,0,0);
	sem_init(empty,0,*n);
	*indc = 0;
	*indp = 0;
	//int p1 = fork();
	//int p2 = fork();
	//producer

	if(fork() == 0){
		n = (int *)shmat(shmID, NULL, 0);
		full = (sem_t *)shmat(shmID1, NULL, 0);
		empty = (sem_t *)shmat(shmID2, NULL, 0); 
		indp = (int *)shmat(shmID4, NULL, 0);
		indc = (int *)shmat(shmID5, NULL, 0); 
		buffer = (int *)shmat(shmID3, NULL, 0);
		for(int done=0;done<15;done++){
			int item = rand()%50;
			sem_wait(empty);
				buffer[*indp] = item;
				*indp = (*indp + 1)%*n;
				printf("Producer produced item = %d\n",item);
			sem_post(full); 
			
		}
		
	
	}
	else{
		//consumer
		n = (int *)shmat(shmID, NULL, 0);
		full = (sem_t *)shmat(shmID1, NULL, 0);
		empty = (sem_t *)shmat(shmID2, NULL, 0); 
		indp = (int *)shmat(shmID4, NULL, 0);
		indc = (int *)shmat(shmID5, NULL, 0); 
		buffer = (int *)shmat(shmID3, NULL, 0);
		
			for(int done=0;done<15;done++){
				sem_wait(full);
					int item = buffer[*indc];
					*indc = (*indc + 1)%*n;
					printf("Consumer consumed item = %d\n",item);
				sem_post(empty); 
				
			}
		
		
			sleep(1);		 	
			wait(NULL);
			wait(NULL);
		
	}
		
}

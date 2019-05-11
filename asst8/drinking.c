#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#define n 5
pthread_t p[n];
int owner[n];
sem_t s[n];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int state[n];


void request(int fork,int ownId){
	while(owner[fork] != ownId){
		if(state[fork] == 0){
			pthread_mutex_lock(&m);
			owner[fork] = ownId;
			pthread_mutex_unlock(&m);
		}
		else{
			sem_wait(&s[fork]);
		}
	}
}

void think(int num){
	printf("Philosopher %d is thinking\n",num);
	sleep(rand()%5);
}
void eat(int num){
	int left = (num - 1 + n)%n;
	int right = (num + 1)%n;
	request(left,num);
	request(right,num);
	
	printf("Philosopher %d is eating\n",num);
	sleep(rand()%3);
	
	sem_post(&s[left]);
	sem_post(&s[right]);

}


void* func(void* num){

	int k = (int)num;
	while(1){
		think(k);
		eat(k);
	}
}

int main(){
	for(int i=0;i<n;i++){
		state[i] = 0;
		sem_init(&s[i],0,1);
		owner[i] = i;
	}
	
	for(int i=0;i<n;i++){
		pthread_create(&p[i],NULL,func,(void*)i);
		
	}
	for(int i=0;i<n;i++){
		pthread_join(p[i],NULL);
	}
	return 0;
}

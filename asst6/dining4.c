#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t Fork[N];
sem_t waiter;

void *philosopher(void *ptr)
{
    int k = *((int *) ptr);

    while (1) 
    {
        printf("Philosopher %d: Thinking\n", k);
        sem_wait(&waiter);
        sleep(1);
        sem_wait(&Fork[k]);
        sem_wait(&Fork[(k + 1) % N]);
        printf("Philosopher %d: Eating\n", k);
        sem_post(&Fork[k]);
        sem_post(&Fork[(k + 1) % N]);
        sleep(1);
        sem_post(&waiter);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int i, tid[N];
    pthread_t thread[N];

	sem_init(&waiter, 0, 1);
	
    for (i = 0; i < N; i++)
        sem_init(&Fork[i], 0, 1);
        
    for (i = 0; i < N; i++) 
    {
        tid[i] = i;
        pthread_create(&thread[i], NULL, &philosopher, &tid[i]);
    }
    
    for (i = 0; i < N; i++)
        pthread_join(thread[i], NULL);

    return 0;
}


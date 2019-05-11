#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t Fork[N];

void *philosopher(void *ptr)
{
    int k = *((int *) ptr);

    while (1) 
    {
        sleep(2);
        printf("Philosopher %d: Thinking\n", k);
        
        if (k == N - 1) 
        {
            sem_wait(&Fork[(k + 1) % N]);
            sem_wait(&Fork[k]);
        } 
        else 
        {
            sem_wait(&Fork[k]) ;
            sem_wait(&Fork[(k + 1) % N]);
        }
        
        printf("Philosopher %d: Eating\n", k);
        sem_post(&Fork[k]) ;
        sem_post(&Fork[(k + 1) % N]);
    }
}

int main(int argc, char *argv[])
{
    int i, tid[N];
    pthread_t thread[N];

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


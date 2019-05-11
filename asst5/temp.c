

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/times.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>

void f_error(char *s)      // error message function
{
  perror(s);
  exit(-1);                   
}

int *Buffer;
int maximum;
//int *var, *var1, *var2;
int bufLength;
sem_t mut;
sem_t empty;
sem_t full;
void producer(int thread_num);
void consumer(int thread_num);

int main(int argc, char *argv[])
{
      int i, x, PID;
      int pno = atoi(argv[3]), cno = atoi(argv[4]);
      int myshmid;
      pthread_t tid1[pno];
      pthread_t tid2[cno];

      if(argc != 5)
    {  
            printf("Wrong number of parameters. Please enter 4 parameters.\n");
            exit(1);
    }
      bufLength = atoi(argv[2]);
      maximum = atoi(argv[1]);
      
      myshmid = shmget (IPC_PRIVATE, ((bufLength * 2) * sizeof(int)) + (3 * sizeof(int)), IPC_CREAT | 0600);
      if (myshmid == -1)
            f_error("shmget failed");
      Buffer = shmat(myshmid, NULL, 0);
      if (((int)Buffer) == -1)
            f_error("Invalid shared memory ID");

      Buffer[0] = 0;
      Buffer[1] = 0;
      Buffer[2] = 0;

      sem_init(&mut, 0, 1);
      sem_init(&full, 0, 0);
      sem_init(&empty, 0, bufLength);
      
      for(i = 0; i < pno; i++)
      {
            if ((PID = fork()) == 0)
            {
                  printf("Creating producer %d\n", i + 1);
                  producer(i + 1);
                  exit(0);
            }
      }
      
      if (PID != 0)
      {
            for(i = 0; i < cno; i++)
            {
                  if ((PID = fork()) == 0)
                  {
                        printf("Creating consumer %d\n", i + 1);
                        consumer(i + 1);
                        exit(0);
                  }
            }
      }

            printf("DONE\n");
}

void producer(int thread_num)
{
      int temp;
      printf("PRODUCER #%d\n", thread_num);
      while (1)
      {
            sem_wait(&empty);
            sem_wait(&mut);
            if (Buffer[0] < maximum)
            {
                  if (Buffer[0] < bufLength)
                  {
                        Buffer[Buffer[3]] = Buffer[0] + 1;
                        Buffer[Buffer[4]] = (int)thread_num;
                        Buffer[1]++;
                        Buffer[0]++;
                  }
                  else if( (Buffer[0] % bufLength) == 0)
                  {
                        Buffer[1] = 0;
                        Buffer[Buffer[3]] = Buffer[0] + 1;
                        Buffer[Buffer[4]] = (int)thread_num;
                        Buffer[1]++;
                  }
                  else
                  {
                        Buffer[Buffer[3]] = Buffer[0] + 1;
                        Buffer[Buffer[4]] = (int)thread_num;
                        Buffer[1]++;;
                  }
            }
            else
            {
                  sem_post(&mut);
                  sem_post(&full);
                  exit(0);
            }
            sem_post(&mut);
            sem_post(&full);
            sleep(1);
      }
}

void consumer(int thread_num)
{
      printf("CONSUMER #%d\n", thread_num);
      while (1)
      {
            sem_wait(&full);
            sem_wait(&mut);
            if (Buffer[2] < Buffer[0])
            {
                  if (Buffer[2] < bufLength)
                  {
                        printf("%d %d %d %d\n", Buffer[Buffer[2] + 3], Buffer[Buffer[2] + 4], (int)thread_num, Buffer[2]);
                        Buffer[2]++;
                  }
                  else if ( (Buffer[2] % bufLength) == 0)
                  {
                        printf("%d %d %d %d\n", Buffer[3], Buffer[4], (int)thread_num, Buffer[2] % bufLength);
                        Buffer[2]++;
                  }
                  else
                  {
                        printf("%d %d %d %d\n", Buffer[Buffer[2] % bufLength + 3] , Buffer[Buffer[2] % bufLength + 4], (int)thread_num, Buffer[2] % bufLength);
                        Buffer[2]++;
                  }
            }
            else
            {
                  sem_post(&mut);
                  sem_post(&empty);
                  pthread_exit(NULL);
            }
            sem_post(&mut);
            sem_post(&empty);
            exit(0);
      }
}


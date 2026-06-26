#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

int counter = 0;

/* Binary Semaphore */
sem_t semaphore;

/* Function executed by each thread */
void *incrementCounter(void *arg)
{
    long id = (long)arg;

    /* Wait (Lock) */
    sem_wait(&semaphore);

    printf("Thread %ld entered critical section.\n", id);

    counter++;

    printf("Thread %ld incremented counter to %d\n", id, counter);

    printf("Thread %ld leaving critical section.\n\n", id);

    /* Signal (Unlock) */
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];

    printf("======= Semaphore Demonstration =======\n\n");

    /* Initialize semaphore to 1 (Binary Semaphore) */
    sem_init(&semaphore, 0, 1);

    /* Create Threads */
    for(long i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, incrementCounter, (void *)i);
    }

    /* Wait for all threads */
    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("--------------------------------------\n");
    printf("Final Counter Value = %d\n", counter);
    printf("--------------------------------------\n");

    sem_destroy(&semaphore);

    return 0;
}
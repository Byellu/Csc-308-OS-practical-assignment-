#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int counter = 0;

/* Create a mutex */
pthread_mutex_t mutex;

/* Function executed by each thread */
void *incrementCounter(void *arg)
{
    long id = (long)arg;

    /* Lock the critical section */
    pthread_mutex_lock(&mutex);

    printf("Thread %ld entered critical section.\n", id);

    counter++;

    printf("Thread %ld incremented counter to %d\n", id, counter);

    printf("Thread %ld leaving critical section.\n\n", id);

    /* Unlock */
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];

    /* Initialize mutex */
    pthread_mutex_init(&mutex, NULL);

    printf("========== Mutex Lock Demonstration ==========\n\n");

    for(long i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, incrementCounter, (void *)i);
    }

    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("--------------------------------------------\n");
    printf("Final Counter Value = %d\n", counter);
    printf("--------------------------------------------\n");

    /* Destroy mutex */
    pthread_mutex_destroy(&mutex);

    return 0;
}
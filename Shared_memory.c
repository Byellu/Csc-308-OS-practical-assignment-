#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
    key_t key = 1234;

    /* Create shared memory */
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if (shmid == -1)
    {
        printf("Failed to create shared memory.\n");
        return 1;
    }

    /* Attach shared memory */
    char *sharedMemory = (char *)shmat(shmid, NULL, 0);

    if (sharedMemory == (char *)-1)
    {
        printf("Failed to attach shared memory.\n");
        return 1;
    }

    /* Write data */
    strcpy(sharedMemory, "Hello! This message is stored in shared memory.");

    printf("Message Written:\n%s\n\n", sharedMemory);

    /* Read data */
    printf("Message Read:\n%s\n\n", sharedMemory);

    /* Detach shared memory */
    shmdt(sharedMemory);

    /* Remove shared memory */
    shmctl(shmid, IPC_RMID, NULL);

    printf("Shared memory released successfully.\n");

    return 0;
}
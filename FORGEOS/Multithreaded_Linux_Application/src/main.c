#include <stdio.h>
#include <pthread.h>

void *worker(void *arg)
{
    printf("Worker thread is running.\n");
    return NULL;
}

int main()
{
    pthread_t thread;

    printf("Main thread started.\n");

    pthread_create(&thread, NULL, worker, NULL);

    pthread_join(thread, NULL);

    printf("Main thread finished.\n");

    return 0;
}

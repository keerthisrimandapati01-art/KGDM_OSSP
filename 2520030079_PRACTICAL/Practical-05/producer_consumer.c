#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define NUM_MESSAGES 10000

int main()
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // Parent - Producer
        close(fd[0]);

        char message[100];
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 1; i <= NUM_MESSAGES; i++)
        {
            snprintf(message, sizeof(message),
                     "Message %d", i);

            write(fd[1], message, strlen(message) + 1);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        close(fd[1]);

        wait(NULL);

        double time_taken =
            (end.tv_sec - start.tv_sec) * 1e6 +
            (end.tv_nsec - start.tv_nsec) / 1000.0;

        printf("\nProducer: Sent %d messages\n", NUM_MESSAGES);
        printf("Communication time: %.2f microseconds\n",
               time_taken);

        if (time_taken > 0)
        {
            printf("Communication rate: %.2f messages/second\n",
                   (NUM_MESSAGES * 1000000.0) / time_taken);
        }
    }
    else
    {
        // Child - Consumer
        close(fd[1]);

        char message[100];

        while (read(fd[0], message, sizeof(message)) > 0)
        {
            // Consume the message
        }

        close(fd[0]);

        printf("Consumer: All messages received successfully\n");
    }

    return 0;
}

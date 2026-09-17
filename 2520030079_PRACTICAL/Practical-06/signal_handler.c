#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int signal_number)
{
    if (signal_number == SIGINT)
    {
        printf("\nSIGINT received: Interrupt signal handled.\n");
    }
    else if (signal_number == SIGTERM)
    {
        printf("\nSIGTERM received: Termination signal handled.\n");
    }
    else if (signal_number == SIGUSR1)
    {
        printf("\nSIGUSR1 received: User-defined signal handled.\n");
    }
}

int main()
{
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGUSR1, handle_signal);

    printf("Process ID: %d\n", getpid());
    printf("Signal handler program started...\n");
    printf("Send SIGINT, SIGTERM, or SIGUSR1 to this process.\n");

    while (1)
    {
        printf("Waiting for signals...\n");
        sleep(3);
    }

    return 0;
}

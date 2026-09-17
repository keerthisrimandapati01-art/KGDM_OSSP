#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define CLIENT_FIFO "/tmp/client_fifo"

int main()
{
    char message[100];
    char response[150];

    // Create server FIFO
    mkfifo(SERVER_FIFO, 0666);

    printf("Server started...\n");
    printf("Waiting for client messages...\n");

    while (1)
    {
        int fd = open(SERVER_FIFO, O_RDONLY);

        if (fd == -1)
        {
            perror("open");
            return 1;
        }

        while (read(fd, message, sizeof(message)) > 0)
        {
            printf("Client: %s\n", message);

            snprintf(response, sizeof(response),
                     "Server processed: %s", message);

            int client_fd = open(CLIENT_FIFO, O_WRONLY);

            if (client_fd == -1)
            {
                perror("client FIFO");
                close(fd);
                return 1;
            }

            write(client_fd, response, strlen(response) + 1);

            close(client_fd);
        }

        close(fd);
    }

    unlink(SERVER_FIFO);

    return 0;
}

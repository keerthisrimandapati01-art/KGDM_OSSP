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

    // Create client FIFO
    mkfifo(CLIENT_FIFO, 0666);

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    // Send message to server
    int server_fd = open(SERVER_FIFO, O_WRONLY);

    if (server_fd == -1)
    {
        perror("server FIFO");
        return 1;
    }

    write(server_fd, message, strlen(message) + 1);

    close(server_fd);

    // Receive response from server
    int client_fd = open(CLIENT_FIFO, O_RDONLY);

    if (client_fd == -1)
    {
        perror("client FIFO");
        return 1;
    }

    read(client_fd, response, sizeof(response));

    printf("Server response: %s\n", response);

    close(client_fd);

    return 0;
}

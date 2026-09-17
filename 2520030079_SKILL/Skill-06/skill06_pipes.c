#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 20

void parse_command(char *command, char *args[])
{
    int i = 0;

    char *token = strtok(command, " ");

    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
}

int main()
{
    char input[500];
    char *commands[MAX_COMMANDS];
    int pipe_count;
    int command_count;

    printf("Enter pipeline: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    /* Split input using | */
    char *token = strtok(input, "|");
    command_count = 0;

    while (token != NULL && command_count < MAX_COMMANDS)
    {
        commands[command_count++] = token;
        token = strtok(NULL, "|");
    }

    if (command_count < 2)
    {
        printf("At least two commands are required.\n");
        return 1;
    }

    pipe_count = command_count - 1;

    int pipes[MAX_COMMANDS - 1][2];
    pid_t pids[MAX_COMMANDS];

    /* Create required pipes */
    for (int i = 0; i < pipe_count; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return 1;
        }
    }

    /* Create processes */
    for (int i = 0; i < command_count; i++)
    {
        pids[i] = fork();

        if (pids[i] == -1)
        {
            perror("fork");
            return 1;
        }

        if (pids[i] == 0)
        {
            char *args[MAX_ARGS];

            /* Input redirection */
            if (i > 0)
            {
                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
                {
                    perror("dup2 input");
                    exit(1);
                }
            }

            /* Output redirection */
            if (i < command_count - 1)
            {
                if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 output");
                    exit(1);
                }
            }

            /* Close all pipe descriptors in child */
            for (int j = 0; j < pipe_count; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            /* Remove leading spaces */
            while (*commands[i] == ' ')
                commands[i]++;

            parse_command(commands[i], args);

            execvp(args[0], args);

            perror("execvp");
            exit(1);
        }
    }

    /* Parent closes all pipe descriptors */
    for (int i = 0; i < pipe_count; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    /* Wait for all children */
    for (int i = 0; i < command_count; i++)
    {
        waitpid(pids[i], NULL, 0);
    }

    printf("\nPipeline execution completed successfully.\n");

    return 0;
}

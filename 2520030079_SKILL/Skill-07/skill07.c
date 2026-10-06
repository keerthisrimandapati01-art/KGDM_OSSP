#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void input_redirection(const char *filename)
{
    int saved_stdin = dup(STDIN_FILENO);

    int fd = open(filename, O_RDONLY);

    if (fd < 0)
    {
        perror("Error opening input file");
        return;
    }

    dup2(fd, STDIN_FILENO);
    close(fd);

    printf("\n--- Input Redirection (<) ---\n");
    printf("Reading from file: %s\n", filename);
    printf("File contents:\n");

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), stdin))
    {
        printf("%s", buffer);
    }

    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);

    printf("\nInput stream restored.\n");
}

void output_redirection(const char *filename)
{
    int saved_stdout = dup(STDOUT_FILENO);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("Error opening output file");
        return;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);

    printf("Output redirection successful.\n");
    printf("This data was written using stdout redirection.\n");

    fflush(stdout);

    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    printf("Output stream restored.\n");
}

void append_redirection(const char *filename)
{
    int saved_stdout = dup(STDOUT_FILENO);

    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0)
    {
        perror("Error opening append file");
        return;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);

    printf("New data appended successfully.\n");

    fflush(stdout);

    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    printf("Output stream restored after append.\n");
}

void error_redirection(const char *filename)
{
    int saved_stderr = dup(STDERR_FILENO);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("Error opening error file");
        return;
    }

    dup2(fd, STDERR_FILENO);
    close(fd);

    fprintf(stderr, "This is a sample error message.\n");
    fprintf(stderr, "Error output was redirected to a file.\n");

    fflush(stderr);

    dup2(saved_stderr, STDERR_FILENO);
    close(saved_stderr);

    printf("Error stream restored.\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage:\n");
        printf("  %s <  input.txt\n", argv[0]);
        printf("  %s >  output.txt\n", argv[0]);
        printf("  %s >> append.txt\n", argv[0]);
        printf("  %s 2> error.txt\n", argv[0]);

        return 1;
    }

    if (strcmp(argv[1], "<") == 0)
    {
        input_redirection(argv[2]);
    }
    else if (strcmp(argv[1], ">") == 0)
    {
        output_redirection(argv[2]);
    }
    else if (strcmp(argv[1], ">>") == 0)
    {
        append_redirection(argv[2]);
    }
    else if (strcmp(argv[1], "2>") == 0)
    {
        error_redirection(argv[2]);
    }
    else
    {
        printf("Invalid redirection operator: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t p1, p2;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    // First child executes ls -l
    p1 = fork();

    if (p1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (p1 == 0)
    {
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        close(fd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);

        perror("execlp ls");
        exit(1);
    }

    // Second child executes grep ".c"
    p2 = fork();

    if (p2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (p2 == 0)
    {
        close(fd[1]);

        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);

        execlp("grep", "grep", ".c", (char *)NULL);

        perror("execlp grep");
        exit(1);
    }

    // Parent closes pipe
    close(fd[0]);
    close(fd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}

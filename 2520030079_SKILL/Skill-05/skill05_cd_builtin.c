#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define INPUT_SIZE 100

void builtin_cd(char *path)
{
    char old_dir[PATH_MAX];
    char new_dir[PATH_MAX];

    if (getcwd(old_dir, sizeof(old_dir)) == NULL)
    {
        perror("getcwd");
        return;
    }

    if (path == NULL)
    {
        path = getenv("HOME");
    }
    else if (strcmp(path, "-") == 0)
    {
        path = getenv("OLDPWD");

        if (path == NULL)
        {
            printf("OLDPWD not set\n");
            return;
        }
    }

    if (chdir(path) == -1)
    {
        perror("cd");
        return;
    }

    if (getcwd(new_dir, sizeof(new_dir)) == NULL)
    {
        perror("getcwd");
        return;
    }

    setenv("OLDPWD", old_dir, 1);
    setenv("PWD", new_dir, 1);

    printf("Changed directory to: %s\n", new_dir);
}

void builtin_pwd()
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("pwd");
        return;
    }

    printf("%s\n", cwd);
}

void builtin_help()
{
    printf("Built-in commands:\n");
    printf("  cd <directory>  - Change directory\n");
    printf("  cd -            - Go to previous directory\n");
    printf("  pwd             - Display current directory\n");
    printf("  help            - Display built-in commands\n");
    printf("  exit            - Exit shell\n");
}

int main()
{
  char input[INPUT_SIZE];

    while (1)
    {
        printf("skill05> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        char *command = strtok(input, " ");
        char *argument = strtok(NULL, " ");

        if (strcmp(command, "cd") == 0)
        {
            builtin_cd(argument);
        }
        else if (strcmp(command, "pwd") == 0)
        {
            builtin_pwd();
        }
        else if (strcmp(command, "help") == 0)
        {
            builtin_help();
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }
        else
        {
            printf("Invalid command: %s\n", command);
        }
    }

    return 0;
}

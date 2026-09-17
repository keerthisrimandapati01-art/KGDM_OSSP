#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#define INPUT_SIZE 200

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

int valid_variable_name(char *name)
{
    if (name == NULL || *name == '\0')
        return 0;

    if (!(isalpha((unsigned char)*name) || *name == '_'))
        return 0;

    for (int i = 1; name[i] != '\0'; i++)
    {
        if (!(isalnum((unsigned char)name[i]) || name[i] == '_'))
            return 0;
    }

    return 1;
}

void builtin_export(char *argument)
{
    if (argument == NULL)
    {
        printf("Usage: export NAME=VALUE\n");
        return;
    }

    char *equal = strchr(argument, '=');

    if (equal == NULL)
    {
        printf("Invalid export syntax. Use NAME=VALUE\n");
        return;
    }

    *equal = '\0';

    char *name = argument;
    char *value = equal + 1;

    if (!valid_variable_name(name))
    {
        printf("Invalid variable name: %s\n", name);
        return;
    }

    if (setenv(name, value, 1) == -1)
    {
        perror("export");
        return;
    }

    printf("Exported %s=%s\n", name, value);
}

void builtin_printenv(char *name)
{
    if (name == NULL)
    {
        printf("Usage: printenv NAME\n");
        return;
    }

    char *value = getenv(name);

    if (value == NULL)
    {
        printf("%s is not set\n", name);
    }
    else
    {
        printf("%s=%s\n", name, value);
    }
}

int main()
{
    char input[INPUT_SIZE];

    printf("Skill-05 Environment Shell\n");

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
        char *argument = strtok(NULL, "");

        if (strcmp(command, "pwd") == 0)
        {
            builtin_pwd();
        }
        else if (strcmp(command, "export") == 0)
        {
            builtin_export(argument);
        }
        else if (strcmp(command, "printenv") == 0)
        {
            builtin_printenv(argument);
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Saving state and exiting...\n");
            break;
        }
        else
        {
            printf("Invalid command: %s\n", command);
        }
    }

    return 0;
}

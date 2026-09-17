#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5
#define MAX_COMMAND 100
#define MAX_PIPELINE 10

char history[HISTORY_SIZE][MAX_COMMAND];
int history_count = 0;

void add_history(char *command)
{
    if (history_count < HISTORY_SIZE)
    {
        strcpy(history[history_count], command);
        history_count++;
    }
    else
    {
        for (int i = 1; i < HISTORY_SIZE; i++)
        {
            strcpy(history[i - 1], history[i]);
        }

        strcpy(history[HISTORY_SIZE - 1], command);
    }
}

void show_history()
{
    printf("\nCommand History:\n");

    if (history_count == 0)
    {
        printf("History is empty.\n");
        return;
    }

    for (int i = 0; i < history_count; i++)
    {
        printf("%d  %s\n", i + 1, history[i]);
    }
}

void validate_history()
{
    if (history_count < 0 || history_count > HISTORY_SIZE)
    {
        printf("History consistency check: FAILED\n");
        return;
    }

    for (int i = 0; i < history_count; i++)
    {
        if (strlen(history[i]) == 0)
        {
            printf("History consistency check: FAILED\n");
            return;
        }
    }

    printf("History consistency check: PASSED\n");
}

void create_pipeline()
{
    int count;
    char commands[MAX_PIPELINE][MAX_COMMAND];

    printf("\nEnter number of commands in pipeline: ");
    scanf("%d", &count);
    getchar();

    if (count < 2 || count > MAX_PIPELINE)
    {
        printf("Invalid pipeline size.\n");
        return;
    }

    printf("Enter pipeline commands:\n");

    for (int i = 0; i < count; i++)
    {
        printf("Command %d: ", i + 1);
        fgets(commands[i], MAX_COMMAND, stdin);

        commands[i][strcspn(commands[i], "\n")] = '\0';

        if (strlen(commands[i]) == 0)
        {
            printf("Invalid empty command.\n");
            return;
        }
    }

    printf("\nPipeline Layout:\n");

    for (int i = 0; i < count; i++)
    {
        printf("[%s]", commands[i]);

        if (i < count - 1)
            printf(" -> ");
    }

    printf("\nPipeline validation: PASSED\n");
}

int main()
{
    char command[MAX_COMMAND];
    int choice;

    while (1)
    {
        printf("\n===== Skill-06 History & Pipeline =====\n");
        printf("1. Add command to history\n");
        printf("2. Display history\n");
        printf("3. Validate history\n");
        printf("4. Create pipeline structure\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                printf("Enter command: ");
                fgets(command, MAX_COMMAND, stdin);

                command[strcspn(command, "\n")] = '\0';

                if (strlen(command) == 0)
                {
                    printf("Empty command not allowed.\n");
                }
                else
                {
                    add_history(command);
                    printf("Command stored successfully.\n");
                }
                break;

            case 2:
                show_history();
                break;

            case 3:
                validate_history();
                break;

            case 4:
                create_pipeline();
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

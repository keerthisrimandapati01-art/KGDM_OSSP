#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 100;
static int static_var = 200;

void code_function()
{
    printf("Code segment address   : %p\n", (void *)code_function);
}

int main()
{
    int stack_var = 300;
    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL)
    {
        perror("malloc");
        return 1;
    }

    *heap_var = 400;

    printf("=== Linux Process Memory Layout ===\n\n");

    code_function();

    printf("Global variable address: %p\n", (void *)&global_var);
    printf("Static variable address: %p\n", (void *)&static_var);
    printf("Heap variable address  : %p\n", (void *)heap_var);
    printf("Stack variable address : %p\n", (void *)&stack_var);

    printf("\nProcess ID (PID)       : %d\n", getpid());

    printf("\nProcess is running...\n");
    printf("Press Ctrl+C to terminate.\n");

    while (1)
    {
        sleep(1);
    }

    free(heap_var);

    return 0;
}

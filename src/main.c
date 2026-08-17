#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"

int main()
{
    char input[1024];
    char *args[64];

    printf("=====================================\n");
    printf(" Welcome to ShellForge Version 2.0\n");
    printf("=====================================\n");

    while (1)
    {
        printf("myshell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        /* Exit command */
        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting ShellForge...\n");
            break;
        }

        /* Change directory command */
        if (strncmp(input, "cd", 2) == 0 &&
            (input[2] == '\0' || input[2] == ' '))
        {
            char *path = input + 2;

            while (*path == ' ')
                path++;

            /* If no path is given, go to HOME directory */
            if (*path == '\0')
                path = getenv("HOME");

            if (chdir(path) != 0)
                perror("cd");

            continue;
        }

        /* Parse the command */
        int argc = parse_command(input, args);

        if (argc == 0)
            continue;

        /* Create child process */
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            continue;
        }

        /* Child process */
        if (pid == 0)
        {
            execvp(args[0], args);

            /* execvp only returns if there is an error */
            perror("execvp");
            return 1;
        }

        /* Parent process waits for child */
        waitpid(pid, NULL, 0);
    }

    return 0;
}

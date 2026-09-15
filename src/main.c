#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"
int main()
{
    char *line;
    char **tokens;

    printf("%s Version %s\n", SHELL_NAME, VERSION);

    while (1)
    {
        printf("myshell> ");

        line = read_line();

        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        tokens = parse_line(line);

        if (tokens[0] != NULL)
        {
            if (execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }
        }

        free_tokens(tokens);
        free(line);
    }

    printf("Goodbye!\n");

    return 0;
}

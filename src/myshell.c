/*
Student Name: Amelia Grigoriev
Student Number: 19348241
In submitting this project, I declare that the project material, which I now submit, is my own work. Any assistance received by way of borrowing from the work of others has been cited and acknowledged within the work. I make this declaration in the knowledge that a breach of the rules pertaining to project submission may carry serious consequences.
*/

//includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "commands.h"

//defines
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "==> " ;                   // shell prompt

/* keep reading input until "quit" command or eof of redirected input */

    while (!feof(stdin)) {

        /* get command line from input */

        fputs (prompt, stdout);                // write prompt
        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */

            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenize input
            while ((*arg++ = strtok(NULL,SEPARATORS)));
            // last entry will be NULL if (args[0]) {                     // if there's anything there

            if(args[0] == NULL)
            {
                continue;
            }
            /* check for internal/external command */
            else if (!strcmp(args[0],"clr")) { // "clear" command
                system("clear");
                continue;
            }

            else if (!strcmp(args[0],"quit"))   // "quit" command
                break;                          // break out of 'while' loop

            else if (!strcmp(args[0],"cd")) // "cd" command
            {
                cd(args); // call cd function
            }

            else if (!strcmp(args[0],"dir")) // "dir" command
            {
                dir(); // call dir function
            }

            else if (!strcmp(args[0],"environ")) // "environ" command
            {
                shell_environment(); // call shell_environment function
                environment(args); // call environment function
            }

            else if (!strcmp(args[0],"echo")) // "echo" command
            {
                echo(args); // call echo function
            }

            else if (!strcmp(args[0],"help")) // "help" command
            {
                system("more ../manual/readme.md"); // manual
                continue;
            }
            
            else if (!strcmp(args[0],"pause")) // "pause" command
            {
                pause_shell(); // call pause_shell function
            }

            else if (!strcmp(args[0],"pwd")) // "pwd" command
            {
                pwd(args); // call pwd function
            }

            else
            {
                ext_commands(args); // call ext_commands function
            } 
        }
    }
return 0;
}

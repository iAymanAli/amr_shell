#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "globals.h"
#include "tokenizers.h"
#include "cmd_handlers.h"
#include "autocompletion_handlers.h"


const char *builtins[] = {"exit", "echo", "type", "pwd", "cd", "complete", NULL};

char *commands_arr[4 * KB];  // Array that contains built-in commands and commands from PATH. Necessary for autocompletion.

comp comp_arr[KB];  // Array of commands registered with the complete command.

// Array of words for the readline autocomplete feature specific for completion registered with the complete command.
char *comp_words[KB] = {NULL};

int argsv_index;  // Points to the start of a command and its arguments. Necessary for piping.
int is_piping;  // Flags whether there is a piping operation or not.
int in_fd = 0;  // Stores the file descriptor from which the current program will take input.


int main(void) {
    get_commands();  // Populates commands_arr.

    rl_attempted_completion_function = cmd_completion;  // For custom commands autocompletion.

    using_history();  // Enable history to retrieve past commands with the UP and DOWN arrows.

    rl_variable_bind("bell-style", "audible");  // Enable bell sound for the shell.

    while (true) {
        char *user_input = readline("$ ");
        if (user_input == NULL) {
            // There is a problem with the user input so end program.
            break;
        }
        else if (user_input[0] == '\0') {
            // User input is empty so show input field immediately again.
            continue;
        }
        else {
            // User entered something, save it into history.
            add_history(user_input);
        }

        char *argsv[CUSTOM_MAX_ARGS];  // Array that stores parsed user input.
        int argc = tokenize(user_input, argsv);  // Parse user input with consideration to single quotes, double quotes, and backslash.

        argsv_index = 0;
        is_piping = 0;

        if (strcmp(argsv[0], "exit") == 0) {
            // Readline function dynamically allocates memory for user input, so it must be freed manually.
            free(user_input);
            break;
        }
        else if (strcmp(argsv[0], "cd") == 0) {
            handle_cd_cmd(argsv, argc);
            continue;
        }
        else if (strcmp(argsv[0], "complete") == 0) {
            handle_complete_cmd(argsv, argc);
            continue;
        }

        while (argsv[argsv_index]) {
            char *programv[CUSTOM_MAX_ARGS];  // Stores a single program and its arguments.
            // Get the name of the program and its arguments, store them in programv, and check for piping.
            int prog_argc = parse_program(argsv, programv);

            int pfds[2];
            if (is_piping == 2) pipe(pfds);  // Make a pipe if user used piping feature.

            pid_t processID = fork();
            if (processID == 0) {  //* Child Process
                if (in_fd != 0) {
                    // If in_fd is not zero, that means we are going to take input from a pipe.
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                if (is_piping == 2) {
                    // If is_piping is two, that means we are going to write into a pipe.
                    fflush(stdout);

                    dup2(pfds[1], STDOUT_FILENO);
                    close(pfds[0]);
                    close(pfds[1]);
                }

                if (strcmp(programv[0], "pwd") == 0) {
                    handle_pwd_cmd(programv, prog_argc);
                    exit(EXIT_SUCCESS);
                }
                else if (strcmp(programv[0], "echo") == 0) {
                    handle_echo_cmd(programv, prog_argc);
                    exit(EXIT_SUCCESS);
                }
                else if (strcmp(programv[0], "type") == 0) {
                    handle_type_cmd(programv, prog_argc);
                    exit(EXIT_SUCCESS);
                }
                else {
                    run_executable(programv, prog_argc);
                }
            }
            else if (processID > 0) {  //* Parent Process
                // If in_fd is not zero, that means input is from a pipe, so it needs to be manually closed.
                if (in_fd != 0) close(in_fd);

                if (is_piping == 2) {
                    close(pfds[1]);

                    /*
                        Store reading part of pipe into in_fd in order for the next program to read from it.
                        It is necessary for piping with more than 2 programs.
                    */
                    in_fd = pfds[0];  
                }
                else {
                    // If there is no piping, set program input to use stdin.
                    in_fd = 0;
                }

                if(is_piping) is_piping--;
            }
            else {
                perror("main(): fork(): failed to fork a child process");
            }
        }

        while(( wait(NULL) != -1 ));

        // Readline function dynamically allocates memory for user input, so it must be freed manually.
        free(user_input);
    }

    // Elements inside commands_arr and comp_words are dynamically allocated, so they need to be freed manually.
    free_commands_arr();
    free_comp_words();

    return 0;
}

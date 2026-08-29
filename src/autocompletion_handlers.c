#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <readline/readline.h>

#include "globals.h"
#include "utils.h"

void handle_complete_cmd (char *argsv[], int argc) {
    //! This function accesses the global array "comp_arr".

    // Hashes the name of the command passed to complete and assigns a proper place for it in comp_arr.
    unsigned int hash_code = hash(argsv[argc - 1]);

    if (strcmp(argsv[1], "-C") == 0) { //* Adds a command to the hash table
        comp_arr[hash_code].populated = true;

        strcpy(comp_arr[hash_code].flag, argsv[1]);
        strcpy(comp_arr[hash_code].arg, argsv[2]);
        strcpy(comp_arr[hash_code].cmd, argsv[3]);

        char *arg_cmd_name = strrchr(argsv[2], '/') + 1;
        strcpy(comp_arr[hash_code].arg_cmd, arg_cmd_name);
    }
    else if (strcmp(argsv[1], "-p") == 0) {  //* Prints info about an added command
        comp comp_cmd = comp_arr[hash_code];

        if (comp_cmd.populated) {
            printf("complete %s '%s' %s\n", comp_cmd.flag, comp_cmd.arg, comp_cmd.cmd);
            return;
        }

        printf("complete: %s: no completion specification\n", argsv[2]);
    }
    else if (strcmp(argsv[1], "-r") == 0) {  //* Removes a command from the hash table
        comp_arr[hash_code].populated = false;
        strcpy(comp_arr[hash_code].flag , "\0");
        strcpy(comp_arr[hash_code].arg , "\0");
        strcpy(comp_arr[hash_code].cmd , "\0");
        strcpy(comp_arr[hash_code].arg_cmd , "\0");
    }
}

void get_commands(void) {
    //! This function accesses the global arrays "builtins" and "commands_arr".

    int cmd_count = 0;

    // This loop adds builtin commands into commands_arr.
    for (int i = 0; builtins[i] != NULL; i++) {
        commands_arr[cmd_count] = strdup(builtins[i]);
        if (commands_arr[cmd_count] == NULL) {
            perror("get_commands(): strdup() error: failed to copy builtin command");
            exit(111);
        }

        cmd_count++;
    }

    // Get the PATH environment variable.
    char *path = getenv("PATH");
    if (path == NULL) {
        perror("get_commands(): getenv() error: failed to get the PATH environment variable");
        exit(EXIT_FAILURE);
    }

    /*
        Make a copy of the PATH environment variable in order to use it with strtok()
        since strtok() function modifies the string it is tokenizing.
    */
    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("get_commands(): strdup() error: failed to copy the path string");
        exit(EXIT_FAILURE);
    }

    char *path_dir = strtok(path_copy, PATH_DELIMITER);  // Initiate parsing path_copy and get the first path.

    while (path_dir) {
        // Open the directory stored in path_dir.
        DIR *dir_ptr = opendir(path_dir);
        if (dir_ptr == NULL) {
            perror("get_commands(): opendir() error: failed to open directory");
            free(path_copy);
            exit(111);
        }

        struct dirent *read_dir;

        // This loop reads the content of the opened directory and adds the names of the exe files as commands to commands_arr.
        while ( (read_dir = readdir(dir_ptr)) != NULL) {
            if (read_dir->d_type == DT_DIR) {
                /* This conditional prevent adding a directory into commands_arr */
                continue;
            }
            else if (strstr(read_dir->d_name, "gnu") || strstr(read_dir->d_name, "lib") || strstr(read_dir->d_name, "linux")) {
                /* This conditional skips irrelevant executable files */
                continue;
            }
            

            commands_arr[cmd_count] = strdup(read_dir->d_name);
            if (commands_arr[cmd_count] == NULL) {
                perror("get_commands(): strdup() error: failed to copy program name");
                free(path_dir);
                exit(111);
            }

            cmd_count++;
        }

        // Close the opened directory.
        if (closedir(dir_ptr) == -1) {
            perror("get_commands(): closedir() error: failed to close directory");
            free(path_dir);
            exit(111);
        }

        // Move to next directory in PATH.
        path_dir = strtok(NULL, PATH_DELIMITER);
    }

    // Add NULL after the last commands as a standard practice.
    commands_arr[cmd_count] = NULL;

    free(path_copy);
}

void free_commands_arr(void) {
    //! This function accesses the global array "commands_arr".

    // Go through commands_arr and free all of its elements.
    for (int i = 0; commands_arr[i] != NULL; i++) {
        free(commands_arr[i]);
        commands_arr[i] = NULL;
    }
}

void free_comp_words(void) {
    //! This function accesses the global array "comp_words".

    // Go through comp_words and free all of its elements.
    for (int i = 0; comp_words[i] != NULL; i++) {
        free(comp_words[i]);
        comp_words[i] = NULL;
    }
}

char *cmd_generator(const char* text, int state) {
    //! This function accesses the global array "commands_arr".

    /*
        list_index: keeps track of where we left off scanning commands_arr between iterations.
        len: stores the length of "text", so we don't call strlen() on every iteration. 
    */
    static int list_index, len;
    char *cmd;

    if (!state) {
        /* Initiates list_index and len in the first iteration since "state" is zero */
        list_index = 0;
        len = strlen(text);
    }

    // This loop goes through commands_arr and looks for matching commands.
    while (( cmd = commands_arr[list_index++] )) {
        if (strncmp(cmd, text, len) == 0) {
            return strdup(cmd);
        }
    }

    return NULL;
}

char *comp_generator(const char* text, int state) {
    //! This function accesses the global array "comp_words".

    /*
        list_index: keeps track of where we left off scanning comp_words between iterations.
        len: stores the length of "text", so we don't call strlen() on every iteration. 
    */
    static int list_index, len;
    char *completion;

    if (!state) {
        /* Initiates list_index and len in the first iteration since "state" is zero */
        list_index = 0;
        len = strlen(text);
    }

    // This loop goes through comp_words and looks for matching commands.
    while (( completion = comp_words[list_index++] )) {
        if (strncmp(completion, text, len) == 0) {
            return strdup(completion);
        }
    }

    return NULL;
}

char **cmd_completion (const char* text, int start, int end) {
    //! This function accesses the global array "comp_arr".

    if (start == 0) {  //* Autocompletion for command names
        rl_attempted_completion_over = 1;  // Prevents completion from returning to its default behavior.
        return rl_completion_matches(text, cmd_generator); // returns the matching command for <TAB> completion.
    }

    char *text_cpy = strdup(rl_line_buffer);  // Copy what the user has entered so far.
    char *cmd = strtok(text_cpy, " ");  // Get the typed command.
    char *first_arg = strtok(NULL, " ");  // Get the first argument passed.
    char *second_arg = strtok(NULL, " ");  // Get the second argument passed.
    unsigned index = hash(cmd);  // Get the hash table index in which the command is supposed to be.

    if (comp_arr[index].populated) {
        /* This conditional is true only if the completion was added via the complete built-in command */

        free_comp_words();  // Delete all the existing elements inside comp_words before populating it with new ones.

        int fd[2]; pipe(fd);  // Initiate a pipe.

        fflush(stdout);

        pid_t processID = fork();
        if (processID == 0) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);

            char comp_point[128];
            sprintf(comp_point, "%i", end);

            if (setenv("COMP_LINE", rl_line_buffer, 1) == -1) {
                perror("cmd_completion(): setenv() error: failed to set COMP_LINE variable");
                exit(125);
            }

            if (setenv("COMP_POINT", comp_point, 1) == -1) {
                perror("cmd_completion(): setenv() error: failed to set COMP_POINT variable");
                exit(125);
            }

            (!second_arg) ? execl(comp_arr[index].arg, comp_arr[index].arg_cmd, cmd, text, cmd, NULL)
                          : execl(comp_arr[index].arg, comp_arr[index].arg_cmd, cmd, text, first_arg, NULL);

            //! This part is only reached if execl failed.
            perror("cmd_completion(): execl() error: failed to execute comp_arr[index].arg");
            exit(125);
        }
        else if (processID > 0) {
            fflush(stdout);

            close(fd[1]);

            // Open the reading part of the pipe as a file.
            FILE *stream = fdopen(fd[0], "r");

            char line_buffer[KB];
            int comp_index = 0;

            // Read every line in the reading part of the pipe.
            while (fgets(line_buffer, sizeof(line_buffer), stream) != NULL) {
                line_buffer[strcspn(line_buffer, "\n")] = '\0';

                // Tokenize every word in the current line and add it as a separate autocompletion word.
                char *word = strtok(line_buffer, " ");
                while (word) {
                    comp_words[comp_index++] = strdup(word);
                    word = strtok(NULL, " ");
                }
            }

            // Add NULL after the last argument as a standard practice.
            comp_words[comp_index] = NULL;

            fclose(stream);
            close(fd[0]);
        }
        else {
            perror("cmd_completion(): fork() error: failed to fork");
            return NULL;
        }

        free(text_cpy);

        rl_attempted_completion_over = 1;  // Prevents completion from returning to its default behavior.
        return rl_completion_matches(text, comp_generator); // returns the matching command for <TAB> completion.
    }

    free(text_cpy);

    /*
        Go back to readline default autocompletion behavior only if the argument to be completed
        is the second or subsequent argument. 
    */
    return NULL;
}

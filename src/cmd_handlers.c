#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/limits.h>

#include "globals.h"
#include "utils.h"

void handle_cd_cmd (char *argsv[], int argc) {
    if (argc > 2) {
        perror("cd: too many arguments");
        return;
    }

    int cd_code;  // Stores the return value of chdir() function.

    // Get the HOME environment variable.
    char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        perror("handle_cd_cmd(): getenv() error: failed to get the HOME environment variable");
        return;
    }

    if (argc == 1) {
        cd_code = chdir(home_dir);
    }
    else if (argsv[1][0] == '~') {
        /* Handle absolute paths that contain tilde "~" */

        char *tilde = strtok(argsv[1], PATH_SEPARATOR);
        char *remaining_path = strtok(NULL, "");

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", home_dir, remaining_path);

        cd_code = (remaining_path) ? chdir(full_path) : chdir(home_dir);

        if (cd_code != 0) {
            // Print an error message if directory did not exist.
            fprintf(stderr, "cd: %s: No such file or directory\n", full_path);
            return;
        }

        return;
    }
    else {
        cd_code = chdir(argsv[1]);
    }

    if (cd_code != 0) {
        // Print an error message if directory did not exist.
        fprintf(stderr, "cd: %s: No such file or directory\n", argsv[1]);
    }
}

void handle_pwd_cmd(char *argsv[], int argc) {
    // Check if any redirecting was specified in the arguments.
    int mode_arr[2] = {0, 0};
    int file_name_index = is_redirecting(argsv, argc, mode_arr);
    int oflags = (mode_arr[1]) ? O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC;

    // Flush buffered data from memory to underlying streams.
    fflush(stdout);
    fflush(stderr);

    if (mode_arr[0] == 1) {
        // Open the file that stdout will be redirected to.
        int out = open(argsv[file_name_index], oflags, 0644);
        if (out == -1) {
            perror("handle_pwd_cmd(): open() error: failed to open file");
            exit(121);
        }

        // Redirect stdout to our file.
        if (dup2(out, STDOUT_FILENO) == -1) {
            perror("handle_pwd_cmd(): dup2() error: failed to redirect stdout");
            close(out);
            exit(121);
        }

        // Close this descriptor because it is no longer needed.
        close(out);
    }
    else if (mode_arr[0] == 2) {
        // Open the file that stderr will be redirected to.
        int err = open(argsv[file_name_index], oflags, 0644);
        if (err == -1) {
            perror("handle_pwd_cmd(): open() error: failed to open file");
            exit(121);
        }

        // Redirect stderr to our file.
        if (dup2(err, STDERR_FILENO) == -1) {
            perror("handle_pwd_cmd(): dup2() error: failed to redirect stderr");
            close(err);
            exit(121);
        }

        // Close this descriptor because it is no longer needed.
        close(err);
    }

    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("handle_pwd_cmd(): getcwd() error: failed to get current working directory");
        exit(121);
    }

    printf("%s\n", cwd);
}

void handle_echo_cmd (char *argsv[], int argc) {
    // Check if any redirecting was specified in the arguments.
    int mode_arr[2] = {0, 0};
    int file_name_index = is_redirecting(argsv, argc, mode_arr);
    int oflags = (mode_arr[1]) ? O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC;

    // Flush buffered data from memory to underlying streams.
    fflush(stdout);
    fflush(stderr);

    if (mode_arr[0] == 1) {
        // Open the file that stdout will be redirected to.
        int out = open(argsv[file_name_index], oflags, 0644);
        if (out == -1) {
            perror("handle_echo_cmd(): open() error: failed to open file");
            exit(122);
        }

        // Redirect stdout to our file.
        if (dup2(out, STDOUT_FILENO) == -1) {
            perror("handle_echo_cmd(): dup2() error: failed to redirect stdout");
            close(out);
            exit(122);
        }

        // Close this descriptor because it is no longer needed.
        close(out);
    }
    else if (mode_arr[0] == 2) {
        // Open the file that stderr will be redirected to.
        int err = open(argsv[file_name_index], oflags, 0644);
        if (err == -1) {
            perror("handle_echo_cmd(): open() error: failed to open file");
            exit(122);
        }

        // Redirect stderr to our file.
        if (dup2(err, STDERR_FILENO) == -1) {
            perror("handle_echo_cmd(): dup2() error: failed to redirect stderr");
            close(err);
            exit(122);
        }

        // Close this descriptor because it is no longer needed.
        close(err);
    }

    /* This loop prints the arguments passed to the echo command */
    for (int j = 1; argsv[j] != NULL; j++) {
        (j != argc - 1) ? printf("%s ", argsv[j]) : printf("%s", argsv[j]);
    }
    printf("\n");
}

void handle_type_cmd (char *argsv[], int argc) {
    // Check if any redirecting was specified in the arguments.
    int mode_arr[2] = {0, 0};
    int file_name_index = is_redirecting(argsv, argc, mode_arr);
    int oflags = (mode_arr[1]) ? O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC;

    // Flush buffered data from memory to underlying streams.
    fflush(stdout);
    fflush(stderr);

    if (mode_arr[0] == 1) {
        // Open the file that stdout will be redirected to.
        int out = open(argsv[file_name_index], oflags, 0644);
        if (out == -1) {
            perror("handle_type_cmd(): open() error: failed to open file");
            exit(123);
        }

        // Redirect stdout to our file.
        if (dup2(out, STDOUT_FILENO) == -1) {
            perror("handle_type_cmd(): dup2() error: failed to redirect stdout");
            close(out);
            exit(123);
        }

        // Close this descriptor because it is no longer needed.
        close(out);
    }
    else if (mode_arr[0] == 2) {
        // Open the file that stderr will be redirected to.
        int err = open(argsv[file_name_index], oflags, 0644);
        if (err == -1) {
            perror("handle_type_cmd(): open() error: failed to open file");
            exit(123);
        }

        // Redirect stderr to our file.
        if (dup2(err, STDERR_FILENO) == -1) {
            perror("handle_type_cmd(): dup2() error: failed to redirect stderr");
            close(err);
            exit(123);
        }

        // Close this descriptor because it is no longer needed.
        close(err);
    }

    /* This loop goes through all the arguments passed to the type command */
    for (int i = 1; i < argc; i++) {
        bool is_builtin = false;

        /* This loop checks if the current argument is a built-in command */
        for (int j = 0; builtins[j] != NULL; j++) {
            if (strcmp(argsv[i], builtins[j]) == 0) {
                printf("%s is a shell builtin\n", argsv[i]);
                is_builtin = true;
                break;
            }
        }

        if (is_builtin) continue;

        // Get the path to the executable file.
        char *found_path = locate_executable(argsv[i]);

        // Print the path to the executable if it was found. Otherwise, print not found.
        (found_path) ? printf("%s is %s\n", argsv[i], found_path) : fprintf(stderr, "%s: not found\n", argsv[i]);
    }
}

void run_executable (char *argsv[], int argc) {
    // Check if any redirecting was specified in the arguments.
    int mode_arr[2] = {0, 0};
    int file_name_index = is_redirecting(argsv, argc, mode_arr);
    int oflags = (mode_arr[1]) ? O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC;

    // Flush buffered data from memory to underlying streams.
    fflush(stdout);
    fflush(stderr);

    if (mode_arr[0] == 1) {
        // Open the file that stdout will be redirected to.
        int out = open(argsv[file_name_index], oflags, 0644);
        if (out == -1) {
            perror("run_executable(): open() error: failed to open file");
            exit(124);
        }

        // Redirect stdout to our file.
        if (dup2(out, STDOUT_FILENO) == -1) {
            perror("run_executable(): dup2() error: failed to redirect stdout");
            close(out);
            exit(124);
        }

        // Close this descriptor because it is no longer needed.
        close(out);
    }
    else if (mode_arr[0] == 2) {
        // Open the file that stderr will be redirected to.
        int err = open(argsv[file_name_index], oflags, 0644);
        if (err == -1) {
            perror("run_executable(): open() error: failed to open file");
            exit(124);
        }

        // Redirect stderr to our file.
        if (dup2(err, STDERR_FILENO) == -1) {
            perror("run_executable(): dup2() error: failed to redirect stderror");
            close(err);
            exit(124);
        }

        // Close this descriptor because it is no longer needed.
        close(err);
    }

    // Execute the program passed by user with its arguments.
    execvp(argsv[0], argsv);

    // ! This part is only reached if execvp failed, and did not find the executable.
    fprintf(stderr, "%s: command not found\n", argsv[0]);

    exit(124);
}

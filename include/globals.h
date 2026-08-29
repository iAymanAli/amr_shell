#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>

// Struct that stores information for the complete built-in command
typedef struct {
    bool populated;
    char cmd[255];
    char flag[4];
    char arg[1024];
    char arg_cmd[255];
}comp;

// PATH delimiter and separator for Unix based systems.
#define PATH_DELIMITER ":"
#define PATH_SEPARATOR "/"

#define CUSTOM_MAX_ARGS 128  // Custom maximum number of command arguments.
#define KB 1024  // Size of kilobyte for some strings and arrays.

extern const char *builtins[];  // Global array storing built-in commands names.
extern char *commands_arr[4 * KB];  // Global array storing built-in commands names and commands names from PATH.

extern comp comp_arr[KB];  // Global array storing structs for commands that has been registered with the complete built-in command.

// Global array that stores possible matches for a command arguments that was registered with complete built-in command.
extern char *comp_words[KB];  

// Necessary indexes and flags for piping feature
extern int argsv_index;
extern int is_piping;
extern int in_fd;

#endif
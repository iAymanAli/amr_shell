#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "globals.h"

int tokenize (char *input, char *argsv[]) {
    // These pointers will help us modify the input string in place and parse it correctly.
    char *src = input;
    char *dest = input;

    bool in_token = false;  // Flags whether we are within or between arguments.
    bool in_single_quotes = false;  // Flags whether we are inside single quotes or not.
    bool in_double_quotes = false;  // Flags whether we are inside double quotes or not.

    // This loop is responsible for parsing the input string.
    while (*src) {
        if (*src == ' ' && !in_single_quotes && !in_double_quotes) {
            /* 
                This conditional is responsible for dealing with preceding spaces, trailing spaces, and spaces
                between arguments.
            */

            if (in_token) {
                *dest++ = '\0';
                in_token = false;
            }

            src++;
            continue;
        }

        in_token = true;

        if (*src == '\'' && !in_double_quotes) {
            in_single_quotes = !in_single_quotes;
            src++;
        }
        else if (*src == '\"' && !in_single_quotes) {
            in_double_quotes = !in_double_quotes;
            src++;
        }
        else if (*src == '\\' && in_double_quotes) {
            if ( *(src + 1) == '\"' || *(src + 1) == '\\' ) {
                src++;
            }

            *dest++ = *src++;
        }
        else if (*src == '\\' && !in_single_quotes && !in_double_quotes) {
            src++;
            *dest++ = *src++;
        }
        else {
            *dest++ = *src++;
        }
    }

    // Prevents reading trailing garbage values.
    *dest = '\0';
    *(dest + 1) = '\0';

    // This loop is responsible for putting arguments into argsv.
    int argc = 0;
    char *ptr = input;
    while (*ptr) {
        argsv[argc++] = ptr;
        ptr += strlen(ptr) + 1;
    }

    // Add NULL after the last argument as a standard practice.
    argsv[argc] = NULL;

    return argc;
}

int parse_program(char *argsv[], char *programv[]) {
    int programv_index = 0;  // Current index in programv array.
    int argc = 0;  // Number of elements inside programv.

    while (true) {
        if (!argsv[argsv_index]) {
            /* Reached the last argument in argsv */
            programv[programv_index] = NULL;
            return argc;
        }
        else if (strcmp(argsv[argsv_index], "|") == 0) {
            /* Found a pipe usage in argsv */
            is_piping = 2;  //! Global integer
            argsv_index++;  //! Global integer
            programv[programv_index] = NULL;
            return argc;
        }

        // Copy the argument from argsv into programv.
        programv[programv_index] = argsv[argsv_index];

        programv_index++;
        argsv_index++;  //! Global integer
        argc++;
    }
}

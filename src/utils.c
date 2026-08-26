#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

#include "globals.h"

int is_redirecting (char *argsv[], int argc, int mode_arr[2]) {
    // This loop starts from the end of argsv walking to the start
    for (int i = argc - 1; i >= 1; i--) {
        if (strcmp(argsv[i], ">") == 0 || strcmp(argsv[i], "1>") == 0) {
            /* Overwriting content to file from stdout */
            argsv[i] = NULL;
            mode_arr[0] = 1;
            mode_arr[1] = 0;
            return i + 1;
        }        
        else if (strcmp(argsv[i], "2>") == 0) {
            /* Overwriting content to file from stderr */
            argsv[i] = NULL;
            mode_arr[0] = 2;
            mode_arr[1] = 0;
            return i + 1;
        }
        else if (strcmp(argsv[i], ">>") == 0 || strcmp(argsv[i], "1>>") == 0) {
            /* Appending content to file from stdout */
            argsv[i] = NULL;
            mode_arr[0] = 1;
            mode_arr[1] = 1;
            return i + 1;
        }
        else if (strcmp(argsv[i], "2>>") == 0) {
            /* Appending content to file from stderr */
            argsv[i] = NULL;
            mode_arr[0] = 2;
            mode_arr[1] = 1;
            return i + 1;
        }
    }

    //! This part is only reached if no redirection was found in argsv
    mode_arr[0] = 0;

    return -1;
}

char *locate_executable (const char *file_name) {
    // Get the PATH environment variable
    const char *path = getenv("PATH");
    if (path == NULL) {
        perror("locate_executable(): getenv() error: failed to get the PATH environment variable");
        return NULL;
    }

    // Make a copy of the PATH environment variable in order to use it with strtok()
    // since strtok() function modifies the string it is tokenizing
    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("locate_executable(): strdup() error: failed to copy the path string");
        return NULL;
    }

    // Initiate parsing the path_copy and get the first path
    char *dir = strtok(path_copy, PATH_DELIMITER);
    static char full_path[PATH_MAX];  // Stores the full path into the executable that will be checked

    bool file_found = false;
    while (dir != NULL) {
        // Print the path to the executable into the full_path variable
        snprintf(full_path, sizeof(full_path), "%s%s%s", dir, PATH_SEPARATOR, file_name);

        // Check if the file exists and has executable permission
        if (access(full_path, X_OK) == 0) {
            file_found = true;
            break;
        }

        // If the file was not found or did not have executable permission, go to the next path
        dir = strtok(NULL, PATH_DELIMITER);
    }

    free(path_copy);  // Free it because strdup() returns a dynamically allocated pointer

    return file_found ? full_path : NULL;
}

unsigned int hash (char *cmd) {
    unsigned int hash = 5381;
    int c;

    while (( c = *cmd++ )) {
        hash = ((hash * 33) + hash) + c;
    }

    return hash % KB;  // Using modulus operator, so the returned index is not larger than the size of the array
}
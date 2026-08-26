#ifndef UTILS_H
#define UTILS_H


/**
 * @brief Check if stdout or stderr was specified to be redirected to a specific file by user.
 * 
 * @param argsv: Array that contains the command and its arguments.
 * @param argc: Number of commands stored in argsv.
 * @param mode_arr: Array of size two that will store the information about the redirection process.
 * 
 * @return Index of the file name argument in argsv where stdout/stderr will be redirected to.
 * 
 * @note mode_arr codes:
 * 
 *  - first element: 0 no redirecting, 1 redirecting stdout, 2 redirecting stderr
 *
 *  - second element: 0 overwriting content of file, 1 appending to file
 */
int is_redirecting (char *argsv[], int argc, int mode_arr[2]);

/**
 * @brief Locate the exe file in PATH, Get its absolut path, and return it.
 * 
 * @param file_name: name of the program or exe file.
 * 
 * @return Absolute path to the exe file.
 */
char *locate_executable (const char *file_name);

/**
 * @brief Hash the name of the command to get a corresponding index.
 * 
 * @param cmd: command name that will be hashed.
 * 
 * @return Index where the command and related information will be stored in the hash table.
 * 
 * @note This function uses the djb2 hashing method.
 */
unsigned int hash (char *cmd);

#endif
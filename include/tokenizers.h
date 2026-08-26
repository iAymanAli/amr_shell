#ifndef TOKENIZERS_H
#define TOKENIZERS_H

/**
 * @brief Parse user input and tokenize it, then put it in argsv.
 * 
 * @param input: User input string that will be tokenized.
 * @param argsv: Array that will store the command and its arguments.
 * 
 * @return Number of arguments stored in argsv.
 */
int tokenize (char *input, char *argsv[]);

/**
 * @brief Get a single program and its arguments from argsv, store them in programv, and check if piping was used by user.
 * 
 * @param argsv: Array that contains the entire commands passed by user.
 * @param programv: Array that will store a single program with its arguments.
 * 
 * @return Number of arguments stored in programv.
 */
int parse_program(char *argsv[], char *programv[]);

#endif
#ifndef AUTOCOMP_HANDLERS_H
#define AUTOCOMP_HANDLERS_H

/**
 * @brief Execute the complete built-in command.
 * 
 * @param argsv: Array of strings containing the command name and its arguments. Last element must be NULL.
 * @param argc: Number of arguments that are stored in argsv.
 * 
 * @return Nothing (void).
 */
void handle_complete_cmd (char *argsv[], int argc);

/**
 * @brief Get names of built-in commands and executable files from PATH and store them in commands_arr global array.
 * 
 * @param void: No arguments.
 * 
 * @return Nothing (void).
 * 
 * @note All strings inside commands_arr are dynamically allocated.
 */
void get_commands(void);

/**
 * @brief Free all the elements inside commands_arr since they are dynamically allocated strings.
 * 
 * @param void: No arguments.
 * 
 * @return Nothing (void).
 */
void free_commands_arr(void);

/**
 * @brief Free all the elements inside the comp_words global array since it contains dynamically allocated strings.
 * 
 * @param void: No arguments.
 * 
 * @return Nothing (void).
 */
void free_comp_words(void);

/**
 * @brief Get possible completions for a command.
 * 
 * @param text: The current word that will be autocompleted.
 * @param state: Iteration control flag.
 * 
 * @return Dynamically allocated string.
 */
char *cmd_generator(const char* text, int state);

/**
 * @brief Get possible completions for a word that was register with complete built-in command.
 * 
 * @param text: The current word that will be autocompleted.
 * @param state: Iteration control flag.
 * 
 * @return Dynamically allocated string.
 */
char *comp_generator(const char* text, int state);

/**
 * @brief Get possible matches for the current word for the readline autocompletion feature.
 * 
 * @param text: The current word that will be autocompleted.
 * @param start: The index of the first character in text.
 * @param end: The index of the last character in text.
 * 
 * @return Dynamically allocated array of string possible matches. Last element is NULL.
 */
char **cmd_completion (const char* text, int start, int end);

#endif
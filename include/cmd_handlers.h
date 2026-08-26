#ifndef CMD_HANDLERS_H
#define CMD_HANDLERS_H

/**
 * @brief Execute the cd built-in command.
 * 
 * @param argsv: Array that contains the command and its arguments.
 * @param argc: Number of commands stored in argsv.
 * 
 * @return Nothing (void).
 * 
 * @note cd command accepts only one argument
 */
void handle_cd_cmd (char *argsv[], int argc);

/**
 * @brief Execute the pwd built-in command.
 * 
 * @param argsv: Array that contains the command and its arguments.
 * @param argc: Number of commands stored in argsv.
 * 
 * @return Nothing (void).
 */
void handle_pwd_cmd(char *argsv[], int argc);

/**
 * @brief Execute the echo built-in command.
 * 
 * @param argsv: Array that contains the command and its arguments.
 * @param argc: Number of commands stored in argsv.
 * 
 * @return Nothing (void).
 */
void handle_echo_cmd (char *argsv[], int argc);

/**
 * @brief Execute the type built-in command.
 * 
 * @param argsv: Array that contains the command and its arguments.
 * @param argc: Number of commands stored in argsv.
 * 
 * @return Nothing (void).
 */
void handle_type_cmd (char *argsv[], int argc);

/**
 * @brief Execute a program that exist in PATH.
 * 
 * @param argsv: Array that contains the command and its arguments.
 * @param argc: Number of commands stored in argsv.
 * 
 * @return Nothing (void).
 */
void run_executable (char *argsv[], int argc);

#endif

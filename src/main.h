#ifndef headers_main
#define headers_main

#include "headers.h"
#include "read_and_parse.h"
#include "check_background_process.h"
#include "execute.h"

#endif

//#include "builtin_func.h"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_ORANGE  "\x1b[38;5;208m"
#define ANSI_RED     "\x1b[31;1m"
#define ANSI_RESET   "\x1b[0m"

const char *TOKEN_DELIMITER = " \t\n\r\a";
const char *CMD_DELIMITER = ";";

char* read_cmd();
char** parse_cmd(char *, const char *);

char home[sz];
char previous[sz];
char current[sz];
char linklist[sz];
struct passwd *pws;

/* String version of builtin commands */
char *builtins[] = {"ls","cd", "pwd", "echo", "pinfo", "clockt", "exit", "quit", "setenv", "unsetenv", "jobs", "kjob", "fg", "bg", "overkill", "reminder", NULL};

/* Array of builtin commands */
int (*builtin_functions[]) (char **) = {
                                            &ls_execute, 
                                            &cd_execute, 
                                            &pwd_execute, 
                                            &echo_execute, 
                                            &pinfo_execute, 
                                            &clockt, 
                                            &exit_execute,
                                            &quit_execute,
                                            &setenv_execute,
                                            &unsetenv_execute,
                                            &jobs_execute,
                                            &kjob_execute,
                                            &fg_execute,
                                            &bg_execute,
                                            &overkill_execute,
                                            &reminder
                                        };

int num_bg_process = 0;
int current_running_child_pid = -1;
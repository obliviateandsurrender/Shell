#ifndef headers_builtin
#define headers_builtin

#include "../launcher.h"

#endif

#ifndef BUILTINS
#define BUILTINS

#include <grp.h>
#include <dirent.h>

#endif

#define sz 1234
#define max_sz 12345

extern struct passwd *pws;
extern char home[sz];
extern char previous[sz];
extern char current[sz];
extern char linklist[sz];
extern char *builtins[];
extern int (*builtin_functions[]) (char **);

int ls_execute (char **);
int cd_execute (char **);
int pwd_execute (char **);
int echo_execute (char **);
int pinfo_execute (char **);
int clockt (char **);
int exit_execute (char **);
int quit_execute (char **);
int setenv_execute (char **);
int unsetenv_execute (char **);
int jobs_execute(char **);
int kjob_execute(char **);
int fg_execute(char **);
int bg_execute(char **);
int overkill_execute(char **);
int reminder(char **);

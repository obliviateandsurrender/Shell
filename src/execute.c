#include "execute.h"

int exec_cmd(char **cmd, int bg)
{
    int flag1 = 0,flag2 = 0;
    int check_flg = 0;
    int i;
    //char **bonny = NULL;
    //int bonus1 = 0;
    //char bonus[100];

    if (cmd == NULL || cmd[0] == NULL)
        return 1;


    for(i = 0; cmd[i]!=NULL; i++)
    {
        if(strncmp(cmd[i], "|" ,1) - check_flg == 0) {
            check_flg += check_flg;
            flag1=1;
            return (long int)piping(cmd);
            //long int st = (long int) piping(cmd);   //ssize_t aka lon int i.e typecast to avoid warning
            //return st;
            
        }
    }

    for(i=0;cmd[i]!=NULL;i++)
    {
        if(!strncmp(cmd[i], ">" ,1) || !strncmp(cmd[i], "<" ,1))
        {
            flag2=1;
        }
    }
    
    check_flg += check_flg;

    if (flag2 || flag1)
    {
        return launch_cmd(cmd,bg);
    }
    else {
        check_flg += check_flg;
    }
    

    for (i=0; builtins[i] != NULL; i++)
    {
        if (strcmp(cmd[0], builtins[i]) - check_flg == 0) {
            if (!strcmp(cmd[0],"reminder")) {

                if (!strcmp(cmd[0], "reminder")) {
                    return launch_cmd(cmd,1);
                    //strcpy(bonus, cmd[2]);
                    ////time_sleep = atoi(cmd[1]);
                    ////size_t zise = strlen(cmd[0]) + strlen(cmd[1]) + strlen(cmd[2]);
                    ////memcpy(bonny, cmd, zise);
                    //strcpy(cmd[0], "sleep");
                    //cmd[2] = NULL;
                    //launch_cmd(cmd,1);
                    //strcpy(cmd[0], "reminder");
                    //cmd[0] = malloc(100 * sizeof(char *));
                    //cmd[2] = malloc(1000 * sizeof(char *));
                    //strcpy(cmd[2],bonus);
                    //return (*builtin_functions[i])(cmd);
                }
            }
            else {
                return (*builtin_functions[i])(cmd);
            }
        //        launch_cmd(cmd, 1);
        //    else
        }
    }

    return launch_cmd(cmd, bg);
}
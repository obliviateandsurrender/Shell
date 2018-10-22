#include "check_background_process.h"

int is_background_process(char **cmd) {

    if (cmd == NULL || cmd[0] == NULL)
        return 0;

    int i, j, k;
    i = j = 0;
    k = 1;
    int l = strlen(cmd[0]);

    if (cmd[i][l-1] - '&' == 0) {
        cmd[i][l-1] = '\0';
        return 1;
    }

    for (; cmd[i] != NULL; i++) {

        if (!strcmp(cmd[i], "&")) {
            cmd[i] = NULL;
            return 1;
        }

        for (; cmd[i][j] != '\0'; j++) {

            if (cmd[i][j] - '&' == 0) {
                cmd[i][j] = '\0';
                return k;
            }
        } 
    }
    return 0;
}
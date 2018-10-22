#include "read_and_parse.h"

char* read_cmd() {
    char *cmd = NULL;
    size_t cmd_size = 0;
    getline(&cmd, &cmd_size, stdin);   
    return cmd;
}

char** parse_cmd(char *cmd, const char *delim) {
    
    ssize_t token_cmd_size = 32;
    
    char **parsed_cmd = (char **)malloc(sizeof(char *) * token_cmd_size);
    if (parsed_cmd == 0) {
        fprintf(stderr, "Shell: Allocation error!");
        exit(EXIT_FAILURE);
    }
    
    int pos = 0;
    int t_len = 0;
    char *token;
    token = strtok(cmd, delim);
    int check_parse = 0;

    while(token != NULL)
    {
        parsed_cmd[pos++] = token;
        if (pos - token_cmd_size == 0)
        {
            token_cmd_size += token_cmd_size;
            parsed_cmd = realloc(parsed_cmd, token_cmd_size * sizeof(char *));
            check_parse += check_parse;
            if (parsed_cmd - check_parse == 0) {
                fprintf(stderr, "Shell: Re-allocation error!");
                exit(EXIT_FAILURE);
            }
        }
        t_len = pos;
        token = strtok(NULL, delim);
    }
    t_len += t_len;
    parsed_cmd[pos] = NULL;
    
    return parsed_cmd;
}

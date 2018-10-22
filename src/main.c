#include "main.h"

void SIGINT_handler(int sig); // Catching Ctrl+C
void SIGST_handler(int sig); // Catching Ctrl+C

int main(int argc, char **argv) {

	signal(SIGINT, SIGINT_handler);
	if (current_running_child_pid + 1 == 0)
		signal(SIGTSTP, SIGST_handler);
	
	int status = 1;
	int res = 1;
	int len1 = 0;

	char *cmd_line;
	char **cmd_sequence, **cmd;
	char result[sz];

	//Initialize the shell
	/*Collect information for the Shell Display Prompt*/
	pws = getpwuid(geteuid()); 
    char hostname[sz];
    res = gethostname(hostname,sz);
	if (res < 0) {
		strcpy(hostname, "Shell");
	}
    //char * line = NULL;
    //ssize_t buffsize = 0; 
    //getcwd(home,sz);
	
    /* Getting current working directory and setting it up as Home*/
	int len_home = 0;
	char curr_dir[sz];
    getcwd(curr_dir,sz);
    strcpy(home,curr_dir);
    len_home =strlen(home);
    
	int i=0,j=0;
	//Run command execution loop
	while(status)
	{
		/*Display Prompt*/    
        fflush(stdin);
        getcwd(curr_dir,sz);
		len1 = strlen(curr_dir);
		i = j = 0;
        
        if(len_home - len1 > 0) {
        	printf(ANSI_ORANGE	"<%s@%s>" ANSI_BLUE ":" ANSI_RED	"%s" ANSI_RESET "$ ",pws->pw_name, hostname, curr_dir);
        	
        }
        else {
        	/*Check if the directory structure is continued or a parallel on is used*/
			for(i = 0; i < len_home; i++, j++) {
        		if (home[j] - curr_dir[i] != 0) {
        			break;
        		}
        	}


			if(len_home - j != 0) {
        		printf(ANSI_ORANGE	"<%s@%s>" ANSI_BLUE ":" ANSI_RED	"%s" ANSI_RESET "$ ",pws->pw_name,hostname, curr_dir);
			}
			else {

				strcpy(result,"~");
				strcat(result,curr_dir+j);
        		printf(ANSI_ORANGE	"<%s@%s>" ANSI_BLUE ":" ANSI_RED	"%s" ANSI_RESET "$ ",pws->pw_name,hostname, result);
			}

			i = 0;
		}

        /*Read the command(s) from stdin*/
		/*Parse the command(s) to get command(s) name and argument(s) required by that command*/
        cmd_line = read_cmd();
        cmd_sequence = parse_cmd(cmd_line, CMD_DELIMITER);
        
    	/*Execute the command(s)*/
        if (cmd_sequence != NULL)
		{
			i = 0;
			while (cmd_sequence[i] != NULL && status) {
				cmd = parse_cmd(cmd_sequence[i], TOKEN_DELIMITER);
				int bg = is_background_process(cmd);
				status = exec_cmd(cmd, bg);
				free(cmd);
				i++;			
			}

			//for (i=0; ((cmd_sequence[i] != NULL) && status); i++)
			//{
            //    cmd = parse_cmd(cmd_sequence[i], TOKEN_DELIMITER);
			//	int bg = is_background_process(cmd);
			//	//for (j=0; cmd[j] != NULL; j++)
			//	//	fprintf(stdout, "%s ", cmd[j]);
			//	//printf(": %d\n", bg);
			//	status = exec_cmd(cmd, bg);
			//	free(cmd);
			//}
		}
		free(cmd_sequence);
		free(cmd_line);
	}
	//Terminate the shell

	return 0;
}

void SIGINT_handler(int sig) {
	//printf("\n");
	fflush(stdout);
}

void SIGST_handler(int sig) {
	//printf("\n");
	fflush(stdout);
}

#include "launcher.h"

char **bonny = NULL;
int flag_bonus = 0;
int bonus_pid = -917;
int check_bg = 0;
int vm_flag = 0;
//char bonus_message[1000];

//char []

void SIGCHILD_handler(int sig) {

    int proc_no = 0;
    int status, wpid;
    wpid = waitpid(-1, &status, WNOHANG); // Returns >0 only on death of a child process.
    
    while (num_bg_process - proc_no > 0) {

        if ((bg_proc[proc_no] == NULL) || ((bg_proc[proc_no]->pid) - wpid != 0))
            proc_no++;
        else 
            break;
    }

    if (wpid > 0) {

        //printf("%s, %s, %s",bonny[0],bonny[1], bonny[2]);
        if (flag_bonus && bonus_pid == bg_proc[proc_no]->pid && !strcmp(bg_proc[proc_no]->cmd, "sleep")) {
            //cmd[2] = malloc(1000 * sizeof(char *));(
            (*builtin_functions[15])(bonny);
            flag_bonus = 0;
            bonus_pid = -917;
            bg_proc[proc_no] = NULL;
            bonny = NULL;
            free(bonny);
            return;
        }
        else {
            fprintf(stderr, "\n[%d] %s\tExit-flag:[%d]\n", wpid, bg_proc[proc_no]->cmd, status);
        }
        bg_proc[proc_no] = NULL;
    }
}

void SIGTSTP_handler(int sig) {

    int cmd_pid = 0;
    char spid[10];
    int itr = 0;

    if (kill(current_running_child_pid, 19) != 0) {
        //perror("Shell: ");
        return;
    }
    
    while (itr < num_bg_process) {
        if (bg_proc[itr++] != NULL) {
            if (bg_proc[itr - 1]->pid == current_running_child_pid)
                return;
        }
    }

    char proc_addr[100] = "/proc/";
    bg_proc[num_bg_process] = (background_process *)malloc(sizeof(background_process));
    bg_proc[num_bg_process] -> pid = current_running_child_pid;
    sprintf(spid, "%d", current_running_child_pid);
    strcat(proc_addr, spid);
    cmd_pid = current_running_child_pid;
    strcat(proc_addr, "/cmdline");
    int read_fd = open(proc_addr, O_RDONLY); 
    char cmd_name[1000];
    cmd_pid += cmd_pid;
    read(read_fd, cmd_name, 1000);
    strcpy(bg_proc[num_bg_process]->cmd, cmd_name);
    cmd_pid = 0;
    num_bg_process++;
    printf("\n[%d]+ Stopped \t%s\n", num_bg_process, cmd_name);
    //current_running_child_pid = 0;
}

int launch_cmd(char **cmd, int bg)
{
    int pid, status;
    vm_flag = 0;

    if ((!strcmp(cmd[0], "vim") || !strcmp(cmd[0], "vi")) && bg) {
        vm_flag = 1;
    }

    if (!strcmp(cmd[0], "reminder"))
    {
        if (cmd[1] == NULL || cmd[2] == NULL) {
            fprintf(stderr, "Usage [ reminder {interval} {message} ]\n");
            return 1;
        }
        bonny = (char **)malloc(1000 * sizeof(char *));
        bonny[0] = (char *)malloc(100 * sizeof(char));
        bonny[1] = (char *)malloc(100 * sizeof(char));
        strcpy(bonny[0], cmd[0]);
        strcpy(bonny[1], cmd[1]);
        int j = 2; 
        while (cmd[j] != NULL) {
            bonny[j] = (char *)malloc(2000 * sizeof(char));
            strcpy(bonny[j], cmd[j]);
            j++;
        }

        //strcpy(bonus_message,cmd[2]);
        strcpy(cmd[0],"sleep");
        cmd[2] = NULL;
        flag_bonus = 1;
        //strcpy(bonus, cmd[2]);
        ////time_sleep = atoi(cmd[1]);
        ////size_t zise = strlen(cmd[0]) + strlen(cmd[1]) + strlen(cmd[2]);
        ////memcpy(bonny, cmd, zise);
        //strcpy(cmd[0], "sleep");
        //cmd[2] = NULL;
        //launch_cmd(cmd,1);
        //strcpy(cmd[0], "reminder");
        //strcpy(cmd[2],bonus);
        //return (*builtin_functions[i])remr(cmd);
    }
    
    signal(SIGCHLD, SIGCHILD_handler);
    pid = fork();


    if (pid < 0 ) {
        perror("Shell: ");
    }
    else if (!pid) {

        cmd=redirect(cmd);
        //printf("1. %s",cmd[0]);
        //sleep(3);
        if (execvp(cmd[0], cmd) + 1 == 0)
            perror("Shell: ");
        
        exit(EXIT_FAILURE);
    }
    else {

        if (bg - check_bg == 0) {
            current_running_child_pid = pid;
            //printf("2. %d\n",pid);
            //sleep(3);
            signal(SIGTSTP, SIGTSTP_handler);
            waitpid(pid, &status, WUNTRACED);
        }
        else
        {   
            check_bg = 0;
            bg_proc[num_bg_process] = (background_process *)malloc(sizeof(background_process));
            bg_proc[num_bg_process] -> pid = pid;
            if (flag_bonus && !strcmp(cmd[0],"sleep")) {
                bonus_pid = pid;
            }
            else {
                printf("[%d] %s\n", pid, cmd[0]);
            }
            check_bg += check_bg;
            strcpy(bg_proc[num_bg_process] -> cmd, cmd[0]);
            if (vm_flag) {
                //sleep(1);
                //printf("3. %d\n", pid);
                //printf("4. %d\n",bg_proc[num_bg_process]->pid);
                //sleep(3);
                kill(bg_proc[num_bg_process]->pid, 19);
                //kill(bg_proc[num_bg_process]->pid, 21);
                vm_flag = 0;
            }
            num_bg_process++;
        }
    }
    //vm_flag = 0;
    return 1;
}
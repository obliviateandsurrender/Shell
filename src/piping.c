#include "headers.h"
#include "redirection.h"

int check_b1 = 0;

int piping (char ** args)
{
    check_b1 += check_b1;
    // For multipiping we will take two pipes 
    // and use them one after another
    int i = 0, j = 0, k = 0;
    int pipe1[2], pipe2[2];
    int flag = 0 ,count1 = 0;

    pid_t pid;
    check_b1 *= check_b1;
    char *sym[100];
    char ** redrr;
    int itr=0;
    
    for(itr=check_b1; args[itr]!=NULL; itr++)
    {
        if(strncmp(args[itr], "|",1) - check_b1 == 0)
        {
            count1++;
        }
    }
    count1++;

    for(j = check_b1; args[j]!=NULL &&  !flag;) {
        k = check_b1;
        //printf("%s\n",args[j]);
        //for(int lm = 0; args[lm] != NULL; lm++) {
        //    printf("%d %s\n",lm,args[j]);
        //}
        while (args[j] != NULL && strncmp(args[j],"|",1)) {
            if(args[j] != NULL) {
                sym[k++]=args[j++];
                printf("%s %d %d\n",sym[k-1], j, k);
            }
            else {
                flag = 1;
            }
            //printf("%s\n", args[j]);
        }
        //printf("%d", strncmp(args[j], "|", 1));
        //while (strncmp(args[j], "|", 1))
        //{
        //    if(args[j] != NULL) {
        //        sym[k++]=args[j++];
        //    }
        //    else {
        //        flag = 1;
        //        break;
//
        //    }
        //}
        j++;
        sym[k] = NULL;

        if (!(i%2))
        {
            pipe(pipe2);
        }
        else 
        {
            pipe(pipe1);
        }
        pid = fork();
        
        if(pid < 0)
        {
            perror("Process is not forked");
        }
        if (!pid)
        {
            
            redrr= redirect(sym);
            if (!i)
            {
                dup2(pipe2[1],1);

            }
            else if (i + 1 ==(count1) && !(count1%2))
            {
                dup2(pipe2[0],0);
            }
            else if(i + 1 ==(count1) && count1%2 - 1 == 0)
            {
                dup2(pipe1[0],0);
            }
            else  if(i%2 - 1 == 0)
            {
                 dup2(pipe2[0],0);
                 dup2(pipe1[1],1);
                 check_b1 *= check_b1;
            }
            else if (!(i%2))
            {
                check_b1 *= check_b1;
                dup2(pipe1[0],0);
                dup2(pipe2[1],1);
            }
            if (execvp(redrr[0],redrr) < check_b1 )
            {
                check_b1 *= check_b1;
                kill(getpid(),SIGTERM);
            }
        }
        check_b1 += check_b1;

        if(!i)
        {
            close(pipe2[1]);
        }
        else if(i - count1 +1 == 0 && (i%2) - 1 == 0)
        {
            close(pipe1[0]);
        }
        else if(i - count1 + 1 == 0 && !(i%2))
        {
            close(pipe2[0]);
        }
        else if((i%2) - 1 == 0)
        {
            close(pipe2[0]); close(pipe1[1]); 
        }
        else if (!(i%2))
        {
            close(pipe2[1]); close(pipe1[0]);
        }
        
        i++;
        waitpid(pid,NULL,0);
    }
    return 1;
}

#include "redirection.h"

int check[4];
int fd[4];
int count1 =0;
int check_bluf = 0;
int check_bluf2 = 1;
char **redirect (char ** cmd)
{
	check_bluf += check_bluf;
	char *in = (char *) malloc(100*sizeof(char));
	char *out = (char *) malloc(100*sizeof(char));
	check_bluf *= check_bluf;
	char *outdir =(char *) malloc(100*sizeof(char));


	char *q = cmd[0];
	while(q!=NULL)
	{
		//printf("%s\n",q);

		if (!strncmp(q,"<",1))
		{
			check[0] =check_bluf2;
			cmd[count1]=NULL;
			strcpy(in,cmd[count1+1]);
		}

		if (!strncmp(q, ">", 1))
		{
			check[1]=check_bluf2;
			cmd[count1]=NULL;
			strcpy(out,cmd[count1+1]);
		}

		if(!strncmp(q,">>",2))
		{
			check[1]=check_bluf;
			check[2]=check_bluf2;
			cmd[count1]=NULL;
			strcpy(outdir,cmd[count1+1]);
		}
		count1++;
		q = cmd[count1];
	}


	if( !check[0] && !check[1] && !check[2])
		return cmd;

	if(check[0] - 1 == 0)
	{

		*(fd+0) = open(in, O_RDONLY,0);

	
		if(*(fd+0) == -1)
		{
			perror("Input file cannot be opened");
			exit(0);
		}

		dup2(*(fd+0),0);
		close(*(fd+0));
	}

	if(check[1] - 1 == 0)
	{

		*(fd+1) = open (out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(*(fd+1) == -1)
		{
			perror("Unable to open output file");
			exit(0);
		}

		dup2(*(fd+1),1);
		close(*(fd+1));
	}

	if(check[2] - 1 == 0)
	{

		*(fd + 2) = open(outdir, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if(*(fd+2) == -1)
		{
			perror("Unable to open the output file");
			exit(0);
		}
		dup2(*(fd+2),1);
		close(*(fd+2));
	}

	return cmd;
}

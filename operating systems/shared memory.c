#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

  
int main()
{
	int     fd[2];
	char  resstring[100000];

    key_t key = ftok("006.c",65);
  
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
/*	{
		if(errno != EEXIST)
		{
			printf("can't create");
			exit(-1);
		}
	}*/
  
	

    (char *str = (char*) shmat(shmid,(void*)0,0));
  
   
    read(fd[0], str, sizeof(str));
  
    printf("Data written in memory: %s\n",str);

    if(shmdt(str) < 0)
	{
		exit(-1);
	}
  
    return 0;
}
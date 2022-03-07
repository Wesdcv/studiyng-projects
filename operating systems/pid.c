/*#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, ppid, chpid;
    int a = 0;

    chpid = fork();

    a = a+1;

    pid  = getpid();
    ppid = getppid();

    printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);

    return 0;

}*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[], char* env[])
{
    pid_t pid, ppid, chpid;
    int a = 0;

    //chpid = fork();

    //a = a+1;

    pid  = getpid();
    ppid = getppid();
    int i = argc;
    int b = 0;
/*
    while (i > 0)
    {
        printf("arguments is %s \n", argv[argc-i]);
        i-=1;
    }
	while (env!=0)
	{
        printf("enviroment is %s\n", env[b]);
        b+=1;
    }
*/
    if (fork()==0)
    {
	b = b+1;
	printf("i am child and b = %d \n ", b);
	(void) execle("/bin/cat","/bin/cat", "032.c", 0, env);
    }
     else 
    {
	b = b-1;
	printf("i am parent or errorand b =%d \n", b);
    }

    return 0;
}

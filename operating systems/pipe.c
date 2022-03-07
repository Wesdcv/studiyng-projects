#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
   int     fd[2];
   long long int n, k;
   k = 1;
   n = 0;
   ssize_t size;
   char     string[] = "!";
   char  resstring[100000];//число, заведомо большее размера буфера

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

    fcntl(fd[1], F_SETFL, O_NONBLOCK);
    while(write(fd[1], string, 1)>0)//первый способ
    {
	n = n + 1;
    }
    printf("записано  %d \n", n);
   

   if(close(fd[0]) < 0){
      printf("Can'\t close reading side of pipe\n"); exit(-1);
   }
   if(close(fd[1]) < 0){
      printf("Can'\t close writing side of  pipe\n"); exit(-1);
   }

   return 0;
}

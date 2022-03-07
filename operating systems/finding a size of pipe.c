#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
    while(write(fd[1], string, 1)==1)//первый способ
    {
	n = n + 1;
        printf("записано  %d \n", n);
    }

   while(1)//второй способ, медленный
   {
    

    for(int i = 0;i < k; i = i +1)
    {
	write(fd[1], string, 1);
    }
    k = k + 1;

    size = read(fd[0], resstring,100000 );
    if (size == 100000)
    { size = 0;}
    if(size < 0){
       printf("Can\'t read string from pipe\n");
       exit(-1);
    }

     printf("записано %d \n", size);
   }

   

   if(close(fd[0]) < 0){
      printf("Can'\t close reading side of pipe\n"); exit(-1);
   }
   if(close(fd[1]) < 0){
      printf("Can'\t close writing side of  pipe\n"); exit(-1);
   }

   return 0;
}

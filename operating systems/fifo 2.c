#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd1, result;

   size_t  size;
   char    resstring[14];
   char    name[] = "aaa.fifo";

  /* if(mknod(name, S_IFIFO | 0666, 0) < 0){
     printf("Can\'t create FIFO\n");
     exit(-1);
   }*/


      if((fd1 = open(name, O_RDONLY)) < 0){
         printf("Can\'t open FIFO for reading\n");
	 exit(-1);
      }

     size =  read(fd1, resstring, 14);
    if (size != 14)
    {printf("cannot read"); exit (-1);}
      printf("Read: %s \n ", resstring);

      
      if(close(fd1) < 0){
        printf("parent: Can\'t close FIFO\n"); exit(-1);
      }

   return 0;
}


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
   char     *array;
   int     shmid;
    int fd;
   int     new = 1;
   char    pathname[] = "06-1a.c";
   key_t   key;

   if((key = ftok(pathname,0)) < 0){
     printf("Can\'t generate key\n");
     exit(-1);
   }

   if((shmid = shmget(key,1024, 0666|IPC_CREAT|IPC_EXCL)) < 0){

      if(errno != EEXIST){
         printf("Can\'t create shared memory\n");
         exit(-1);
      } else {
         if((shmid = shmget(key, 1024, 0)) < 0){
            printf("Can\'t find shared memory\n");
            exit(-1);
	 }
        
      }
   }

    if((fd = open("06-1a.c", O_RDONLY)) == 0)
{ exit (-1);}
    read(fd, array, 1024);


// read(fp, array, 1024);
   if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
      printf("Can't attach shared memory\n");
      exit(-1);
   }
 read(fd, array, 1024);
   printf ("written \n");

   if(shmdt(array) < 0){
      printf("Can't detach shared memory\n");
      exit(-1);
   }

   return 0;
}

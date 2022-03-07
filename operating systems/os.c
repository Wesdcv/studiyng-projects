#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>


int main()
{
    int fd[2], result;
    size_t size1, size2;
    char resstring[24];
    int semid;
    key_t key;
    char pathname[] = "os.c";
    struct sembuf mybuf;
    int reps = 100;

    if ( (key = ftok (pathname, 0) ) < 0)
    {
        printf ("Can\'t generate key\n");
        exit (-1);
    }
    if ( (semid = semget (key, 1, 0666 | IPC_CREAT) ) < 0)
    {
        printf ("Can\'t get semid\n");
        exit (-1);
    }

    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if (pipe (fd) < 0)
    {
        printf ("Can\'t create pipe\n");
        exit (-1);
    }
    if ( (result = fork() ) < 0)
    {
        printf ("Can\'t fork child\n");
        exit (-1);
    }
    else if (result > 0)
    {
        while (reps > 0)
        {
            size1 = write (fd[1], "first write-read cycle", 23);
            if (size1 != 23)
            {
                printf ("Can\'t write all string\n");
                exit (-1);
            }
        //    printf ("first write\n");

            mybuf.sem_op = 2;
            if (semop (semid, &mybuf, 1) < 0)
            {
                printf ("Can\'t wait for condition\n");
                exit (-1);
            }

            mybuf.sem_op = 0;
            if (semop (semid, &mybuf, 1) < 0)
            {
                printf ("Can\'t wait for condition\n");
                exit (-1);
            }

            size2 = read (fd[0], resstring, 24);
            if (size2 < 0)
            {
                printf ("Can\'t read string\n");
                exit (-1);
            }
        //    printf ("second read\n");

            printf ("%s\n", resstring);
            reps -= 1;
        }

    }
    else
    {
        while (reps > 0)
        {
            mybuf.sem_op = -1;

            if (semop (semid, &mybuf, 1) < 0)
            {
                printf ("Can\'t wait for condition\n");
                exit (-1);
            }

            size1 = read (fd[0], resstring, 23);
            if (size1 < 0)
            {
                printf ("Can\'t read string\n");
                exit (-1);
            }

        //    printf ("first read\n");
            printf ("%s\n", resstring);

            if (semop (semid, &mybuf, 1) < 0)
            {
                printf ("Can\'t wait for condition\n");
                exit (-1);
            }

            size2 = write (fd[1], "second write-read cycle", 24);
            if (size2 != 24)
            {
                printf ("Can\'t write all string\n");
                exit (-1);
            }
        //    printf ("second write\n");
            reps -= 1;
        }

    }

    close (fd[0]);
    close (fd[1]);

    return 0;
}

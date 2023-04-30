#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#define USAGE "Usage: ./2 <SYNC/ASYNC>\n"
#define FILE_SIZE 999

pthread_barrier_t barrier;
bool is_sync;
char *data;

void *thread(void *arg)
{
    pthread_barrier_wait(&barrier);
    memcpy(data, "This is written by thread\n", 25);
    if (is_sync)
    {
        msync(data, FILE_SIZE, MS_SYNC);
    }
    else
    {
        msync(data, FILE_SIZE, MS_ASYNC);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(USAGE);
        return 1;
    }
    if (!strcmp(argv[1], "SYNC"))
    {
        is_sync = true;
    }
    else if (!strcmp(argv[1], "ASYNC"))
    {
        is_sync = false;
    }
    else
    {
        printf(USAGE);
        return 1;
    }

    int fd = open("data", O_RDWR | O_CREAT, 0777);
    lseek(fd, FILE_SIZE, SEEK_SET);
    write(fd, "", 1);

    data = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int n = 2;

    pthread_t threads[n];
    pthread_barrier_init(&barrier, NULL, n);

    for (int i = 0; i < n; i++)
    {
        pthread_create(&threads[i], NULL, thread, NULL);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    munmap(data, FILE_SIZE);
    close(fd);
    return 0;
}
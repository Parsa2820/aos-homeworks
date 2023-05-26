#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define FILE_SIZE 10 * 1L << 30
#define FILE_NAME "file.txt"
#define NUMBER_OF_READS 20

int main()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < NUMBER_OF_READS; i++)
    {
        int fd = open(FILE_NAME, O_DIRECT | O_APPEND | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        ftruncate(fd, FILE_SIZE);
        close(fd);
    }

    gettimeofday(&end, NULL);
    printf("Time taken: %d ms\n", end.tv_usec - start.tv_usec);
    
    return 0;
}
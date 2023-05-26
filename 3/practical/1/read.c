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
    char *buffer = malloc(FILE_SIZE);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < NUMBER_OF_READS; i++)
    {
        int fd = open(FILE_NAME, O_RDONLY | O_DIRECT);
        read(fd, buffer, FILE_SIZE);
        close(fd);
    }

    gettimeofday(&end, NULL);
    printf("Time taken: %d s\n", end.tv_sec - start.tv_sec);
    
    return 0;
}
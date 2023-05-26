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
    int fd = open(FILE_NAME, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ftruncate(fd, FILE_SIZE);

    close(fd);

    char *buffer = malloc(FILE_SIZE);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < NUMBER_OF_READS; i++)
    {
        int fd = open(FILE_NAME, O_RDONLY);
        read(fd, buffer, FILE_SIZE);
        close(fd);
    }

    gettimeofday(&end, NULL);
    printf("Time taken: %d s\n", end.tv_sec - start.tv_sec);
    
    return 0;
}
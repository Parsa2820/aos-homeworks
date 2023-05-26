#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUMBER_OF_FILES 1000
#define USAGE printf("Usage: %s <NOBUFFERCACHE/BUFFERCACHE>\n", argv[0])

char *get_random_name()
{
    char *filename = malloc(15);
    for (int i = 0; i < 10; i++)
    {
        filename[i] = 'a' + rand() % 26;
    }
    filename[10] = '.';
    filename[11] = 't';
    filename[12] = 'x';
    filename[13] = 't';
    return filename;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        USAGE;
        return 1;
    }

    bool buffercache = true;

    if (strcmp(argv[1], "NOBUFFERCACHE") == 0)
    {
        buffercache = false;
    }
    else if (strcmp(argv[1], "BUFFERCACHE") == 0)
    {
        buffercache = true;
    }
    else
    {
        USAGE;
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < NUMBER_OF_FILES; i++)
    {
        int flags = buffercache ? O_CREAT | O_TRUNC : O_DIRECT | O_CREAT | O_TRUNC;
        int fd = open(get_random_name(), flags, S_IRUSR | S_IWUSR);
        lseek(fd, 0, SEEK_SET);
        int id = i;
        write(fd, &id, sizeof(int));
        close(fd);
    }

    gettimeofday(&end, NULL);
    double time_taken = end.tv_usec - start.tv_usec;
    printf("Time taken: %f ms\n", time_taken);
    
    return 0;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/xattr.h>

#define NUMBER_OF_FILES 1000000
#define USAGE printf("Usage: %s <NOBUFFERCACHE/BUFFERCACHE>\n", argv[0])
#define METADATA_KEY "unique_identifier"

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
        int flags = buffercache ? O_WRONLY | O_APPEND | O_CREAT | O_TRUNC : O_WRONLY | O_APPEND | O_CREAT | O_TRUNC | O_DIRECT;
        char *filename = get_random_name();
        int fd = open(filename, flags, S_IRUSR | S_IWUSR);
        char *unique_identifier = malloc(10);
        sprintf(unique_identifier, "%d", i);
        setxattr(filename, METADATA_KEY, unique_identifier, strlen(unique_identifier), 0);
        close(fd);
        free(unique_identifier);
        free(filename);
    }

    gettimeofday(&end, NULL);
    printf("Time taken: %d s\n", end.tv_sec - start.tv_sec);
    
    return 0;
}
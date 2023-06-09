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
#include <sys/xattr.h>

#define NUMBER_OF_FILES 1000000
#define USAGE printf("Usage: %s <NOBUFFERCACHE/BUFFERCACHE>\n", argv[0])
#define METADATA_KEY "unique_identifier"

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

    DIR *dir;
    dir = opendir(".");
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    char *files[NUMBER_OF_FILES];
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            char *dot = strrchr(entry->d_name, '.');
            if (dot && !strcmp(dot, ".txt"))
            {
                char *filename = malloc(strlen(entry->d_name) + 1);
                strcpy(filename, entry->d_name);
                files[i] = filename;
                i++;
            }
        }
    }
    closedir(dir);

    struct timeval start, end;
    char *buffer = malloc(10);
    gettimeofday(&start, NULL);

    for (int i = 0; i < NUMBER_OF_FILES; i++)
    {
        int flags = buffercache ? O_RDONLY : O_RDONLY | O_DIRECT;
        int fd = open(files[i], flags);
        if (fd == -1)
        {
            perror("open");
            return 1;
        }

        fgetxattr(fd, METADATA_KEY, buffer, 10);
        close(fd);
    }

    gettimeofday(&end, NULL);
    free(buffer);
    printf("Time taken: %d s\n", end.tv_sec - start.tv_sec);
    
    return 0;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define USAGE "Usage: ./1 <number of threads>\n"
#define LOOP 100000

pthread_barrier_t barrier;

void *thread(void *arg)
{
    pthread_barrier_wait(&barrier);
    for (int i = 0; i < LOOP; i++)
    {
        madvise(NULL, 0, MADV_DONTNEED);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(USAGE);
        return 1;
    }

    int n = atoi(argv[1]);
    int cores = sysconf(_SC_NPROCESSORS_ONLN);

    if (n > cores - 1)
    {
        printf("Number of threads must be less than number of cores - 1\n");
        return 1;
    }

    pthread_t threads[n];
    pthread_attr_t attr;
    cpu_set_t cpus;
    pthread_attr_init(&attr);
    pthread_barrier_init(&barrier, NULL, n);

    for (int i = 0; i < n; i++)
    {
        CPU_ZERO(&cpus);
        CPU_SET(i + 1, &cpus);
        pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpus);
        pthread_create(&threads[i], &attr, thread, NULL);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}
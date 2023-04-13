#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>

#define USAGE "Usage: ./1.1 alef|be|jim\n"
#define MAX_SIZE 1024

char *exchanged;
pthread_barrier_t barrier;

void *thread_a(void *arg)
{
    exchanged = mmap(NULL, MAX_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	strcpy(exchanged, "exchanged first");
}

void *thread_b(void *arg)
{
    pthread_barrier_wait(&barrier);
    exchanged = mmap(NULL, MAX_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	strcpy(exchanged, "exchanged second");
}

void *thread_b_alt(void *arg)
{
    pthread_barrier_wait(&barrier);
	munmap(exchanged, MAX_SIZE);
}

void *thread_c_alef(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_b: reading shared memory\n");
	printf("thread_b: %s\n", exchanged);
	printf("thread_b: read shared memory\n");
}

void *thread_d_alef(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_d: reading shared memory\n");
	printf("thread_d: %s\n", exchanged);
	printf("thread_d: read shared memory\n");
}

void *(*thread_c_be)(void *) = thread_c_alef;

void *thread_d_be(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_b: writing to shared memory\n");
	strcpy(exchanged, "thread b was here");
	printf("thread_b: wrote to shared memory\n");
}

void *thread_c_jim(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_c: writing to shared memory\n");
	strcpy(exchanged, "thread b was here");
	printf("thread_c: wrote to shared memory\n");
}

void *(*thread_d_jim)(void *) = thread_d_be;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf(USAGE);
		return 1;
	}

	void *(*thread_c)(void *);
	void *(*thread_d)(void *);

	if (strcmp(argv[1], "alef") == 0)
	{
		thread_c = thread_c_alef;
		thread_d = thread_d_alef;
	}
	else if (strcmp(argv[1], "be") == 0)
	{
		thread_c = thread_c_be;
		thread_d = thread_d_be;
	}
	else if (strcmp(argv[1], "jim") == 0)
	{
		thread_c = thread_c_jim;
		thread_d = thread_d_jim;
	}
	else
	{
		printf(USAGE);
		return 1;
	}

    pthread_barrier_init(&barrier, NULL, 3);
	pthread_t a, b, c, d;

	pthread_create(&a, NULL, thread_a, NULL);
	pthread_join(a, NULL);
#ifdef ALT
	pthread_create(&b, NULL, thread_b_alt, NULL);
#else
	pthread_create(&b, NULL, thread_b, NULL);
#endif
	pthread_create(&c, NULL, thread_c, NULL);
	pthread_create(&d, NULL, thread_d, NULL);

	pthread_join(b, NULL);
	pthread_join(c, NULL);
	pthread_join(d, NULL);
    pthread_barrier_destroy(&barrier);

	return 0;
}

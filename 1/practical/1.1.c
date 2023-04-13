#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>

#define USAGE "Usage: ./1.1 alef|be|jim\n"
// mprotect should not be used with malloc
// according to https://stackoverflow.com/questions/15775178/protecting-allocated-memory
// and https://chicken-hackers.nongnu.narkive.com/w3ylemQ9/mprotect-on-malloc-ed-memory
#define malloc(size) mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)

char *shared;
pthread_barrier_t barrier;

void *thread_a(void *arg)
{
	printf("thread_a: allocating %dB memory\n", PAGE_SIZE);
	shared = malloc(PAGE_SIZE);
	strcpy(shared, "hello world");
	printf("thread_a: allocated %dB memory\n", PAGE_SIZE);
}

void *thread_b(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_b: protecting shared pointer from read\n");
	mprotect(shared, PAGE_SIZE, PROT_READ);
	printf("thread_b: protected shared pointer from read\n");
}

void *thread_c_alef(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_c: reading shared pointer\n");
	printf("thread_c: %s\n", shared);
	printf("thread_c: read shared pointer\n");
}

void *thread_d_alef(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_d: reading shared pointer\n");
	printf("thread_d: %s\n", shared);
	printf("thread_d: read shared pointer\n");
}

void *(*thread_c_be)(void *) = thread_c_alef;

void *thread_d_be(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_d: writing to shared pointer\n");
	strcpy(shared, "thread_d was here");
	printf("thread_d: wrote to shared pointer\n");
}

void *thread_c_jim(void *arg)
{
    pthread_barrier_wait(&barrier);
	printf("thread_c: writing to shared pointer\n");
	strcpy(shared, "thread_c was here");
	printf("thread_c: wrote to shared pointer\n");
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
	pthread_create(&b, NULL, thread_b, NULL);
	pthread_create(&c, NULL, thread_c, NULL);
	pthread_create(&d, NULL, thread_d, NULL);

	pthread_join(b, NULL);
	pthread_join(c, NULL);
	pthread_join(d, NULL);
    pthread_barrier_destroy(&barrier);

	return 0;
}

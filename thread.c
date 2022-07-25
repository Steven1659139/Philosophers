#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void *fonction()
{
	printf("pid du thread fils = %d\n", (int) getpid());

	while (1);
	return NULL;	
}

int main(void)
{
	pthread_t thread;

	printf("pid de main = %d\n", (int) getpid());
	pthread_create(&thread, NULL, &fonction, NULL);
	while (1);

	return (0);
}
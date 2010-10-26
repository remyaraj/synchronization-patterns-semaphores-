/*rendezvous problem
	thread1					thread2
	statement a1				statement b1
	statement a2				statement b2
          The problem is such that a1 happens before b2 and b1 happens before a2*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t flaga;
sem_t flagb;

void * fun1(void * s)
{
	printf("Message :%s\n",(char *)s);
	sem_post(&flaga);
	sem_wait(&flagb);
	printf("After message....%s\n",(char *)s);
}

void * fun2(void *s)
{
	printf("Message:%s\n",(char *)s);
	sem_post(&flagb);
	sem_wait(&flaga);
	printf("After message.........%s\n",(char *)s);
}

main()
{
	pthread_t t1,t2;
	sem_init(&flaga,0,0);
	sem_init(&flagb,0,0);
	pthread_create(&t1,0,fun1,"thread1");
	pthread_create(&t2,0,fun2,"thread2");

	pthread_join(t1,0);
	pthread_join(t2,0);
}

/*barrier problem : rendezvous
                    critical point
No thread executes critical point until after all threads have executed rendezvous. This handles rendezvous problem where the no:of threads are more than 2*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
sem_t barrier;

int count;
int n=4;

void * fun1(void * s)
{
	printf("Message :%s\n",(char *)s);
	
	sem_wait(&mutex);
	count=count + 1;
	sem_post(&mutex);

	if(count==n)
		sem_post(&barrier);
	sem_wait(&barrier);
	sem_post(&barrier);           // turnstile: a wait and a post occurs in                                                               rapid succession
	
	printf("After sleep..:%s\n",(char *)s);

	
}

void * fun2(void *s)
{
	printf("Message:%s\n",(char *)s);

        sem_wait(&mutex);
        count=count + 1;
        sem_post(&mutex);

        if(count==n)
                sem_post(&barrier);
        sem_wait(&barrier);
        sem_post(&barrier);

        printf("After sleep..:%s\n",(char *)s);

}




main()
{
	pthread_t t1,t2,t3,t4;
	sem_init(&mutex,0,1);
	sem_init(&barrier,0,0);
	pthread_create(&t1,0,fun1,"thread1");
	pthread_create(&t2,0,fun2,"thread2");
        pthread_create(&t3,0,fun1,"thread1again");
        pthread_create(&t4,0,fun2,"thread2again");


	pthread_join(t1,0);
	pthread_join(t2,0);
        pthread_join(t3,0);
        pthread_join(t4,0);

}

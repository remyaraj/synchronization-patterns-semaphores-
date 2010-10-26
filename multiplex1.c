/* multiplex problem : here the sem_t variable is initialized to the no:of threads that should be executed parallely executed.*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t flag;
int count;

void * fun1(void * s)
{
	sem_wait(&flag);                                 
	printf("count in fun1= %d\n",count);
	sleep(3);
	count = count+1;
	printf("count in fun1 after wait:%d\n",count); 
	sem_post(&flag);
}

void * fun2(void * s)
{
        sem_wait(&flag);
        printf("count in fun2= %d\n",count);
	sleep(3);
        count = count+1;
        printf("count in fun2 after wait:%d\n",count);
        sem_post(&flag);
}

void * fun3(void * s)
{
        sem_wait(&flag);
        printf("count in fun3= %d\n",count);
	sleep(3);
        count = count+1;
        printf("count in fun3 after wait:%d\n",count);
        sem_post(&flag);
}


main()
{
	pthread_t t1,t2,t3,t4;
	sem_init(&flag,0,3);
	
	pthread_create(&t1,0,fun1,0);
	pthread_create(&t2,0,fun1,0);
	pthread_create(&t3,0,fun2,0);
	pthread_create(&t4,0,fun3,0);

	pthread_join(t1,0);
	pthread_join(t2,0);
	pthread_join(t3,0);
	pthread_join(t4,0);
}

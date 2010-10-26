/* mutex problem: to enforce mutual exclusion. only one thread is executed at a time or it is locked for some statements in the thread where global variables are dealt with*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t flag;                 // flag is maintained only in 2 states.
int count;

void * fun1(void * s)
{
	int i;
	printf("count in fun1= %d\n",count);
	for(i=0;i<10;i++){
	sem_wait(&flag);                                 
	count = count+1;
	printf("count in fun1 after wait:%d\n",count); 
	sem_post(&flag);
	}
}


main()
{
	pthread_t t1,t2;
	sem_init(&flag,0,1);
	
	pthread_create(&t1,0,fun1,0);
	pthread_create(&t2,0,fun1,0);

	pthread_join(t1,0);
	pthread_join(t2,0);
	printf("The final value of count is %d\n",count);
}

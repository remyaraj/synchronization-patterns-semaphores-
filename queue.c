/*queue pattern: 2 kinds of dancers-leaders and followers,wait in two queues. leader arrives it checks whether a follower is waiting. if so it proceeds else it waits*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t leaderq;
sem_t followerq;


void * leader(void *p)
{
	printf("the leader\n");
	sem_post(&followerq);
	sem_wait(&leaderq);
	printf("Leader dance : %s\n",(char *)p);
}

void * follower(void * p)
{
	printf("the follower\n");
	sem_post(&leaderq);
	sem_wait(&followerq);
	printf("The follower dance: %s\n",(char *)p);
}


main()
{
	pthread_t t1,t2,t3;
	sem_init(&leaderq,0,0);
	sem_init(&followerq,0,0);

	pthread_create(&t1,0,leader,"me");
	pthread_create(&t2,0,follower,"you");

	pthread_join(t1,0);
	pthread_join(t2,0);
}

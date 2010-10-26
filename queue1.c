/* exclusive queue */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t leaderq;
sem_t followerq;
sem_t mutex;
sem_t rendezvous;

int followers,leaders;

void * leader(void *p)
{
	printf("the leader\n");
	sem_wait(&mutex);
	if(followers>0){
		followers--;
		sem_post(&followerq);
	}
	else{
		leaders++;
		sem_post(&mutex);
		sem_wait(&leaderq);
	}
	printf("Leader dance : %s\n",(char *)p);
	sem_wait(&rendezvous);
	sem_post(&mutex);
}

void * follower(void * p)
{
	printf("the follower\n");
	sem_wait(&mutex);
	if(leaders>0){
		leaders--;
		sem_post(&leaderq);
	}
	else{
		followers++;
		sem_post(&mutex);
		sem_wait(&followerq);
	}
	printf("The follower dance: %s\n",(char *)p);
	sem_post(&rendezvous);
}


main()
{
	pthread_t t1,t2,t3,t4;
	sem_init(&leaderq,0,0);
	sem_init(&followerq,0,0);
	sem_init(&mutex,0,1);
	sem_init(&rendezvous,0,0);


	pthread_create(&t1,0,leader,"me");
	pthread_create(&t2,0,follower,"you");
        pthread_create(&t3,0,leader,"last");
        pthread_create(&t4,0,follower,"you1");



	pthread_join(t1,0);
	pthread_join(t2,0);
        pthread_join(t3,0);
        pthread_join(t4,0);

}

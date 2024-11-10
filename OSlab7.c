#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t r,w;
int rcount=0;

void *reader (void *arg)
{
	sem_wait(&r);
	rcount++;
	if(rcount==1)
	{
		sem_wait(&w);
	}
	sem_post(&r);
	
	printf("Reader is Reading \n");
	
	sem_wait(&r);
	rcount--;
	if(rcount==0)
	{
		sem_post(&w);
	}
	sem_post(&r);
	
	return NULL;
}

void *writer (void *arg)
{
	sem_wait(&w);
	printf("Writer is Writing");
	sem_post(&w);
	return NULL;
}

void main()
{
	pthread_t Rtid[5];
	pthread_t Wtid[5];
	int i;
	
	sem_init(&r,0,1);
	sem_init(&w,0,1);
	
	for(i=0;i<5;i++)
	{
		pthread_create(&Rtid[i],NULL,reader,NULL);
		pthread_create(&Wtid[i],NULL,writer,NULL);
	}
	
	for(i=0;i<5;i++)
	{
		pthread_join(Rtid[i],NULL);
		pthread_join(Wtid[i],NULL);
	}	

    sem_destroy(&r);
    sem_destroy(&w);

}

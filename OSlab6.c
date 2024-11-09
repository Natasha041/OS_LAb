#include<stdlib.h>
#include<unistd.h>
#inslude<semaphore.h>
#include<pthread.h>

sem_t e,f,s;
int data[5] , in=0 , out=0 ;

void *producer(void *args)
{
   sem_wait(&e);
   sem_wait(&s);
   data[in]=rand();
   in=(in+1)%5;
   sem_post(&s);
   sem_post(&f);
   printf("Producer Executed \n");
}

void *consumer(void *args)
{
 int val;
 do
	{
		sem_wait(&f);
		sem_wait(&s);
		val=data[out];
		printf("Consumer Executed \n ");
		out=(out+1)%5;
		sem_post(&s);
		sem_post(&e);
		sem_getvalue(&e,&val);
	}While(val!=5);
}

void main()
{
	ptherad_t tid[10],c;
	int i,j;
	sem_init(&f,0,0);
	sem_init(&e,0,5);
	sem_init(&s,0,1);
	
	pthread_create(&c,NULL,consumer,NULL);
	for(i=0;i<5;i++)
	{
		pthread_create(&tid[i],NULL,producer,NULL);
	}
	pthraed_join(c,NULL);
	for(i=0;i<5;i++)
	{
		pthraed_join(tid[i],NULL);
	}
}

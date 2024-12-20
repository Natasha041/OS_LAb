//OS_LAB_3 (Process Call System Control (Fork))
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void asc_sort(int a[30],int n)
{
    int i,j,temp;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {  
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("Ascending Order :- \n ");
    
    for(i=0;i<n;i++)
    {
        printf("\t %d",a[i]);
    }
    printf("\n");
}

void desc_sort(int a[30] , int n)
{
    int i,j,temp;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(a[j]<a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("Descending Order :- \n");
    for(i=0;i<n;i++)
    {
        printf("\t %d",a[i]);
    }
    printf("\n");
}

int main()
{
    int a[30],n,i;
    printf("Enter size of array you want to be sorted :- \n");
    scanf("%d",&n);
    
    for(i=0;i<n;i++)
    {
        printf("Enter the %dth element of the array :- \n",i+1);
        scanf("%d",&a[i]);
    }
    
    if(fork==0)
    {
        printf("Child Process Id :- %d \n",getpid());
        desc_sort(a,n);
    }
    else
    {
        printf("Parent Process Id :- %d \n",getppid());
        asc_sort(a,n);
    }
    return 0;
}


//Orphan
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void main()
{
	pid_t pid,temp;
	pid=fork();
	if(pid==0)
	{
		sleep(3);
		temp=getpid();
		printf("\nChild Process ID: %d\n",temp);
		temp=getppid();
		printf("Child Parent Process ID: %d\n",temp);
		printf("Child Child Process ID: %d\n",pid);
		system("ps");
	}
	else
	{
		temp=getpid();
		printf("Parent Process ID: %d\n",temp);
		temp=getppid();
		printf("Parent Parent Process ID: %d\n",temp);
		printf("Parent Child Process ID: %d\n",pid);	
	}
}

//zombie 
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void main()
{
	int status;
	pid_t pid,temp;
	pid=fork();
	if(pid==0)
	{
		temp=getpid();
		printf("Child Process ID: %d\n",temp);
		temp=getppid();
		printf("Child Parent Process ID: %d\n",temp);
		printf("Child Child Process ID: %d\n",pid);
	}
	else
	{
		system("ps");
		wait(&status);
		temp=getpid();
		printf("Parent Process ID: %d\n",temp);
		temp=getppid();
		printf("Parent Parent Process ID: %d\n",temp);
		printf("Parent Child Process ID: %d\n",pid);	
	}
}

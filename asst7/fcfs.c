//fcfs
#include <stdio.h>

int seektime=0;

int main()
{
    int head,schedule[100],diff=0,n,i,d;
    printf("enter the position of head:");
    scanf("%d",&head);
    printf("enter the number of seeks:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter the track you want to go to:");
        scanf("%d",&d);
        schedule[i]=d;
        diff=head-schedule[i];
        if (diff<0)
            diff=schedule[i]-head;
        printf("%d\n",diff);
        head=schedule[i];
        seektime=seektime+diff;
    }
    printf("seek time=%d\n",seektime);
}















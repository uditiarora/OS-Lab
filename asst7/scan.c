//scan

#include <stdio.h>

int seektime=0;
int head=0;
int end=200;

int scheduleb1[100];
int scheduleb2[100];

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

int main()
{
    int i,d,n,j,diff;
    printf("enter the number of seeks:");
    scanf("%d",&n);
    for (i=0;i<n/2;i++)
    {
        printf("enter the track you want to go to:");
        scanf("%d",&d);
        scheduleb1[i]=d;
    }
    
    for (i=0;i<n/2;i++)
    {
        printf("enter the track you want to go to:");
        scanf("%d",&d);
        scheduleb2[i]=d;
    }
    
    //bubblesort -ascending
    for (i=0;i<(n/2)-1;i++)
    {
        for (j=0;j<(n/2)-i-1;j++)
        {
            //printf("hi\n");
            if (scheduleb1[j]>scheduleb1[j+1])
            {
                
                int temp=scheduleb1[j];
                scheduleb1[j]=scheduleb1[j+1];
                scheduleb1[j+1]=temp;
                //printf("as sort%d %d\n",scheduleb1[j],scheduleb1[j+1]);
            }
        }
    }
    for (i=0;i<n/2;i++)
    {
        printf("%d ",scheduleb1[i]);
    }
    printf("\n");
    //bubblesort -descending
    for (i=0;i<(n/2)-1;i++)
    {
        for (j=0;j<(n/2)-i-1;j++)
        {
            //printf("hi\n");
            if (scheduleb2[j]<scheduleb2[j+1])
            {
                
                int temp=scheduleb2[j];
                scheduleb2[j]=scheduleb2[j+1];
                scheduleb2[j+1]=temp;
                //printf("de sort%d %d\n",scheduleb2[j],scheduleb2[j+1]);
            }
        }
    }
    for (i=0;i<n/2;i++)
    {
        printf("%d ",scheduleb2[i]);
    }
    printf("\n");
    //scan
    for (i=0;i<n/2;i++)
    {
        diff=head-scheduleb1[i];
        if (diff<0)
            diff=scheduleb1[i]-head;
        printf("%d\n",diff);
        head=scheduleb1[i];
        seektime=seektime+diff;
    }
    seektime=seektime+(end-head);
    head=end;
    for (i=0;i<n/2;i++)
    {
        diff=head-scheduleb2[i];
        if (diff<0)
            diff=scheduleb2[i]-head;
        printf("%d\n",diff);
        head=scheduleb2[i];
        seektime=seektime+diff;
    }
    seektime=seektime+head;
    printf("seek time=%d\n",seektime);
}

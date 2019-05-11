#include<stdio.h>
void main(){
	int n,start=0,end=0,size=0,vpn;
	printf("Enter the size of the queue for FIFO.\n");
	scanf("%d",&n);
	int arr[n];
	float hit_ratio = 0;
	int hits=0,misses=0;
	while(1){
		printf("Enter virtual page number\n");
		scanf("%d",&vpn);
		int i = 0,flag = 0;
		for(i=0;i<n;i++){
			if(arr[i] == vpn){
				printf("Hit\n");
				hits++;
				flag = 1;
			}
		}
		if(flag!=1){
			printf("Miss\n");
			misses++;
			int temp = arr[start];
			arr[end] = vpn;
			end = (end+1)%n;
			if(size > n){
				start = (start+1)%n;
				printf("Page Replaced = %d",temp);
			}
		}
		hit_ratio = (float)(hits)/(hits+misses);
		printf("Hit ratio till now: %f \n",hit_ratio);
		
	}
	
}

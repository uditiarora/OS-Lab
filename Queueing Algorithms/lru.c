#include<stdio.h>
void main(){
	int n,size=0,vpn,t=0;
	printf("Enter the size of the queue for LRU.\n");
	scanf("%d",&n);
	int arr[n];
	int time[n];
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
				time[i] = ++t;
				break;
			}
		}
		if(flag!=1){
			printf("Miss\n");
			misses++;
			
			if(size > n){
				
				int index=0,min = 10000;
				for(i=0;i<n;i++){
					if(time[i]<min){
						min = time[i];
						index = i;
					
					}
				}
				int temp = arr[index];
				arr[index] = vpn;
				time[index] = ++t;
				printf("Page Replaced = %d\n",temp);
			}
			else{
				arr[size] = vpn;
				time[size] = ++t;
				
			}
		}
		size++;
		hit_ratio = (float)(hits)/(hits+misses);
		printf("Hit ratio till now: %f \n",hit_ratio);
		int ij=0;
		for(ij=0;ij<n;ij++){
			printf("%d ",arr[ij]);
		}
		printf("\n");
	}
	
}

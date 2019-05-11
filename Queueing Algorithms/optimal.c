#include<stdio.h>

int main(){
	printf("Enter size of the queue\n");
	int n,i=0,hits=0,misses=0,m;
	scanf("%d",&n);
	int queue[n];
	for(int i=0;i<n;i++){
		queue[i] = 0;
	}
	int time[n];
	printf("Enter number of pages\n");
	scanf("%d",&m);
	int arr[m];
	int ab =0;
	printf("Enter pages");
	for(i=0;i<m;i++){
		scanf("%d",&arr[i]);
	
	}
	for(i=0;i<m;i++){
		int j = 0,flag=0;
		for(j=0;j<n;j++){
			if(arr[i] == queue[j]){
				flag=1;
				break;
			}
		}
		if(flag==1){
			printf("Hit\n");
			hits++;
		}
		else if(ab<n){
			misses++;
			printf("Miss\n");
			queue[ab] = arr[i];
			ab++;
		}
		else{
			misses++;
			printf("Miss\n");
			int index = 0,max = 0;
			int k = 0;
			for(j=0;j<n;j++){
				time[j] = 10000;
				for(k=i+1;k<i+6 && k<m;k++){
					if(arr[k] == queue[j]){
						if(time[j] > k){
							time[j] = k;
						}
					}
				}
			}
			for(j=0;j<n;j++){
				if(max<time[j]){
					max = time[j];
					index = j;
				}
			}
			printf("Page Replaced = %d\n",queue[index]);
			queue[index] = arr[i]; 
			
		}
		for(j=0;j<n;j++){
			printf("%d ",queue[j]);
		}
		printf("\n");
	}
	float temp = (float)hits/(hits+misses);
	printf("Hit ratio = %f\n",temp);
	return 0;
}

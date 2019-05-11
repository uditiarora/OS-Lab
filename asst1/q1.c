
#include <stdlib.h>
#include <stdio.h>
#include<dirent.h>
#include<string.h>
struct QNode
{
    char *key;
    struct QNode *next;
};
 

struct Queue
{
    struct QNode *front, *rear;
};
 

struct QNode* newNode(char* k)
{
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp; 
}
 

struct Queue *createQueue()
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
 

void enQueue(struct Queue *q, char* k)
{
    
    struct QNode *temp = newNode(k);
 
    
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
 
   
    q->rear->next = temp;
    q->rear = temp;
}
 

 char* deQueue(struct Queue *q)
{
    
    if (q->front == NULL)
       return NULL;
 
    
    struct QNode *temp = q->front;
    q->front = q->front->next;
 
   
    if (q->front == NULL)
       q->rear = NULL;
    return temp->key;
}
  char* poll(struct Queue *q)
{
    
    if (q->front == NULL)
       return NULL;
 
    
    struct QNode *temp=q->front;
    return temp->key;
}



void bfs(char* startDir){
	struct Queue *q = createQueue();
	struct Queue *q2 = createQueue();
	struct Queue *q3 = createQueue();
	enQueue(q,startDir);
	enQueue(q2,"");
	enQueue(q3,"");
	struct dirent* de;
	
	while(poll(q)!=NULL){
		char* currDir = deQueue(q);
		//printf("%s\n",currDir);
		DIR *dr = opendir(currDir);
		char* prefix = deQueue(q2);
		char* spaces = deQueue(q3);
		if(dr != NULL){
			while((de = readdir(dr)) != NULL){
				printf("%s%s\n",spaces,de->d_name);
				if(strcmp(de->d_name,".") !=0 && strcmp(de->d_name,"..")!=0){
					char* temp = (char*)malloc(strlen(de->d_name) + strlen(currDir)+2);
					strcpy(temp,currDir);
					strcat(temp,"/");
					strcat(temp,de->d_name);
					enQueue(q,temp);	
					char* temp2 = (char*)malloc(strlen("\t") + strlen(spaces)+1);
					strcpy(temp2,spaces);
					strcat(temp2,"\t"); 
					enQueue(q3,temp2);
				}
			}
		} 
	}
}


void dfs(char* startDir,char* spaces,char* dir){
	char *str = (char*)malloc(strlen(dir) + strlen(startDir)+1);
	strcpy(str,dir);
	strcat(str,startDir);
	//printf("%s\n",str);
	DIR* dr = opendir(str);
	struct dirent* de;
	if(dr != NULL){
		while((de = readdir(dr)) != NULL){
			printf("%s%s\n",spaces,de->d_name);
				if(strcmp(de->d_name,".") !=0 && strcmp(de->d_name,"..")!=0){
					char* temp = (char*)malloc(strlen(dir)+strlen(startDir)+2);
					strcpy(temp,dir);
					strcat(temp,startDir);
					strcat(temp,"/");
					char* temp2 = (char*)malloc(strlen("\t") + strlen(spaces)+1);
					strcpy(temp2,spaces);
					strcat(temp2,"\t"); 
					dfs(de->d_name,temp2,temp);
				}
		}
	}
}


int main(int argc,char *argv[]){
	if(strcmp("-b",argv[1])==0)
		bfs(argv[2]);
	else if(strcmp("-d",argv[1])==0)
		dfs(argv[2],"","");
	return 0;

}

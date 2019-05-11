#include <stdio.h> 
#include <sys/wait.h> 
#include <unistd.h> 
int main() 
{ 
    
    pid_t id1 = fork(); 
    pid_t id2 = fork(); 
    pid_t id3 = fork();
    //pid_t id4 = fork();
    if (id1 > 0 && id2 > 0 && id3>0) { 
         
        printf("Parent: %i\n",getpid()); 
	wait(NULL);
    } 
  
    
    else if (id1 == 0 && id2 > 0 && id3>0) { 
  
        
       //sleep(2);
         
        printf("Child 1: %i\n",getpid()); 
	wait(NULL);
    } 
  
    
    else if (id1 > 0 && id2 == 0 && id3>0) { 
        
        //sleep(2);
	
        printf("Child 2: %i\n",getpid());
	wait(NULL);
    } 
    else if(id1>0 && id2>0 && id3==0){
	printf("Child 3 :%i\n",getpid());
	wait(NULL);
    }
    
    else { 
	//sleep(4);
        printf("Child of process with pid: %i\n",getppid()); 
    } 
  
    return 0; 
} 

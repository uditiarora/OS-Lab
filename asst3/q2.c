#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
    int fd[2],fd2[2],nbytes,nbytes2;
    pid_t childpid;
    char string[100];
    char readbuffer[100],readbuffer2[100];
    char newString[100];
    FILE *fp;

    pipe(fd);
    pipe(fd2);
    char var[100];

    if ((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (childpid != 0) {
	int i = 0;
        printf("PID of parent %u\n", getpid());
        
        close(fd[0]);
        fp = fopen("test.txt", "r");

	char ch = fgetc(fp);
        while (ch  != EOF && ch!='\n') {
            var[i] = ch;
            i++;
            ch = fgetc(fp);
        }
	var[i] = '\0';
        write(fd[1], var, (strlen(var) + 1));
        close(fd[1]);
      

#if 1
        waitpid(childpid,NULL,0);
#endif
    }

    else {
      
        
        pid_t childpid2;
        
        if((childpid2 = fork())==-1){
        	perror("fork");
        	exit(1);
        
        }
       
         if (childpid2 != 0) {
		  printf("PID of child %u\n", getpid());


		close(fd[1]);

		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %s\n", readbuffer);

		int k = 0,l=0;
		int n = strlen(readbuffer);
		int i = 0;
		for(i=0;i<n;i++){
			newString[k] = readbuffer[i];
			k++;
			if(readbuffer[i] == ' '){
				while(readbuffer[i]==' '){
					i++;
				}
			
				if(readbuffer[i] == '.' || readbuffer[i] == '!' || readbuffer[i] == '?' || readbuffer[i] == ','){
					k--;
				}
				i--;
			}
		
		
		}
		newString[k] = '\0';
		printf("New String : %s\n",newString);
		close(fd[0]);
			
			

			
			close(fd2[0]);
			
			write(fd2[1], newString, (strlen(newString) + 1));
			close(fd2[1]);
		      

		#if 1
			waitpid(childpid2,NULL,0);
		#endif
    	}
    	else{
    	
    		//sleep(4);
   		  printf("PID of grandchild %u\n", getpid());
    		close(fd2[1]);

		nbytes2 = read(fd2[0], readbuffer2, sizeof(readbuffer2));
		printf("Received string by grandchild: %s\n", readbuffer2);
		close(fd2[0]);
		
		char final[100];
		int n1 = strlen(readbuffer2);
		int l = 0;
		int i = 0;
		for(i=0;i<n1;i++){
			int temp = (int)readbuffer2[i];
			if(i==0){
				temp = (int)readbuffer2[i];
				if(temp>=97 && temp<=122){
					final[l++] = (char)(temp-32);
				}
				else{
					final[l++] = readbuffer2[i];
				}
				
			}
			else if(readbuffer2[i] == ' ' && i<n1-1){
				final[l++] = readbuffer2[i];
				i++;
				temp = (int)readbuffer2[i];
				if(temp>=97 && temp<=122){
					final[l++] = (char)(temp-32);
				}
				else{
					final[l++] = readbuffer2[i];
				}
							
			}
			else{
				if(temp>=65 && temp<=90){
					final[l++] = (char)(temp+32);
				}
				else{
					final[l++] = readbuffer2[i];
				}
			}
		}
		final[l] = '\0';
		printf("Final Answer: %s\n",final);
		
    	
    	}
        
        
        
        
    }

    return (0);
}

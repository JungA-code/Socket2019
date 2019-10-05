#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

#define PORT 10000
#define BUFSIZE 100

char buffer[100];
char rcvBuffer[100];
char sendBuffer[100];

int main(){
	
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	
	s_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	if(bind(s_socket,(struct sockaddr *) &s_addr, sizeof(s_addr)) == -1){
		printf("Cannot Bind\n");
		return -1;
	}

	if(listen(s_socket, 5) == -1){
		printf("Listen Fail\n");
		return -1;
	}

	len = sizeof(c_addr);
	printf("Waiting for Client ... \n");
	c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len);
	printf("Client is connected!\n");

			n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
			printf("%s\n", rcvBuffer);


			if(strncasecmp(rcvBuffer, "strlen", 6) == 0){
				printf("len : %d\n", strlen(rcvBuffer) - 8);
				write(c_socket, rcvBuffer, n);			
			}
	
			if(strncasecmp(rcvBuffer, "strcmp", 6) == 0){
				   char* temp = strtok(rcvBuffer, " ");
                  char *str1 = malloc(sizeof(char) * 30);
                  char *str2 = malloc(sizeof(char) * 30);
                  char *str3 = malloc(sizeof(char) * 30);
                   int cnt = 0;
                  while(temp != NULL && cnt < 2){
                     if(cnt == 0){
					  temp =  strtok(NULL, " ");
                    strcpy(str1, temp);
               		printf("str 1 > %s\n", str1);		
				      } //if cnt=0end 
                     if(cnt == 1){ 
                     temp =  strtok(NULL, " ");
						int i = strlen(temp);
					  temp[i - 1] = '\0';
                      strcpy(str2, temp);  
					   printf("str 2 > %s\n",str2); 
					
               				      }
                  cnt += 1;
               }
            printf("str1 : %s size : %d compare str2 : %s size : %d \n",str1,strlen(str1),str2,strlen(str2));
            printf("return %d\n",strcmp(str1,str2));
				} //end if
	

	close(c_socket);
	close(s_socket);

}

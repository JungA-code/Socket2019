#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 10000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100


int main(){
	int c_socket;
	struct sockaddr_in c_addr;
	int n;
	char rcvBuffer[BUFSIZE];
	char sendBuffer[BUFSIZE] = " WHAT YOUR NAME? \n";
	char sendBuffer2[BUFSIZE] = " HOW OLD ARE YOU? \n";
	

	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	if(connect(c_socket, (struct sockaddr *)&c_addr, sizeof(c_addr)) == -1){
		printf("Cannot Connect\n");
		close(c_socket);	
		return -1;
	}

	int cnt=0;
	while(cnt<2){
		
			write(c_socket, sendBuffer, strlen(sendBuffer));

			n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
			if(n < 0) {	printf("Buffer1 Read Fail\n"); return -1; }	
			
			rcvBuffer[n] = '\0';
			printf("Server : %s\n", rcvBuffer);
			cnt += 1;
		
			write(c_socket, sendBuffer2, strlen(sendBuffer2));
		
			n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
			if(n < 0)	{	printf("Buffer2 Read Fail\n"); return -1; }	
	
			rcvBuffer[n] = '\0';
			printf("Server : %s\n", rcvBuffer);
			cnt += 1;
			}
	
	close(c_socket);	

	return 0;
}

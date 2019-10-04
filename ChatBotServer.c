#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 10000
#define BUFSIZE 100

char buffer[100] = "Hello, I'm Server. Nice to meet you\n";

int main(){
	
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	
	int len;
	char rcvBuffer[BUFSIZE];
	int n;
	int s;

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

	while(1){
	len = sizeof(c_addr);
	printf("Waiting for Client ... \n");
	c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len);
	printf("Client is connected!\n");

	
	n = strlen(buffer);
	write(c_socket, buffer, n);


	s = read(c_socket,	rcvBuffer, sizeof(rcvBuffer));
	if(s < 0){
		printf("Read Fail\n");
	return -1;
	}

	printf("%s\n",rcvBuffer);

	close(c_socket);
	
	return 0;
	}
	
	close(s_socket);
	return 0;
}

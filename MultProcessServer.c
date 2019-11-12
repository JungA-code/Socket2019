#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define PORT 10000

void do_service(int c_socket);
void sig_handler(int signo);

char buffer[100] = "Hi, I'm server.\n"; // 클라이언트에게 보낼 메시지를 저장
char rcvBuffer[100]; //클라이언트가 보낸 메시지를 저장
int numClient=0; 

int main(){
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	
	signal(SIGCHLD, sig_handler); // param1 : 시그널 번호,  param2 : 첫번째 인자의 시그널이 발생했을때 실행되는 함수

	// 1. 서버 소켓 생성
	//서버 소켓 = 클라이언트의 접속 요청을 처리(허용)해 주기 위한 소켓
	s_socket = socket(PF_INET, SOCK_STREAM, 0); //TCP/IP 통신을 위한 서버 소켓 생성
	
	//2. 서버 소켓 주소 설정
	memset(&s_addr, 0, sizeof(s_addr)); //s_addr의 값을 모두 0으로  초기화
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP 주소 설정
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	//3. 서버 소켓바인딩
	if(bind(s_socket,(struct sockaddr *) &s_addr, sizeof(s_addr)) == -1){ 
		//바인딩 작업 실패 시, Cannot Bind 메시지 출력 후 프로그램 종료
		printf("Cannot Bind\n");
		return -1;
	}
	
	//4.listen() 함수 실행
	if(listen(s_socket, 5) == -1){
		printf("listen Fail\n");
		return -1;
	}

	//5. 클라이언트 요청 처리
	// 요청을 허용한 후, Hello World 메세지를 전송함
	while(1){ //무한 루프
		len = sizeof(c_addr);
		printf("클라이언트 접속을 기다리는 중....\n");
		c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len); 
		//클라이언트의 요청이 오면 허용(accept)해 주고, 해당 클라이언트와 통신할 수 있도록 클라이언트 소켓(c_socket)을 반환함.
		printf("/client is connected\n");
		numClient++;
		printf("%d번째 클라이언트 접속 허용\n",numClient);
		
		int pid = fork();
				if(pid > 0){
			      	  continue;
				}
				else if(pid == 0){
    				do_service(c_socket);
					
    				exit(0);
				}else{
   				 printf("fork failed\n");
  				 exit(0);
				}	
	}
	close(s_socket);
	return 0;	
}

void do_service(c_socket){
	int n;
	while(1){ //메시지 주고받기 무한루프
			n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
			printf("rcvBuffer: %s\n", rcvBuffer);
			if(strncasecmp(rcvBuffer, "quit", 4) == 0)
				break;
			else if (!strncasecmp(rcvBuffer, "안녕하세요", strlen("안녕하세요")))
				 strcpy(buffer, "안녕하세요 만나서 반가워요");
			else if (!strncasecmp(rcvBuffer, "이름이 뭐야?", strlen("이름이 뭐야?")))
				strcpy(buffer, "내 이름은 정아봇이야 ");
			else if (!strncasecmp(rcvBuffer, "너 몇살이야?", strlen("너 몇살이야?")))
				strcpy(buffer, "나 22살이야");
			else if (!strncasecmp(rcvBuffer, "hi", strlen("hi")))
				 strcpy(buffer, "hi I'm Server");
			else 
				strcpy(buffer, "다시 말씀해주시겠어요 ?");

			write(c_socket, buffer, strlen(buffer)); //클라이언트에게 buffer의 내용을 전송함
	
		}
}


void sig_handler(int signo){
	int pid;
	int status;
	
	pid = wait(&status);
	printf("pid[%d] is terminated. status = %d\n",pid, status);
	numClient--;
	printf("현재 접속중인 클라이언트 수 >> %d\n",numClient);
}


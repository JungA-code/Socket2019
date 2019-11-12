#include <stdio.h>

main(){
	int a = 10;
	int b = 100;

	a = a+10;
	sleep(10);	
	//멀티 프로세스 프로그래밍 
	int pid = fork(); 
	// fork함수는 현재 구동중인 프로세스의 복제본을 생성 
	// 현재 프로세스 = 부모 프로세스
	// fork()에 의해 생성된 프로세스 = 자식 프로세스 
	//리턴 값(pid) = 0, if 자식 프로세스
	//리턴값 = 자식 프로세스의 pid값 if 부모 프로세스
	// fork() 실패 시 , -1 리턴

	
	if(pid > 0){ //부모 프로세스냐 
		printf("\tPARENT process\n");
		a += 10;
		printf("\ta = %d   b = %d\n",a,b);
		sleep(20);
	}else if(pid == 0){ //자식 프로세스냐 
		printf("\tCHILD process\n");
		b *= 10;
		printf("\ta = %d   b = %d\n",a,b);
		sleep(20);
	}else{ //실패냐
		printf("fork() FAILED\n");
	}
		
	return 0;
}

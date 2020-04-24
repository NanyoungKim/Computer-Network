  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])        //커멘드라인에서 포트번호를 받는다. (포트번호는 argv에 저장)
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_adr;

	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)    //서버에 커넥트
		error_handling("connect() error!");
	else
		puts("Connected...........");
	
	while(1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);    //콘솔창으로부터 (유저로부터)인풋 받음
		
		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))    //q 가 입력되면 연결 종료
			break;

		write(sock, message, strlen(message));  //서버에 메세지 보냄
		str_len=read(sock, message, BUF_SIZE-1);    //서버가 sending back한 메세지 읽음.
		message[str_len]=0; //문자열의 마지막에 NULL문자를 넣어서 문자열의 끝임을 지정해주는 중요한 라인임. 네트워크 혹은 버퍼로부터 메세지를 받을 때 쓰레기값이 포함되어 있는 경우 많다.
        //예를들어 message = "ab12311gwgk43tg5" 일때 ab만 받으려고 한다고 하자.
        //message[str_len] = 0 을 해주면 str_len은 ab 뒤를 가리키고 있으므로 message = "ab\012311gwgk43tg5" 이 되고
		printf("Message from server: %s", message); //여기서 프린트해주면 ab 만 출력된다. 
	}
	
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

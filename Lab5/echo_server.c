 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;   //tcp는 파일 디스크립터 2개 필요
	char message[BUF_SIZE];
	int str_len, i;
	
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   //서버 소켓 생성
	if(serv_sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY); //listening to Any client connection from any interface on our computer
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)  //server socekt 과 server address 를 바인딩한다.
		error_handling("bind() error");
	
	if(listen(serv_sock, 5)==-1)    //listening to client connections
		error_handling("listen() error");
	
	clnt_adr_sz=sizeof(clnt_adr);

	for(i=0; i<5; i++)  //accepting 5 clients in an iterative approach
	{
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // one client that we will have socket file descriptor here
		if(clnt_sock==-1)
			error_handling("accept() error");
		else
			printf("Connected client %d \n", i+1);
	
		while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)  //클라이언트가 보낸 메세지를 버퍼에서 읽아옴.
			write(clnt_sock, message, str_len); //읽어온 메세지를 다시 send back. 

		close(clnt_sock);
	}

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

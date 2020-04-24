#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char opmsg[BUF_SIZE];
	int result, opnd_cnt, i;
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
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected...........");

    
    
    
	fputs("Operand count: ", stdout);
	scanf("%d", &opnd_cnt);         //연산이 이루어지는 숫자 갯수
	opmsg[0]=(char)opnd_cnt;        //4를 입력하면 opmsg = [4] 가 된다.
	
	for(i=0; i<opnd_cnt; i++)
	{
		printf("Operand %d: ", i+1);
		scanf("%d", (int*)&opmsg[i*OPSZ+1]);        //1,2,3,4 입력하면 opsmg = [4,1,2,3,4] 가 된다.
	}
	fgetc(stdin);
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);       //+ 입력하면 opsmg = [4,1,2,3,4,'+'] 가 된다.
	write(sock, opmsg, opnd_cnt*OPSZ+2);        //서버에 보내고
	read(sock, &result, RLT_SIZE);              //결과를 받아옴
	
	printf("Operation result: %d \n", result);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

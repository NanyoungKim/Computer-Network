#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sd;
	FILE *fp;
	
	char buf[BUF_SIZE];
	int read_cnt;
	struct sockaddr_in serv_adr;
	if(argc!=3) {
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	fp=fopen("receive.dat", "wb");         //서버가 전송하는 파일 데이터를 담기위한 파일 생성.
	sd=socket(PF_INET, SOCK_STREAM, 0);   

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));         //서버의 주소와 connect
	
	while((read_cnt=read(sd, buf, BUF_SIZE ))!=0)       //서버가 보낸 데이터를 읽어서 버퍼에 저장하고 (0이 아닐 때 까지 읽는다 = 그만 보낼 때 까지 읽는다)
		fwrite((void*)buf, 1, read_cnt, fp);            //버퍼의 데이터를 fp가 가리키는 파일에 쓴다.
	
	puts("Received file data");
	write(sd, "Thank you", 10);         //서버에 보낸다.
	fclose(fp);
	close(sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

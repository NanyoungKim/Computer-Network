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
	int serv_sd, clnt_sd;
	FILE * fp;
	char buf[BUF_SIZE];
	int read_cnt;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc!=2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
    
	fp=fopen("file_server.c", "rb");   //파일을 open 한다. rb : reading as bytes
	serv_sd=socket(PF_INET, SOCK_STREAM, 0);   //basic tcp socket 오픈
	
    
    //주소 셋팅
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
    //tcp server socket 과 주소를 바인딩.
	bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    
    //리스닝
	listen(serv_sd, 5);
	
	clnt_adr_sz=sizeof(clnt_adr);
	clnt_sd=accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); //accept
	
    
    //여기가 중요한 부분. 위의 accept() 를 통해 연결된 클라이언트에게 파일 데이터를 전송한다.
	while(1)
	{
        //fread를 이용하여 fp가 가리키는 파일을 읽어온다.
        // buf : 얘가 가리키는 버퍼에 저장한다. , 1 : each byte, BUF_SIZE : 이 바이트 수 만큼 store 한다.
		read_cnt=fread((void*)buf, 1, BUF_SIZE, fp);
		if(read_cnt<BUF_SIZE)       //파일의 끝에 도달했을 때 read_cnt가 버퍼사이즈보다 작아야함.
		{
			write(clnt_sd, buf, read_cnt);  //write each window of bytes (each 30bytes) until the file finished.
			break;
		}
		write(clnt_sd, buf, BUF_SIZE);
	}
	
	shutdown(clnt_sd, SHUT_WR);    	//출력 스트림 닫음.
	read_cnt = read(clnt_sd, buf, BUF_SIZE);    // 여전히 수신은 가능.
    buf[read_cnt] = '\0';               //이 코드 실습 시간에 추가됨. 문자열의 끝을 나타내줌. 쓰레기값 출력ㅂ 방지.
    printf("Message from client: %s \n", buf);   //받은 메세지 출력
	
	fclose(fp);
	close(clnt_sd); close(serv_sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

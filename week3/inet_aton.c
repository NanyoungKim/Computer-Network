#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	char *addr="127.232.124.79";   //What is the IP address behind this value
	struct sockaddr_in addr_inet;
	
	if(!inet_aton(addr, &addr_inet.sin_addr))	//string형의 숫자를 network ordered address로
		error_handling("Conversion error");		//addr에서 각 바이트마다 최대 숫자 255인데 255넘어가거나 하면 에러 
	else
		printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);	// 0x4f7ce87f
	return 0;
}


//addr 을 255.255.255.255 하면 0xffffffff 출력
//addr 을 256.255.255.255 하면 Conversion error 출력
//addr 을 127.0.0.1 하면 0x100007f 출력. 가장 commonly하게 볼 수 있다. 내 자신에게 패킷 보낼 때 사용 

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
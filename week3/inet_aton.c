#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	char *addr="127.232.124.79";   //What is the IP address behind this value
	struct sockaddr_in addr_inet;
	
	if(!inet_aton(addr, &addr_inet.sin_addr))	//string���� ���ڸ� network ordered address��
		error_handling("Conversion error");		//addr���� �� ����Ʈ���� �ִ� ���� 255�ε� 255�Ѿ�ų� �ϸ� ���� 
	else
		printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);	// 0x4f7ce87f
	return 0;
}


//addr �� 255.255.255.255 �ϸ� 0xffffffff ���
//addr �� 256.255.255.255 �ϸ� Conversion error ���
//addr �� 127.0.0.1 �ϸ� 0x100007f ���. ���� commonly�ϰ� �� �� �ִ�. �� �ڽſ��� ��Ŷ ���� �� ��� 

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}